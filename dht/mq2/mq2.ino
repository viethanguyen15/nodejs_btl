void setup() {
  Serial.begin(115200);
  pinMode(D1, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A0));
  if(analogRead(A0) > 700){
      digitalWrite(D1, HIGH);
    }
  else{
      digitalWrite(D1, LOW);
    }
  delay(1000);    
}
