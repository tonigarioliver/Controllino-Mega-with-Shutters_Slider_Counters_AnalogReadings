#include <Controllino.h>

////////////////////////
void setmovingavg(int numcounter, uint16_t sizeavg[], uint16_t readIndex[], uint16_t total[],
                  uint16_t movingaverage1[], uint16_t movingaverage2[], uint16_t movingaverage3[], uint16_t movingaverage4[], uint16_t movingaverage5[], uint16_t movingaverage6[]);

void parseResponse(int numservers, String queries[], String server_output[], float prevAnalogReadings[], float nowAnalogReadings[], uint16_t readIndex[], uint16_t total[],
                   uint32_t &freqanalogread, unsigned long listpulses[], uint16_t listfreq[], uint16_t listfreqavg[], uint16_t sizeavg[],
                   uint16_t movingaverage1[], uint16_t movingaverage2[], uint16_t movingaverage3[], uint16_t movingaverage4[], uint16_t movingaverage5[], uint16_t movingaverage6[]);
