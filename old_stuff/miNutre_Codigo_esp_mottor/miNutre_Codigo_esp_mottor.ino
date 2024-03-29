//  MAQUINA INJETORA DE DIETA VIA SERINGA 60ML

// 10-03-2019
// VERSAO 1.1.0
//mar 2021

#include <AccelStepper.h>
#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 5, /* data=*/ 4);   // ESP32 Thing, HW I2C with pin remapping

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

#define STEP_PIN                   0
#define DIRECTION_PIN              2
#define MOTOR_ENABLE_PIN          15
#define PRESSURE_SENSOR           A0
#define BUTTONS                   A0
#define BUZZER                     16
#define BLUE                      13
#define GREEN                     12
#define RED                       14


AccelStepper myStepMotor(AccelStepper::DRIVER, STEP_PIN, DIRECTION_PIN );

char command;
String stringBluetooth;

String MACHINE_NAME = "m i N U T R E";
String RECALL = "RECALLn";
String WAIT   = "WAITING";
String INJECT = "INJECTn";
String START = "STARTIn";
String LOGO = "miNUTRE";

long myStepRevolutions = -1000000;

int preto     [3]  = { 0, 0, 0 };
int dimbranco [3]  = { 30, 30, 30};
int redValue = preto[0];
int greenValue = preto[1];
int blueValue = preto[2];
// VARIAVEIS DE CORES
int nRed = redValue;
int nGreen = greenValue;
int nBlue = blueValue;

int buttonBusStatus = 0;
int isInjecting  = 0;
int isWaiting = 1;
int isRecalling = 0;
int  botI = 1;
int  botR = 0;
int  botP = 0;
int  fcI  = 0;
int  fcR  = 0;
int pressureReading;
int incomingByte = 0;
int PULSE_WIDTH = 3;

int BT01_MIN = 200;
int BT01_MAX = 228;
int BT02_MIN = 240;
int BT02_MAX = 297;
int FDC01_MIN = 500;
int FDC01_MAX = 550;
int FDC02_MIN = 1000;
int FDC02_MAX = 1030;

void setup() {
  Serial.begin(115200);
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
  //M O C K

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);

    if (incomingByte == 49) {
      startInjection() ;
    } else  if (incomingByte == 50) {
      stopInjectionAndPickup() ;
    } else  if (incomingByte == 48) {
      stopMachine() ;
    }
  }
  //M O C K
  myStepMotor.run();
}


void startInjection() {
  Serial.println("startInjection");
  settingInjectionStatus();
  turnOnBlueLight();
  drawInjet();
  settingInjectionMotor();
  stringBluetooth = "";
  printStatusOnSerial();
}

void stopInjectionAndPickup() {
  Serial.println("stopInjectionAndPickup");
  turnOnVioletLight();
  drawWait();
  settingStopRecallStatus();
  settingWaitMotor();
  printStatusOnSerial();
  pickupRecall();
}

void pickupRecall() {
  Serial.println("pickupRecall");
  settingRecallStatus();
  turnOnWhiteLight();
  drawRecall();
  settingRecallMotor();
  printStatusOnSerial();
}

void stopMachine() {
  Serial.println(" stopMachine");
  turnOnRedLight();
  drawWait();
  settingWaitStatus();
  settingWaitMotor();
  printStatusOnSerial();
  playHappyMelody();
}

void pressurePanic() {
  Serial.println(" pressurePanic");
  Serial.println("a pressão atingiu niveis alarmantes");
  turnOnRedLight();
  drawLogo();
  settingWaitStatus();
  settingWaitMotor();
  playImperialMarch();
  printStatusOnSerial();
}

void backALitle() {
  Serial.println("backALitle");
  turnOnGreenLight();
  drawLogo();
  settingWaitStatus();
  settingBackLittleMotor();
  delay(1000);
  drawWait();
  printStatusOnSerial();

}

void colorCrossFade(int cor[3]) {
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

void drawInit() {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr( 5, 15, "(31)988470290");
    u8g2.setFont(u8g2_font_helvR14_tr);
    u8g2.drawStr( 10, 57, START.c_str());
    //frame
    u8g2.drawRFrame(0, 18, 128, 46, 4);
  } while ( u8g2.nextPage() );
}

void drawInjet() {
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_helvR14_tr);
      u8g2.drawStr( 5, 15, MACHINE_NAME.c_str());
      u8g2.setFont(u8g2_font_helvR14_tr);
      u8g2.drawStr( 10, 57, INJECT.c_str());
      //frame
      u8g2.drawRFrame(0, 18, 128, 46, 4);
    } while ( u8g2.nextPage() );
}

void drawRecall() {
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_helvR14_tr);
      u8g2.drawStr( 5, 15, MACHINE_NAME.c_str());
      u8g2.setFont(u8g2_font_helvR14_tr);
      u8g2.drawStr( 10, 57, RECALL.c_str());
      //frame
      u8g2.drawRFrame(0, 18, 128, 46, 4);
    } while ( u8g2.nextPage() );
}

