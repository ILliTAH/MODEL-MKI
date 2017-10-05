#define L1 A4
#define L2 A5
#define L3 2
#define L4 3

#define M1 4
#define M2 5
#define M3 6
#define M4 7
#define M5 8
#define M6 9

#define H1 10
#define H2 11
#define H3 12
#define H4 13
#define H5 A6

#define sw1 A3
#define sw2 A2
#define sw3 A1
#define sw4 A0

int ds = 950;

int bounceTime = 50;
int holdTime = 250;
int doubleTime = 500;

int lastReading = LOW;
int hold = 0;
int single = 0;

long onTime = 0;
long lastSwitchTime = 0;
int exloop = 0;
int speedLed = 2;

void Lloop() {
  Serial.println("LStart");
  digitalWrite(L1, HIGH);
  delay(ds);
  digitalWrite(L1, LOW);

  digitalWrite(L2, HIGH);
  delay(ds);
  digitalWrite(L2, LOW);

  digitalWrite(L3, HIGH);
  delay(ds);
  digitalWrite(L3, LOW);


  digitalWrite(L4, HIGH);
  delay(ds);
  digitalWrite(L4, LOW);

  digitalWrite(L1, HIGH);
  delay(1000);
  digitalWrite(L1, LOW);
  Serial.println("LFinish");



}


void Mloop() {

  Serial.println("MStart");

  digitalWrite(M1, HIGH);
  delay(ds);
  digitalWrite(M1, LOW);

  digitalWrite(M2, HIGH);
  delay(ds);
  digitalWrite(M2, LOW);

  digitalWrite(M3, HIGH);
  delay(ds);
  digitalWrite(M3, LOW);

  digitalWrite(M4, HIGH);
  delay(ds);
  digitalWrite(M4, LOW);

  digitalWrite(M5, HIGH);
  delay(ds);
  digitalWrite(M5, LOW);

  digitalWrite(M6, HIGH);
  delay(ds);
  digitalWrite(M6, LOW);

  digitalWrite(M1, HIGH);
  delay(1000);
  digitalWrite(M1, LOW);

  Serial.println("MFinish");



}

void Hloop() {

  Serial.println("HStart");

  digitalWrite(H1, HIGH);
  delay(ds);
  digitalWrite(H1, LOW);

  digitalWrite(H2, HIGH);
  delay(ds);
  digitalWrite(H2, LOW);

  digitalWrite(H3, HIGH);
  delay(ds);
  digitalWrite(H3, LOW);


  digitalWrite(H4, HIGH);
  delay(ds);
  digitalWrite(H4, LOW);

  
  digitalWrite(H5, HIGH);
  delay(ds);
  digitalWrite(H5, LOW);


  digitalWrite(H1, HIGH);
  delay(ds);
  digitalWrite(H1, LOW);
  Serial.println("HFinish");


}

void clearLed() {

  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(L3, LOW);
  digitalWrite(L4, LOW);

  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);
  digitalWrite(M5, LOW);
  digitalWrite(M6, LOW);

  digitalWrite(H1, LOW);
  digitalWrite(H2, LOW);
  digitalWrite(H3, LOW);
  digitalWrite(H4, LOW);
  digitalWrite(H5, LOW);

  Serial.println("Cleared");
}


void setupTime() {
  Serial.println("SETUP");
  exloop = 2;
  delay(500);
  while (exloop < 5) {

    int rd = digitalRead(sw1);
    int rd1 = digitalRead(sw2);


    if (rd == HIGH) {
      exloop =  8;
    }
    if (rd1 == HIGH) {
      speedLed = speedLed += 1;
      

    }



    Serial.println(exloop);
    if (speedLed == 1) {
      ds = 500;

      digitalWrite(H1, HIGH);
      digitalWrite(H2, LOW);
      digitalWrite(H3, LOW);
      digitalWrite(H4, LOW);
    }
    if (speedLed == 2) {
      ds = 1000;
      digitalWrite(H1, HIGH);
      digitalWrite(H2, HIGH);
      digitalWrite(H3, LOW);
      digitalWrite(H4, LOW);
    }
    if (speedLed == 3) {
      ds = 1500;
      digitalWrite(H1, HIGH);
      digitalWrite(H2, HIGH);
      digitalWrite(H3, HIGH);
      digitalWrite(H4, LOW);
    }
 

if (speedLed > 4) {
        speedLed = 1;

      }

  }

  exloop = 0;



}

void setup()
{ Serial.begin(9600);
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(sw3, INPUT);
  pinMode(sw4, INPUT);

  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);

  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  pinMode(M5, OUTPUT);
  pinMode(M6, OUTPUT);

  pinMode(H1, OUTPUT);
  pinMode(H2, OUTPUT);
  pinMode(H3, OUTPUT);
  pinMode(H4, OUTPUT);



}

void loop()
{
  clearLed();
  int reading = digitalRead(sw1);
  int reading1 = digitalRead(sw2);
  int reading2 = digitalRead(sw3);
  int reading3 = digitalRead(sw4);


  if (reading1 == HIGH) {
    Hloop();

  }

  if (reading2 == HIGH) {
    Mloop();

  }

  if (reading3 == HIGH) {
    Lloop();

  }


  //first pressed
  if (reading == HIGH && lastReading == LOW) {
    onTime = millis();
  }

  //held
  if (reading == HIGH && lastReading == HIGH) {
    if ((millis() - onTime) > holdTime) {

      hold = 1;
    }
  }

  //released
  if (reading == LOW && lastReading == HIGH) {
    if (((millis() - onTime) > bounceTime) && hold != 1) {
      onRelease();
    }
    if (hold == 1) {
      Serial.println("held");
      setupTime();
      hold = 0;
    }
  }
  lastReading = reading;

  if (single == 1 && (millis() - lastSwitchTime) > doubleTime) {
    Serial.println("single press");

    Lloop();
    Mloop();
    Hloop();
    single = 0;
  }

}

void onRelease() {

  if ((millis() - lastSwitchTime) >= doubleTime) {
    single = 1;
    lastSwitchTime = millis();
    return;
  }

  if ((millis() - lastSwitchTime) < doubleTime) {

    Serial.println("double press");
    single = 0;
    lastSwitchTime = millis();
  }

}
