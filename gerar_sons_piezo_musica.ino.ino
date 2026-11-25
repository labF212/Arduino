const int pin = 3;

// 0 significa pausa (silencio) entre frases
const int notas[] = {
  // "Parabens a voce..."
  262, 262, 294, 262, 349, 330, 0,
  // "...nesta data querida..."
  262, 262, 294, 262, 392, 349, 0,
  // "...muitas felicidades..."
  262, 262, 523, 440, 349, 330, 294, 0,
  // "...muitos anos de vida!"
  466, 466, 440, 349, 392, 349
};

const char* nomesNotas[] = {
  "DO", "DO", "RE", "DO", "FA", "MI", "PAUSA",
  "DO", "DO", "RE", "DO", "SOL", "FA", "PAUSA",
  "DO", "DO", "DO5", "LA", "FA", "MI", "RE", "PAUSA",
  "SIb", "SIb", "LA", "FA", "SOL", "FA"
};

// Duracao total de cada passo em milissegundos
const int duracoes[] = {
  // "Parabens a voce..."
  180, 180, 360, 360, 360, 650, 220,
  // "...nesta data querida..."
  180, 180, 360, 360, 360, 650, 220,
  // "...muitas felicidades..."
  180, 180, 360, 360, 360, 360, 650, 220,
  // "...muitos anos de vida!"
  180, 180, 360, 360, 360, 750
};

const int totalNotas = sizeof(notas) / sizeof(notas[0]);

bool aTocar = false;
int indiceNota = 0;
unsigned long tempoInicioNota = 0;
bool notaIniciada = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Pronto! Envia 'A' para comecar ou 'P' para parar.");
}

void loop() {
  // 1. Ler comandos da porta serie
  if (Serial.available() > 0) {
    char comando = Serial.read();

    if (comando == 'A' || comando == 'a') {
      if (!aTocar) {
        aTocar = true;
        indiceNota = 0;
        notaIniciada = false;
        Serial.println("--- A iniciar musica ---");
      }
    } 
    else if (comando == 'P' || comando == 'p') {
      if (aTocar) {
        aTocar = false;
        noTone(pin);
        Serial.println("--- Musica parada ---");
      }
    }
  }

  // 2. Reproduzir a melodia sem bloquear o loop
  if (aTocar) {
    if (indiceNota < totalNotas) {
      if (!notaIniciada) {
        if (notas[indiceNota] > 0) {
          // Toca durante ~85% da duracao para separar notas repetidas
          int duracaoSom = (duracoes[indiceNota] * 85) / 100;
          tone(pin, notas[indiceNota], duracaoSom);
        } else {
          noTone(pin);
        }

        Serial.print("A tocar: ");
        Serial.println(nomesNotas[indiceNota]);

        tempoInicioNota = millis();
        notaIniciada = true;
      }

      if (millis() - tempoInicioNota >= (unsigned long)duracoes[indiceNota]) {
        indiceNota++;
        notaIniciada = false;
      }
    } else {
      aTocar = false;
      noTone(pin);
      Serial.println("--- Fim da musica ---");
    }
  }
}