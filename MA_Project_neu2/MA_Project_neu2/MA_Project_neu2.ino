/*
Name:		Sketch1.ino
Created:	20.02.2017 14:08:23
Author:	Dennis
*/




char incomingData;

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
const int buttonPin_3 = 6;
const int buttonPin_4 = 5;

long zeichenKette[8 * 8];

byte tempZeichen_1;
byte tempZeichen_2;

byte font[3][2] = {
	{ 0x05, 0x02 },
	{ 0x02, 0x05 },
	{ 0x07, 0x04 },
};
/*byte fontZahlen[10][8] = {
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
};*/

byte fontZahlen[11][8] = {
	{ 0x00, 0x07, 0x05, 0x05, 0x05, 0x05, 0x05, 0x07 },		//0
	{ 0x00, 0x01, 0x03, 0x05, 0x01, 0x01, 0x01, 0x01 },		//1
	{ 0x00, 0x07, 0x01, 0x01, 0x07, 0x04, 0x04, 0x07 },		//2
	{ 0x00, 0x07, 0x01, 0x01, 0x07, 0x01, 0x01, 0x07 },		//3
	{ 0x00, 0x05, 0x07, 0x05, 0x01, 0x01, 0x01, 0x01 },		//4
	{ 0x00, 0x07, 0x04, 0x04, 0x07, 0x01, 0x01, 0x07 },		//5
	{ 0x00, 0x07, 0x04, 0x04, 0x07, 0x05, 0x05, 0x07 },		//6
	{ 0x00, 0x07, 0x01, 0x01, 0x07, 0x01, 0x01, 0x01 },		//7
	{ 0x00, 0x07, 0x05, 0x05, 0x07, 0x05, 0x05, 0x07 },		//8
	{ 0x00, 0x07, 0x07, 0x05, 0x01, 0x01, 0x01, 0x07 },		//9
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },		//leer
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

	pinMode(buttonPin_3, INPUT);
	pinMode(buttonPin_4, INPUT);

	Serial.begin(9600);

}



//1. 1byte um die länge nach rechts 2tes byte um länge und um 8 nach rechts. Beide loslaufen lassen
//2. Warten bis erstes byte um 8 nach links verschoben wurde und dann zewites byte anfangen loslaufen zu lassen

int start_old = 0;

																//int zeichenlength ist überflüssig kann raus
void Zeichen2_neu(int start, int height, int zeichenlength)		//neu 9.3.17
{
	//Serial.println("Zeichnen:\n");
	for (int i = 0; i < 8; i++)
	{
		//tempZeichen_1 = zeichenKette[i+height] >> (zeichenlength * 4 - start);
		//tempZeichen_2 = zeichenKette[i+height] >> (zeichenlength * 4 + 8 - start);

		tempZeichen_1 = zeichenKette[7-i + height] >> (8 * 4 - 16 - start);
		tempZeichen_2 = zeichenKette[7-i + height] >> (8 * 4 - 8 - start);

		//tempZeichen_1 = zeichenKette[i + height] >> (start);
		//tempZeichen_2 = zeichenKette[i + height] >> (8 - start);

		/*if (start_old != start)
		{
		Serial.println(tempZeichen_1, BIN);
		Serial.println(tempZeichen_2, BIN);
		}*/

		//Serial.println(tempZeichen_1, BIN);
		//Serial.println(tempZeichen_2, BIN);

		//Serial.println(tempZeichen, BIN);

		digitalWrite(latchPin, LOW);
		shiftOut(dataPin, clockPin, LSBFIRST, (0x01 << 7-i));
		digitalWrite(latchPin, HIGH);

		digitalWrite(latchPin_2, LOW);
		shiftOut(dataPin_2, clockPin_2, LSBFIRST, tempZeichen_1);
		shiftOut(dataPin_2, clockPin_2, LSBFIRST, tempZeichen_2);
		digitalWrite(latchPin_2, HIGH);

		//delay(10);
	}
	start_old = start;
}


void Lauflicht2(String muster)
{
	int zeichenlength = muster.length();
	musterInitZ(muster);
	for (int i = 0; i <(zeichenlength * 4 + 2 * 8); i++)
	{
		for (int k = 0; k<100; k++)
			Zeichen2_neu(i, 0, zeichenlength);
	}
}

