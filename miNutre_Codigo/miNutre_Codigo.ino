//  MAQUINA INJETORA DE DIETA VIA SERINGA 60ML

// A IMPLEMENTAR
// SENSOR DE PRESSAO PARA DETECTAR ENTUPIMENTO e prever possível estouro do sistema devido a pressão

// 10-03-2019
// VERSAO 1.1.0
// 15.03.2021

#include <AccelStepper.h>
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

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

#define PRESSURE_SENSOR           A1
#define BUTTONS                   A0
#define BUZZER                    12
#define BLUE                      11
#define REEN                      10
#define RED                        9
#define STEP_PIN_ENABLE            5
AccelStepper myStepMotor(1, 4, 3 );

char command;
String stringBluetooth;

String MACHINE_NAME = "m i N U T R E";
String RECALL = "RECALLn";
String WAIT   = "WAITING";
String INJECT = "INJECTn";
String START = "STARTIn";


long myStepRevolutions = 1000000;

//ARRAY DE CORES  PARA LED RGB
int preto     [3]  = { 0, 0, 0 };

int dimbranco [3]  = { 30, 30, 30};

// SETANDO CORES INICIAIS LED RGB
int redValue = preto[0];
int greenValue = preto[1];
int blueValue = preto[2];
// VARIAVEIS DE CORES
int nRed = redValue;
int nGreen = greenValue;
int nBlue = blueValue;

//VARIAVEIS QUE VAO DETECTAR O ESTADO DE CADA BOTAO DO BARRAMENTO
int buttonBusStatus = 0;

//VARIAVEIS QUE DETECTAM ESTADOS DE FUNCIONAMENTO
int isInjecting  = 0;
int isWaiting = 1;
int isRecalling = 0;
//VARIAVEIS QUE ISOLAM COMPONENTES DO BARRAMENTO
int  botI = 1;
int  botR = 0;
int  botP = 0;
int  fcI  = 0;
int  fcR  = 0;

void setup() {

  setupInOut();
  putMachineInReadyState();
  setupOled();
  printStatusOnSerial();
  drawInit();
  turnOnGreenLight();
  drawLogo();

}

void loop() {

  bluetoothCommandsListener();
  readComponentStatus();
  checkPressedButtons();
  checkBluetoothCommands();
  readInjectionPressure() ;
  myStepMotor.run();

}

//F U N C O E S  D A   M A Q U I N A   I N J E T O R A

void startInjection() {
  Serial.println("INICIANDO INJECAO");
  settingInjectionStatus();
  turnOnBlueLight();
  drawInjet();
  settingInjectionMotor();
  stringBluetooth = "";
  printStatusOnSerial();
}

//INICIAR O RECOLHIMENTO DO TRIlHO
void pickupRecall() {
  Serial.println("RECOLHENDO CURSOR");
  settingRecallStatus();
  turnOnWhiteLight();
  drawRecall();
  settingRecallMotor();
  printStatusOnSerial();
}

//PARAR INJECAO E RECOLHE MEMBOLO
void stopInjectionAndPickup() {
  Serial.println("A INJECAO ACABOU");
  turnOnVioletLight();
  drawWait();
  settingStopRecallStatus();
  settingWaitMotor();
  printStatusOnSerial();
  pickupRecall();
}

//PARAR MAQUINA
void stopMachine() {
  Serial.println(" MAQUINA PAUSADA");
  turnOnRedLight();
  drawWait();
  settingWaitStatus();
  settingWaitMotor();
  printStatusOnSerial();
}

//PARAR MAQUINA CASO ENTUPIMENTO
void pressurePanic() {
  Serial.println(" MAQUINA PAUSADA");
  Serial.println("a pressão atingiu niveis alarmantes");
  turnOnRedLight();
  drawLogo();
  settingWaitStatus();
  settingWaitMotor();
  playImperialMarch();
  printStatusOnSerial();
}

// QUANDO ATINGE O FDC - PARAR RECOLHIMENTO E EMITE ALERTA SONORO
void stopMotorAtPickup() {
  Serial.println("O RECOLHIMENTO CHEGOU AO FIM");
  turnOnWhiteLight();
  drawInit();
  playHappyMelody();
  myStepMotor.move(0);
  digitalWrite(STEP_PIN_ENABLE, HIGH);
  delay(500);
  backALitle();
}

