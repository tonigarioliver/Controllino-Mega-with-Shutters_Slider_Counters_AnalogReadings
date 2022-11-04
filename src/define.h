// Pulses define
#define NUMCOUNTERS 6
#define timefreq 1000
#define DUTYCYCLE 127 //(0-255)
#define longEEPROM 4
#define analogInputs 8
#define voltatgeSupply 0.0147

struct Count{
  volatile unsigned long listpulses[NUMCOUNTERS] = {0, 0, 0, 0, 0, 0};
  unsigned long listpulses_before[NUMCOUNTERS] = {0, 0, 0, 0, 0, 0};
  uint16_t listfreq[NUMCOUNTERS] = {0, 0, 0, 0, 0, 0};
  unsigned long timmerfreq = 0;
};

struct AVGCount{
    uint16_t sizeavg[NUMCOUNTERS] = {10, 10, 10, 10, 10, 10};
    uint16_t movingaverage1[60];
    uint16_t movingaverage2[60];
    uint16_t movingaverage3[60];
    uint16_t movingaverage4[60];
    uint16_t movingaverage5[60];
    uint16_t movingaverage6[60];

    uint16_t total[NUMCOUNTERS] = {0, 0, 0, 0, 0, 0};
    uint16_t readIndex[NUMCOUNTERS] = {0, 0, 0, 0, 0, 0};
    uint16_t listfreqavg[NUMCOUNTERS] = {0, 0, 0, 0, 0, 0};
};

struct AnalogReadings{
    unsigned long timeanalog = 0;
    uint32_t numAnalogReadings = 0;
    float AnalogReadings[analogInputs] = {0, 0, 0, 0, 0, 0, 0, 0};
    float prevAnalogReadings[analogInputs] = {0, 0, 0, 0, 0, 0, 0, 0};
    float nowAnalogReadings[analogInputs] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint16_t freqanalogread = 1000;
};