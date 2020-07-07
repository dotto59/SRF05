/*
SRF05 - HY-SRF05 and SR04 sensor library
by Dotto59 - dotto59alex@gmail.com
Arduino forum: docdoc

Versione 1.2.1 - 07/07/2020
*/
#ifndef SRF05_h
#define SRF05_h
#include "Arduino.h"

#define SRF_TIMEOUT 45000UL    // microseconds

class SRF05
{
public:
  // Constructors
  SRF05(int Trig, int Echo, int MaxDist, int Interval);
  SRF05(int Trig, int Echo, int MaxDist);
  SRF05(int Trig, int Echo);
  
  // Methods
  float Read();
  
  // Properties
  int ReadInterval;
  int TrigPin;
  int EchoPin;
  float Distance;
  float MaxDistance;
  boolean Unlock;

private:
  float prevDistance;
  long lastPing;

};

#endif
