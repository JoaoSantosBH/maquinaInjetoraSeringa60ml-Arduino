//  MAQUINA INJETORA DE DIETA VIA SERINGA 60ML

// A IMPLEMENTAR
// SENSOR DE PRESSAO PARA DETECTAR ENTUPIMENTO
// 10-03-2019
// VERSAO 1.1.0


//IMPORTANDO BIBLIOTECA MOTOR PASSO
#include <AccelStepper.h>
// OLED
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send AC

const uint8_t logo[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0,
  0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0,
  0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xc0, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xe0, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xef, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x01, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x01, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x60, 0x80, 0x00, 0x60,
  0x07, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x00, 0x60,
  0x07, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x9e, 0x20, 0x00, 0x60,
  0x07, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x01, 0x11, 0x10, 0x00, 0x60,
  0x07, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x01, 0x11, 0x10, 0x00, 0x60,
  0x07, 0x08, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x01, 0x1e, 0x10, 0x00, 0x60,
  0x07, 0x1e, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x01, 0x12, 0x10, 0x00, 0x60,
  0x07, 0x3e, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x01, 0x13, 0x10, 0x00, 0x60,
  0x07, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x91, 0x20, 0x00, 0x60,
  0x07, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x60, 0x00, 0x60,
  0x07, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x60, 0x80, 0x00, 0x60,
  0x07, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x60,
  0x07, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x0f, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x0f, 0xff, 0xdf, 0xff, 0x00, 0x00, 0x00, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x0f, 0xfe, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x07, 0xe0, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x07, 0xe0, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x07, 0xe0, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x03, 0xc0, 0x07, 0x80, 0x00, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x01, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x06, 0xe3, 0x63, 0x7e, 0xf9, 0xf0, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x06, 0xe3, 0x63, 0x7e, 0xf9, 0xf0, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0xf3, 0x63, 0x18, 0xdd, 0x80, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0x1f, 0xe6, 0xfb, 0x63, 0x18, 0xdd, 0xf0, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0x1f, 0xf6, 0xdb, 0x63, 0x18, 0xf9, 0xf0, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0x1b, 0x36, 0xcf, 0x63, 0x18, 0xf1, 0x80, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xe0, 0x1b, 0x36, 0xcf, 0x77, 0x18, 0xf9, 0x80, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xe0, 0x1b, 0x36, 0xc7, 0x7e, 0x18, 0xdd, 0xf0, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0x1b, 0x36, 0xc3, 0x3e, 0x18, 0xcd, 0xf0, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0,
  0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0,
  0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
// OLED
//DECLARANDO OS COMPONENTES DA MAQUINA INJETORA
int botoes                    = A0;
int buzzer                    = 12;
int BLUE                      = 11;
int GREEN                     = 10;
int RED                       =  9;
// DEFINIDO PINO ENABLE MOTOR PASSO
int pino_enable = 5;
// DEFININDO OS PINOS STEP e DIR MOTOR PASSO
AccelStepper motorPasso(1, 4, 3 );

// B L U E T O O T H
char command;
String stringBluetooth;
// B L U E T O O T H

//SOBRANDO 13,8,7,6, 2

//DEFININDO QUANTIDADE GIROS DO MOTOR,
//COMO HÁ UM FIM DE CURSO IMPLEMENTOU_SE UM NUMERO MUITO GRANDE DE VOLTAS
long passo = 1000000;

//ARRAY DE CORES  PARA LED RGB
int preto     [3]  = { 0, 0, 0 };
int branco    [3]  = { 100, 100,  100 };
int vermelho  [3]  = { 100, 0, 0 };
int verde     [3]  = { 0, 100, 0 };
int azul      [3]  = { 0, 0, 100 };
int amarelo   [3]  = { 40, 95, 0 };
int dimbranco [3]  = { 30, 30, 30};

// SETANDO CORES INICIAIS LED RGB
int valorVermelho = preto[0];
int valororVerde = preto[1];
int valororAzul = preto[2];
// VARIAVEIS DE CORES
int anteVermelho = valorVermelho;
int anteVerde = valororVerde;
int anteAzul = valororAzul;

//VARIAVEIS QUE VAO DETECTAR O ESTADO DE CADA BOTAO DO BARRAMENTO
int estadoBotaoBarramento = 0;

//VARIAVEIS QUE DETECTAM ESTADOS DE FUNCIONAMENTO
int estaInjetando  = 0;
int estaAguardando = 1;
int estaRecolhendo = 0;
//VARIAVEIS QUE ISOLAM COMPONENTES DO BARRAMENTO
int  botI = 1;
int  botR = 0;
int  botP = 0;
int  fcI  = 0;
int  fcR  = 0;
boolean bluetooth = false;
//DETECTA TEMPO EM QUE BOTAO FOI PRESSIONADO
unsigned long changeTime;

//SETUP DOS COMPONENTES
void setup() {

  pinMode(botoes, INPUT);
  pinMode(BLUE, OUTPUT) ;
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pino_enable, OUTPUT);

  // CONFIGURTACOES INICIAIS MOTOR PASSO - INICIAR PARADO
  motorPasso.move(0);
  digitalWrite(pino_enable, HIGH);

  crossFade(dimbranco);
  //INICIA COMUNICACAO SERIAL
  Serial.begin(9600);
  Serial.print("Maquina inicializada\n\n");

  //OLED
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255, 255, 255);
  }

  //OLED
  verificarStatus();
  drawInicia();
  acenderLuzVerde();
  drawLogo();


}


