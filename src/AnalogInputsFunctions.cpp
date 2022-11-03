#include <Controllino.h>
#include "define.h"
#include "AnalogInputsFunctions.h"

/////////////////////////////////////////////////////////////////////////////
void readanaloginputs(float nowAnalogReadings[], uint32_t &numAnalogReadings, float AnalogReadings[])
{
    for (int i = 0; i < analogInputs; i++)
    {
        nowAnalogReadings[i] = (analogRead(CONTROLLINO_A0 + i) * voltatgeSupply);
        AnalogReadings[i] = AnalogReadings[i] + nowAnalogReadings[i];
    }
    numAnalogReadings = numAnalogReadings + 1;
}

uint32_t smooth(int numcounter, uint16_t sizeavg[], uint16_t readIndex[], uint16_t total[], uint16_t listfreq[],
            uint16_t movingaverage1[], uint16_t movingaverage2[], uint16_t movingaverage3[], uint16_t movingaverage4[], uint16_t movingaverage5[], uint16_t movingaverage6[])
{ /* function smooth */
    ////Perform average on sensor readings
    uint32_t average;
    // subtract the last reading:
    switch (numcounter)
    {
    case 0:
        total[numcounter] = total[numcounter] - movingaverage1[readIndex[numcounter]];
        // read the sensor:
        movingaverage1[readIndex[numcounter]] = listfreq[numcounter];
        // add value to total:
        total[numcounter] = total[numcounter] + movingaverage1[readIndex[numcounter]];
        // handle index
        readIndex[numcounter]++;
        if (readIndex[numcounter] >= sizeavg[numcounter])
        {
            readIndex[numcounter] = 0;
        }
        break;

    case 1:
        total[numcounter] = total[numcounter] - movingaverage2[readIndex[numcounter]];
        // read the sensor:
        movingaverage2[readIndex[numcounter]] = listfreq[numcounter];
        // add value to total:
        total[numcounter] = total[numcounter] + movingaverage2[readIndex[numcounter]];
        // handle index
        readIndex[numcounter]++;
        if (readIndex[numcounter] >= sizeavg[numcounter])
        {
            readIndex[numcounter] = 0;
        }
        break;

    case 2:
        total[numcounter] = total[numcounter] - movingaverage3[readIndex[numcounter]];
        // read the sensor:
        movingaverage3[readIndex[numcounter]] = listfreq[numcounter];
        // add value to total:
        total[numcounter] = total[numcounter] + movingaverage3[readIndex[numcounter]];
        // handle index
        readIndex[numcounter]++;
        if (readIndex[numcounter] >= sizeavg[numcounter])
        {
            readIndex[numcounter] = 0;
        }
        break;

    case 3:
        total[numcounter] = total[numcounter] - movingaverage4[readIndex[numcounter]];
        // read the sensor:
        movingaverage4[readIndex[numcounter]] = listfreq[numcounter];
        // add value to total:
        total[numcounter] = total[numcounter] + movingaverage4[readIndex[numcounter]];
        // handle index
        readIndex[numcounter]++;
        if (readIndex[numcounter] >= sizeavg[numcounter])
        {
            readIndex[numcounter] = 0;
        }
        break;

    case 4:
        total[numcounter] = total[numcounter] - movingaverage5[readIndex[numcounter]];
        // read the sensor:
        movingaverage5[readIndex[numcounter]] = listfreq[numcounter];
        // add value to total:
        total[numcounter] = total[numcounter] + movingaverage5[readIndex[numcounter]];
        // handle index
        readIndex[numcounter]++;
        if (readIndex[numcounter] >= sizeavg[numcounter])
        {
            readIndex[numcounter] = 0;
        }
        break;

    case 5:
        total[numcounter] = total[numcounter] - movingaverage6[readIndex[numcounter]];
        // read the sensor:
        movingaverage6[readIndex[numcounter]] = listfreq[numcounter];
        // add value to total:
        total[numcounter] = total[numcounter] + movingaverage6[readIndex[numcounter]];
        // handle index
        readIndex[numcounter]++;
        if (readIndex[numcounter] >= sizeavg[numcounter])
        {
            readIndex[numcounter] = 0;
        }
        break;

    default:
        break;
    }
    // calculate the average:
    average = total[numcounter] / sizeavg[numcounter];

    return average;
}