//FUNCAO QUE RECOLHE EMBOLO PARA NAO COLIDIR COM MOLA DO FIM DE CURSO
void backALitle() {
  Serial.println("INICIANDO RETORNO POSICAO ZERO");
  turnOnGreenLight();
  drawLogo();
  settingWaitStatus();
  settingBackLittleMotor();
  delay(5000);
  drawWait();
  printStatusOnSerial();

}

//realiza corsfade de luz
void colorCrossFade(int cor[3]) {
  // Convert to 0-255
  int R = (cor[0] * 255) / 100;
  int G = (cor[1] * 255) / 100;
  int B = (cor[2] * 255) / 100;

  int sweepRed = calcColorSweep(nRed, R);
  int sweepGreen = calcColorSweep(nGreen, G);
  int sweepBlue = calcColorSweep(nBlue, B);

  for (int i = 0; i <= 1020; i++) {
    redValue = calculateValue(sweepRed, redValue, i);
    greenValue = calculateValue(sweepGreen, greenValue, i);
    blueValue = calculateValue(sweepBlue, blueValue, i);

    analogWrite(RED, redValue);   // Write current valorues to LED pins
    analogWrite(GREEN, greenValue);
    analogWrite(BLUE, blueValue);

    delay(10);
  }
  nRed = redValue;
  nGreen = greenValue;
  nBlue = blueValue;
  delay(0);
}

int calcColorSweep(int previousValue, int finalValue) {
  int sweep = finalValue - previousValue;
  if (sweep) {
    sweep = 1020 / sweep;
  }
  return sweep;
}

int calculateValue(int sweep, int valor, int i) {

  if ((sweep) && i % sweep == 0) {
    if (sweep > 0) {
      valor += 1;
    }
    else if (sweep < 0) {
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

void turnOnGreenLight() {
  digitalWrite(GREEN, 255);
  digitalWrite(RED, 0);
  digitalWrite(BLUE, 0);
}
void turnOnRedLight() {
  digitalWrite(GREEN, 0);
  digitalWrite(RED, 255);
  digitalWrite(BLUE, 0);
}
void turnOnBlueLight() {
  digitalWrite(GREEN, 0);
  digitalWrite(RED, 0);
  digitalWrite(BLUE, 255);
}

void turnOnVioletLight() {
  digitalWrite(GREEN, 0);
  digitalWrite(RED, 255);
  digitalWrite(BLUE, 255);
}

void turnOnWhiteLight() {
  digitalWrite(GREEN, 255);
  digitalWrite(RED, 255);
  digitalWrite(BLUE, 255);
}

// A L E R T A s  S O N O R Os
// THE IMPERIAL MARCH - John Williams
void playImperialMarch() {
  tone(BUZZER, 1500);
  delay(500);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 1500);
  delay(500);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 1500);
  delay(500);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 1200);
  delay(250);
  tone(BUZZER, 1850);
  delay(250);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 1500);
  delay(500);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 1200);
  delay(250);
  tone(BUZZER, 1850);
  delay(250);
  tone(BUZZER, 1500);
  delay(500);
  noTone(BUZZER);
  delay(500);
  ///////////////////
  tone(BUZZER, 2220);
  delay(500);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 2220);
  delay(500);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 2220);
  delay(500);
  tone(BUZZER, 2369);
  delay(250);
  tone(BUZZER, 1850);
  delay(250);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 1500);
  delay(500);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 1200);
  delay(250);
  tone(BUZZER, 1850);
  delay(250);
  tone(BUZZER, 1500);
  delay(500);
  noTone(BUZZER);
}

void playHappyMelody() {
  tone(BUZZER, 1046);
  delay(125);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 1318);
  delay(125);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 1567);
  delay(125);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 2093);
  delay(125);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 2637);
  delay(125);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 1046);
  delay(125);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 1567);
  delay(125);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 2637);
  delay(125);
  noTone(BUZZER);
  delay(50);
  tone(BUZZER, 2093);
  delay(250);
  noTone(BUZZER);
  delay(50);
}

//OLED

void drawInit() {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_8x13B);
    u8g.drawStr( 5, 15, "(31)98847-0290");
    u8g.setFont(u8g_font_fub20);
    u8g.drawStr( 10, 57, START.c_str());
    //frame
    u8g.drawRFrame(0, 18, 128, 46, 4);
  } while ( u8g.nextPage() );
}


