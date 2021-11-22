int preto     [3]  = { 0, 0, 0 };
int dimbranco [3]  = { 30, 30, 30};
int redValue = preto[0];
int greenValue = preto[1];
int blueValue = preto[2];
// VARIAVEIS DE CORES
int nRed = redValue;
int nGreen = greenValue;
int nBlue = blueValue;

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
