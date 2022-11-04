
void pinSetupShutters();

void timmershutterState(unsigned long &_timmershutters);

bool checkShuttersState(volatile bool _AnalogState[], volatile bool _AnalogOldState[], bool _newstates[]);

void moveShutter(int _shutter, enum shutter_direction dir);