String str;

void ButtonControl(String muster)
{
	int buttonState[] = { 0,0,0,0 };
	int buttonState_old[] = { 0,0,0,0 };
	int zeichenlength = muster.length();
	int i = 0;
	int height = 0;
	musterInitZ(muster);
	Serial.println("hallochen");
	while (true)
	{
		if (Serial.available() > 0) {
			// read the incoming byte:
			if (Serial.available() > 0)
			{
				str = Serial.readStringUntil('\n');
			}
			//incomingData = Serial.read();

			// say what you got:
			Serial.print("I received: ");
			Serial.println(str);
			musterInitZ(str);
		}


		//Serial.println("lol");
		buttonState[0] = digitalRead(buttonPin_1);
		buttonState[1] = digitalRead(buttonPin_2);
		buttonState[2] = digitalRead(buttonPin_3);
		buttonState[3] = digitalRead(buttonPin_4);

		if (buttonState[0] == HIGH && buttonState[0] != buttonState_old[0] && i < 16)
		{
			i++;
			Serial.println(i);
		}

		if (buttonState[1] == HIGH && buttonState[1] != buttonState_old[1] && i>0)
		{
			i--;
			Serial.println(i);
		}

		if (buttonState[2] == HIGH && buttonState[2] != buttonState_old[2] && height < 32)
		{
			height++;
			Serial.println(height);
		}

		if (buttonState[3] == HIGH && buttonState[3] != buttonState_old[3] && height > 0)
		{
			height--;
			Serial.println(height);
		}

		Zeichen2_neu(i, height, zeichenlength);

		buttonState_old[0] = buttonState[0];
		buttonState_old[1] = buttonState[1];
		buttonState_old[2] = buttonState[2];
		buttonState_old[3] = buttonState[3];

	}
}

void Paint(String muster)
{
	Serial.println("size");
	Serial.println(sizeof(muster));
	int buttonState[] = { 0,0,0,0 };
	int buttonState_old[] = { 0,0,0,0 };
	int zeichenlength = muster.length();
	int i = 0;
	int height = 0;
	String tempStr = "";
	String test[2];
	musterInitPicture(muster);
	Serial.println("hallochen");
	while (true)
	{
		if (Serial.available() > 0) {

			tempStr = "";
			str = "";

			// read the incoming byte:
			if (Serial.available() > 0)
			{
				test[0] = str = Serial.readStringUntil(',');
				test[1] = Serial.readStringUntil(',');
			}
			//incomingData = Serial.read();

			Serial.println("1: ");
			Serial.println(test[0]);
			Serial.println("2: ");
			Serial.println(test[1]);


			// say what you got:
			Serial.println("I received: ");
			Serial.println(str);

			for (int k = 0; k < str.length(); k++)
			{
				if (str[k] == 'X' || str[k] == '.')
				{
					//Serial.println(str[k]);
					tempStr += str[k];
				}
				else if(str[k] == '\n')
				{
					Serial.println("linefeed");
					Serial.println(tempStr.length() % 32);

					for (int n = 0; n < (tempStr.length() % 32); n++)
						tempStr += '.';

				}
			}

			Serial.println("neu: ");
			Serial.println(tempStr);


			musterInitPicture(tempStr);
		}


		//Serial.println("lol");
		buttonState[0] = digitalRead(buttonPin_1);
		buttonState[1] = digitalRead(buttonPin_2);
		buttonState[2] = digitalRead(buttonPin_3);
		buttonState[3] = digitalRead(buttonPin_4);

		if (buttonState[0] == HIGH && buttonState[0] != buttonState_old[0] && i < 16)
		{
			i++;
			Serial.println(i);
		}

		if (buttonState[1] == HIGH && buttonState[1] != buttonState_old[1] && i>0)
		{
			i--;
			Serial.println(i);
		}

		if (buttonState[2] == HIGH && buttonState[2] != buttonState_old[2] && height < 32)
		{
			height++;
			Serial.println(height);
		}

		if (buttonState[3] == HIGH && buttonState[3] != buttonState_old[3] && height > 0)
		{
			height--;
			Serial.println(height);
		}

		Zeichen2_neu(i, height, zeichenlength);

		buttonState_old[0] = buttonState[0];
		buttonState_old[1] = buttonState[1];
		buttonState_old[2] = buttonState[2];
		buttonState_old[3] = buttonState[3];

	}
}


