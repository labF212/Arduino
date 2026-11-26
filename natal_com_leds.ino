const int pin = 3;
const int ledPin = 6;
const int BRILHO_PWM_75 = 3
100; // ~75% de 255
const int NUM_MUSICAS = 5;

struct PassoNota {
  int freq;
  int duracao;
  const char* nome;
};

// 1. Jingle Bells
const PassoNota musica1[] = {
  {330, 220, "MI"}, {330, 220, "MI"}, {330, 440, "MI"},
  {330, 220, "MI"}, {330, 220, "MI"}, {330, 440, "MI"},
  {330, 220, "MI"}, {392, 220, "SOL"}, {262, 220, "DO"}, {294, 220, "RE"}, {330, 650, "MI"},
  {0, 180, "PAUSA"},
  {349, 220, "FA"}, {349, 220, "FA"}, {349, 220, "FA"}, {349, 220, "FA"},
  {349, 220, "FA"}, {330, 220, "MI"}, {330, 220, "MI"}, {330, 110, "MI"}, {330, 110, "MI"},
  {392, 220, "SOL"}, {392, 220, "SOL"}, {349, 220, "FA"}, {294, 220, "RE"}, {262, 700, "DO"}
};

// 2. We Wish You a Merry Christmas
const PassoNota musica2[] = {
  {262, 240, "DO"},
  {349, 240, "FA"}, {349, 120, "FA"}, {392, 120, "SOL"}, {349, 120, "FA"}, {330, 120, "MI"},
  {294, 240, "RE"}, {294, 240, "RE"}, {294, 240, "RE"},
  {392, 240, "SOL"}, {392, 120, "SOL"}, {440, 120, "LA"}, {392, 120, "SOL"}, {349, 120, "FA"},
  {330, 240, "MI"}, {262, 240, "DO"}, {262, 240, "DO"},
  {440, 240, "LA"}, {440, 120, "LA"}, {466, 120, "SIb"}, {440, 120, "LA"}, {392, 120, "SOL"},
  {349, 240, "FA"}, {294, 240, "RE"}, {262, 120, "DO"}, {262, 120, "DO"},
  {294, 240, "RE"}, {392, 240, "SOL"}, {330, 240, "MI"}, {349, 650, "FA"}
};

// 3. Silent Night (Noite Feliz) - Estrofe alargada
const PassoNota musica3[] = {
  {392, 360, "SOL"}, {440, 180, "LA"}, {392, 360, "SOL"}, {330, 650, "MI"},
  {0, 150, "PAUSA"},
  {392, 360, "SOL"}, {440, 180, "LA"}, {392, 360, "SOL"}, {330, 650, "MI"},
  {0, 150, "PAUSA"},
  {587, 480, "RE5"}, {587, 240, "RE5"}, {494, 650, "SI"},
  {523, 480, "DO5"}, {523, 240, "DO5"}, {392, 650, "SOL"},
  {0, 160, "PAUSA"},
  {440, 480, "LA"}, {440, 240, "LA"}, {523, 360, "DO5"}, {494, 180, "SI"}, {440, 360, "LA"},
  {392, 360, "SOL"}, {440, 180, "LA"}, {392, 360, "SOL"}, {330, 650, "MI"},
  {0, 160, "PAUSA"},
  {440, 480, "LA"}, {440, 240, "LA"}, {523, 360, "DO5"}, {494, 180, "SI"}, {440, 360, "LA"},
  {392, 360, "SOL"}, {440, 180, "LA"}, {392, 360, "SOL"}, {330, 650, "MI"},
  {0, 160, "PAUSA"},
  {587, 480, "RE5"}, {587, 240, "RE5"}, {698, 360, "FA5"}, {587, 180, "RE5"}, {494, 360, "SI"},
  {523, 720, "DO5"}, {659, 650, "MI5"},
  {0, 160, "PAUSA"},
  {523, 240, "DO5"}, {392, 240, "SOL"}, {330, 240, "MI"},
  {392, 360, "SOL"}, {349, 180, "FA"}, {294, 650, "RE"},
  {262, 850, "DO"}
};

// 4. O Christmas Tree (O Meu Pinheirinho)
const PassoNota musica4[] = {
  {262, 260, "DO"},
  {349, 260, "FA"}, {349, 130, "FA"}, {349, 360, "FA"},
  {392, 260, "SOL"}, {440, 130, "LA"}, {440, 130, "LA"}, {440, 400, "LA"},
  {0, 140, "PAUSA"},
  {392, 220, "SOL"}, {440, 130, "LA"}, {349, 240, "FA"},
  {330, 240, "MI"}, {294, 240, "RE"}, {349, 650, "FA"}
};

