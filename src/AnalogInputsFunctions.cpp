#include <Controllino.h>
#include "define.h"
#include "AnalogInputsFunctions.h"

/////////////////////////////////////////////////////////////////////////////
void readanaloginputs(AnalogReadings &_Analog)
{
    for (int i = 0; i < analogInputs; i++)
    {
        _Analog.nowAnalogReadings[i] = (analogRead(CONTROLLINO_A0 + i) * voltatgeSupply);
        _Analog.AnalogReadings[i] = _Analog.AnalogReadings[i] + _Analog.nowAnalogReadings[i];
    }
    _Analog.numAnalogReadings = _Analog.numAnalogReadings + 1;
}
void pinmodeAnalogSetup(){
  pinMode(CONTROLLINO_A0, INPUT);
  pinMode(CONTROLLINO_A1, INPUT);
  pinMode(CONTROLLINO_A2, INPUT);
  pinMode(CONTROLLINO_A3, INPUT);
  pinMode(CONTROLLINO_A4, INPUT);
  pinMode(CONTROLLINO_A5, INPUT);
  pinMode(CONTROLLINO_A6, INPUT);
  pinMode(CONTROLLINO_A7, INPUT);
}