//neu 9.3.17
//String max 8 Zeichen, da Int(pro Zeichen 4 bit)
//Init: Erstellt aus Zeichenmuster das Bitmuster für jede Zeile
void musterInitZ(String zeichen)
{
	Serial.println("Zeichenlange:");
	Serial.println(zeichen.length());

	int zeilen = 0;

	for (int i = 0; i < 64; i++)
	{
		zeichenKette[i] = 0;
	}

	zeilen = zeichen.length() / 8;
	if ((zeichen.length() % 8) > 0)
		zeilen++;
	if (zeilen > 8)
		zeilen--;

	Serial.println(zeilen);

	//Anzahl Zeilen --> Zeilen
	for (int k = 0; k < zeilen; k++)
	{
		for (int j = 0; j < 8; j++)
		{
			Serial.println("Durchgang: ");
			for (int i = 0; i < 8; i++)
			{
				if (zeichen[i + k * 8] == '0')
				{
					if (i == 0)
						zeichenKette[j + k * 8] = fontZahlen[0][j];
					else {
						zeichenKette[j + k * 8] = zeichenKette[j + k * 8] << 4;
						zeichenKette[j + k * 8] += fontZahlen[0][j];
					}

					Serial.println(zeichenKette[j + k * 8], BIN);
					//break;
				}
				else if (zeichen[i + k * 8] == '1')
				{
					if (i == 0)
						zeichenKette[j + k * 8] = fontZahlen[1][j];
					else {
						zeichenKette[j + k * 8] = zeichenKette[j + k * 8] << 4;
						zeichenKette[j + k * 8] += fontZahlen[1][j];
					}
					Serial.println(zeichenKette[j + k * 8], BIN);
					//break;
				}
				else if (zeichen[i + k * 8] == '2')
				{
					if (i == 0)
						zeichenKette[j + k * 8] = fontZahlen[2][j];
					else {
						zeichenKette[j + k * 8] = zeichenKette[j + k * 8] << 4;
						zeichenKette[j + k * 8] += fontZahlen[2][j];
					}
					Serial.println(zeichenKette[j + k * 8], BIN);
					//break;
				}
				else if (zeichen[i + k * 8] == '3')
				{
					if (i == 0)
						zeichenKette[j + k * 8] = fontZahlen[3][j];
					else {
						zeichenKette[j + k * 8] = zeichenKette[j + k * 8] << 4;
						zeichenKette[j + k * 8] += fontZahlen[3][j];
					}
					Serial.println(zeichenKette[j + k * 8], BIN);
					//break;
				}
				else if (zeichen[i + k * 8] == '4')
				{
					if (i == 0)
						zeichenKette[j + k * 8] = fontZahlen[4][j];
					else {
						zeichenKette[j + k * 8] = zeichenKette[j + k * 8] << 4;
						zeichenKette[j + k * 8] += fontZahlen[4][j];
					}
					Serial.println(zeichenKette[j + k * 8], BIN);
					//break;
				}
				else if (zeichen[i + k * 8] == '5')
				{
					if (i == 0)
						zeichenKette[j + k * 8] = fontZahlen[5][j];
					else {
						zeichenKette[j + k * 8] = zeichenKette[j + k * 8] << 4;
						zeichenKette[j + k * 8] += fontZahlen[5][j];
					}
					Serial.println(zeichenKette[j + k * 8], BIN);
					//break;
				}
				else if (zeichen[i + k * 8] == '6')
				{
					if (i == 0)
						zeichenKette[j + k * 8] = fontZahlen[6][j];
					else {
						zeichenKette[j + k * 8] = zeichenKette[j + k * 8] << 4;
						zeichenKette[j + k * 8] += fontZahlen[6][j];
					}
					Serial.println(zeichenKette[j + k * 8], BIN);
					//break;
				}
				else if (zeichen[i + k * 8] == '7')
				{
					if (i == 0)
						zeichenKette[j + k * 8] = fontZahlen[7][j];
					else {
						zeichenKette[j + k * 8] = zeichenKette[j + k * 8] << 4;
						zeichenKette[j + k * 8] += fontZahlen[7][j];
					}
					Serial.println(zeichenKette[j + k * 8], BIN);
					//break;
				}
				else if (zeichen[i + k * 8] == '8')
				{
					if (i == 0)
						zeichenKette[j + k * 8] = fontZahlen[8][j];
					else {
						zeichenKette[j + k * 8] = zeichenKette[j + k * 8] << 4;
						zeichenKette[j + k * 8] += fontZahlen[8][j];
					}
					Serial.println(zeichenKette[j + k * 8], BIN);
					//break;
				}
				else if (zeichen[i + k * 8] == '9')
				{
					if (i == 0)
						zeichenKette[j + k * 8] = fontZahlen[9][j];
					else {
						zeichenKette[j + k * 8] = zeichenKette[j + k * 8] << 4;
						zeichenKette[j + k * 8] += fontZahlen[9][j];
					}
					Serial.println(zeichenKette[j + k * 8], BIN);
					//break;
				}
				else if (zeichen[i + k * 8] == ' ')
				{
					if (i == 0)
						zeichenKette[j + k * 8] = fontZahlen[10][j];
					else {
						zeichenKette[j + k * 8] = zeichenKette[j + k * 8] << 4;
						zeichenKette[j + k * 8] += fontZahlen[10][j];
					}
					Serial.println(zeichenKette[j + k * 8], BIN);
					//break;
				}
				else
					zeichenKette[j + k * 8] = zeichenKette[j + k * 8] << 4;


			}
		}
	}

	Serial.println("zeichenkette1:");
	//Serial.println(zeichenKette[0], BIN);
	Serial.println(zeichenKette[8], BIN);
	Serial.println("zeichenkette1_ende:");

}


