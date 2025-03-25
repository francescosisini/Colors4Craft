import pygame
import sys
import random

# Inizializzazione pygame
pygame.init()

# Costanti
LARGHEZZA, ALTEZZA = 800, 600
COLORI = {"R": (255, 0, 0), "G": (0, 255, 0), "B": (0, 0, 255), "W": (255, 255, 255)}
FONT = pygame.font.SysFont("arial", 24)
FPS = 60

# Sequenze
sequenza_p1 = ["W", "R", "G", "B", "W"]
sequenza_p2 = ["W", "G", "R", "B", "W"]

# Setup schermo
schermo = pygame.display.set_mode((LARGHEZZA, ALTEZZA))
pygame.display.set_caption("Gioco delle Sequenze")
clock = pygame.time.Clock()

# Funzione di transizione di stato
def transizione(stato, giocatore):
    if giocatore == 1:
        indice = sequenza_p1.index(stato)
        return sequenza_p1[(indice + 1) % len(sequenza_p1)]
    elif giocatore == 2:
        indice = sequenza_p2.index(stato)
        return sequenza_p2[(indice + 1) % len(sequenza_p2)]

# Funzione per generare nuova partita
def nuova_partita():
    global stato_corrente, sequenza_azioni, sequenza_colorata, input_giocatori
    global indice_input, gioco_terminato, messaggio
    stato_corrente = "W"
    sequenza_azioni = []
    sequenza_colorata = []
    input_giocatori = []
    indice_input = 0
    gioco_terminato = False
    messaggio = ""
    for _ in range(5):
        giocatore = random.choice([1, 2])
        sequenza_azioni.append(giocatore)
        stato_corrente = transizione(stato_corrente, giocatore)
        sequenza_colorata.append(stato_corrente)
    stato_corrente = "W"

# Disegna diagramma
def disegna_diagramma(sequenza, x, y):
    for i, stato in enumerate(sequenza):
        colore = COLORI[stato]
        pygame.draw.circle(schermo, colore, (x, y + i * 40), 15)
        if i < len(sequenza) - 1:
            pygame.draw.line(schermo, (0, 0, 0), (x, y + i * 40 + 15), (x, y + (i + 1) * 40 - 15), 2)

# Bottone restart
def disegna_bottone_restart():
    rettangolo = pygame.Rect(LARGHEZZA // 2 - 60, 550, 120, 30)
    pygame.draw.rect(schermo, (70, 70, 70), rettangolo)
    pygame.draw.rect(schermo, (255, 255, 255), rettangolo, 2)
    testo = FONT.render("Ricomincia", True, (255, 255, 255))
    schermo.blit(testo, (rettangolo.x + 10, rettangolo.y + 3))
    return rettangolo

# Inizializza partita
nuova_partita()

# Loop principale
while True:
    clock.tick(FPS)
    schermo.fill((30, 30, 30))

    # Eventi
    for evento in pygame.event.get():
        if evento.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        elif evento.type == pygame.MOUSEBUTTONDOWN:
            x, y = pygame.mouse.get_pos()

            if gioco_terminato:
                if bottone_restart.collidepoint(x, y):
                    nuova_partita()
            else:
                if x < 200:
                    giocatore = 1
                elif x > LARGHEZZA - 200:
                    giocatore = 2
                else:
                    giocatore = None

                if giocatore:
                    input_giocatori.append(giocatore)
                    stato_corrente = transizione(stato_corrente, giocatore)

                    if stato_corrente != sequenza_colorata[indice_input]:
                        gioco_terminato = True
                        messaggio = "Game Over! Sequenza errata."
                    else:
                        indice_input += 1
                        if indice_input == len(sequenza_colorata):
                            gioco_terminato = True
                            messaggio = "Bravo! Hai completato la sequenza."

    # Disegna quadrati centrali
    #for i, colore in enumerate(["R", "G", "B", "W"]):
     #   pygame.draw.rect(schermo, COLORI[colore], (300 + i * 50, 250, 40, 100))

    # Disegna stato corrente
    pygame.draw.circle(schermo, COLORI[stato_corrente], (LARGHEZZA // 2, 200), 30)
    label_stato = FONT.render(f"Stato: {stato_corrente}", True, (255, 255, 255))
    schermo.blit(label_stato, (LARGHEZZA // 2 - label_stato.get_width() // 2, 160))

    # Testi e diagrammi
    testo_p1 = FONT.render("Giocatore 1", True, (255, 255, 255))
    testo_p2 = FONT.render("Giocatore 2", True, (255, 255, 255))
    schermo.blit(testo_p1, (50, 50))
    schermo.blit(testo_p2, (LARGHEZZA - 200, 50))

    disegna_diagramma(sequenza_p1, 100, 100)
    disegna_diagramma(sequenza_p2, LARGHEZZA - 100, 100)

    # Mostra la sequenza da replicare
    testo_seq = FONT.render("Sequenza da replicare:", True, (255, 255, 0))
    schermo.blit(testo_seq, (LARGHEZZA // 2 - testo_seq.get_width() // 2, 400))
    for i, stato in enumerate(sequenza_colorata):
        colore = COLORI[stato]
        pygame.draw.circle(schermo, colore, (200 + i * 80, 450), 20)
        if i == indice_input:
            pygame.draw.circle(schermo, (255, 255, 0), (200 + i * 80, 450), 24, 3)

    # Messaggio finale e bottone restart
    if gioco_terminato:
        txt = FONT.render(messaggio, True, (255, 255, 0))
        schermo.blit(txt, (LARGHEZZA // 2 - txt.get_width() // 2, 500))
        bottone_restart = disegna_bottone_restart()

    pygame.display.flip()
