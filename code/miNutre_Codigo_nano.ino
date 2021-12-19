//  MAQUINA INJETORA DE DIETA VIA SERINGA 60ML

// 10-03-2019
// VERSAO 1.1.0
//nov 2021

#include "Oled.h"
#include "Constants.h"
#include "Sound.h"
#include "Led.h"
#include "Motor.h"
#include "Pressure.h"


char command;
String stringBluetooth;


int buttonBusStatus = 0;
int isInjecting  = 0;
int isWaiting = 1;
int isRecalling = 0;
int  botI = 1;
int  botR = 0;
int  botP = 0;
int  fcI  = 0;
int  fcR  = 0;
int incomingByte = 0;

//iniciar
int BT01_MIN = 230;
int BT01_MAX = 250;
//int BT01_MIN = 220;
//int BT01_MAX = 230;

//PARAR
int BT02_MIN = 170;
int BT02_MAX = 180;
//
//int BT02_MIN = 165;
//int BT02_MAX = 170;

//FIM infecao
int FDC01_MIN = 345;
int FDC01_MAX = 350;
//int FDC01_MIN = 330;
//int FDC01_MAX = 340;

//FIM recolhimeto
int FDC02_MIN = 700;
int FDC02_MAX = 710;

//int FDC02_MIN = 670;
//int FDC02_MAX = 680;

void setup() {
  Serial.begin(9600);
  setupInOut();
  putMachineInReadyState();
  setupOled();
  drawInit();
  drawLogo();
  printStatusOnSerial();
  turnOnGreenLight();
  drawWait();

}

void loop() {


  bluetoothCommandsListener();
  readComponentStatus();
  checkPressedButtons();
  checkBluetoothCommands();
  readInjectionPressure() ;
  readSerialCommand();
  myStepMotor.run();
}


void startInjection() {
  Serial.println(F("startInjection"));
  settingInjectionStatus();
  turnOnBlueLight();
  drawInjet();
  settingInjectionMotor();
  stringBluetooth = "";
  printStatusOnSerial();
}

void stopInjectionAndPickup() {
  Serial.println(F("stopInjectionAndPickup"));
  turnOnVioletLight();
  drawWait();
  settingStopRecallStatus();
  settingWaitMotor();
  printStatusOnSerial();
  pickupRecall();
}

void pickupRecall() {
  Serial.println(F("pickupRecall"));
  settingRecallStatus();
  turnOnWhiteLight();
  drawRecall();
  settingRecallMotor();
  printStatusOnSerial();
}

void stopMachine() {
  Serial.println(F(" stopMachine"));
  turnOnRedLight();
  drawWait();
  settingWaitStatus();
  settingWaitMotor();
  printStatusOnSerial();
  playHappyMelody();
}

void pressurePanic() {
  Serial.println(F(" pressurePanic"));
  Serial.println(F("a pressão atingiu niveis alarmantes"));
  turnOnRedLight();
  drawLogo();
  settingWaitStatus();
  settingWaitMotor();
  playImperialMarch();
  printStatusOnSerial();
}

void backALitle() {
  Serial.println(F("backALitle"));
  turnOnGreenLight();
  drawLogo();
  settingWaitStatus();
  settingBackLittleMotor();
  delay(1000);
  drawWait();
  printStatusOnSerial();

}


void bluetoothCommandsListener() {

  if (Serial.available() > 0) {
    stringBluetooth = "";
  }

  while (Serial.available() > 0) {
    command = ((byte)Serial.read());

    if (command == ':') {
      Serial.println(F("Parando"));
      break;
    } else {
      stringBluetooth += command;
    }
    delay(1);
  }

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
//  drawBtn(buttonBusStatus);
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
      Serial.println(F("SE DA BLUETOOTH INI INJE "));
      startInjection();
    }
  } else if (stringBluetooth == "TF") {
    //COLOCAR UM BOOLEANO AQUI
    if (isInjecting == 1 && isWaiting == 0 && isRecalling == 0) {
      Serial.println(F("SE DA BLUETOOTH PARA INJE "));

      stopMachine();
    }
  }
}


void printStatusOnSerial() {
  if (isRecalling == 1) {
    Serial.println(F("Maquina esta Recolhendo"));
    String message = (String)  "EI=" + isInjecting + " EA=" + isWaiting + " ER=" + isRecalling + " BI=" + botI + " bR=" + botR + " bP=" + botP + " FCI=" + fcI + " FCR=" + fcR;
    Serial.println(message );
  }
  if (isInjecting == 1) {
    Serial.println(F("Maquina esta Injetando"));
    String message = (String) "EI=" + isInjecting + " EA=" + isWaiting + " ER=" + isRecalling + " BI=" + botI + " bR=" + botR + " bP=" + botP + " FCI=" + fcI + " FCR=" + fcR;
    Serial.println(message );
  }
  if (isWaiting == 1) {
    Serial.println(F("Maquina esta Aguardando"));
    String message = (String)  "EI=" + isInjecting + " EA=" + isWaiting + " ER=" + isRecalling + " BI=" + botI + " bR=" + botR + " bP=" + botP + " FCI=" + fcI + " FCR=" + fcR;
    Serial.println(message );
  }
}

void readSerialCommand() {
  //M O C K

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.println(F("I received: "));
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
