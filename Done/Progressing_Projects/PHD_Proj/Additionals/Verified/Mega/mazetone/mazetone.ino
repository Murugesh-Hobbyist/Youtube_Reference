

#include "pitches.h"

int melody[] = {  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4  };

int noteDurations[] = {  4, 8, 8, 4, 4, 4, 4, 4  };
int potPin = A8;

void setup() {}

  

void loop() {

for (int thisNote = 0; thisNote < 8; thisNote++) {
  int potReading = analogRead (potPin);

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / noteDurations[thisNote];

    tone(52, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    int pitch = map(potReading, 0, 1023, 120, 5000);

    delay(potReading);

    noTone(52);

  }
}