void loop() {

  // B L U E T O O T H
  if (Serial.available() > 0) {
    stringBluetooth = "";
  }

  while (Serial.available() > 0) {
    command = ((byte)Serial.read());

    if (command == ':') {
      Serial.println("Parando");
      break;
    }

    else {
      stringBluetooth += command;
    }

    delay(1);
  }
  // B L U E T O O T H


  //LER ESTADO DOS COMPONENTES

  estadoBotaoBarramento   = analogRead(botoes);

  //CASO BOTAO VERDE INICIAR APERTADO
  if (estadoBotaoBarramento >= 130 && estadoBotaoBarramento < 150 ) {
    if (estaInjetando == 0 && estaAguardando == 1 && estaRecolhendo == 0
        && botI == 1 && botR == 0 && botP == 0 && fcI == 0 && fcR == 0 ) {
      iniciarInjecao();
    }
  }
  //CASO BOTAO VERMELHO PARAR APERTADO
  else    if (estadoBotaoBarramento >= 159 && estadoBotaoBarramento < 200) { //>=220 && estadoBotaoBarramento<240
    if (estaInjetando == 1 && estaAguardando == 0 && estaRecolhendo == 0) {
      pararMaquina();
    }
  }
  //CASO FIM DE CURSO RECOLHIMENTO COMPLETO
  else   if (estadoBotaoBarramento >= 200 &&  estadoBotaoBarramento < 300) { //estadoBotaoBarramento >=670
    if (estaInjetando == 0 && estaAguardando == 0 && estaRecolhendo == 1
        && botI == 0 && botR == 0 && botP == 0 && fcI == 0 && fcR == 1) {
      pararMotorPassoRecolhimento();
    }
  }
  //CASO FIM DE CURSO INJECAO COMPLETA
  else  if (estadoBotaoBarramento >= 301 && estadoBotaoBarramento < 350) {
    if (estaInjetando == 1 && estaAguardando == 0 && estaRecolhendo == 0
        && botI == 0 && botR == 0 && botP == 1 && fcI == 1 && fcR == 0) {
      pararMotorPassoInjecao();
    }
  }
  //CASO PRESSAO DA MAQUINA ATINJA ALTO NIVEL
  else  if (estadoBotaoBarramento >= 666) { //>=330 && estadoBotaoBarramento<350
    if (estaInjetando == 1 && estaAguardando == 0 && estaRecolhendo == 0) {
      pararMaquinaPressao();
    }
  }
  // B L U E T O O T H
  else if (stringBluetooth == "TO") {

    if (estaInjetando == 0 && estaAguardando == 1 && estaRecolhendo == 0
        && botI == 1 && botR == 0 && botP == 0 && fcI == 0 && fcR == 0 ) {
      Serial.println("SE DA BLUETOOTH INI INJE ");

      iniciarInjecao();
    }
  }

  else if (stringBluetooth == "TF") {
    //COLOCAR UM BOOLEANO AQUI
    if (estaInjetando == 1 && estaAguardando == 0 && estaRecolhendo == 0) {
      Serial.println("SE DA BLUETOOTH PARA INJE ");

      pararMaquina();
    }
  }
  // B L U E T O O T H
  motorPasso.run();





}


