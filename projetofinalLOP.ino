
const int sensorEsquerdo = A1;  // Sensor esquerdo conectado ao pino analógico A1
const int sensorDireito = A0;  // Sensor direito conectado ao pino analógico A0


const int A1A = 6;   // Controle da direção do motor A (esquerdo), pino digital 6
const int A1B = 5;   // Controle da velocidade do motor A (esquerdo), pino digital 5
const int B1A = 9;  // Controle da direção do motor B (direito), pino digital 9
const int B1B = 10;   // Controle da velocidade do motor B (direito), pino digital 10

// Definir o valor limiar para detecção da linha
const int limiar = 400;  // Valor limite para determinar se o sensor detecta a linha
const int velocidade = 255;  // Velocidade do motor

void setup() {
  // Iniciar a comunicação serial para monitoramento
  Serial.begin(9600);

  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);
}

void loop() {
  // Ler os valores dos sensores de linha
  int valorEsquerdo = analogRead(sensorEsquerdo);  // Leitura do sensor esquerdo
  int valorDireito = analogRead(sensorDireito);    // Leitura do sensor direito

  // Enviar os valores dos sensores para o Serial Monitor
  Serial.print("E: ");  // Imprimir "E: " para indicar o sensor esquerdo
  Serial.print(valorEsquerdo);  // Imprimir o valor lido do sensor esquerdo
  Serial.print(" | D: ");  // Imprimir " | D: " para separar os valores
  Serial.println(valorDireito);  // Imprimir o valor lido do sensor direito e pular para a próxima linha
moverFrente();
  // Lógica para controle dos motores com base nos sensores
  if (valorEsquerdo < limiar && valorDireito < limiar) {
    // Se ambos os sensores detectam a linha (valores abaixo do limiar), o robô segue em frente
    moverFrente();
  } else if (valorEsquerdo > limiar) {
    // Se apenas o sensor esquerdo detecta a linha, o robô vira à esquerda
    virarEsquerda();
  } else if (valorDireito > limiar) {
    // Se apenas o sensor direito detecta a linha, o robô vira à direita
    virarDireita();
  } else {
    // Se nenhum sensor detecta a linha, o robô para
    parar();
  }

   delay(100);
  parar();
  // Pequena pausa para estabilizar a leitura dos sensores
  delay(500);
}

// Função para mover o robô para frente
void moverFrente() {
  motorA('R');
  motorB('L');
}

// Função para virar o robô à esquerda
void virarEsquerda() {
  motorA('L');
  motorB('L');
}

// Função para virar o robô à direita
void virarDireita() {
  motorA('R');
  motorB('R');
}

// Função para parar o robô
void parar() {
  motorA('O');
  motorB('O');
}

// Função para controlar o motor A (esquerdo)
void motorA(char d) {
  if(d == 'R'){
    analogWrite(A1A, LOW);
    analogWrite(A1B, velocidade);
  } else if(d == 'L'){
    analogWrite(A1A, velocidade);
    analogWrite(A1B, LOW);
  } else {
    analogWrite(A1A, LOW);
    analogWrite(A1B, LOW);
  }
}

// Função para controlar o motor B (direito)
void motorB(char d) {
  if(d == 'R'){
    analogWrite(B1A, LOW);
    analogWrite(B1B, velocidade);
  } else if(d == 'L'){
    analogWrite(B1A, velocidade);
    analogWrite(B1B, LOW);
  } else {
    analogWrite(B1A, LOW);
    analogWrite(B1B, LOW);
  }
}
