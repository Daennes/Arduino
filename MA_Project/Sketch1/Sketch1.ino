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

int zeichenKette[8];

byte font[3][2] = {
	{ 0x05, 0x02 },  
	{ 0x02, 0x05 },  
	{ 0x07, 0x04 }, 
};
byte fontZahlen[10][8] = {
	{ 0x07, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x07 },		//0
	{ 0x01, 0x01, 0x01, 0x01, 0x01, 0x05, 0x03, 0x01 },		//1
	{ 0x07, 0x04, 0x04, 0x04, 0x07, 0x01, 0x01, 0x07 },		//2
	{ 0x07, 0x01, 0x01, 0x01, 0x07, 0x01, 0x01, 0x07 },		//3
	{ 0x01, 0x01, 0x01, 0x01, 0x07, 0x05, 0x05, 0x05 },		//5
	{ 0x07, 0x01, 0x01, 0x01, 0x07, 0x04, 0x04, 0x07 },		//5
	{ 0x07, 0x05, 0x05, 0x05, 0x07, 0x04, 0x04, 0x07 },		//6
	{ 0x01, 0x01, 0x01, 0x01, 0x01, 0x05, 0x05, 0x07 },		//7
	{ 0x07, 0x05, 0x05, 0x05, 0x07, 0x05, 0x05, 0x07 },		//8
	{ 0x07, 0x01, 0x01, 0x01, 0x07, 0x05, 0x05, 0x07 },		//9
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

void musterInit(String zeichen)
{
	Serial.println("Zeichenlange:");
	Serial.println(zeichen.length());


	zeichenKette[0] = 0;
	zeichenKette[1] = 0;					//Anzahl Zeilen --> Zeilen
	for (int j = 0; j < 2; j++)
	{
		Serial.println("Durchgang: ");
		for (int i = 0; i < zeichen.length(); i++)
		{
			if (zeichen[i] == '0')
			{
				if (i == 0)
					zeichenKette[j] = font[0][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += font[0][j];
				}

				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '1')
			{
				if (i == 0)
					zeichenKette[j] = font[1][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += font[1][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '2')
			{
				if (i == 0)
					zeichenKette[j] = font[2][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += font[2][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}


		}
	}

	Serial.println("zeichenkette1:");
	Serial.println(zeichenKette[0], BIN);
	Serial.println(zeichenKette[1], BIN);
	Serial.println("zeichenkette1_ende:");

}


void Zeichen2(int start)
{
	byte tempZeichen;
	for (int i = 0; i < 2; i++)
	{
		tempZeichen = zeichenKette[i] >> (8-start);

		Serial.println(tempZeichen, BIN);

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
	musterInit("012");
	for (int i = 0; i < 2*8; i++)
	{
		for(int k =0; k<100; k++)
			Zeichen2(i);
	}
}

//String max 4 Zeichen, da Int
void musterInitZ(String zeichen)
{
	Serial.println("Zeichenlange:");
	Serial.println(zeichen.length());

	for (int i = 0; i < 8; i++)
	{
		zeichenKette[i] = 0;
	}
					//Anzahl Zeilen --> Zeilen
	for (int j = 0; j < 8; j++)
	{
		Serial.println("Durchgang: ");
		for (int i = 0; i < zeichen.length(); i++)
		{
			if (zeichen[i] == '0')
			{
				if (i == 0)
					zeichenKette[j] = font[0][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += font[0][j];
				}

				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '1')
			{
				if (i == 0)
					zeichenKette[j] = font[1][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += font[1][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '2')
			{
				if (i == 0)
					zeichenKette[j] = font[2][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += font[2][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '3')
			{
				if (i == 0)
					zeichenKette[j] = font[3][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += font[3][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '4')
			{
				if (i == 0)
					zeichenKette[j] = font[4][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += font[4][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '5')
			{
				if (i == 0)
					zeichenKette[j] = font[5][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += font[5][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '6')
			{
				if (i == 0)
					zeichenKette[j] = font[6][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += font[6][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '7')
			{
				if (i == 0)
					zeichenKette[j] = font[7][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += font[7][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '8')
			{
				if (i == 0)
					zeichenKette[j] = font[8][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += font[8][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '9')
			{
				if (i == 0)
					zeichenKette[j] = font[9][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += font[9][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}


		}
	}

	Serial.println("zeichenkette1:");
	Serial.println(zeichenKette[0], BIN);
	Serial.println(zeichenKette[1], BIN);
	Serial.println("zeichenkette1_ende:");

}

void musterInitZ_test(String zeichen)
{
	Serial.println("Zeichenlange:");
	Serial.println(zeichen.length());

	for (int i = 0; i < 8; i++)
	{
		zeichenKette[i] = 0;
	}
	//Anzahl Zeilen --> Zeilen
	for (int j = 0; j < 8; j++)
	{
		Serial.println("Durchgang: ");
		for (int i = 0; i < zeichen.length(); i++)
		{

				if (i == 0)
					zeichenKette[j] = font[(int)zeichen[i]][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += font[(int)zeichen[i]][j];
				}

				Serial.println(zeichenKette[j], BIN);

			


		}
	}

	Serial.println("zeichenkette1:");
	Serial.println(zeichenKette[0], BIN);
	Serial.println(zeichenKette[1], BIN);
	Serial.println("zeichenkette1_ende:");

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
