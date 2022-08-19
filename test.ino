void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
pinMode(5, OUTPUT);
pinMode(19, OUTPUT);
 pinMode(21, OUTPUT);
}

void loop() {
  dacWrite(25, 0);
   digitalWrite(21, HIGH);
   digitalWrite(5, LOW);
   delay(1000);
   dacWrite(25, 124);
   digitalWrite(19, HIGH);
   digitalWrite(21, LOW); 
    delay(2000);
dacWrite(25, 240);
digitalWrite(19, LOW);
   digitalWrite(5, HIGH);
    delay(2000);
}
