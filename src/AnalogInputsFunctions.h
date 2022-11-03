#include <Controllino.h>
#include "define.h"
/////////////////////////////////////////////////////////////////////////////
void readanaloginputs(float nowAnalogReadings[], uint32_t &numAnalogReadings, float AnalogReadings[]);
uint32_t smooth(int numcounter, uint16_t sizeavg[], uint16_t readIndex[], uint16_t total[], uint16_t listfreq[],
            uint16_t movingaverage1[], uint16_t movingaverage2[], uint16_t movingaverage3[], uint16_t movingaverage4[], uint16_t movingaverage5[], uint16_t movingaverage6[]);