void drawInjet() {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_8x13B);
    u8g.drawStr( 5, 15, MACHINE_NAME.c_str());
    u8g.setFont(u8g_font_fub20);
    u8g.drawStr( 10, 57, INJECT.c_str());
    //frame
    u8g.drawRFrame(0, 18, 128, 46, 4);
  } while ( u8g.nextPage() );
}

void drawRecall() {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_8x13B);
    u8g.drawStr( 5, 15, MACHINE_NAME.c_str());
    u8g.setFont(u8g_font_fub20);
    u8g.drawStr( 10, 57, RECALL.c_str());
    //frame
    u8g.drawRFrame(0, 18, 128, 46, 4);
  } while ( u8g.nextPage() );
}

void drawWait() {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_8x13B);
    u8g.drawStr( 5, 15, MACHINE_NAME.c_str());
    u8g.setFont(u8g_font_fub20);
    u8g.drawStr( 10, 57, WAIT.c_str());
    //frame
    u8g.drawRFrame(0, 18, 128, 46, 4);
  } while ( u8g.nextPage() );
}

void drawLogo() {
  u8g.firstPage();
  do {
    u8g.drawBitmapP( 0, 0, 16, 64, logo);
  } while ( u8g.nextPage() );
}

void bluetoothCommandsListener() {

  if (Serial.available() > 0) {
    stringBluetooth = "";
  }

  while (Serial.available() > 0) {
    command = ((byte)Serial.read());

    if (command == ':') {
      Serial.println("Parando");
      break;
    } else {
      stringBluetooth += command;
    }
    delay(1);
  }

}

void setupOled() {

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

}

void setupInOut() {
  pinMode(BUTTONS, INPUT);
  pinMode(BLUE, OUTPUT) ;
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(STEP_PIN_ENABLE, OUTPUT);
}

void putMachineInReadyState() {
  // CONFIGURTACOES INICIAIS MOTOR myStepRevolutions - INICIAR PARADO
  myStepMotor.move(0);
  digitalWrite(STEP_PIN_ENABLE, HIGH);
  colorCrossFade(dimbranco);
  //INICIA COMUNICACAO SERIAL
  Serial.begin(9600);
  Serial.print("Maquina inicializada\n\n");
}

void readComponentStatus() {
  buttonBusStatus   = analogRead(BUTTONS);
}

void checkPressedButtons() {
  //CASO BOTAO VERDE INICIAR APERTADO
  if (buttonBusStatus >= 130 && buttonBusStatus < 150 ) {
    if (isInjecting == 0 && isWaiting == 1 && isRecalling == 0
        && botI == 1 && botR == 0 && botP == 0 && fcI == 0 && fcR == 0 ) {
      startInjection();
    }
  }
  //CASO BOTAO VERMELHO PARAR APERTADO
  else    if (buttonBusStatus >= 159 && buttonBusStatus < 200) { //>=220 && buttonBusStatus<240
    if (isInjecting == 1 && isWaiting == 0 && isRecalling == 0) {
      stopMachine();
    }
  }
  //CASO FIM DE CURSO RECOLHIMENTO COMPLETO
  else   if (buttonBusStatus >= 200 &&  buttonBusStatus < 300) { //buttonBusStatus >=670
    if (isInjecting == 0 && isWaiting == 0 && isRecalling == 1
        && botI == 0 && botR == 0 && botP == 0 && fcI == 0 && fcR == 1) {
      stopMotorAtPickup();
    }
  }
  //CASO FIM DE CURSO INJECAO COMPLETA
  else  if (buttonBusStatus >= 301 && buttonBusStatus < 350) {
    if (isInjecting == 1 && isWaiting == 0 && isRecalling == 0
        && botI == 0 && botR == 0 && botP == 1 && fcI == 1 && fcR == 0) {
      stopInjectionAndPickup();
    }
  }
  //CASO PRESSAO DA MAQUINA ATINJA ALTO NIVEL
  else  if (buttonBusStatus >= 666) { //>=330 && buttonBusStatus<350
    if (isInjecting == 1 && isWaiting == 0 && isRecalling == 0) {
      pressurePanic();
    }
  }
}

void checkBluetoothCommands() {
  if (stringBluetooth == "TO") {
    if (isInjecting == 0 && isWaiting == 1 && isRecalling == 0
        && botI == 1 && botR == 0 && botP == 0 && fcI == 0 && fcR == 0 ) {
      Serial.println("SE DA BLUETOOTH INI INJE ");
      startInjection();
    }
  } else if (stringBluetooth == "TF") {
    //COLOCAR UM BOOLEANO AQUI
    if (isInjecting == 1 && isWaiting == 0 && isRecalling == 0) {
      Serial.println("SE DA BLUETOOTH PARA INJE ");

      stopMachine();
    }
  }
}


