#include <Controllino.h>
#include "define.h"
#include "SliderFunctions.h"


void pinmodeFiltersliderSetup()
{
  pinMode(inMotion, INPUT_PULLUP);
  pinMode(backward, OUTPUT);
  pinMode(forward, OUTPUT);
  digitalWrite(backward, HIGH);
  digitalWrite(forward, HIGH);
};

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
};
