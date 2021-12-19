
int pressureReading;

boolean readInjectionPressure() {
  pressureReading = analogRead(PRESSURE_SENSOR);
//  Serial.print("Pressao ");
//  Serial.println(pressureReading);
//  Diversos limiares
  if (pressureReading < 10) {}
  else if (pressureReading < 200) {}
  else if (pressureReading < 500) {}
  else if (pressureReading < 600) {}
  else {
//    Serial.println(" - PANIC");
    return true;
  }
}
