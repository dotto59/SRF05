/*
SRF05 - HY-SRF05 and SR04 sensor library

by Alex Palmese - docdoc@sertel.net
Arduino forum: docdoc

Release 1.1 - Unlock property added for SR04 "freezes" when
no echo received. When "Unlock=true;" the library executes
a "recovery" procedure to force Echo pin to LOW trying to
unlock the sensor.

Release 1.2 - Changed returned value from "int" to "float" for better precision

*/
#include "Arduino.h"
#include "SRF05.h"

// ------------------------------------------------
// VARIABILES
// ------------------------------------------------
// Public
int ReadInterval = 0;
int TrigPin;
int EchoPin;
float Distance;	// 0=out of range
float MaxDistance;
boolean Unlock = false;
// Private
float prevDistance;
long lastPing;

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
    PrevDistance = 0;
    lastPing = -1;
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
        if ( Distance > MaxDistance || ( Distance == 3 && PrevDistance == 0 ) )
            Distance = 0;
        PrevDistance = Distance;
        return Distance;
    } else {
        // Not yet...
        return -1;
    }
}



