#include <Controllino.h>
#include "define.h"
#include "CountersFunctions.h"
#include "EEPROMFunctions.h"

void countersAVG(Count &counters,AVGCount &avgcount){
  if (millis() - counters.timmerfreq > timefreq)
  {
    //Ethernet.maintain();
    //Serial.print("Average frequencies->");
    for (int i = 0; i < NUMCOUNTERS; i++)
    {
      counters.listfreq[i] = uint16_t((counters.listpulses[i] - counters.listpulses_before[i]));
      counters.listpulses_before[i] = counters.listpulses[i];
      avgcount.listfreqavg[i] = smoothCounterFrequencies(i, counters, avgcount);
      //Serial.print("Counter num " + String(i) + ": " + avgcount.listfreqavg[i] + " ");
    }
    //Serial.println();
    counters.timmerfreq = millis();
  }
}


uint32_t smoothCounterFrequencies(int numcounter, Count &counters,AVGCount &avgcount){
    uint32_t average;
    avgcount.total[numcounter] = avgcount.total[numcounter] - avgcount.movingaverages[avgcount.readIndex[numcounter]][numcounter]; //deleting the previous value if is 0 is start nothign to delete 
                                                                                                                        // the first time we fill the array:
    avgcount.movingaverages[avgcount.readIndex[numcounter]][numcounter] = counters.listfreq[numcounter];
    // add value to total:
    avgcount.total[numcounter] = avgcount.total[numcounter] + avgcount.movingaverages[avgcount.readIndex[numcounter]][numcounter];
    // handle index
    avgcount.readIndex[numcounter]++;
    if (avgcount.readIndex[numcounter] >= avgcount.sizeavg[numcounter]) //checking if my reading has reach my limit of moving average
    {
        avgcount.readIndex[numcounter] = 0;
    }
    average = avgcount.total[numcounter] / avgcount.sizeavg[numcounter]; //computes average from all the previous divide by the size

    return average;
}

void updatemovingavgArray(int numcounter,AVGCount &avgcount){
        avgcount.sizeavg[numcounter] = EEPROMReadlong(longEEPROM * numcounter);
        avgcount.readIndex[numcounter] = 0;
        avgcount.total[numcounter] = 0;
        for (int i = 0; i < avgcount.sizeavg[numcounter]; i++)
        {
            avgcount.movingaverages[i][numcounter] = 0;
        }
}
