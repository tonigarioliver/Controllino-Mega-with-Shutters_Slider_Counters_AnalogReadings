#include <Controllino.h>
#include "EEPROMFunctions.h"
#include "define.h"
#include "ServerFunctions.h"
#include "CountersFunctions.h"

////////////////////////
void parseResponse(int numservers, String queries[], String server_output[], AnalogReadings &_Analog, Count &counters, AVGCount &avgcount, Slider &_filter)
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
                    server_output[i] = "<get,analog," + (String(num)) + ",avg," + String(_Analog.prevAnalogReadings[num]) + ">" + "\n\r";
                }
                else if (feature == "now")
                {
                    server_output[i] = "<get,analog," + (String(num)) + ",now," + String(_Analog.nowAnalogReadings[num]) + ">" + "\n\r";
                }
            }
            else if (parameter == "counter")
            {
                if (feature == "pulses")
                {
                    server_output[i] = "<get,counter," + (String(num)) + ",pulses," + String(counters.listpulses[num]) + ">" + "\n\r";
                }
                else if (feature == "freq")
                {
                    server_output[i] = "<get,counter," + (String(num)) + ",freq," + String(counters.listfreq[num]) + ">" + "\n\r";
                }
                else if (feature == "avg")
                {
                    server_output[i] = "<get,counter," + (String(num)) + ",avg," + String(avgcount.listfreqavg[num]) + ">" + "\n\r";
                }
            }
            else if (parameter == "slider")
            {
                if(_filter.error == false){
                    if (feature == "status")
                    {
                        server_output[i] = "<get,slider," + (String(num)) + ",status," + String(_filter.motionstatus) + ">" + "\r\n";
                    }
                    else if (feature == "position")
                    {
                        server_output[i] = "<get,slider," + (String(num)) + ",position," + String(_filter.currentposition) + ">" + "\r\n";
                    }
                }else{
                    server_output[i] = "<Error in motion>\r\n";
                }
            }
        }
        else if (action == "set")
        {
            if (parameter == "analog")
            {
                command = strtok(NULL, ",");
                _Analog.freqanalogread = String(command).toInt();
                server_output[i] = "<set,analog," + (String(num)) + ",avg," + String(_Analog.freqanalogread) + ">" + "\n\r";
            }
            else if (parameter == "slider")
            {
                command = strtok(NULL, ",");
                _filter.nextposition = String(command).toInt();
                if(_filter.error == false){
                    server_output[i] = "<set,slider," + (String(num)) + ",position," + String(_filter.nextposition) + ">" + "\r\n";
                }else{
                    server_output[i] = "<Error in motion>\r\n";
                }
            }
            else if (parameter == "counter")
            {
                command = strtok(NULL, ",");
                avgcount.sizeavg[num] = String(command).toInt();
                EEPROMWritelong(longEEPROM * num, avgcount.sizeavg[num]);
                updatemovingavgArray(num, avgcount);
                server_output[i] = "<set,counter," + (String(num)) + ",avg," + String(avgcount.sizeavg[num]) + ">" + "\n\r";
            }
        }
    }
}