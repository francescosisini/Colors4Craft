# Color4Craft

**Color4Craft** è un gioco cooperativo a due giocatori che combina logica, matematica e creatività. Il gioco è realizzato su Arduino e si sviluppa in due fasi: inizialmente come automa a stati finiti, poi come automa a pila. L’obiettivo è produrre, attraverso la collaborazione dei giocatori, una sequenza specifica di stati che Arduino visualizzerà tramite colori e suoni.

## Panoramica del Gioco

In Color4Craft ogni giocatore ha a disposizione un pulsante. Il gioco si basa su una serie di transizioni tra stati, dove ogni stato è rappresentato da un colore:

- **Q = {W, R, G, B}**
  - **W**: White (Bianco)
  - **R**: Red (Rosso)
  - **G**: Green (Verde)
  - **B**: Blue (Blu)

Le azioni possibili sono:

- **player_1**: Azione eseguita dal primo giocatore
- **player_2**: Azione eseguita dal secondo giocatore
- **NULL**: Nessuna azione (stato inattivo)

## Tabella delle Transizioni

Le transizioni degli stati sono regolate dalla seguente tabella:

| Stato Corrente | player_1 | player_2 | NULL  |
|----------------|----------|----------|-------|
| **R**          | G        | B        |       |
| **G**          | B        | R        |       |
| **B**          | W        | W        |       |
| **W**          | R        | G        |       |

*Nota*: Le transizioni per l’azione NULL non sono definite, quindi in assenza di pressione sul pulsante lo stato rimane invariato.

## Fasi di Implementazione

1. **Automa a Stati Finiti (FSA):**  
   La versione iniziale del gioco utilizza un automa a stati finiti per gestire le transizioni in base alle azioni dei giocatori.
   
2. **Automa a Pila (PDA):**  
   In una fase successiva, il gioco verrà riprogettato come automa a pila, introducendo una componente di "memoria" per gestire sequenze di transizioni più complesse.

## Modalità di Gioco

1. **Preparazione:**
   - Collegare la scheda Arduino (inizialmente Arduino Uno, poi Arduino Nano su circuito millefori e infine con PCB personalizzato).
   - Assicurarsi che i pulsanti siano correttamente cablati.
   - Caricare il codice sul dispositivo Arduino.

2. **Svolgimento del Gioco:**
   - Ogni giocatore preme il proprio pulsante per navigare attraverso gli stati.
   - La collaborazione è essenziale: il successo dipende dalla capacità dei giocatori di seguire la corretta sequenza di transizioni.
   - Arduino visualizzerà lo stato corrente attraverso il colore (W, R, G, B) e produrrà suoni di feedback.

## Obiettivi Educativi

- **Comprendere gli Automata:**  
  Il gioco offre un approccio pratico per comprendere il funzionamento degli automi a stati finiti e a pila.
  
- **Sviluppare il Ragionamento Logico:**  
  I giocatori imparano a gestire sequenze e transizioni, sviluppando capacità di problem solving e di pensiero critico.

- **Stimolare la Creatività:**  
  L’integrazione di colori, suoni e interazione cooperativa rende il gioco un’esperienza coinvolgente e creativa.

## Requisiti Hardware

- **Arduino Uno/Arduino Nano:**  
  Utilizzati nelle fasi prototipo e definitiva.
- **Breadboard e Circuito Millefori:**  
  Per il montaggio iniziale e il passaggio al circuito definitivo.
- **PCB Personalizzato:**  
  In fase avanzata, per una soluzione hardware robusta.
- **Pulsanti:**  
  Uno per ciascun giocatore.
- **LED e Modulo Audio:**  
  Per la visualizzazione dei colori e la riproduzione dei suoni.

## Struttura del Repository


## Contributi

I contributi sono benvenuti! Se vuoi aiutare a migliorare Color4Craft, consulta il file [CONTRIBUTING.md](CONTRIBUTING.md) per le linee guida su come partecipare.

## Licenza

Questo progetto è distribuito sotto la licenza [MIT](LICENSE).

## Team
- **Francesco Sisini** - Docenza e direzione delle attività didattiche
- **Lisa Galvani** – Coordinamento delle attività e della collaborazione tra studenti e docenti.
- **Annalisa Pazzi** – Direzione artistica

---

Color4Craft unisce la logica degli automi alla creatività dei colori. Divertiti a esplorare il mondo degli automi e a collaborare per creare sequenze uniche e coinvolgenti!
