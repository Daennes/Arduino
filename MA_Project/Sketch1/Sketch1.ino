/*
 Name:		Sketch1.ino
 Created:	25.02.2017 14:08:23
 Author:	Dennis
*/


int latchPin = 12;
int clockPin = 11;
int dataPin = 13;
byte leds = 0;
byte leds_2 = 0;
int currentLED = 6;
int currentLED_2 = 3;

int latchPin_2 = 8;
int clockPin_2 = 9;
int dataPin_2 = 7;

byte font[3][2] = {
	{ 0x05, 0x02 },  
	{ 0x02, 0x05 },  
	{ 0x07, 0x04 }, 
};

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(latchPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);

	pinMode(latchPin_2, OUTPUT);
	pinMode(dataPin_2, OUTPUT);
	pinMode(clockPin_2, OUTPUT);

	leds = 0;

}


void TestLauflicht()
{
	leds_2 = 0x80;
	for (int k = 0; k < 8; k++)
	{
		for (int i = 0; i < 100; i++)
		{
			leds = 0;
			leds_2 = 0x0A << k;
			
			bitSet(leds, 6 );
			//bitSet(leds_2, 3+k);
			//bitSet(leds_2, 5);
			Serial.println("Hex1:");
			Serial.println(leds, HEX);

			Serial.println("Erstes:\n");
			Serial.println(leds);
			Serial.println(leds_2);

			digitalWrite(latchPin, LOW);
			shiftOut(dataPin, clockPin, LSBFIRST, leds);
			digitalWrite(latchPin, HIGH);

			digitalWrite(latchPin_2, LOW);
			shiftOut(dataPin_2, clockPin_2, LSBFIRST, leds_2);
			digitalWrite(latchPin_2, HIGH);

			delay(10);

			leds = 0;
			//leds_2 = 0;
			leds_2 = 0x04 << k;
			bitSet(leds, 7 );
			//bitSet(leds_2, 4+k);
			Serial.println("Hex2:");
			Serial.println(leds, HEX);

			Serial.println("Zweites:\n");
			Serial.println(leds);
			Serial.println(leds_2);

			digitalWrite(latchPin, LOW);
			shiftOut(dataPin, clockPin, LSBFIRST, leds);
			digitalWrite(latchPin, HIGH);

			digitalWrite(latchPin_2, LOW);
			shiftOut(dataPin_2, clockPin_2, LSBFIRST, leds_2);
			digitalWrite(latchPin_2, HIGH);

			delay(10);
		}
	}

}

void Zeichen(int zeichen, int start)
{
	byte tempZeichen;
	for (int i = 0; i < sizeof(font[0]); i++)
	{
		tempZeichen = font[zeichen][i] << start;

		Serial.println(tempZeichen, HEX);

		digitalWrite(latchPin, LOW);
		shiftOut(dataPin, clockPin, LSBFIRST, (0x40 << i));
		digitalWrite(latchPin, HIGH);

		digitalWrite(latchPin_2, LOW);
		shiftOut(dataPin_2, clockPin_2, LSBFIRST, tempZeichen);
		digitalWrite(latchPin_2, HIGH);

		delay(10);
	}
}

void Zeichen2(String zeichen, int start)
{
	Serial.println("Zeichenlange:");
	Serial.println(zeichen.length());

	byte zeichenKette[2];			//Anzahl Zeilen --> Zeilen
	for (int j = 0; j < sizeof(zeichenKette); j++)
	{
		for (int i = 0; i < zeichen.length(); i++)
		{
			switch (zeichen[i])
			{
			case '0':
			{
				zeichenKette[j] = zeichenKette[j] << i * 4 + font[0][j];
				break;
			}
			case '1':
			{
				zeichenKette[j] = zeichenKette[j] << i * 4 + font[1][j];
				break;
			}
			case '2':
			{
				zeichenKette[j] = zeichenKette[j] << i * 4 + font[2][j];
				break;
			}

			}
		}
	}

	Serial.println("zeichenkette:");
	Serial.println(zeichenKette[0], HEX);
	Serial.println(zeichenKette[1], HEX);


	byte tempZeichen;
	for (int i = 0; i < sizeof(zeichenKette); i++)
	{
		tempZeichen = zeichenKette[i] << start;

		Serial.println(tempZeichen, HEX);

		digitalWrite(latchPin, LOW);
		shiftOut(dataPin, clockPin, LSBFIRST, (0x40 << i));
		digitalWrite(latchPin, HIGH);

		digitalWrite(latchPin_2, LOW);
		shiftOut(dataPin_2, clockPin_2, LSBFIRST, tempZeichen);
		digitalWrite(latchPin_2, HIGH);

		delay(10);
	}
}

void Lauflicht2()
{
	for (int i = 0; i < 8; i++)
	{
		for(int k =0; k<100; k++)
			Zeichen2("012", i);
	}
}

// the loop function runs over and over again until power down or reset
void loop() {

	//TestLauflicht();

	Lauflicht2();

	/*leds = 0;

	if (currentLED == 7)
	{
		currentLED = 6;
	}
	else
	{
		currentLED++;
	}

	bitSet(leds, currentLED);

	Serial.println(leds, HEX);

	digitalWrite(latchPin, LOW);
	shiftOut(dataPin, clockPin, LSBFIRST, 0xC0);
	digitalWrite(latchPin, HIGH);

	for (int i = 3; i < 8; i++)
	{
		leds_2 = 0;
		bitSet(leds_2, i);
		bitSet(leds_2, 7-i+3);
		digitalWrite(latchPin_2, LOW);
		shiftOut(dataPin_2, clockPin_2, LSBFIRST, leds_2);
		digitalWrite(latchPin_2, HIGH);
		delay(500);

	}*/

	

	/*bitSet(leds, 0);
	Serial.println("Hallo");
	Serial.println(leds);

	digitalWrite(latchPin, LOW);
	shiftOut(dataPin, clockPin, LSBFIRST, leds);
	digitalWrite(latchPin, HIGH);

	digitalWrite(latchPin_2, LOW);
	shiftOut(dataPin_2, clockPin_2, LSBFIRST, leds);
	digitalWrite(latchPin_2, HIGH);
	

	delay(1000);

	bitSet(leds, 0);
	
	digitalWrite(latchPin, LOW);
	shiftOut(dataPin, clockPin, LSBFIRST, leds);
	digitalWrite(latchPin, HIGH);

	delay(1000);*/
  
}
