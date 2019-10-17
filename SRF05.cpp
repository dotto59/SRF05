/*
SRF05 - Libreria per la gestione del sensore ultrasuoni SRF05

by Alex Palmese - docdoc@sertel.net
Arduino forum: docdoc

Release 1.2
*/
#include "Arduino.h"
#include "SRF05.h"

// ------------------------------------------------
// VARIABILI E INIZIALIZZAZIONI
// ------------------------------------------------
// Public
int ReadInterval = 0;
int TrigPin;
int EchoPin;
long Distance;	// 0=fuori portata
long MaxDistance;
boolean Unblock = false;
// Private
long prevDistance;
long lastPing;

// ------------------------------------------------
// METODI
// ------------------------------------------------
// *** Costruttore: inizializzazione parametri
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
    pinMode(TrigPin, OUTPUT);// set the trig pin to output (Send sound waves)
    pinMode(EchoPin, INPUT);// set the echo pin to input (recieve sound waves)
    
	MaxDistance = MaxDist;
    Distance = 0;
    PrevDistance = 0;
    lastPing = -1;
}

int SRF05::Read() {
    if ( lastPing == -1 || millis() - lastPing >= ReadInterval ) {
        lastPing = millis();
        //porta bassa l'uscita del trigger
        digitalWrite( TrigPin, LOW );
        delayMicroseconds(2); // Pull down
        //invia un impulso su trigger
        digitalWrite( TrigPin, HIGH );
        delayMicroseconds(10); // Ping width
        digitalWrite( EchoPin, LOW );  
        long pulseDuration = pulseIn( EchoPin, HIGH, SRF_TIMEOUT);
		if ( Unblock && pulseDuration == 0 ) {
			// Tenta di recuperare l'eventuale blocco dell'SR04
			pinMode(EchoPin, OUTPUT);
			digitalWrite(EchoPin, LOW);
			delay(50);
			pinMode(EchoPin, INPUT);
		}
        //Distance = 0.034F * pulseDuration / 2;
        Distance = 17L * pulseDuration / 100L
        if ( Distance > MaxDistance || ( Distance == 3 && PrevDistance == 0 ) )
            Distance = 0;
        PrevDistance = Distance;
        return Distance;
    } else {
        // Non è ancora il momento...
        return -1;
    }
}



