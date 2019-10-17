// SENSOR DEMO
#include "SRF05.h"

// trigPin, echoPin, MaxDist, readInterval
SRF05 Sensor(6, 7, 200, 500);

void setup() {
    Serial.begin(9600);
	// If using SR04 enable the following line:
	//Sensor.Unlock = true;
}

void loop() {
    // Distance read
    if ( Sensor.Read() > -1 ) {
        // New distance reading!
        if ( Sensor.Distance == 0 ) {
            Serial.println("Out of range");
        } else {
            // -------------
            Serial.print("Dist: ");
            Serial.print(Sensor.Distance);
            Serial.println(" cm");
        }
    }
}

