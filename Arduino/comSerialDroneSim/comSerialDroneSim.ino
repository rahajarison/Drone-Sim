int pinThrottle = 13;
int pinYaw = 6;

void setup() {
  Serial.begin(9600);
  pinMode(pinThrottle, OUTPUT);
  pinMode(pinYaw, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    byte data;
    data = Serial.read();
//    if (data == 'Y')
//    {
      digitalWrite(pinYaw, HIGH);
      delay(500);
      digitalWrite(pinYaw, LOW);
//    }
//    else
//    {
//      analogWrite(pinThrottle, data);
//      delay(500);
//    }
    Serial.write(data);
  }  
}