//F U N C O E S  D A   M A Q U I N A   I N J E T O R A


//INICIA A INJECAO
void iniciarInjecao() {
  estaInjetando  = 1;
  estaAguardando = 0;
  estaRecolhendo = 0;
  botI = 0;
  botR = 0;
  botP = 1;
  fcI  = 1;
  fcR  = 0;
  Serial.println("INICIANDO INJECAO");
  acenderLuzAzul();
  drawInjet();
  motorPasso.setMaxSpeed(150);
  motorPasso.setSpeed(150);
  motorPasso.setAcceleration(150);//Novo
  digitalWrite(pino_enable, LOW);
  stringBluetooth = "";
  motorPasso.move(-passo);
  verificarStatus();
}

//INICIAR O RECOLHIMENTO DO TRIlHO
void recolherCursor() {
  estaInjetando  = 0;
  estaAguardando = 0;
  estaRecolhendo = 1;
  botI = 0;
  botR = 0;
  botP = 0;
  fcI  = 0;
  fcR  = 1;
  acenderLuzBranca();
  drawRecolhe();
  Serial.println("RECOLHENDO CURSOR");
  digitalWrite(pino_enable, LOW);
  motorPasso.setMaxSpeed(2000);
  motorPasso.setSpeed(2000);
  motorPasso.setAcceleration(2000);//Novo
  motorPasso.move(passo);
  verificarStatus();
}

//PARAR INJECAO E RECOLHE MEMBOLO
void pararMotorPassoInjecao() {
  Serial.println("A INJECAO ACABOU");
  acenderLuzMagenta();
  drawAguard();
  estaInjetando  = 0;
  estaAguardando = 1;
  estaRecolhendo = 0;
  botI = 0;
  botR = 1;
  botP = 0;
  fcI  = 0;
  fcR  = 1;
  motorPasso.move(0);
  digitalWrite(pino_enable, HIGH);
  verificarStatus();
  recolherCursor();
}

//PARAR MAQUINA
void pararMaquina() {
  Serial.println(" MAQUINA PAUSADA");
  acenderLuzVermelha();
  drawAguard();
  estaInjetando  = 0;
  estaAguardando = 1;
  estaRecolhendo = 0;
  botI = 1;
  botR = 0;
  botP = 0;
  fcI  = 0;
  fcR  = 0;
  motorPasso.move(0);
  digitalWrite(pino_enable, HIGH);
  verificarStatus();
}

//PARAR MAQUINA CASO ENTUPIMENTO
void pararMaquinaPressao() {
  Serial.println(" MAQUINA PAUSADA");
  Serial.println("a pressão atingiu niveis alarmantes");
  acenderLuzVermelha();
  drawLogo();
  estaInjetando  = 0;
  estaAguardando = 1;
  estaRecolhendo = 0;
  botI = 1;
  botR = 0;
  botP = 0;
  fcI  = 0;
  fcR  = 0;
  motorPasso.move(0);
  digitalWrite(pino_enable, HIGH);
  tocarMarchaImperial();
  verificarStatus();
}

// QUANDO ATINGE O FDC - PARAR RECOLHIMENTO E EMITE ALERTA SONORO
void pararMotorPassoRecolhimento() {
  Serial.println("O RECOLHIMENTO CHEGOU AO FIM");
  acenderLuzBranca();
  drawInicia();
  tocarArpejoFeliz();
  motorPasso.move(0);
  digitalWrite(pino_enable, HIGH);
  delay(500);
  voltarUmPoquinho();
}

//FUNCAO QUE RECOLHE EMBOLO PARA NAO COLIDIR COM MOLA DO FIM DE CURSO
void voltarUmPoquinho() {
  Serial.println("INICIANDO RETORNO POSICAO ZERO");
  digitalWrite(pino_enable, LOW);
  motorPasso.move(-1000);
  estaInjetando  = 0;
  estaAguardando = 1;
  estaRecolhendo = 0;
  botI = 1;
  botR = 0;
  botP = 0;
  fcI  = 0;
  fcR  = 0;
  acenderLuzVerde();
    drawLogo();
  delay(5000);
  drawAguard();
  verificarStatus();

}

