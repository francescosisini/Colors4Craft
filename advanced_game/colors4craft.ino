/****************************************************
 * Esempio completo con gestione della sequenza, 
 * segnalazioni musicali tramite PWM e partenza da 
 * stato iniziale "bianco" (W):
 *
 * - 2 pulsanti per i giocatori (BUTTON1 e BUTTON2)
 * - 1 pulsante per (ri)avviare il gioco (BUTTON3)
 * - 4 LED (Rosso, Verde, Blu, Bianco)
 * - Buzzer collegato al digital pin 5
 * 
 * Funzionalità:
 * 1) Genera una sequenza casuale di input (BUTTON1 o BUTTON2) 
 *    e la trasforma in una sequenza di colori, partendo da 'W'.
 * 2) Prima di mostrare la sequenza, il sistema suona una musica di
 *    avviso (playSequenceAlertMelody()).
 * 3) La sequenza di colori viene mostrata, con ogni colore visualizzato
 *    per 3 secondi.
 * 4) Terminata la sequenza, il sistema suona una musica che segnala la
 *    prontezza al gioco (playReadyMelody()).
 * 5) I giocatori si alternano a premere il proprio pulsante per riprodurre
 *    la sequenza.
 * 6) Se un input non corrisponde, il sistema suona una musica di errore 
 *    (playErrorMelody()) e segnala la sconfitta.
 * 7) Se la sequenza viene riprodotta correttamente, il sistema suona 
 *    una musica di vittoria (playVictoryMelody()).
 * 8) Il gioco ricomincia premendo BUTTON3.
 ****************************************************/

// Pin dei LED
const int RED_LED   = 9;
const int GREEN_LED = 10;
const int BLUE_LED  = 11;
const int WHITE_LED = 12;

// Pin dei pulsanti
const int BUTTON1 = 2;  // Giocatore 1
const int BUTTON2 = 3;  // Giocatore 2
const int BUTTON3 = 4;  // Bottone per (ri)avviare il gioco

// Pin del buzzer
const int BUZZER = 5;

// Costante: lunghezza della sequenza da riprodurre
const int SEQUENCE_LENGTH = 5;

// Lo stato iniziale è sempre "bianco"
char initialState = 'W';

// Variabili per la gestione della sequenza
int generatedActions[SEQUENCE_LENGTH];      // 1 = BUTTON1, 2 = BUTTON2
char expectedSequence[SEQUENCE_LENGTH];       // Sequenza di colori attesa
int playerInputIndex = 0;

// Enum per gestire lo stato del gioco
enum GameState { WAIT_START, SHOW_SEQUENCE, WAIT_INPUT, GAME_OVER, GAME_WIN };
GameState gameState = WAIT_START;

// Funzione per generare la transizione dello stato
char getNextState(char state, int player) {
  if (state == 'R') {
    return (player == 1) ? 'G' : 'B';
  } 
  else if (state == 'G') {
    return (player == 1) ? 'B' : 'R';
  }
  else if (state == 'B') {
    // Per entrambi i giocatori, B -> W
    return 'W';
  }
  else if (state == 'W') {
    return (player == 1) ? 'R' : 'G';
  }
  return state;
}

// Funzione per aggiornare i LED in base allo stato
void updateLED(char state) {
  // Spegne tutti i LED
  digitalWrite(RED_LED,   LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED,  LOW);
  digitalWrite(WHITE_LED, LOW);

  // Accende il LED corrispondente, se lo stato è valido
  switch (state) {
    case 'R': digitalWrite(RED_LED,   HIGH); break;
    case 'G': digitalWrite(GREEN_LED, HIGH); break;
    case 'B': digitalWrite(BLUE_LED,  HIGH); break;
    case 'W': digitalWrite(WHITE_LED, HIGH); break;
    default: break;
  }
}

// Funzioni per modulare le "musicahette" usando PWM sul buzzer
void playSequenceAlertMelody() {
  tone(BUZZER, 1000, 200);
  delay(250);
  tone(BUZZER, 1200, 200);
  delay(250);
  noTone(BUZZER);
}

void playReadyMelody() {
  tone(BUZZER, 1500, 300);
  delay(350);
  tone(BUZZER, 1700, 300);
  delay(350);
  noTone(BUZZER);
}

void playErrorMelody() {
  tone(BUZZER, 500, 500);
  delay(550);
  noTone(BUZZER);
}

void playVictoryMelody() {
  tone(BUZZER, 2500, 500);
  delay(550);
  tone(BUZZER, 3000, 500);
  delay(550);
  noTone(BUZZER);
}

// Genera la sequenza casuale e calcola la sequenza di colori attesa
void generateSequence() {
  char currentState = initialState;
  for (int i = 0; i < SEQUENCE_LENGTH; i++) {
    // Genera casualmente 1 o 2
    int action = random(1, 3); // random(1,3) restituisce 1 o 2
    generatedActions[i] = action;
    // Calcola il nuovo stato in base all'azione
    currentState = getNextState(currentState, action);
    expectedSequence[i] = currentState;
  }
}

