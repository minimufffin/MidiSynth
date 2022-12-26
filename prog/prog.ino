#define BAUDRATE 9600   // change to midi baud rate

int incomingByte;       // byte sent from midi controller

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (Serial.available() > 0)
  {
    // read incoming byte
    incomingByte = Serial.read();

    Serial.print("Recieved: 0x");
    Serial.println(incomingByte, HEX);

  }
}