//VERIFICA STATUS CORRENTE DA MAQUINA - IMPRESSAO NA SERIAL PARA MONITORAMENTO DO FUNCIONAMENTO
//PODE SER SUPRIMIDA CASO DESEJADO
void verificarStatus() {
  if (estaRecolhendo == 1) {
    Serial.println("Maquina esta Recolhendo");
    String message = (String)  "EI=" + estaInjetando + " EA=" + estaAguardando + " ER=" + estaRecolhendo + " BI=" + botI + " bR=" + botR + " bP=" + botP + " FCI=" + fcI + " FCR=" + fcR;
    Serial.println(message );
  }
  if (estaInjetando == 1) {
    Serial.println("Maquina esta Injetando");
    String message = (String) "EI=" + estaInjetando + " EA=" + estaAguardando + " ER=" + estaRecolhendo + " BI=" + botI + " bR=" + botR + " bP=" + botP + " FCI=" + fcI + " FCR=" + fcR;
    Serial.println(message );
  }
  if (estaAguardando == 1) {
    Serial.println("Maquina esta Aguardando");
    String message = (String)  "EI=" + estaInjetando + " EA=" + estaAguardando + " ER=" + estaRecolhendo + " BI=" + botI + " bR=" + botR + " bP=" + botP + " FCI=" + fcI + " FCR=" + fcR;
    Serial.println(message );
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//realiza corsfade de luz
void crossFade(int cor[3]) {
  // Convert to 0-255
  int R = (cor[0] * 255) / 100;
  int G = (cor[1] * 255) / 100;
  int B = (cor[2] * 255) / 100;

  int passoSweepR = calcularPasso(anteVermelho, R);
  int passoSweepG = calcularPasso(anteVerde, G);
  int passoSweepB = calcularPasso(anteAzul, B);

  for (int i = 0; i <= 1020; i++) {
    valorVermelho = calcularValor(passoSweepR, valorVermelho, i);
    valororVerde = calcularValor(passoSweepG, valororVerde, i);
    valororAzul = calcularValor(passoSweepB, valororAzul, i);

    analogWrite(RED, valorVermelho);   // Write current valorues to LED pins
    analogWrite(GREEN, valororVerde);
    analogWrite(BLUE, valororAzul);

    delay(10);
  }
  anteVermelho = valorVermelho;
  anteVerde = valororVerde;
  anteAzul = valororAzul;
  delay(0);
}


int calcularPasso(int valororAnterior, int valororFinal) {
  int passoSweep = valororFinal - valororAnterior;
  if (passoSweep) {
    passoSweep = 1020 / passoSweep;
  }
  return passoSweep;
}

int calcularValor(int passoSweep, int valor, int i) {

  if ((passoSweep) && i % passoSweep == 0) {
    if (passoSweep > 0) {
      valor += 1;
    }
    else if (passoSweep < 0) {
      valor -= 1;
    }
  }

  if (valor > 255) {
    valor = 255;
  }
  else if (valor < 0) {
    valor = 0;
  }
  return valor;
}

void acenderLuzVerde() {
  for (int i = 0; i < 256; i++) {
    digitalWrite(GREEN, i);
    digitalWrite(RED, 0);
    digitalWrite(BLUE, 0);
  }
}
void acenderLuzVermelha() {
  for (int i = 0; i < 256; i++) {
    digitalWrite(GREEN, 0);
    digitalWrite(RED, 255);
    digitalWrite(BLUE, 0);
  }
}
void acenderLuzAzul() {
  for (int i = 0; i < 256; i++) {
    digitalWrite(GREEN, 0);
    digitalWrite(RED, 0);
    digitalWrite(BLUE, i);
  }
}

void acenderLuzMagenta() {
  for (int i = 0; i < 256; i++) {
    digitalWrite(GREEN, 0);
    digitalWrite(RED, i);
    digitalWrite(BLUE, i);
  }
}

void acenderLuzBranca() {
  for (int i = 0; i < 256; i++) {
    digitalWrite(GREEN, i);
    digitalWrite(RED, i);
    digitalWrite(BLUE, i);
  }
}

// A L E R T A s  S O N O R Os
// THE IMPERIAL MARCH - John Williams
void tocarMarchaImperial() {
  tone(buzzer, 1500);
  delay(500);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1500);
  delay(500);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1500);
  delay(500);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1200);
  delay(250);
  tone(buzzer, 1850);
  delay(250);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1500);
  delay(500);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1200);
  delay(250);
  tone(buzzer, 1850);
  delay(250);
  tone(buzzer, 1500);
  delay(500);
  noTone(buzzer);
  delay(500);
  ///////////////////
  tone(buzzer, 2220);
  delay(500);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 2220);
  delay(500);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 2220);
  delay(500);
  tone(buzzer, 2369);
  delay(250);
  tone(buzzer, 1850);
  delay(250);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1500);
  delay(500);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1200);
  delay(250);
  tone(buzzer, 1850);
  delay(250);
  tone(buzzer, 1500);
  delay(500);
  noTone(buzzer);
}
void tocarArpejoFeliz() {
  tone(buzzer, 1046);
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1318);
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1567);
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 2093);
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 2637);
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1046);
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1567);
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 2637);
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 2093);
  delay(250);
  noTone(buzzer);
  delay(50);
}