void drawWait() {
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_helvR14_tr);
      u8g2.drawStr( 5, 15, MACHINE_NAME.c_str());
      u8g2.setFont(u8g2_font_helvR14_tr);
      u8g2.drawStr( 10, 57, WAIT.c_str());
      //frame
      u8g2.drawRFrame(0, 18, 128, 46, 4);
    } while ( u8g2.nextPage() );
}

void drawLogo() {

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr( 5, 15, "(31)988470290");
    u8g2.setFont(u8g2_font_helvR14_tr);
    u8g2.drawStr( 10, 57, LOGO.c_str());
    //frame
    u8g2.drawRFrame(0, 18, 128, 46, 4);
  } while ( u8g2.nextPage() );
  delay(3000);
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

  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvR14_tr);
  u8g2.setCursor(0, 24);
  u8g2.print("Hello!");
  u8g2.sendBuffer();
  delay(100);

}

void setupInOut() {
//  pinMode(PRESSURE_SENSOR, INPUT);
  pinMode(BUTTONS, INPUT);
  pinMode(BLUE, OUTPUT) ;
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(MOTOR_ENABLE_PIN, OUTPUT);

}


void readComponentStatus() {
  buttonBusStatus   = analogRead(BUTTONS);
}

void checkPressedButtons() {
//    Serial.print("My status = ");
//    Serial.println(buttonBusStatus);

  //BOTAO VERDE INICIAR
  if (buttonBusStatus >= BT01_MIN && buttonBusStatus < BT01_MAX ) {
    if (isInjecting == 0 && isWaiting == 1 && isRecalling == 0
        && botI == 1 && botR == 0 && botP == 0 && fcI == 0 && fcR == 0 ) {
      startInjection();
    }
  }
  //BOTAO VERMELHO PARAR
  else    if (buttonBusStatus >= BT02_MIN && buttonBusStatus < BT02_MAX) { //>=220 && buttonBusStatus<240
    if (isInjecting == 1 && isWaiting == 0 && isRecalling == 0) {
      stopMachine();
    }
  }
  //FIM RECOLHIMENTO
  else   if (buttonBusStatus >= FDC02_MIN &&  buttonBusStatus < FDC02_MAX) { //buttonBusStatus >=670
    if (isInjecting == 0 && isWaiting == 0 && isRecalling == 1
        && botI == 0 && botR == 0 && botP == 0 && fcI == 0 && fcR == 1) {
      stopMachine();
    }
  }
  //FIM INJECAO
  else  if (buttonBusStatus >= FDC01_MIN && buttonBusStatus < FDC01_MAX) {
    if (isInjecting == 1 && isWaiting == 0 && isRecalling == 0
        && botI == 0 && botR == 0 && botP == 1 && fcI == 1 && fcR == 0) {
      stopInjectionAndPickup();
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

void putMachineInReadyState() {
  myStepMotor.setMinPulseWidth(PULSE_WIDTH);
  myStepMotor.setPinsInverted(false, false);
  myStepMotor.setPinsInverted(true, true);
  myStepMotor.moveTo(0);
  myStepMotor.enableOutputs();
  colorCrossFade(dimbranco);
  Serial.print("Maquina inicializada\n\n");
}

void settingInjectionMotor() {
  digitalWrite(MOTOR_ENABLE_PIN, LOW);
  myStepMotor.setMinPulseWidth(PULSE_WIDTH);
  myStepMotor.setMaxSpeed(15);
  myStepMotor.setSpeed(15);
  myStepMotor.setAcceleration(15);//Novo
  myStepMotor.moveTo(-myStepRevolutions);
  myStepMotor.disableOutputs();
}

void settingRecallMotor() {
  digitalWrite(MOTOR_ENABLE_PIN, LOW);
  myStepMotor.setMinPulseWidth(PULSE_WIDTH);
  myStepMotor.setMaxSpeed(1000);
  myStepMotor.setSpeed(1000);
  myStepMotor.setAcceleration(1000);
  myStepMotor.moveTo(myStepRevolutions);
}

void settingWaitMotor() {
  myStepMotor.move(0);
  myStepMotor.disableOutputs();
  digitalWrite(MOTOR_ENABLE_PIN, HIGH);
}

void settingBackLittleMotor() {
  myStepMotor.move(-10);
}

void readInjectionPressure() {
  //  pressureReading = analogRead(PRESSURE_SENSOR);
  //  Serial.print("Pressao ");
  //  Serial.println(pressureReading);
  // Diversos limiares
  //    if (pressureReading < 10) {}
  //    else if (pressureReading < 200) {}
  //    else if (pressureReading < 500) {}
  //    else if (pressureReading < 600) {}
  //    else {
  //      Serial.println(" - PANIC");
  //      pressurePanic();
  //    }
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
