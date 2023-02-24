
void pinSetupShutters(Shutters &_shutters);

void timmershutterState(Shutters &_shutters);

bool checkShuttersState(Shutters &_shutters);

void moveShutter(int _shutter, enum shutter_direction dir);
void moveShutters(Shutters &_shutters);
void ISRShutters(Shutters &_shutters);