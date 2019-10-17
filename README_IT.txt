SRF05 - Libreria per la gestione del sensore ultrasuoni SRF05/SR04
by Alex Palmese - docdoc@sertel.net
Arduino forum: docdoc

Dopo aver installato la libreria, aprire l'esempio per mostrare l'uso:
---------------------------------------------
#include "SRF05.h"

// TrigPin, EchoPin, <MaxDistance>, <ReadInterval>
SRF05 Sensor(6, 7, 200, 500);

void setup() {
    Serial.begin(9600);
    // Se si usa un SR04 e questo sembra restituire sempre 
    // 0, abilitare la riga successiva:
    //Sensor.Unlock = true;
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
---------------------------------------------

Come si vede, basta creare l'oggetto SRF05 specificando i parametri di configurazione, nell'ordine:
  TrigPin: pin digitale collegato a Trig
  EchoPin: pin digitale collegato a Echo
  MaxDist: distanza massima di misurazione (cm); opzionale, default=300 (3mt) 
  ReadInterval: intervallo tra acquisizioni (millis); opzionale, default=0

I primi due non hanno bisogno di spiegazioni. 
Il terzo penso sia abbastanza chiaro, comunque specifica la distanza massima che vogliamo misurare, ossia si specifica il valore massimo per il quale il sensore fornisce risultati affidabili.
Per l'ultimo bisogna spiegare meglio. Generalmente il sensore si utilizza per oggetti in movimento, per i quali non è generalmente necessario effettuare misurazioni ad ogni ciclo di loop (anche per evitare di far perdere tempo alla CPU). Per semplificare questa gestione, ho implementato quindi un metodo per evitare misurazioni ad intervalli di tempo inferiori a "readInterval". Se vogliamo usare la libreria per leggere continuamente dal sensore, basta impostare a zero il parametro.

Passiamo quindi all'uso. 
Come vedete, ha un solo metodo, "Read()" il quale restituisce la distanza misurata, in centimetri. 
Se viene invocato prima di "readInterval" millisecondi, la Read() restituisce il valore "-1" che significa "non è ancora tempo di leggere la distanza, non mi rompere". 8) 
Se viene invocato oltre il tempo minimo, effettua la nuova lettura e restituisce la nuova distanza. 
Se il sensore non rileva ostacoli o l'ostacolo si trova ad una distanza maggiore di "MaxDist", il metodo restituisce zero.

Oltre al valore restituito dalla Read() sono disponibili varie proprietà pubbliche, ossia i parametri del costruttore più l'ultima distanza misurata:
  int TrigPin;
  int EchoPin;
  long MaxDistance;
  long ReadInterval;
  long Distance; // l'ultima lettura effettuata dalla Read()

Nella versione 1.1 della libreria, per i sensori SR04 che in alcuni casi sembrano "bloccarsi" quando non ricevono alcun echo dopo il timeout e restituiscono sempre zero anche quando un oggetto entra nel campo. Per attivare questa "patch" basta impostare "Unlock = true;" dopo l'inizializzazione, come mostrato nell'esempio all'interno della funzione "setup()".

