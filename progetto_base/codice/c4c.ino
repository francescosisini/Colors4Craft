/****************************************************
 * Esempio semplificato con debug su Serial:
 * - 2 pulsanti (pull-down) 
 * - 4 LED (Rosso, Verde, Blu, Bianco)
 * - Una "macchina a stati" che cambia colore a ogni
 *   pressione di un pulsante
 ****************************************************/

// Pin dei LED
const int RED_LED   = 9;
const int GREEN_LED = 10;
const int BLUE_LED  = 11;
const int WHITE_LED = 12;

// Pin dei pulsanti
const int BUTTON1 = 2;  // Giocatore 1
const int BUTTON2 = 3;  // Giocatore 2

// Stati possibili: R, G, B, W
char currentState = 'R';  // Partiamo da Rosso

void setup() {
  // Avvio comunicazione seriale per debug
  Serial.begin(9600);
  Serial.println("=== Avvio sistema ===");

  // Configura i LED come OUTPUT
  pinMode(RED_LED,   OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED,  OUTPUT);
  pinMode(WHITE_LED, OUTPUT);

  // Spegne tutti i LED all'avvio
  digitalWrite(RED_LED,   LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED,  LOW);
  digitalWrite(WHITE_LED, LOW);

  // Configura i pulsanti come INPUT (pull-down esterna)
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);

  // Imposta lo stato iniziale del LED (Rosso acceso)
  updateLED(currentState);

  Serial.println("Stato iniziale: R (Rosso)");
}

void loop() {
  // Legge lo stato dei due pulsanti
  int button1State = digitalRead(BUTTON1);
  int button2State = digitalRead(BUTTON2);

  // Se il pulsante 1 è premuto (HIGH)
  if (button1State == HIGH) {
    Serial.println("Pulsante 1 premuto: passo allo stato successivo (player 1).");
    nextState(1);
    delay(200);   // Evita letture multiple in rapida successione
  }

  // Se il pulsante 2 è premuto (HIGH)
  if (button2State == HIGH) {
    Serial.println("Pulsante 2 premuto: passo allo stato successivo (player 2).");
    nextState(2);
    delay(200);   // Evita letture multiple in rapida successione
  }
}

// Cambia stato in base al "giocatore" che ha premuto
void nextState(int player) {
  // Stampa lo stato attuale prima del cambio
  Serial.print("Stato corrente: ");
  Serial.println(currentState);

  // Logica di transizione
  if (currentState == 'R') {
    currentState = (player == 1) ? 'G' : 'B';
  } 
  else if (currentState == 'G') {
    currentState = (player == 1) ? 'B' : 'R';
  }
  else if (currentState == 'B') {
    // Per entrambi i giocatori, B -> W
    currentState = 'W';
  }
  else if (currentState == 'W') {
    currentState = (player == 1) ? 'R' : 'G';
  }

  // Stampiamo chi ha causato il cambiamento e il nuovo stato
  Serial.print(" -> Giocatore ");
  Serial.print(player);
  Serial.print(" cambia stato a: ");
  Serial.println(currentState);

  // Aggiorna i LED
  updateLED(currentState);
}

// Accende soltanto il LED corrispondente allo stato corrente
void updateLED(char state) {
  // Spegne tutti i LED
  digitalWrite(RED_LED,   LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED,  LOW);
  digitalWrite(WHITE_LED, LOW);

  // Accende il LED giusto
  switch (state) {
    case 'R': digitalWrite(RED_LED,   HIGH); break;
    case 'G': digitalWrite(GREEN_LED, HIGH); break;
    case 'B': digitalWrite(BLUE_LED,  HIGH); break;
    case 'W': digitalWrite(WHITE_LED, HIGH); break;
  }
}
