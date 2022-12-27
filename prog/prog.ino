#define BAUDRATE 31250   // change to midi baud rate

// status messages (without midi channel)
#define NOTEON 0x90
#define NOTEOFF 0x80

#define SPKRPIN 2

int runningStatus = 0;      // last midi status byte
int currentNote = -1;       // tone being played

struct message
{
  char status;
  char data1;
  char data2;
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);

  pinMode(SPKRPIN, OUTPUT);
}

void printByte(int byte)
{
  if (byte > 0)
  {
    Serial.println("Recieved: 0x");
    Serial.println(byte, HEX);
  }
}

struct message readNoteMessage(int firstByte)
{
  int noteValue;
  int noteVelocity;
  delay(1);   // make sure that the full midi message goes through
  if (firstByte == runningStatus)
    noteValue = Serial.read();
  else
    noteValue = firstByte;
  noteVelocity = Serial.read();

  struct message msg;
  msg.status = runningStatus;
  msg.data1 = noteValue;
  msg.data2 = noteVelocity;
  return msg;
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

  struct message *msg = NULL;
  // at this point if byte is not -1, we can read a full message
  if (incomingByte > 0)
  {
    (*msg) = readNoteMessage(incomingByte);
  }

  if (msg)
  {
    if (msg->status & 0xF0 == NOTEON)
    {
      int freq = pow(2, (msg->data1-69)/12.0) * 440;
      noTone(SPKRPIN);
      tone(SPKRPIN, freq);
      currentNote = msg->data1;
    }
    else if (msg->status & 0xF0 == NOTEOFF && msg->data1 == currentNote)
      noTone(SPKRPIN);
  }
}
