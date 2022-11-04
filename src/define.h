// Pulses define
#define NUMCOUNTERS 4
#define timefreq 1000
#define DUTYCYCLE 127 //(0-255)
#define longEEPROM 4
#define analogInputs 8
#define voltatgeSupply 0.0147
//Slider defines
#define inMotion CONTROLLINO_D12
#define backward CONTROLLINO_D13
#define forward CONTROLLINO_D14
#define timedelay 4000
///Shutters define 
#define timmerdelay 5000
#define NUM_SHUTTERS 5
#define SHUTTERS_DELAY 1000 // time on each state of the shutter
enum shutter_direction
{
  BACKWARDS,
  FORWARDS
};

struct Count
{
  volatile unsigned long listpulses[NUMCOUNTERS] = {0, 0, 0, 0}; //current pulses
  unsigned long listpulses_before[NUMCOUNTERS] = {0, 0, 0, 0};   //old pulses
  uint16_t listfreq[NUMCOUNTERS] = {0, 0, 0, 0}; //dif between current and old pulses
  unsigned long timmerfreq = 0;
};

struct AVGCount
{
  uint16_t sizeavg[NUMCOUNTERS] = {10, 10, 10, 10};  //size of moving average
  uint16_t movingaverage1[60]; // arrays to store each frequenci
  uint16_t movingaverage2[60];
  uint16_t movingaverage3[60];
  uint16_t movingaverage4[60];
  uint16_t total[NUMCOUNTERS] = {0, 0, 0, 0};  //array to fill with the sum of all current moving average to be divided by sizeavg
  uint16_t readIndex[NUMCOUNTERS] = {0, 0, 0, 0}; //reading index old values
  uint16_t listfreqavg[NUMCOUNTERS] = {0, 0, 0, 0};  //freq average after smooth fucnton
};

struct AnalogReadings
{
  unsigned long timeanalog = 0;
  uint32_t numAnalogReadings = 0;
  float AnalogReadings[analogInputs] = {0, 0, 0, 0, 0, 0, 0, 0};
  float prevAnalogReadings[analogInputs] = {0, 0, 0, 0, 0, 0, 0, 0};
  float nowAnalogReadings[analogInputs] = {0, 0, 0, 0, 0, 0, 0, 0};
  uint16_t freqanalogread = 1000;
};

struct Shutters{
  volatile bool AnalogState[NUM_SHUTTERS] = {LOW, LOW, LOW, LOW, LOW};
  volatile bool AnalogOldState[NUM_SHUTTERS] = {LOW, LOW, LOW, LOW, LOW};
  bool newstates[NUM_SHUTTERS] = {false,false,false,false,false};
  int dir = 0;
  unsigned long timmer = 0;
  unsigned long timmershutters = 0;
  int test = LOW;
};
struct Slider
{
  int motionstatus =0;
  int nextposition = 0;
};
