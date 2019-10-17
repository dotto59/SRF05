// SENSORE
#include "SRF05.h"

// trigPin, echoPin, MaxDist, readInterval
SRF05 Sensor(6, 7, 200, 500);

void setup() {
    Serial.begin(9600);
	// Se si usa un SR04 e questo sembra restituire sempre 0, abilitare
	// la riga successiva:
//	Unblock = true;
}

void loop() {
    // Leggo la distanza
    if ( Sensor.Read() > -1 ) {
        // Ha fatto una nuova lettura!
        if ( Sensor.Distance == 0 ) {
            Serial.println("Fuori portata");
        } else {
            // -------------
            Serial.print("Dist: ");
            Serial.print(Sensor.Distance);
            Serial.println(" cm");
        }
    }
}