//OLED

void drawInicia()
{
  u8g.firstPage();
  do
  {
    u8g.setFont(u8g_font_8x13B);
    u8g.drawStr( 5, 15, "(31) 98847-0290");
    u8g.setFont(u8g_font_fub20);
    u8g.drawStr( 10, 57, "INIC..");
    //moldura
    u8g.drawRFrame(0, 18, 128, 46, 4);
  } while ( u8g.nextPage() );
}


void drawInjet()
{
  u8g.firstPage();
  do
  {
    u8g.setFont(u8g_font_8x13B);
    u8g.drawStr( 5, 15, "m i N U T R E");
    u8g.setFont(u8g_font_fub20);
    u8g.drawStr( 10, 57, "INJETA");
    //moldura
    u8g.drawRFrame(0, 18, 128, 46, 4);
  } while ( u8g.nextPage() );
}

void drawRecolhe()
{
  u8g.firstPage();
  do
  {
    u8g.setFont(u8g_font_8x13B);
    u8g.drawStr( 5, 15, "m i N U T R E");
    u8g.setFont(u8g_font_fub20);
    u8g.drawStr( 10, 57, "RECOLH");
    //moldura
    u8g.drawRFrame(0, 18, 128, 46, 4);
  } while ( u8g.nextPage() );
}

void drawAguard()
{
  u8g.firstPage();
  do
  {
    u8g.setFont(u8g_font_8x13B);
    u8g.drawStr( 5, 15, "m i N U T R E");
    u8g.setFont(u8g_font_fub20);
    u8g.drawStr( 10, 57, "AGUARD");
    //moldura
    u8g.drawRFrame(0, 18, 128, 46, 4);
  } while ( u8g.nextPage() );
}

void drawLogo()
{
  u8g.firstPage();
  do
  {
u8g.drawBitmapP( 0, 0, 16, 64, logo);

  } while ( u8g.nextPage() );
}
//ONLINE IMAGE TO C ARRAY https://littlevgl.com/image-to-c-array
//OLED
//SUPRIMIDOS
//CASO BOTAO AZUL RECOLHER APERTADO
//  else if (estadoBotaoBarramento >=160 && estadoBotaoBarramento<170){ >=160 && estadoBotaoBarramento<170
//      if(estaInjetando == 0 && estaAguardando ==1 && estaRecolhendo== 0
//      && botI==0 && botR==1 && botP==0 && fcI==0 && fcR==1){
//          recolherCursor();
//        }
//    }


//    T A B E L A   V E R D A D E   d o  S T A T U S da maquina
//
//  LEGENDA : Esta Injetando = EI  Esta Aguardando = EA   Esta Recolhendo = ER
//
// _______________________________  EI  | EA  | ER
// (00) ESTADO INICIAL DA MAQUINA |  0  |  1  |  0  |
//__________________________________________________|
// (01) INICIAR INJECAO           |  1  |  0  |  0  |
//__________________________________________________|
// (02) FIM CURSO ACABOU INJECAO  |  0  |  1  |  0  |
//__________________________________________________|
// (03) RECOLHER CURSOR           |  0  |  0  |  1  |
//__________________________________________________|
// (04) FIM CURSO RECOLHIMENTO    |  0  |  1  |  0  |
//__________________________________________________|
// (05) PARAR MAQUINA            |  0  |  1  |  0  |
//__________________________________________________|
