#define BAUDRATE 9600   // change to midi baud rate

// status messages (without midi channel)
#define NOTEON 0x90
#define NOTEOFF 0x80

int runningStatus = 0;      // last midi status byte

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);
}

void printByte(int byte)
{
  if (byte > 0)
  {
    Serial.println("Recieved: 0x");
    Serial.println(byte, HEX);
  }
}

void readMessage(int firstByte)
{
  int noteValue;
  int noteVelocity;
  if (runningStatus & 0xF0 == NOTEON || runningStatus & 0xF0 == NOTEOFF)
  {
    delay(1);   // make sure that the full midi message goes through
    if (firstByte == runningStatus)
      noteValue = Serial.read();
    else
      noteValue = firstByte;
    noteVelocity = Serial.read();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  // First, read a byte for next message
  int incomingByte = Serial.read();
  printByte(incomingByte);
  if (incomingByte > 0 && incomingByte & 0x80)
    runningStatus = incomingByte; // update status byte

  // Next, make sure status byte is either note on or note off
  while (incomingByte != -1 && (runningStatus & 0xF0) != NOTEON && (runningStatus & 0xF0) != NOTEOFF)
  {
    incomingByte = Serial.read();
    printByte(incomingByte);
    if (incomingByte > 0 && incomingByte & 0x80)
      runningStatus = incomingByte;
  }

  // at this point if byte is not -1, we can read a full message
  if (incomingByte > 0)
    readMessage(incomingByte);

}
