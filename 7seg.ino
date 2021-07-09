#define FIRST_SEGMENT_PIN   2
#define SEGMENT_COUNT       8
bool butt = false;
bool butt_flag = false;
int number = 0;
byte numberSegments[10] = {
  0b00111111,
  0b00001100,
  0b01011011,
  0b01011110,
  0b01101100,
  0b01110110,
  0b01110111,
  0b00011100,
  0b01111111,
  0b01111110,
};

void setup() {
  Serial.begin(9600);
  for (int i = FIRST_SEGMENT_PIN; i <= SEGMENT_COUNT; ++i) {
    pinMode(i, OUTPUT);
  }
  pinMode(13, INPUT);

}

void loop() {
  Serial.println(Serial.read()- '0');
  if (Serial.available()) {
      number = Serial.parseInt();
      
  }

  
  butt = digitalRead(13);

  if (butt && !butt_flag) {
    butt_flag = true;
  }

  if (!butt && butt_flag) {
    butt_flag = false;
    delay(60);

    if (number > 8) {
      number = 0;
    } else {
      number = ++number;
    }
  }

/*

   if (analogRead(A1) < 750) {

    if (number > 8) {
      number = 0;
    } else {
      number = ++number;
    }
    delay(100);
  }
 */


  int mask = numberSegments[number];
  for (int i = 0; i < SEGMENT_COUNT; ++i) {
    boolean enableSegment = bitRead(mask, i);
    digitalWrite(i + FIRST_SEGMENT_PIN, enableSegment);
  }

}