void musterInitPicture(String zeichen)
{
	Serial.println("Zeichenlange:");
	Serial.println(zeichen.length());

	int zeilen = 0;

	for (int i = 0; i < 64; i++)
	{
		zeichenKette[i] = 0;
	}

	zeilen = zeichen.length() / 32;
	if ((zeichen.length() % 32) > 0)
		zeilen++;
	if (zeilen > 8)
		zeilen--;

	Serial.println(zeilen);

	//Anzahl Zeilen --> Zeilen
	for (int k = 0; k < zeilen; k++)
	{
		Serial.println("Durchgang: ");
		for (int i = 0; i < 32; i++)
		{
			if (zeichen[i + k * 32] == 'X')
			{
				if (i == 0)
					zeichenKette[k] = 0x1;
				else {
					zeichenKette[k] = zeichenKette[k] << 1;
					zeichenKette[k] += 0x1;
				}

				//Serial.println(zeichenKette[k], BIN);
				//break;
			}
			else if (zeichen[i + k * 32] == '.')
			{
				if (i == 0)
					zeichenKette[k] = 0x0;
				else {
					zeichenKette[k] = zeichenKette[k] << 1;
					zeichenKette[k] += 0x0;
				}
				//Serial.println(zeichenKette[k], BIN);
				//break;
			}
			else if (zeichen[i + k * 32] == '\n')
			{
				//zeichenKette[k] = zeichenKette[k] << 32-i;
				Serial.println("break");
				//zeilen++;
				break;
			}
			else
				zeichenKette[k] = zeichenKette[k] << 1;


		}
		
	}

	Serial.println("zeichenkette1:");
	//Serial.println(zeichenKette[0], BIN);
	Serial.println(zeichenKette[8], BIN);
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
	for (int j = 0; j<16; j++)
		Serial.println(zeichenKette[j], BIN);
	//Serial.println(zeichenKette[1], BIN);

	Serial.println("zeichenkette1_ende:");

}


// the loop function runs over and over again until power down or reset
void loop() {
	//File  file;
	//file.open("C:\ArduinoProjekt\test.txt");
	//ButtonControl("01234");
	Paint(".");
}