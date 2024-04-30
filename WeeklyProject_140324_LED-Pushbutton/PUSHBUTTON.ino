int LED1 = D1;
int LED2 = D2;
int LED3 = D3;
int LED4 = D5;
int btn1 = D6;
int btn2 = D7; 

void setup(){
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
}

void loop(){
  int buttonstatus1 = digitalRead(btn1);
  int buttonstatus2 = digitalRead(btn2);

  if (buttonstatus1 == LOW){ //
    runningRight(); // 
  } else if (buttonstatus2 == LOW){ 
    runningLeft();
  } else {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    delay(100);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    delay(100);
  }
}

void runningRight() {
  digitalWrite(LED1, HIGH);
  delay(100);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(100);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  delay(100);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, HIGH);
  delay(100);
  digitalWrite(LED4, LOW);
}

void runningLeft() {
  digitalWrite(LED4, HIGH);
  delay(100);
  digitalWrite(LED4, LOW);
  digitalWrite(LED3, HIGH);
  delay(100);
  digitalWrite(LED3, LOW);
  digitalWrite(LED2, HIGH);
  delay(100);
  digitalWrite(LED2, LOW);
  digitalWrite(LED1, HIGH);
  delay(100);
  digitalWrite(LED1, LOW);
}
