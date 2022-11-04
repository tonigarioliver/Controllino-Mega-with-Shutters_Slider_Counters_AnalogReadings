#include <Controllino.h>
#include "define.h"
#include "CountersFunctions.h"
#include "EEPROMFunctions.h"


uint32_t smooth(int numcounter, Count &counters,AVGCount &avgcount)
{ /* function smooth */
    ////Perform average on sensor readings
    uint32_t average;
    // subtract the last reading:
    switch (numcounter)
    {
    case 0:
        avgcount.total[numcounter] = avgcount.total[numcounter] - avgcount.movingaverage1[avgcount.readIndex[numcounter]]; //deleting the previous value if is 0 is start nothign to delete 
                                                                                                                          // the first time we fill the array:
        avgcount.movingaverage1[avgcount.readIndex[numcounter]] = counters.listfreq[numcounter];
        // add value to total:
        avgcount.total[numcounter] = avgcount.total[numcounter] + avgcount.movingaverage1[avgcount.readIndex[numcounter]];
        // handle index
        avgcount.readIndex[numcounter]++;
        if (avgcount.readIndex[numcounter] >= avgcount.sizeavg[numcounter]) //checking if my reading has reach my limit of moving average
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
    default:
        break;
    }
    // calculate the average:
    average = avgcount.total[numcounter] / avgcount.sizeavg[numcounter]; //computes average from all the previous divide by the size

    return average;
}

void setmovingavg(int numcounter,AVGCount &avgcount)
{
    switch (numcounter)
    {
    case 0:
        avgcount.sizeavg[numcounter] = EEPROMReadlong(longEEPROM * numcounter);
        avgcount.readIndex[numcounter] = 0;
        avgcount.total[numcounter] = 0;
        for (int i = 0; i < avgcount.sizeavg[numcounter]; i++)
        {
            avgcount.movingaverage1[i] = 0;
        }
        break;

    case 1:
        avgcount.sizeavg[numcounter] = EEPROMReadlong(longEEPROM * numcounter);
        avgcount.readIndex[numcounter] = 0;
        avgcount.total[numcounter] = 0;
        for (int i = 0; i < avgcount.sizeavg[numcounter]; i++)
        {
            avgcount.movingaverage2[i] = 0;
        }
        break;

    case 2:
        avgcount.sizeavg[numcounter] = EEPROMReadlong(longEEPROM * numcounter);
        avgcount.readIndex[numcounter] = 0;
        avgcount.total[numcounter] = 0;
        for (int i = 0; i < avgcount.sizeavg[numcounter]; i++)
        {
            avgcount.movingaverage3[i] = 0;
        }
        break;

    case 3:
        avgcount.sizeavg[numcounter] = EEPROMReadlong(longEEPROM * numcounter);
        avgcount.readIndex[numcounter] = 0;
        avgcount.total[numcounter] = 0;
        for (int i = 0; i < avgcount.sizeavg[numcounter]; i++)
        {
            avgcount.movingaverage4[i] = 0;
        }
        break;
    default:
        break;
    }
}