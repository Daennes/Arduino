/*
 Name:		LedTest.ino
 Created:	21.03.2017 20:52:54
 Author:	Dennis
*/

//Zeilen: 8 Stück
int latchPin = 12;
int clockPin = 11;
int dataPin = 13;



//Spalten
int latchPin_2 = 8;
int clockPin_2 = 9;
int dataPin_2 = 7;


// the setup function runs once when you press reset or power the board
void setup() {

}

// the loop function runs over and over again until power down or reset
void loop() {

	for (int i = 0; i < 8; i++)
	{



		//Serial.println(tempZeichen, BIN);

		digitalWrite(latchPin, LOW);
		shiftOut(dataPin, clockPin, LSBFIRST, (0x01 << i));
		digitalWrite(latchPin, HIGH);

		digitalWrite(latchPin_2, LOW);
		shiftOut(dataPin_2, clockPin_2, LSBFIRST, 0xff);
		shiftOut(dataPin_2, clockPin_2, LSBFIRST, 0xff<<8);
		digitalWrite(latchPin_2, HIGH);

		delay(2);
	}
  
}
