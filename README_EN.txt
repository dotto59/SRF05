SRF05 - HY-SRF05 and SR04 sensors library
by Dotto59 - dotto59alex@gmail.com - Arduino forum: docdoc
Versione1.2.1 - 07/07/2020

After installing the library, open the example "SRF05_Test.ino"

As you can see, first of all you need to create an SRF05 object with all the following configuration parameters:
  TrigPin: digital pin for Trig
  EchoPin: digital pin for Echo
  MaxDist: max measuring distance (cm); optional, default=300 (3mt) 
  ReadInterval: interval between measures(millis); optional, default=0

ReadInterval makes it easy to manage reading intervals without a specific timer: usually we don't check the distance on every loop() call, so set you can ReadInterval to the desired milliseconds and the library will do the job. If you need to read continuously simpy set ReadInterval=0.

This way, the loop() calls only the "Read()" method: it returns measured distance in centimeters but if called before "ReadInterval" milliseconds after the last read, it returns "-1" meaning "it's not the time!". 8)
If called after ReadInterval milliseconds, it performs a new "ping" and returns the updated distance. If the sensor doesn't read obstacles within the range (no echo or echo after "MadDist" cm), the Read() method returns zero.

Apart from Read(), some public properties are available including constructor parameters and latest measured distance:
  int TrigPin;
  int EchoPin;
  long MaxDistance;
  long ReadInterval;
  long Distance; // Last Read()

Version 1.1 includes a workaround for "locking" SR04 sensors when no echo is received. To enable this feature simply set "Unlock=true;" inside "setup()", as shown in the example.

Hope you enjoy the library!

 - Alex
 