#include <PelcoBuffer.h>
#include <PelcoMessage.h>

#define           pinTilt       (5)
#define           pinThrottle   (6)

#define           LIGHTUP       (LOW)
#define           LIGHTDOWN     (HIGH)

PelcoBuffer          joystickBuffer;

int                   statusTilt = LIGHTDOWN;
int                   target = pinTilt;

byte			rawBytes[7] = {
  0xFF, 0x01, 0x00, 0x04, 0x3F, 0x00, 0x44
};

void initializeMonitor()
{
  for (byte i = 0; i < 4; i++)
  {
    digitalWrite(pinTilt, LIGHTDOWN);
    delay(500);
    digitalWrite(pinTilt, LIGHTUP);
    delay(500);
  }
  digitalWrite(pinTilt, LIGHTDOWN);
  delay(1000);
}

void setup()
{
  pinMode(pinTilt, OUTPUT);
  pinMode(pinThrottle, OUTPUT);
  digitalWrite(pinThrottle, LIGHTDOWN);
  initializeMonitor();
  Serial3.begin(9600);
  Serial.begin(9600);
  Serial.println("Initialisation terminee");
}

void loop()
{
  joystickBuffer.acquire();
  if (joystickBuffer.isComplete())
  {
    Serial.println("Buffer complet");
    decodePelcoMessage();
    joystickBuffer.flush();
  }
}

void decodePelcoMessage()
{
  PelcoMessage message(joystickBuffer);
  
  if (!message.isCorrect())
  {
    Serial.print("MESSAGE INCORRECT DETECTE: ");
    joystickBuffer.printBuffer();
    while (Serial3.available() > 0)
      Serial3.read();
    joystickBuffer.flush();
    digitalWrite(pinTilt, LIGHTDOWN);
    digitalWrite(pinThrottle, LIGHTDOWN);
    return;
  }
  
  joystickBuffer.printBuffer();
    
  if (message.isADirectionCommand())
  {
    Serial.println("C est une direction");
    digitalWrite(pinTilt, LIGHTUP);
  }
  else
  {
    Serial.println("Ce n est pas une direction");
    digitalWrite(pinTilt, LIGHTDOWN);
  }
  
  if (message.isAThrustCommand())
  {
    Serial.println("C est une commande de gaz");
    digitalWrite(pinThrottle, LIGHTUP);
  }
  else
  {
    Serial.println("Ce n est pas une commande de gaz");
    digitalWrite(pinThrottle, LIGHTDOWN);
  }
  // delay(10);
}

