const int pin = 6;

int time_ms = 10;
int freq = 440;
int fMax = 1000;
int fMin = 200;
int freq_inc = 20;
int sign = 1;
int notoneMode = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  tone(pin, freq);
  delay(time_ms);
  if (!notoneMode)
    noTone(pin);
    delay(time_ms);
  freq = freq + freq_inc * sign;
  if (freq > fMax)
    sign = -1;
  if (freq < fMin)
    sign = 1;
}
