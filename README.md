# SRF05
<h2>Libreria Arduino per la gestione del sensore ad ultrasuoni</h2>
<p>by Dotto59 - dotto59alex@gmail.com<br />
Arduino forum: docdoc<br />
Versione: 1.2.1<br />
<i>For english, open "README_EN.txt" file!</i>
</p>
<p>La libreria consente di gestire più comodamente i sensori ad ultrasuoni come gli HY-SRF05 (consigliati) ma anche i meno performanti SRF04 (sconsigliati).</p>
<p>Come vedete, la libreria ha un solo metodo, "Read()" il quale restituisce la distanza misurata, in centimetri. 
Se viene invocato prima di "readInterval" millisecondi, la Read() restituisce il valore "-1" che significa "non è ancora tempo di leggere la distanza, non mi rompere".
Se viene invocato oltre il tempo minimo, effettua la nuova lettura e restituisce la nuova distanza. 
Se il sensore non rileva ostacoli o l'ostacolo si trova ad una distanza maggiore di "MaxDist", il metodo restituisce zero.

<p>Per ulteriori informazioni e per una descrizione di un semplice esempio, leggere il file "README.txt".</p>

<hr>
<h2>RELEASE HISTORY</h2>

<h3>Versione 1.2.1</h3>
Alcuni bug fix minori e correzione del metodo read().

<h3>Versione 1.2</h3>
Migliorato il calcolo della distanza per sfruttare le precisione massima della funzione pulseIn() di 10 microsecondi corrispondenti a circa 3 mm (grazie a Claudio_FF del forum Arduino!); Pubblicazione della libreria su GitHub.

<h3>Versione 1.1</h3>
Introdotta una estensione per gestire anche i sensori SR04 i quali in alcuni casi sembrano "bloccarsi" quando non ricevono alcun echo dopo il timeout, e restituiscono sempre zero anche quando un oggetto entra nel campo. Per attivare questa "patch" basta impostare "Unblock = true;" dopo l'inizializzazione, come mostrato nell'esempio all'interno della funzione "setup()".

<h3>Versione 1.0</h3>
Primo rilascio, la libreria funziona con tutti i sensori ad ultrasuoni come gli SRF05 (per i quali è stata creata la libreria) e gli SR04 (i quali soffrono però spesso di un problema hardware che li fa "bloccare").
