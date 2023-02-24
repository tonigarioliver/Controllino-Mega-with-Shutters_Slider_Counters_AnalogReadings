
#include <Controllino.h>
#include "define.h"
#include "ShuttersFunctions.h"

void pinSetupShutters(Shutters &_shutters)
{
    for (int i = 0; i < NUM_SHUTTERS * 2; i++)
    {
        pinMode(FIRST_SHUTTER_OUT + i, OUTPUT);
        digitalWrite(FIRST_SHUTTER_OUT + i, LOW);
    }
    for (int i = 0; i < NUM_SHUTTERS; i++)
    {
        pinMode(FIRST_SHUTTER_IN + i, INPUT);
        _shutters.AnalogState[i]=digitalRead(FIRST_SHUTTER_IN + i);
        _shutters.AnalogOldState[i]=_shutters.AnalogState[i];
    }
    PCICR |= B00000100;  // ENBALBE Pin change interrupt PORT K
    PCMSK2 |= B00111111; // Set PCINT16-23 (A8-A15) to trigger an interrupt on state change.
}

void timmershutterState(Shutters &_shutters) // to check time is on high value each state
{
    for (int i = 0; i < NUM_SHUTTERS; i++)
    {
        if (millis() - _shutters.timmershutters[i] >= SHUTTERS_DELAY_STATE)
        {
            if(digitalRead(FIRST_SHUTTER_OUT+(i* 2))==HIGH){
                Serial.println("Shutter off"+String(i));
                digitalWrite(FIRST_SHUTTER_OUT+(i*2), LOW);
            }
            if(digitalRead(FIRST_SHUTTER_OUT+(i* 2)+1)==HIGH){
                Serial.println("Shutter off"+String(i));
                digitalWrite(FIRST_SHUTTER_OUT+(i*2)+1, LOW);
            }
            _shutters.timmershutters[i] = millis();
        }
    }
}

bool checkShuttersState(Shutters &_shutters)
{
    bool isnew = false;
    for (int i = 0; i < NUM_SHUTTERS; i++)
    {
        if (_shutters.AnalogState[i] != _shutters.AnalogOldState[i])
        {
            Serial.println("Shutter-"+String(i));
            //Serial.println("Old-"+String(_shutters.AnalogOldState[i]));
            //Serial.println("New-"+String(_shutters.AnalogState[i]));
            isnew = true;
            _shutters.newstates[i] = true;
            _shutters.AnalogOldState[i] = _shutters.AnalogState[i];
        }
    }
    return isnew;
}
void moveShutter(int _shutter, enum shutter_direction dir)
{
    switch (dir)
    {
    case BACKWARDS:
        digitalWrite(FIRST_SHUTTER_OUT + (_shutter * 2), HIGH);
        digitalWrite(FIRST_SHUTTER_OUT + (_shutter * 2 + 1), LOW);
        break;
    case FORWARDS:
        digitalWrite(FIRST_SHUTTER_OUT + (_shutter * 2), LOW);
        digitalWrite(FIRST_SHUTTER_OUT + (_shutter * 2) + 1, HIGH);
        break;
    default:
        Serial.println("Default");
        break;
    }
}

void moveShutters(Shutters &_shutters)
{
    for (int i = 0; i < NUM_SHUTTERS; i++)
    {
        if (_shutters.newstates[i] == true)
        {
            _shutters.newstates[i] = false;
            if (_shutters.AnalogState[i] == HIGH)
            {
                moveShutter(i, FORWARDS);
                _shutters.timmershutters[i] = millis();
            }
            else
            {
                moveShutter(i, BACKWARDS);
                _shutters.timmershutters[i] = millis();
            }
            //Serial.print("Value shutter first" + String(i) + ":" + String(digitalRead(FIRST_SHUTTER_OUT + i)));
            //Serial.println("Value shutter second" + String(i) + ":" + String(digitalRead(FIRST_SHUTTER_OUT + i + 1)));
        }
    }
}
void ISRShutters(Shutters &_shutters){
  for (int i = 0; i < NUM_SHUTTERS; i++)
  {
    if (digitalRead(FIRST_SHUTTER_IN + i) != _shutters.AnalogState[i])
    {
      // Pin D2 triggered the ISR on a Falling pulse
       Serial.println("Shutter-"+String(i));
      _shutters.AnalogState[i] =! _shutters.AnalogState[i];
    }
  }
}