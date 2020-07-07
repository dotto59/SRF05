/*
SRF05 - HY-SRF05 and SR04 sensor library
by Dotto59 - dotto59alex@gmail.com
Arduino forum: docdoc

Versione 1.2.1 - 07/07/2020
*/
#include "Arduino.h"
#include "SRF05.h"

// ------------------------------------------------
// METHODS
// ------------------------------------------------
// *** Constructors
SRF05::SRF05(int Trig, int Echo) {
  SRF05(Trig,Echo,300,0);
}
SRF05::SRF05(int Trig, int Echo, int MaxDist) {
  SRF05(Trig,Echo,MaxDist,0);
}
SRF05::SRF05(int Trig, int Echo, int MaxDist, int Interval) {
  TrigPin = Trig;
  EchoPin = Echo;
  ReadInterval = Interval;
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
    
  MaxDistance = MaxDist;
  Distance = 0;
  prevDistance = 0;
  lastPing = -1;
  Unlock = false;
}

float SRF05::Read() {
  // Ping interval
  if ( lastPing == -1 || millis() - lastPing >= ReadInterval ) {
    lastPing = millis();
    // ping procedure
    digitalWrite( TrigPin, LOW );
    delayMicroseconds(2); // Pull down
    digitalWrite( TrigPin, HIGH );
    delayMicroseconds(10); // Ping width
    digitalWrite( EchoPin, LOW );  
    long pulseDuration = pulseIn( EchoPin, HIGH, SRF_TIMEOUT);

    if ( Unlock && pulseDuration == 0 ) {
      // SR04 unlock
      pinMode(EchoPin, OUTPUT);
      digitalWrite(EchoPin, LOW);
      delay(50);
      pinMode(EchoPin, INPUT);
    }
    
    Distance = 0.034F * pulseDuration / 2;
    
    // SRF05 "phantom" 3 cm distance override
    if ( Distance > MaxDistance || ( Distance == 3 && prevDistance == 0 ) )
      Distance = 0;

    prevDistance = Distance;
    return Distance;
  } else {
    // Not yet...
    return -1;
  }
}
