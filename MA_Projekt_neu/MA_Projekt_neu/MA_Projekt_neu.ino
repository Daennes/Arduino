/*
Name:		Sketch1.ino
Created:	20.02.2017 14:08:23
Author:	Dennis
*/

//Zeilen: 8 Stück
int latchPin = 12;
int clockPin = 11;
int dataPin = 13;


//Spalten: 16 Stück
int currentLED = 6;
int currentLED_2 = 3;

int latchPin_2 = 8;
int clockPin_2 = 9;
int dataPin_2 = 7;

//buttons
const int buttonPin_1 = 2;
const int buttonPin_2 = 4;

int zeichenKette[8];

byte tempZeichen_1;
byte tempZeichen_2;

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

	pinMode(buttonPin_1, INPUT);
	pinMode(buttonPin_2, INPUT);

	Serial.begin(9600);

}



//1. 1byte um die länge nach rechts 2tes byte um länge und um 8 nach rechts. Beide loslaufen lassen
//2. Warten bis erstes byte um 8 nach links verschoben wurde und dann zewites byte anfangen loslaufen zu lassen
void Zeichen2_neu(int start, int zeichenlength)		//neu 9.3.17
{
	
	for (int i = 0; i < 8; i++)
	{
		tempZeichen_1 = zeichenKette[i] >> (zeichenlength * 4 - start);
		tempZeichen_2 = zeichenKette[i] >> (zeichenlength * 4 + 8 - start);

		//Serial.println(tempZeichen_1, BIN);
		//Serial.println(tempZeichen_2, BIN);

		//Serial.println(tempZeichen, BIN);

		digitalWrite(latchPin, LOW);
		shiftOut(dataPin, clockPin, LSBFIRST, (0x01 << i));
		digitalWrite(latchPin, HIGH);

		digitalWrite(latchPin_2, LOW);
		shiftOut(dataPin_2, clockPin_2, LSBFIRST, tempZeichen_1);
		shiftOut(dataPin_2, clockPin_2, LSBFIRST, tempZeichen_2);
		digitalWrite(latchPin_2, HIGH);

		//delay(1);
	}
}


void Lauflicht2(String muster)
{
	int zeichenlength = muster.length();
	musterInitZ(muster);
	for (int i = 0; i <(zeichenlength * 4 + 2 * 8); i++)
	{
		for (int k = 0; k<100; k++)
			Zeichen2_neu(i, zeichenlength);
	}
}

void ButtonControl(String muster)
{
	int buttonState[] = { 0,0 };
	int buttonState_old[] = { 0,0 };
	int zeichenlength = muster.length();
	int i = 0;
	musterInitZ(muster);
	Serial.println("hallochen");
	while (true)
	{
		//Serial.println("lol");
		buttonState[0] = digitalRead(buttonPin_1);
		buttonState[1] = digitalRead(buttonPin_2);

		if (buttonState[0] == HIGH && buttonState[0] != buttonState_old[0])
		{
			i++;
			Serial.println(i);
		}

		if (buttonState[1] == HIGH && buttonState[1] != buttonState_old[1])
		{
			i--;
			Serial.println(i);
		}
		Zeichen2_neu(i, zeichenlength);

		buttonState_old[0] = buttonState[0];
		buttonState_old[1] = buttonState[1];

	}
}

//neu 9.3.17
//String max 8 Zeichen, da Int(pro Zeichen 4 bit)
//Init: Erstellt aus Zeichenmuster das Bitmuster für jede Zeile
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
					zeichenKette[j] = fontZahlen[0][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += fontZahlen[0][j];
				}

				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '1')
			{
				if (i == 0)
					zeichenKette[j] = fontZahlen[1][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += fontZahlen[1][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '2')
			{
				if (i == 0)
					zeichenKette[j] = fontZahlen[2][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += fontZahlen[2][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '3')
			{
				if (i == 0)
					zeichenKette[j] = fontZahlen[3][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += fontZahlen[3][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '4')
			{
				if (i == 0)
					zeichenKette[j] = fontZahlen[4][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += fontZahlen[4][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '5')
			{
				if (i == 0)
					zeichenKette[j] = fontZahlen[5][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += fontZahlen[5][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '6')
			{
				if (i == 0)
					zeichenKette[j] = fontZahlen[6][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += fontZahlen[6][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '7')
			{
				if (i == 0)
					zeichenKette[j] = fontZahlen[7][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += fontZahlen[7][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '8')
			{
				if (i == 0)
					zeichenKette[j] = fontZahlen[8][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += fontZahlen[8][j];
				}
				Serial.println(zeichenKette[j], BIN);
				//break;
			}
			else if (zeichen[i] == '9')
			{
				if (i == 0)
					zeichenKette[j] = fontZahlen[9][j];
				else {
					zeichenKette[j] = zeichenKette[j] << 4;
					zeichenKette[j] += fontZahlen[9][j];
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
	Serial.println("Main");
	ButtonControl("0123");

}