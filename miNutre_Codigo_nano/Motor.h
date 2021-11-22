#include <AccelStepper.h>

AccelStepper myStepMotor(AccelStepper::DRIVER, STEP_PIN, DIRECTION_PIN );

int PULSE_WIDTH = 3;


void putMachineInReadyState() {
  myStepMotor.setMinPulseWidth(PULSE_WIDTH);
  myStepMotor.setPinsInverted(false, false);
  myStepMotor.setPinsInverted(true, true);
  myStepMotor.moveTo(0);
  myStepMotor.enableOutputs();
  colorCrossFade(dimbranco);
  Serial.println(F("Maquina inicializada\n\n"));
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
