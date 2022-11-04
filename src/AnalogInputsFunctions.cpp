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

uint32_t smooth(int numcounter, Count &counters,AVGCount &avgcount)
{ /* function smooth */
    ////Perform average on sensor readings
    uint32_t average;
    // subtract the last reading:
    switch (numcounter)
    {
    case 0:
        avgcount.total[numcounter] = avgcount.total[numcounter] - avgcount.movingaverage1[avgcount.readIndex[numcounter]];
        // read the sensor:
        avgcount.movingaverage1[avgcount.readIndex[numcounter]] = counters.listfreq[numcounter];
        // add value to total:
        avgcount.total[numcounter] = avgcount.total[numcounter] + avgcount.movingaverage1[avgcount.readIndex[numcounter]];
        // handle index
        avgcount.readIndex[numcounter]++;
        if (avgcount.readIndex[numcounter] >= avgcount.sizeavg[numcounter])
        {
            avgcount.readIndex[numcounter] = 0;
        }
        break;

    case 1:
        avgcount.total[numcounter] = avgcount.total[numcounter] - avgcount.movingaverage2[avgcount.readIndex[numcounter]];
        // read the sensor:
        avgcount.movingaverage2[avgcount.readIndex[numcounter]] = counters.listfreq[numcounter];
        // add value to total:
        avgcount.total[numcounter] = avgcount.total[numcounter] + avgcount.movingaverage2[avgcount.readIndex[numcounter]];
        // handle index
        avgcount.readIndex[numcounter]++;
        if (avgcount.readIndex[numcounter] >= avgcount.sizeavg[numcounter])
        {
            avgcount.readIndex[numcounter] = 0;
        }
        break;

    case 2:
        avgcount.total[numcounter] = avgcount.total[numcounter] - avgcount.movingaverage3[avgcount.readIndex[numcounter]];
        // read the sensor:
        avgcount.movingaverage3[avgcount.readIndex[numcounter]] = counters.listfreq[numcounter];
        // add value to total:
        avgcount.total[numcounter] = avgcount.total[numcounter] + avgcount.movingaverage3[avgcount.readIndex[numcounter]];
        // handle index
        avgcount.readIndex[numcounter]++;
        if (avgcount.readIndex[numcounter] >= avgcount.sizeavg[numcounter])
        {
            avgcount.readIndex[numcounter] = 0;
        }
        break;

    case 3:
        avgcount.total[numcounter] = avgcount.total[numcounter] - avgcount.movingaverage4[avgcount.readIndex[numcounter]];
        // read the sensor:
        avgcount.movingaverage4[avgcount.readIndex[numcounter]] = counters.listfreq[numcounter];
        // add value to total:
        avgcount.total[numcounter] = avgcount.total[numcounter] + avgcount.movingaverage4[avgcount.readIndex[numcounter]];
        // handle index
        avgcount.readIndex[numcounter]++;
        if (avgcount.readIndex[numcounter] >= avgcount.sizeavg[numcounter])
        {
            avgcount.readIndex[numcounter] = 0;
        }
        break;

    case 4:
        avgcount.total[numcounter] = avgcount.total[numcounter] - avgcount.movingaverage5[avgcount.readIndex[numcounter]];
        // read the sensor:
        avgcount.movingaverage5[avgcount.readIndex[numcounter]] = counters.listfreq[numcounter];
        // add value to total:
        avgcount.total[numcounter] = avgcount.total[numcounter] + avgcount.movingaverage5[avgcount.readIndex[numcounter]];
        // handle index
        avgcount.readIndex[numcounter]++;
        if (avgcount.readIndex[numcounter] >= avgcount.sizeavg[numcounter])
        {
            avgcount.readIndex[numcounter] = 0;
        }
        break;

    case 5:
        avgcount.total[numcounter] = avgcount.total[numcounter] - avgcount.movingaverage6[avgcount.readIndex[numcounter]];
        // read the sensor:
        avgcount.movingaverage6[avgcount.readIndex[numcounter]] = counters.listfreq[numcounter];
        // add value to total:
        avgcount.total[numcounter] = avgcount.total[numcounter] + avgcount.movingaverage6[avgcount.readIndex[numcounter]];
        // handle index
        avgcount.readIndex[numcounter]++;
        if (avgcount.readIndex[numcounter] >= avgcount.sizeavg[numcounter])
        {
            avgcount.readIndex[numcounter] = 0;
        }
        break;

    default:
        break;
    }
    // calculate the average:
    average = avgcount.total[numcounter] / avgcount.sizeavg[numcounter];

    return average;
}