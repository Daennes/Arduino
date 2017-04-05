const int tabloHigh = 20;
const int tabloWidth = 20;
struct tablo {
	boolean wert[tabloHigh][tabloWidth];
};
struct tablo myTablo;

const int viewHigh = 8;
const int viewWidth = 16;
struct view {
	boolean wert[viewHigh][viewWidth];
};
struct view myView;

int cursorX = 0;
int cursorY = 0;

String str = "";

int latchPin_1 = 9;
int clockPin_1 = 10;
int dataPin_1 = 8;

int latchPin_2 = 12;
int clockPin_2 = 13;
int dataPin_2 = 11;

//buttons
const int buttonPin_1 = 2; //
const int buttonPin_2 = 5;
const int buttonPin_3 = 4;
const int buttonPin_4 = 3;

int buttonState[] = { 0,0,0,0 };
int buttonState_old[] = { 0,0,0,0 };






void setup() {
	viewInit();

	pinMode(latchPin_1, OUTPUT);
	pinMode(clockPin_1, OUTPUT);
	pinMode(dataPin_1, OUTPUT);

	pinMode(latchPin_2, OUTPUT);
	pinMode(clockPin_2, OUTPUT);
	pinMode(dataPin_2, OUTPUT);

	pinMode(buttonPin_1, INPUT);
	pinMode(buttonPin_2, INPUT);

	pinMode(buttonPin_3, INPUT);
	pinMode(buttonPin_4, INPUT);

	Serial.begin(9600);
	// put your setup code here, to run once:

	makeTest();
	makeView(cursorX, cursorY);

}

void viewInit() {
	for (int i = 0; i < viewHigh; i++) {
		for (int j = 0; j < viewWidth; j++) {
			myView.wert[i][j] = false;
		}
	}

}

void tabloInit(int high, int width) {
	for (int i = 0; i < high; i++) {
		for (int j = 0; j < width; j++) {
			myTablo.wert[i][j] = false;
		}
	}
	if (NULL == myTablo.wert) {
		Serial.print("Tablo init : myTablo = NULL");

	}

}

void makeTest() {
	tabloInit(tabloHigh, tabloWidth);


	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (j % 2 == 0 && i%2 ==0)
			{
				myTablo.wert[i][j] = true;
			}
			else
			{
				myTablo.wert[i][j] = false;
			}
		}
	}
}

void lookupInput() {
	str = "";
	while (Serial.available() > 0) {
		str = Serial.readString();
		Serial.println("I received: ");
		Serial.println(str);
	}
}

void makeTabloBool(String str, int tabloHigh, int tabloWidth) {
	int x = 0;
	int y = 0;
	tabloInit(tabloHigh, tabloWidth);
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '\n') {
			x++;
			y = 0;
		}
		else if (str[i] == 'x') {
			myTablo.wert[x][y] = true;
			y++;
		}
		else if (str[i] == '.') {
			myTablo.wert[x][y] = false;
			y++;
		}
	}
}

void makeView(int cursorX, int cursorY) {
	viewInit();
	if (cursorX >= 0 && cursorX + viewWidth <= tabloWidth) {
		if (cursorY >= 0 && cursorY + viewHigh <= tabloHigh) {
			for (int i = 0; i < viewHigh; i++) {
				for (int j = 0; j < viewWidth; j++) {
					myView.wert[i][j] = myTablo.wert[cursorY + i][cursorX + j];
				}
			}
		}
	}
}

int muster = 0x0;
byte localMuster[2] = { 0x0,0x0 };