void printStatusOnSerial() {
  if (isRecalling == 1) {
    Serial.println("Maquina esta Recolhendo");
    String message = (String)  "EI=" + isInjecting + " EA=" + isWaiting + " ER=" + isRecalling + " BI=" + botI + " bR=" + botR + " bP=" + botP + " FCI=" + fcI + " FCR=" + fcR;
    Serial.println(message );
  }
  if (isInjecting == 1) {
    Serial.println("Maquina esta Injetando");
    String message = (String) "EI=" + isInjecting + " EA=" + isWaiting + " ER=" + isRecalling + " BI=" + botI + " bR=" + botR + " bP=" + botP + " FCI=" + fcI + " FCR=" + fcR;
    Serial.println(message );
  }
  if (isWaiting == 1) {
    Serial.println("Maquina esta Aguardando");
    String message = (String)  "EI=" + isInjecting + " EA=" + isWaiting + " ER=" + isRecalling + " BI=" + botI + " bR=" + botR + " bP=" + botP + " FCI=" + fcI + " FCR=" + fcR;
    Serial.println(message );
  }
}


void settingInjectionStatus() {
  isInjecting  = 1;
  isWaiting = 0;
  isRecalling = 0;
  botI = 0;
  botR = 0;
  botP = 1;
  fcI  = 1;
  fcR  = 0;
}
void settingRecallStatus() {
  isInjecting  = 0;
  isWaiting = 0;
  isRecalling = 1;
  botI = 0;
  botR = 0;
  botP = 0;
  fcI  = 0;
  fcR  = 1;
}
void settingStopRecallStatus() {
  isInjecting  = 0;
  isWaiting = 1;
  isRecalling = 0;
  botI = 0;
  botR = 1;
  botP = 0;
  fcI  = 0;
  fcR  = 1;
}

void settingWaitStatus() {
  isInjecting  = 0;
  isWaiting = 1;
  isRecalling = 0;
  botI = 1;
  botR = 0;
  botP = 0;
  fcI  = 0;
  fcR  = 0;
}

void settingInjectionMotor() {
  myStepMotor.setMaxSpeed(150);
  myStepMotor.setSpeed(150);
  myStepMotor.setAcceleration(150);//Novo
  digitalWrite(STEP_PIN_ENABLE, LOW);
  myStepMotor.move(-myStepRevolutions);
}

void settingRecallMotor() {
  digitalWrite(STEP_PIN_ENABLE, LOW);
  myStepMotor.setMaxSpeed(2000);
  myStepMotor.setSpeed(2000);
  myStepMotor.setAcceleration(2000);
  myStepMotor.move(myStepRevolutions);
}

void settingWaitMotor() {
  myStepMotor.move(0);
  digitalWrite(STEP_PIN_ENABLE, HIGH);
}

void settingBackLittleMotor() {
  digitalWrite(STEP_PIN_ENABLE, LOW);
  myStepMotor.move(-1000);
}

void readInjectionPressure() {
  fsrreading = analogRead(fsrpin);
  // Print the string "Analog reading = ".
  Serial.print("Analog reading = ");
  // Print the fsrreading:
  Serial.print(fsrreading);
  // We can set some threshholds to display how much pressure is roughly applied:
  if (fsrreading < 10) {
    Serial.println(" - No pressure");
  } else if (fsrreading < 200) {
    Serial.println(" - Light touch");
  } else if (fsrreading < 500) {
    Serial.println(" - Light squeeze");
  } else if (fsrreading < 600) {
    Serial.println(" - Medium squeeze");
  } else {
    Serial.println(" - Big squeeze");
    //PANIC
    pressurePanic();
  }
}

//ONLINE IMAGE TO C ARRAY https://littlevgl.com/image-to-c-array

//SUPRIMIDOS
//CASO BOTAO AZUL RECOLHER APERTADO
//  else if (buttonBusStatus >=160 && buttonBusStatus<170){ >=160 && buttonBusStatus<170
//      if(isInjecting == 0 && isWaiting ==1 && isRecalling== 0
//      && botI==0 && botR==1 && botP==0 && fcI==0 && fcR==1){
//          pickupRecall();
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
