#include <Controllino.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include "define.h"
#include "EEPROMFunctions.h"
#include "AnalogInputsFunctions.h"
#include "ServerFunctions.h"
#include <EthernetServers.h>
#include "CountersFunctions.h"
#include "ShuttersFunctions.h"
#include "SliderFunctions.h"

////////////////Ethernet MAC for DHCP
uint8_t mac[] = {0xA8, 0x61, 0x0A, 0xAE, 0x7B, 0x79};
byte ip[] = {192, 168, 100, 27};
byte buffersize = 127;
String *query;
boolean *newData;
EthernetServer servers[] = {EthernetServer(80), EthernetServer(8080), EthernetServer(22)};
int numServers = sizeof(servers) / sizeof(servers[0]);
EthernetServers Servers(buffersize, numServers);
String *serveroutput;

///// AnalogReadings
AnalogReadings Analog;
////Struct for Pulse Counter
Count Counters;
/// Struct for Moving Average for Counters
AVGCount avgCounters;

// Struct shutters
Shutters shutters;
/// Struct slider
Slider SliderFilter;

/////InterruptionCounters
const byte count1 = CONTROLLINO_IN0;
const byte count2 = CONTROLLINO_IN1;
const byte count3 = CONTROLLINO_PIN_HEADER_SCL;
const byte count4 = CONTROLLINO_PIN_HEADER_SDA;
/**testing*/
const byte pulse1 = CONTROLLINO_D15;
////////////////////////////////////////////////////////////////

///////////ISRs COUNTERS
void counter1()
{
  Counters.listpulses[0]++;
}
void counter2()
{
  Counters.listpulses[1]++;
}
void counter3()
{
  Counters.listpulses[2]++;
}
void counter4()
{
  Counters.listpulses[3]++;
}
/////////////////////////////////////////
ISR(PCINT2_vect)
{
  for (int i = 0; i < NUM_SHUTTERS; i++)
  {
    if (digitalRead(CONTROLLINO_A8 + i) != shutters.AnalogState[i])
    {
      // Pin D2 triggered the ISR on a Falling pulse
      shutters.AnalogState[i] = !shutters.AnalogState[i];
    }
  }
}
/////////////////////////////////////////////////////////////////
void setpulses(int dutycycle)
{
  pinMode(pulse1, OUTPUT);
  analogWrite(pulse1, dutycycle);
  pinMode(CONTROLLINO_D16, OUTPUT);
  digitalWrite(CONTROLLINO_D16, HIGH);
}

////////////////////////////////////////////
void pinmodeCountersSetup()
{
  pinMode(count1, INPUT_PULLUP);
  pinMode(count2, INPUT_PULLUP);
  pinMode(count3, INPUT_PULLUP);
  pinMode(count4, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(count1), counter1, FALLING);
  attachInterrupt(digitalPinToInterrupt(count2), counter2, FALLING);
  attachInterrupt(digitalPinToInterrupt(count3), counter3, FALLING);
  attachInterrupt(digitalPinToInterrupt(count4), counter4, FALLING);
}

/////////////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(115200);
  delay(2000);
  pinmodeCountersSetup();
  pinmodeAnalogSetup();
  pinSetupShutters();
  pinmodeFiltersliderSetup();
  setpulses(DUTYCYCLE);
  Servers.startServers(servers, mac, ip);
  delay(2000);
  for (int i = 0; i < NUMCOUNTERS; i++)
  {
    setmovingavg(i, avgCounters);
  }
}
//////////////////////////////////////////////////////////////
void loop()
{
  SliderFilter.motionstatus = digitalRead(inMotion);

  query = Servers.servermsgreceive(servers);

  if (Servers.existnewMessage())
  {
    delete[] serveroutput;
    serveroutput = new String[numServers];
    parseResponse(numServers, query, serveroutput, Analog, Counters, avgCounters, SliderFilter);
    Servers.sendreply(servers, serveroutput);
    moveSliderFilter(SliderFilter);
  }

  readanaloginputs(Analog);

  if (millis() - Analog.timeanalog > Analog.freqanalogread)
  {
    Serial.print("Average Analogs->");
    for (int i = 0; i < analogInputs; i++)
    {
      Analog.prevAnalogReadings[i] = (Analog.AnalogReadings[i]) / Analog.numAnalogReadings;
      Serial.print("Analog num " + String(i) + ": " + Analog.prevAnalogReadings[i] + " ");
      Analog.AnalogReadings[i] = 0;
    }
    Serial.println();
    Analog.numAnalogReadings = 0;
    Analog.timeanalog = millis();
  }

  if (millis() - Counters.timmerfreq > timefreq)
  {
    Ethernet.maintain();
    Serial.print("Average frequencies->");
    for (int i = 0; i < NUMCOUNTERS; i++)
    {
      Counters.listfreq[i] = uint16_t((Counters.listpulses[i] - Counters.listpulses_before[i]));
      Counters.listpulses_before[i] = Counters.listpulses[i];
      avgCounters.listfreqavg[i] = smooth(i, Counters, avgCounters);
      Serial.print("Counter num " + String(i) + ": " + avgCounters.listfreqavg[i] + " ");
    }
    Serial.println();
    Counters.timmerfreq = millis();
  }

  timmershutterState(shutters);                         // to check high output state
  bool newupdateShutter = checkShuttersState(shutters); // new updates
  if (newupdateShutter)
  {
    for (int i = 0; i < NUM_SHUTTERS; i++)
    {
      if (shutters.newstates[i] == true)
      {
        shutters.newstates[i] = false;
        if (shutters.AnalogOldState[i] == HIGH)
        {
          moveShutter(i, FORWARDS);
        }
        else
        {
          moveShutter(i, BACKWARDS);
        }
        Serial.print("Value shutter first" + String(i) + ":" + String(digitalRead(CONTROLLINO_D0 + i)));
        Serial.println("Value shutter second" + String(i) + ":" + String(digitalRead(CONTROLLINO_D0 + i + 1)));
      }
    }
  }
  /// testing part///
  if (shutters.test != digitalRead(CONTROLLINO_A9))
  {
    shutters.test = !shutters.test;
  };
  if (millis() - shutters.timmer >= 5000)
  {
    digitalWrite(CONTROLLINO_D16, !shutters.test);
    shutters.timmer = millis();
  }
}