void output(struct view myView) {
	muster = 0x0;
	localMuster[0] = 0x0;
	localMuster[1] = 0x0;

	for (int i = 0; i < viewHigh; i++) {

		digitalWrite(latchPin_1, LOW);
		shiftOut(dataPin_1, clockPin_1, LSBFIRST, 0x0);
		digitalWrite(latchPin_1, HIGH);

		for (int j = 0; j < viewWidth; j++) {
			if (myView.wert[i][j] == true) {
				muster = muster << 1;
				muster += 0b1;

			}
			else {
				muster = muster << 1;
			}
		}



		localMuster[0] = muster;
		localMuster[1] = muster >> 8;

		digitalWrite(latchPin_2, LOW);
		shiftOut(dataPin_2, clockPin_2, LSBFIRST, localMuster[0]);
		shiftOut(dataPin_2, clockPin_2, LSBFIRST, localMuster[1]);
		digitalWrite(latchPin_2, HIGH);


		digitalWrite(latchPin_1, LOW);
		shiftOut(dataPin_1, clockPin_1, LSBFIRST, 0x1 << i);
		digitalWrite(latchPin_1, HIGH);

		delay(1);


	}


}

void loop() {

	// put your main code here, to run repeatedly:

	lookupInput();
	if (str != "") {
		if (str == "1") {
			makeTest();
			makeView(cursorX, cursorY);  
		}
		else {
			makeTabloBool(str, tabloHigh, tabloWidth);
			makeView(cursorX, cursorY);
		}
		str = "";
	}


	buttonState[0] = digitalRead(buttonPin_1);
	buttonState[1] = digitalRead(buttonPin_2);
	buttonState[2] = digitalRead(buttonPin_3);
	buttonState[3] = digitalRead(buttonPin_4);

	if (buttonState[0] == HIGH && buttonState[0] != buttonState_old[0] && ((cursorX + viewWidth) < tabloWidth))
	{
		cursorX++;
		makeView(cursorX, cursorY);
	}

	else if (buttonState[1] == HIGH && buttonState[1] != buttonState_old[1] && cursorX>0)
	{
		cursorX--;
		makeView(cursorX, cursorY);
	}

	else if (buttonState[2] == HIGH && buttonState[2] != buttonState_old[2] && ((cursorY + viewHigh) < tabloHigh))
	{
		cursorY++;
		makeView(cursorX, cursorY);
	}

	else if (buttonState[3] == HIGH && buttonState[3] != buttonState_old[3] && cursorY > 0)
	{
		cursorY--;
		makeView(cursorX, cursorY);
	}

	buttonState_old[0] = buttonState[0];
	buttonState_old[1] = buttonState[1];
	buttonState_old[2] = buttonState[2];
	buttonState_old[3] = buttonState[3];



	output(myView);
}


int getHigh(String str) {
	int count = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '\\' && str[i + 1] == 'n') {
			count++;
			break;
		}
	}
	return count;
}

int getWidth(String str) {
	int count = 0;
	for (int i = 0; i < str.length(); i++) {
		count++;
		if (str[i] == '\n') {
			break;
		}
	}
	return count;
}

void outputTablo(struct tablo localTablo, String location) {

	Serial.print("Location : ");
	Serial.println(location);

	int x = 0;
	int y = 0;
	x = sizeof(myTablo) / tabloWidth;
	Serial.print("Tablo High: ");
	Serial.println(x);

	if (x > 0) {
		y = sizeof(myTablo.wert[0]);
		Serial.print("Tablo Width: ");
		Serial.println(y);

	}
	if (x > 0 && y > 0) {
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < y; j++) {
				Serial.print(myTablo.wert[i][j]);
				Serial.print(" ");
			}
			Serial.println();
		}
	}
}

void outputView(struct view localView, String location) {

	Serial.print("Location : ");
	Serial.println(location);

	int x = 0;
	int y = 0;
	x = sizeof(myView) / viewWidth;  //durch view l?nge
	Serial.print("View High: ");
	Serial.println(x);

	if (x > 0) {
		y = sizeof(myView.wert[0]);
		Serial.print("View Width: ");
		Serial.println(y);

	}

	if (x > 0 && y > 0) {
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < y; j++) {
				Serial.print(myView.wert[i][j]);
				Serial.print(" ");
			}
			Serial.println();
		}
	}
}

