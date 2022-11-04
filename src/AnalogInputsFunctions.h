#include <Controllino.h>
/////////////////////////////////////////////////////////////////////////////
void readanaloginputs(AnalogReadings &_Analog);
uint32_t smooth(int numcounter, Count &counters, AVGCount &avgcount);