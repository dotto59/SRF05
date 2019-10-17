# SRF05
<h2>Libreria Arduino per la gestione del sensore ad ultrasuoni</h2>
<p>by Alex Palmese - alex.palmese@gmail.com<br />
Arduino forum: docdoc<br />
Versione: 1.2<br />
</p>
<p>La libreria consente di gestire più comodamente i sensori ad ultrasuoni come gli HY-SRF05 (consigliati) ma anche i meno performanti SRF04 (sconsigliati).</p>
<p>Per utilizzarla, collegare il sensore correttamente (Vcc e GND, più 2 pin digitali uno per Trig l'altro per Echo), quindi nello sketch utilizzare la classe SRF05. Iniziamo da un piccolo sketch per mostrare l'uso:</p>
<p style="font-family: monospace; background-color: lightgray"><i>
#include "SRF05.h"<br />
// TrigPin, EchoPin, &lt;MaxDistance&gt;, &lt;ReadInterval&gt;<br />
SRF05 Sensor(6, 7, 200, 500);<br />
void setup() {<br />
&nbsp;&nbsp;Serial.begin(9600);<br />
&nbsp;&nbsp;// Se si usa un SR04 e questo sembra restituire sempre <br />
&nbsp;&nbsp;// 0, abilitare la riga successiva:<br />
&nbsp;&nbsp;//Unblock = true;<br />
}<br />
void loop() {<br />
&nbsp;&nbsp;// Leggo la distanza<br />
&nbsp;&nbsp;if ( Sensor.Read() &gt; -1 ) {<br />
&nbsp;&nbsp;&nbsp;&nbsp;// Ha fatto una nuova lettura!<br />
&nbsp;&nbsp;&nbsp;&nbsp;if ( Sensor.Distance == 0 ) {<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Serial.println("Fuori portata");<br />
&nbsp;&nbsp;&nbsp;&nbsp;} else {<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;// -------------<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Serial.print("Dist: ");<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Serial.print(Sensor.Distance);<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Serial.println(" cm");<br />
&nbsp;&nbsp;&nbsp;&nbsp;}<br />
&nbsp;&nbsp;}<br />
  }</i></p>
<p>Come si vede, basta creare l'oggetto SRF05 specificando i parametri di configurazione, nell'ordine:
  TrigPin: pin digitale collegato a Trig
  EchoPin: pin digitale collegato a Echo
  MaxDist: distanza massima di misurazione (cm); opzionale, default=300 (3mt) 
  ReadInterval: intervallo tra acquisizioni (millis); opzionale, default=0
</p>
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

<hr>
<h2>RELEASE HISTORY</h2>

<h3>Versione 1.2</h3>
Migliorato il calcolo della distanza per sfruttare le precisione massima della funzione pulseIn() di 10 microsecondi corrispondenti a circa 3 mm (grazie a Claudio_FF del forum Arduino!); Pubblicazione della libreria su GitHub.

<h3>Versione 1.1</h3>
Introdotta una estensione per gestire anche i sensori SR04 i quali in alcuni casi sembrano "bloccarsi" quando non ricevono alcun echo dopo il timeout, e restituiscono sempre zero anche quando un oggetto entra nel campo. Per attivare questa "patch" basta impostare "Unblock = true;" dopo l'inizializzazione, come mostrato nell'esempio all'interno della funzione "setup()".

<h3>Versione 1.0</h3>
Primo rilascio, la libreria funziona con tutti i sensori ad ultrasuoni come gli SRF05 (per i quali è stata creata la libreria) e gli SR04 (i quali soffrono però spesso di un problema hardware che li fa "bloccare").

