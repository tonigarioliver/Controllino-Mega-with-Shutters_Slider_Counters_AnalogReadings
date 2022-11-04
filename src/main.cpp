#include <Controllino.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include "define.h"
#include "EEPROMFunctions.h"
#include "AnalogInputsFunctions.h"
#include "ServerFunctions.h"
#include <EthernetServers.h>

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

/////InterruptionCounters
const byte count1 = CONTROLLINO_IN0;
const byte count2 = CONTROLLINO_IN1;
const byte count3 = CONTROLLINO_D0;
const byte count4 = CONTROLLINO_D1;
const byte count5 = CONTROLLINO_PIN_HEADER_SCL;
const byte count6 = CONTROLLINO_PIN_HEADER_SDA;

const byte pulse1 = CONTROLLINO_D2;
const byte pulse2 = CONTROLLINO_D3;
const byte pulse3 = CONTROLLINO_D4;
const byte pulse4 = CONTROLLINO_D5;
const byte pulse5 = CONTROLLINO_D6;
const byte pulse6 = CONTROLLINO_D7;


////Struct for Pulse Counter
Count Counters;

///Struct for Moving Average for Counters
AVGCount avgCounters;
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
void counter5()
{
  Counters.listpulses[4]++;
}
void counter6()
{
  Counters.listpulses[5]++;
}

/////////////////////////////////////////////////////////////////
void setpulses(int dutycycle)
{
  pinMode(pulse1, OUTPUT);
  pinMode(pulse2, OUTPUT);
  pinMode(pulse3, OUTPUT);
  pinMode(pulse4, OUTPUT);
  pinMode(pulse5, OUTPUT);
  pinMode(pulse6, OUTPUT);
  analogWrite(pulse1, dutycycle);
  analogWrite(pulse2, dutycycle);
  analogWrite(pulse3, dutycycle);
  analogWrite(pulse4, dutycycle);
  analogWrite(pulse5, dutycycle);
  analogWrite(pulse6, dutycycle);
}
////////////////////////////////////////////
void pinmodeSetup()
{
  pinMode(count1, INPUT_PULLUP);
  pinMode(count2, INPUT_PULLUP);
  pinMode(count3, INPUT_PULLUP);
  pinMode(count4, INPUT_PULLUP);
  pinMode(count5, INPUT_PULLUP);
  pinMode(count6, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(count1), counter1, FALLING);
  attachInterrupt(digitalPinToInterrupt(count2), counter2, FALLING);
  attachInterrupt(digitalPinToInterrupt(count3), counter3, FALLING);
  attachInterrupt(digitalPinToInterrupt(count4), counter4, FALLING);
  attachInterrupt(digitalPinToInterrupt(count5), counter5, FALLING);
  attachInterrupt(digitalPinToInterrupt(count6), counter6, FALLING);
  pinMode(CONTROLLINO_A0, INPUT);
  pinMode(CONTROLLINO_A1, INPUT);
  pinMode(CONTROLLINO_A2, INPUT);
  pinMode(CONTROLLINO_A3, INPUT);
  pinMode(CONTROLLINO_A4, INPUT);
  pinMode(CONTROLLINO_A5, INPUT);
  pinMode(CONTROLLINO_A6, INPUT);
  pinMode(CONTROLLINO_A7, INPUT);
  pinMode(CONTROLLINO_A8, INPUT);
  pinMode(CONTROLLINO_A9, INPUT);
}

/////////////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(115200);
  delay(2000);
  pinmodeSetup();
  setpulses(DUTYCYCLE);
  Servers.startServers(servers, mac, ip);
  delay(2000);
  for (int i = 0; i < NUMCOUNTERS; i++)
  {
    setmovingavg(i, avgCounters);
  }
}

void loop()
{
  query = Servers.servermsgreceive(servers);

  if (Servers.existnewMessage())
  {
    delete[] serveroutput;
    serveroutput = new String[numServers];
    parseResponse(numServers, query, serveroutput, Analog, Counters, avgCounters);
    Servers.sendreply(servers, serveroutput);
  }

  readanaloginputs(Analog);

  if (millis() - Analog.timeanalog > Analog.freqanalogread)
  {
    Analog.timeanalog = millis();
    for (int i = 0; i < analogInputs; i++)
    {
      Analog.prevAnalogReadings[i] = (Analog.AnalogReadings[i]) / Analog.numAnalogReadings;
      Serial.println(Analog.prevAnalogReadings[i]);
      Analog.AnalogReadings[i] = 0;
    }
    Analog.numAnalogReadings = 0;
  }

  if (millis() - Counters.timmerfreq > timefreq)
  {
    Counters.timmerfreq = millis();
    Ethernet.maintain();
    for (int i = 0; i < NUMCOUNTERS; i++)
    {
      Counters.listfreq[i] = uint16_t((Counters.listpulses[i] - Counters.listpulses_before[i]));
      Counters.listpulses_before[i] = Counters.listpulses[i];
      avgCounters.listfreqavg[i] = smooth(i, Counters, avgCounters);
      Serial.println(avgCounters.listfreqavg[i]);
    }
  }
}