// Mostra la sequenza di colori (ogni colore per 3 secondi)
void showSequence() {
  Serial.println("Mostro la sequenza:");
  for (int i = 0; i < SEQUENCE_LENGTH; i++) {
    Serial.print("Colore ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(expectedSequence[i]);
    updateLED(expectedSequence[i]);
    delay(3000); // mostra ogni colore per 3 s
    // Spegni i LED tra una visualizzazione e l'altra
    updateLED(' ');
    delay(500);
  }
  // Dopo la sequenza, accende il LED dell'ultimo stato per conferma
  updateLED(expectedSequence[SEQUENCE_LENGTH - 1]);
}

// Inizializza un nuovo gioco: genera la sequenza e mostra i segnali
void startNewGame() {
  Serial.println("=== Inizio nuova partita ===");
  // Genera la sequenza casuale
  generateSequence();
  // Avvisa con una musica di alert che sta per mostrare la sequenza
  playSequenceAlertMelody();
  delay(200);
  // Stato: mostra la sequenza
  gameState = SHOW_SEQUENCE;
  // Mostra la sequenza
  showSequence();
  // Suono che indica la prontezza al gioco
  playReadyMelody();
  // Resetta l'indice di input
  playerInputIndex = 0;
  Serial.println("Sequenza completata. Inizia la riproduzione da parte dei giocatori.");
  gameState = WAIT_INPUT;
}

void setup() {
  // Avvio comunicazione seriale per debug
  Serial.begin(9600);
  Serial.println("=== Avvio sistema ===");

  // Configura i LED come OUTPUT
  pinMode(RED_LED,   OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED,  OUTPUT);
  pinMode(WHITE_LED, OUTPUT);

  // Configura il buzzer
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  // Spegne tutti i LED all'avvio
  updateLED(' ');

  // Configura i pulsanti come INPUT (assumendo pull-down esterni)
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);

  // Stato iniziale del LED (bianco)
  updateLED(initialState);
  Serial.println("Stato iniziale: W (Bianco)");

  // Inizialmente, attendi il comando di start (BUTTON3)
  Serial.println("Premere BUTTON3 per iniziare il gioco.");
}

void loop() {
  // Gestione della macchina a stati
  switch (gameState) {
    case WAIT_START:
      if (digitalRead(BUTTON3) == HIGH) {
        delay(200); // Debounce
        startNewGame();
      }
      break;

    case SHOW_SEQUENCE:
      // Durante la visualizzazione non si accettano input dai giocatori
      break;

    case WAIT_INPUT: {
      // Legge lo stato dei pulsanti dei giocatori
      int button1State = digitalRead(BUTTON1);
      int button2State = digitalRead(BUTTON2);

      if (button1State == HIGH) {
        Serial.println("Giocatore 1 ha premuto BUTTON1.");
        char newState = getNextState((playerInputIndex == 0 ? initialState : expectedSequence[playerInputIndex - 1]), 1);
        if (newState == expectedSequence[playerInputIndex]) {
          Serial.print("OK, colore corretto: ");
          Serial.println(newState);
          updateLED(newState);
          playerInputIndex++;
          delay(300); // Debounce
        } else {
          Serial.println("Colore errato! Giocatori hanno perso.");
          playErrorMelody();
          gameState = GAME_OVER;
        }
      }

      if (button2State == HIGH) {
        Serial.println("Giocatore 2 ha premuto BUTTON2.");
        char newState = getNextState((playerInputIndex == 0 ? initialState : expectedSequence[playerInputIndex - 1]), 2);
        if (newState == expectedSequence[playerInputIndex]) {
          Serial.print("OK, colore corretto: ");
          Serial.println(newState);
          updateLED(newState);
          playerInputIndex++;
          delay(300); // Debounce
        } else {
          Serial.println("Colore errato! Giocatori hanno perso.");
          playErrorMelody();
          gameState = GAME_OVER;
        }
      }
      // Se la sequenza è stata riprodotta correttamente
      if (playerInputIndex >= SEQUENCE_LENGTH) {
        Serial.println("Sequenza completata! Giocatori hanno vinto.");
        playVictoryMelody();
        gameState = GAME_WIN;
      }
      break;
    }

    case GAME_OVER:
      Serial.println("Premere BUTTON3 per riavviare la partita.");
      if (digitalRead(BUTTON3) == HIGH) {
        delay(200);
        startNewGame();
      }
      break;

    case GAME_WIN:
      Serial.println("Premere BUTTON3 per giocare ancora.");
      if (digitalRead(BUTTON3) == HIGH) {
        delay(200);
        startNewGame();
      }
      break;
  }
}
