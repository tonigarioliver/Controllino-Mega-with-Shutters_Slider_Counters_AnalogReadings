#include <Controllino.h>
#include "EEPROMFunctions.h"
#include "define.h"
#include "ServerFunctions.h"

////////////////////////
void setmovingavg(int numcounter, uint16_t sizeavg[], uint16_t readIndex[], uint16_t total[],
                  uint16_t movingaverage1[], uint16_t movingaverage2[], uint16_t movingaverage3[], uint16_t movingaverage4[], uint16_t movingaverage5[], uint16_t movingaverage6[])
{
    switch (numcounter)
    {
    case 0:
        sizeavg[numcounter] = EEPROMReadlong(longEEPROM * numcounter);
        readIndex[numcounter] = 0;
        total[numcounter] = 0;
        for (long i = 0; i < sizeavg[numcounter]; i++)
        {
            movingaverage1[i] = 0;
        }
        break;

    case 1:
        sizeavg[numcounter] = EEPROMReadlong(longEEPROM * numcounter);
        readIndex[numcounter] = 0;
        total[numcounter] = 0;
        for (long i = 0; i < sizeavg[numcounter]; i++)
        {
            movingaverage2[i] = 0;
        }
        break;

    case 2:
        sizeavg[numcounter] = EEPROMReadlong(longEEPROM * numcounter);
        readIndex[numcounter] = 0;
        total[numcounter] = 0;
        for (long i = 0; i < sizeavg[numcounter]; i++)
        {
            movingaverage3[i] = 0;
        }
        break;

    case 3:
        sizeavg[numcounter] = EEPROMReadlong(longEEPROM * numcounter);
        readIndex[numcounter] = 0;
        total[numcounter] = 0;
        for (long i = 0; i < sizeavg[numcounter]; i++)
        {
            movingaverage4[i] = 0;
        }
        break;

    case 4:
        sizeavg[numcounter] = EEPROMReadlong(longEEPROM * numcounter);
        readIndex[numcounter] = 0;
        total[numcounter] = 0;
        for (long i = 0; i < sizeavg[numcounter]; i++)
        {
            movingaverage5[i] = 0;
        }
        break;

    case 5:
        sizeavg[numcounter] = EEPROMReadlong(longEEPROM * numcounter);
        readIndex[numcounter] = 0;
        total[numcounter] = 0;
        for (long i = 0; i < sizeavg[numcounter]; i++)
        {
            movingaverage6[i] = 0;
        }
        break;

    default:
        break;
    }
}

void parseResponse(int numservers, String queries[], String server_output[], float prevAnalogReadings[], float nowAnalogReadings[], uint16_t readIndex[], uint16_t total[],
                   uint32_t &freqanalogread, unsigned long listpulses[], uint16_t listfreq[], uint16_t listfreqavg[], uint16_t sizeavg[],
                   uint16_t movingaverage1[], uint16_t movingaverage2[], uint16_t movingaverage3[], uint16_t movingaverage4[], uint16_t movingaverage5[], uint16_t movingaverage6[])
{
    for (int i = 0; i < numservers; i++)
    {
        char receivedChars[queries[i].length() + 1];
        strcpy(receivedChars, queries[i].c_str());
        char *command = strtok(receivedChars, ",");
        String action = String(command);
        command = strtok(NULL, ",");
        String parameter = String(command);
        command = strtok(NULL, ",");
        int num = String(command).toInt();
        command = strtok(NULL, ",");
        String feature = String(command);
        if (action == "get")
        {
            command = strtok(NULL, ",");
            if (parameter == "analog")
            {
                if (feature == "avg")
                {
                    server_output[i] = "<get,analog," + (String(num)) + ",avg," + String(prevAnalogReadings[num]) + ">" + "\n\r";
                }
                else if (feature == "now")
                {
                    server_output[i] = "<get,analog," + (String(num)) + ",now," + String(nowAnalogReadings[num]) + ">" + "\n\r";
                }
            }
            else if (parameter == "counter")
            {
                if (feature == "pulses")
                {
                    server_output[i] = "<get,counter," + (String(num)) + ",pulses," + String(listpulses[num]) + ">" + "\n\r";
                }
                else if (feature == "freq")
                {
                    server_output[i] = "<get,counter," + (String(num)) + ",freq," + String(listfreq[num]) + ">" + "\n\r";
                }
                else if (feature == "avg")
                {
                    server_output[i] = "<get,counter," + (String(num)) + ",avg," + String(listfreqavg[num]) + ">" + "\n\r";
                }
            }
        }
        else if (action == "set")
        {
            if (parameter == "analog")
            {
                command = strtok(NULL, ",");
                freqanalogread = String(command).toInt();
                server_output[i] = "<set,analog," + (String(num)) + ",avg," + String(freqanalogread) + ">" + "\n\r";
            }
            else if (parameter == "counter")
            {
                switch (num)
                {
                case 0:
                    command = strtok(NULL, ",");
                    sizeavg[num] = String(command).toInt();
                    EEPROMWritelong(longEEPROM * num, sizeavg[num]);
                    setmovingavg(num, sizeavg, readIndex, total, movingaverage1, movingaverage2, movingaverage3, movingaverage4, movingaverage5, movingaverage6);
                    break;

                case 1:
                    command = strtok(NULL, ",");
                    sizeavg[num] = String(command).toInt();
                    EEPROMWritelong(longEEPROM * num, sizeavg[num]);
                    setmovingavg(num, sizeavg, readIndex, total, movingaverage1, movingaverage2, movingaverage3, movingaverage4, movingaverage5, movingaverage6);
                    break;

                case 2:
                    command = strtok(NULL, ",");
                    sizeavg[num] = String(command).toInt();
                    EEPROMWritelong(longEEPROM * num, sizeavg[num]);
                    setmovingavg(num, sizeavg, readIndex, total, movingaverage1, movingaverage2, movingaverage3, movingaverage4, movingaverage5, movingaverage6);
                    break;

                case 3:
                    command = strtok(NULL, ",");
                    sizeavg[num] = String(command).toInt();
                    EEPROMWritelong(longEEPROM * num, sizeavg[num]);
                    setmovingavg(num, sizeavg, readIndex, total, movingaverage1, movingaverage2, movingaverage3, movingaverage4, movingaverage5, movingaverage6);
                    break;

                case 4:
                    command = strtok(NULL, ",");
                    sizeavg[num] = String(command).toInt();
                    EEPROMWritelong(longEEPROM * num, sizeavg[num]);
                    setmovingavg(num, sizeavg, readIndex, total, movingaverage1, movingaverage2, movingaverage3, movingaverage4, movingaverage5, movingaverage6);
                    break;

                case 5:
                    command = strtok(NULL, ",");
                    sizeavg[num] = String(command).toInt();
                    EEPROMWritelong(longEEPROM * num, sizeavg[num]);
                    setmovingavg(num, sizeavg, readIndex, total, movingaverage1, movingaverage2, movingaverage3, movingaverage4, movingaverage5, movingaverage6);
                    break;

                default:
                    break;
                }
                server_output[i] = "<set,counter," + (String(num)) + ",avg," + String(sizeavg[num]) + ">" + "\n\r";
            }
        }
    }
}