/*
SRF05 - Libreria per la gestione del sensore ultrasuoni SRF05

by Alex Palmese - docdoc@sertel.net
Arduino forum: docdoc

Release 1.2
*/
#ifndef SRF05_h
#define SRF05_h
#include "Arduino.h"

#define SRF_TIMEOUT 45000UL    // millisecondi

class SRF05
{
public:
  // Costruttore
  SRF05(int Trig, int Echo, int MaxDist, int Interval);
  SRF05(int Trig, int Echo, int MaxDist);
  SRF05(int Trig, int Echo);
  // Metodi
  int Read();
  // Proprietà pubbliche
  long Distance;
  int TrigPin;
  int EchoPin;
  long MaxDistance;
  long ReadInterval;
  long PrevDistance;
  boolean Unblock;

private:
  long lastPing;

};

#endif
