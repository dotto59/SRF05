#ifndef SRF05_h
#define SRF05_h
#include "Arduino.h"

#define SRF_TIMEOUT 45000UL    // milliseconds

class SRF05
{
public:
    // Costruttore
    SRF05(int Trig, int Echo, int MaxDist, int Interval);
    SRF05(int Trig, int Echo, int MaxDist);
    SRF05(int Trig, int Echo);
    // Metodi
    float Read();
    // Proprietà pubbliche
    float Distance;
    int TrigPin;
    int EchoPin;
	float MaxDistance;
    int ReadInterval;
    float PrevDistance;
	boolean Unlock;

private:
    long lastPing;

};

#endif
