#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

int motor = D4;
int sensor = A0;
int sens_val;
int flag = 0;

char auth[] = "key";
char ssid[] = "username";
char pass[] = "password";

int Relay = 0;
int automatic = 1;

void setup() {
  pinMode(motor, OUTPUT);
  pinMode(sensor, INPUT);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  Serial.begin(9600);
}

BLYNK_WRITE(V1) {
  Relay = param.asInt();
}

BLYNK_WRITE(V2) {
  automatic = param.asInt();
}

void loop() {

  sens_val = analogRead(A0);

  if(sens_val > 700 && automatic == 0){
    Blynk.virtualWrite(V1, Relay);
    digitalWrite(motor, LOW);
  }
  else if(sens_val<=700 && automatic == 0){
    Blynk.virtualWrite(V1, Relay);
    digitalWrite(motor, HIGH);
  }
  else if (Relay==0 && automatic==1){
    digitalWrite(motor, LOW);
  }
  else if (Relay==1 && automatic==1){
    digitalWrite(motor, HIGH);
  }

  int value = sens_val;
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;
  Blynk.virtualWrite(V0, value);

  char buffer[40];
  sprintf(buffer, "Sens_val: %d, value: %d, Relay: %d, automatic: %d", sens_val, value, Relay, automatic);
  Serial.println(buffer);

  Blynk.run();

}
