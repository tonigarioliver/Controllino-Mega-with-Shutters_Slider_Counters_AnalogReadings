
#include <Controllino.h>
#include "define.h"
#include "ShuttersFunctions.h"

void pinSetupShutters()
{
    for (int i = 0; i < NUM_SHUTTERS * 2; i++)
    {
        pinMode(FIRST_SHUTTER_OUT + i, OUTPUT);
        digitalWrite(FIRST_SHUTTER_OUT + i, LOW);
    }
    for (int i = 0; i < NUM_SHUTTERS; i++)
    {
        pinMode(FIRST_SHUTTER_IN + i, INPUT_PULLUP);
    }
    PCICR |= B00000100;  // ENBALBE Pin change interrupt PORT K
    PCMSK2 |= B00111111; // Set PCINT16-23 (A8-A15) to trigger an interrupt on state change.
}

void timmershutterState(Shutters &_shutters) // to check time is on high value each state
{
    if (millis() - _shutters.timmershutters >= SHUTTERS_DELAY_STATE)
    {
        for (int i = 0; i < NUM_SHUTTERS * 2; i++)
        {
            digitalWrite(FIRST_SHUTTER_OUT + i, LOW);
        }
        _shutters.timmershutters = millis();
    }
}

bool checkShuttersState(Shutters &_shutters)
{
    bool isnew = false;
    for (int i = 0; i < NUM_SHUTTERS; i++)
    {
        if (_shutters.AnalogState[i] != _shutters.AnalogOldState[i])
        {
            isnew = true;
            _shutters.newstates[i] = true;
            _shutters.AnalogOldState[i] = _shutters.AnalogState[i];
        }
    }
    return isnew;
}
void moveShutter(int _shutter, enum shutter_direction dir)
{
    digitalWrite(FIRST_SHUTTER_OUT + _shutter * 2, LOW);
    digitalWrite(FIRST_SHUTTER_OUT + _shutter * 2 + 1, LOW);

    switch (dir)
    {
    case BACKWARDS:
        digitalWrite(FIRST_SHUTTER_OUT + _shutter * 2, HIGH);
        break;
    case FORWARDS:
        digitalWrite(FIRST_SHUTTER_OUT + _shutter * 2 + 1, HIGH);
        break;
    default:
        Serial.println("Default");
        digitalWrite(FIRST_SHUTTER_OUT + _shutter * 2, LOW);
        digitalWrite(FIRST_SHUTTER_OUT + _shutter * 2 + 1, LOW);
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
            if (_shutters.AnalogOldState[i] == HIGH)
            {
                moveShutter(i, FORWARDS);
            }
            else
            {
                moveShutter(i, BACKWARDS);
            }
            //Serial.print("Value shutter first" + String(i) + ":" + String(digitalRead(FIRST_SHUTTER_OUT + i)));
            //Serial.println("Value shutter second" + String(i) + ":" + String(digitalRead(FIRST_SHUTTER_OUT + i + 1)));
        }
    }
}