// 5. Deck the Halls
const PassoNota musica5[] = {
  {392, 320, "SOL"}, {349, 160, "FA"}, {330, 220, "MI"}, {294, 220, "RE"},
  {262, 220, "DO"}, {294, 220, "RE"}, {330, 220, "MI"}, {262, 220, "DO"},
  {294, 160, "RE"}, {330, 160, "MI"}, {349, 160, "FA"}, {294, 160, "RE"},
  {330, 320, "MI"}, {294, 160, "RE"}, {262, 650, "DO"}
};

const PassoNota* musicas[NUM_MUSICAS] = {
  musica1, musica2, musica3, musica4, musica5
};

const int comprimentos[NUM_MUSICAS] = {
  sizeof(musica1) / sizeof(musica1[0]),
  sizeof(musica2) / sizeof(musica2[0]),
  sizeof(musica3) / sizeof(musica3[0]),
  sizeof(musica4) / sizeof(musica4[0]),
  sizeof(musica5) / sizeof(musica5[0])
};

const char* nomesMusicas[NUM_MUSICAS] = {
  "1 - Jingle Bells",
  "2 - We Wish You a Merry Christmas",
  "3 - Silent Night",
  "4 - O Christmas Tree",
  "5 - Deck the Halls"
};

bool aTocar = false;
bool modoSequencia = false;
int musicaAtual = 0;
int indiceNota = 0;
unsigned long tempoInicioNota = 0;
unsigned long duracaoSomAtual = 0;
bool notaIniciada = false;
bool ledLigado = false;

void apagarLed() {
  analogWrite(ledPin, 0);
  ledLigado = false;
}

void iniciarMusica(int indice, bool sequencia) {
  musicaAtual = indice;
  modoSequencia = sequencia;
  indiceNota = 0;
  notaIniciada = false;
  aTocar = true;
  noTone(pin);
  apagarLed();

  Serial.print("=== A tocar: ");
  Serial.print(nomesMusicas[musicaAtual]);
  if (modoSequencia) {
    Serial.print(" (sequencia ");
    Serial.print(musicaAtual + 1);
    Serial.print("/");
    Serial.print(NUM_MUSICAS);
    Serial.print(")");
  }
  Serial.println(" ===");
}

void pararTudo() {
  aTocar = false;
  modoSequencia = false;
  notaIniciada = false;
  noTone(pin);
  apagarLed();
  Serial.println("--- Reproducao parada ---");
}

void setup() {
  pinMode(ledPin, OUTPUT);
  apagarLed();

  Serial.begin(9600);
  randomSeed(analogRead(A0));

  Serial.println("Comandos:");
  Serial.println("  1..5 : Tocar musica de Natal 1 a 5");
  Serial.println("  6    : Tocar uma musica aleatoria");
  Serial.println("  7    : Tocar todas as 5 musicas em sequencia");
  Serial.println("  P    : Parar");
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();

    if (cmd >= '1' && cmd <= '5') {
      iniciarMusica(cmd - '1', false);
    } else if (cmd == '6') {
      int sorteio = random(0, NUM_MUSICAS);
      iniciarMusica(sorteio, false);
    } else if (cmd == '7') {
      iniciarMusica(0, true);
    } else if (cmd == 'P' || cmd == 'p') {
      pararTudo();
    }
  }

  if (aTocar) {
    int totalNotas = comprimentos[musicaAtual];
    const PassoNota* lista = musicas[musicaAtual];

    if (indiceNota < totalNotas) {
      if (!notaIniciada) {
        if (lista[indiceNota].freq > 0) {
          duracaoSomAtual = (unsigned long)((lista[indiceNota].duracao * 85) / 100);
          tone(pin, lista[indiceNota].freq, duracaoSomAtual);
          analogWrite(ledPin, BRILHO_PWM_75);
          ledLigado = true;
        } else {
          duracaoSomAtual = 0;
          noTone(pin);
          apagarLed();
        }

        Serial.print("Nota: ");
        Serial.println(lista[indiceNota].nome);

        tempoInicioNota = millis();
        notaIniciada = true;
      }

      if (ledLigado && (millis() - tempoInicioNota >= duracaoSomAtual)) {
        apagarLed();
      }

      if (millis() - tempoInicioNota >= (unsigned long)lista[indiceNota].duracao) {
        indiceNota++;
        notaIniciada = false;
      }
    } else {
      noTone(pin);
      apagarLed();
      if (modoSequencia && (musicaAtual + 1 < NUM_MUSICAS)) {
        iniciarMusica(musicaAtual + 1, true);
      } else {
        aTocar = false;
        modoSequencia = false;
        notaIniciada = false;
        Serial.println("--- Fim da reproducao ---");
      }
    }
  }
}