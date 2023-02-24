#include <Controllino.h>
#include "define.h"
#include "SliderFunctions.h"

void pinmodeFiltersliderSetup(Slider &_filter)
{
  pinMode(TRIGGER_MOVE_PIN,INPUT);
  pinMode(inMotion, INPUT_PULLUP);
  pinMode(backward, OUTPUT);
  pinMode(forward, OUTPUT);
  digitalWrite(backward, HIGH);
  digitalWrite(forward, HIGH);
  _filter.currentPosition=digitalRead(TRIGGER_MOVE_PIN);
  _filter.oldPosition=digitalRead(TRIGGER_MOVE_PIN);
}

void ISRSlider(Slider &_filter){
  if (digitalRead(TRIGGER_MOVE_PIN) != _filter.oldPosition)
  {
    // Pin D2 triggered the ISR on a Falling pulse
    _filter.currentPosition =! _filter.oldPosition;
  }
}

void moveSliderFilter(Slider &_filter)
{
  if (_filter.nextposition == BACKWARDS)
  {
    digitalWrite(backward, LOW);
    digitalWrite(forward, HIGH);
  }
  else
  {
    digitalWrite(backward, HIGH);
    digitalWrite(forward, LOW);
  }
}

void timmingQuerySlider(Slider &_filter) // to check time is on high value each state
{
  if (millis() - _filter.timmerslider >= SLIDER_TIMEQUERY)
  {
    if (Serial2.available() > 0)
    {
      char incomingByte = ' ';
      String answer = "";
      while (incomingByte != '\n')
      {
        incomingByte = Serial2.read();
        answer.concat(incomingByte);
      }
      parseResponseSlider(_filter, answer);
      _filter.timmerslider = millis();
      if(_filter.motionstatus == 1){
        if((_filter.nextposition == 0 && _filter.currentposition ==0)||(_filter.nextposition == 1 && _filter.currentposition ==31)){
          _filter.error = false;
        }else{
          _filter.error =true;
        }
      }
    }
    Serial2.println("0gp");
  }
}

void parseResponseSlider(Slider &_filter, String &response)
{
  if (response == _filter.maxposition)
  {
    _filter.currentposition = 31;
  }
  else if (response == _filter.minposition)
  {
    _filter.currentposition = 0;
  }
}

