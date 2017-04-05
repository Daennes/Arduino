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
const int buttonPin_1 = 2;
const int buttonPin_2 = 5;
const int buttonPin_3 = 3;
const int buttonPin_4 = 4;

int buttonState[] = { 0,0,0,0 };
int buttonState_old[] = { 0,0,0,0 };





void setup() {
  myView = viewInit();

  pinMode(latchPin_1, OUTPUT);
  pinMode(clockPin_1 ,OUTPUT);
  pinMode(dataPin_1 ,OUTPUT);

  pinMode(latchPin_2 ,OUTPUT);
  pinMode(clockPin_2 ,OUTPUT);
  pinMode(dataPin_2 ,OUTPUT);

  pinMode(buttonPin_1, INPUT);
  pinMode(buttonPin_2, INPUT);

  pinMode(buttonPin_3, INPUT);
  pinMode(buttonPin_4, INPUT);

  Serial.begin(9600);
  // put your setup code here, to run once:

}

struct view viewInit() {
  struct view localView;
  for (int i = 0 ; i < viewHigh ; i++) {
    for (int j = 0 ; j < viewWidth ; j++) {
      localView.wert[i][j] = false;
    }
  }

  /*Serial.print("View init : ");
  for (int i = 0; i < viewHigh; i++) {
	  for (int j = 0; j < viewWidth; j++) {
		  Serial.print(localView.wert[i][j]);
	  }
	  Serial.println();
  }*/
//  outputView(localView, "myViewInit");
  return localView;
}

struct tablo tabloInit(int high, int width) {
  struct tablo localTablo;
  /*localTablo.wert = malloc(high * sizeof(boolean *));
  for (int i = 0 ; i < high ; i++) {
    localTablo.wert[i] = malloc(sizeof(boolean) * width);
  }*/
  for (int i = 0 ; i < high ; i++) {
    for (int j = 0 ; j < width ; j++) {
      localTablo.wert[i][j] = false;
    }
  }
  if (NULL == localTablo.wert) {
    Serial.print("Tablo init : localTablo = NULL");
    
  }
  Serial.print("Tablo init : ");
  for (int i = 0 ; i < high ; i++) {
    for (int j = 0 ; j < width ; j++) {
      Serial.print(localTablo.wert[i][j]);
    }
    Serial.println();
  }

//  outputTablo(localTablo, "tabloInit");
  return localTablo;
}

struct tablo makeTest() {
  struct tablo localTablo = tabloInit(tabloHigh, tabloWidth);

  Serial.println("makeTest");

  localTablo.wert[0][0] = true;
  localTablo.wert[1][1] = true;
  localTablo.wert[2][2] = true;
  localTablo.wert[3][3] = true;
  localTablo.wert[4][4] = true;
  localTablo.wert[5][5] = true;
  localTablo.wert[6][6] = true;
  localTablo.wert[7][7] = true;

  localTablo.wert[0][15] = true;
  localTablo.wert[1][14] = true;
  localTablo.wert[2][13] = true;
  localTablo.wert[3][12] = true;
  localTablo.wert[4][11] = true;
  localTablo.wert[5][10] = true;
  localTablo.wert[6][9] = true;
  localTablo.wert[7][8] = true;

//  outputTablo(localTablo, "makeTest");
  return localTablo;
}

String lookupInput() {
  String str = "";
  if (Serial.available() > 0) {
    str = Serial.readString();
    Serial.print("I received: ");
    Serial.println(str);
  }
  return str;
}

struct tablo makeTabloBool(String str, int tabloHigh, int tabloWidth) {
  int x = 0;
  int y = 0;
  Serial.println("makeTabloBool:");
  struct tablo localTablo = tabloInit(tabloHigh, tabloWidth);
  for (int i = 0 ; i < str.length() ; i++) {
	  Serial.print(str[i]);
    if (str[i] == "\\n") {
      x++;
      y=0;
    } else if (str[i] == 'x') {
      localTablo.wert[x][y] = true;
      y++;
    } else if (str[i] == '.') {
      localTablo.wert[x][y] = false;
      y++;      
    }
  
	outputTablo(localTablo, "makeTabloBool");
  return localTablo;
}

struct view makeView(struct tablo myTablo, int cursorX, int cursorY) {
  struct view localView;
  localView = viewInit();
  if (cursorX >= 0 && cursorX + viewWidth <= tabloWidth) {		//kleiner gleich eingefügt, weil Rand ist zulässig
    if (cursorY >= 0 && cursorY + viewHigh <= tabloHigh) {
      for (int i = 0 ; i < viewHigh ; i++) {
        for (int j = 0 ; j < viewWidth ; j++) {
          localView.wert[i][j] = myTablo.wert[cursorX + i][cursorY + j];
        }
      }
    }
  }

  //Serial.println("MakeView : ");
  /*for (int i = 0; i < viewHigh; i++) {
	  for (int j = 0; j < viewWidth; j++) {
		  Serial.print(localView.wert[i][j]);
	  }
	  Serial.println();
  }*/
  return localView;
}


void output(struct view myView) {
  int muster = 0x0;
  byte localMuster[2] = { 0x0,0x0 };
 
  for (int i = 0 ; i < viewHigh ; i++) {
    
    digitalWrite(latchPin_1, LOW);
    shiftOut(dataPin_1, clockPin_1, LSBFIRST, 0x0);
    digitalWrite(latchPin_1, HIGH);
    
    for (int j = 0 ; j < viewWidth ; j++) {
      if (myView.wert[i][j] == true) {
		  muster = muster << 1;
		  muster += 0b1;
		  
      } else {
		  muster = muster << 1;
      }
    }

	

	localMuster[0] = muster;
	localMuster[1] = muster>>8;

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
	
  str = lookupInput();
  Serial.println(str);
  if (str != "") {
    if (str == "1") {
      Serial.println("str = 1");
      myTablo = makeTest();
      myView = makeView(myTablo, cursorX, cursorY); 
   
    } else {
      myTablo = makeTabloBool(str, tabloHigh, tabloWidth);
      myView = makeView(myTablo, cursorX, cursorY);
    }
    str = "";
  }


  buttonState[0] = digitalRead(buttonPin_1);
  buttonState[1] = digitalRead(buttonPin_2);
  buttonState[2] = digitalRead(buttonPin_3);
  buttonState[3] = digitalRead(buttonPin_4);

  if (buttonState[0] == HIGH && buttonState[0] != buttonState_old[0] && (cursorX + viewWidth < tabloWidth))
  {
	  cursorX++;
	  myView = makeView(myTablo, cursorX, cursorY);
  }

  else if (buttonState[1] == HIGH && buttonState[1] != buttonState_old[1] && cursorX>0)
  {
	  cursorX--;
	  myView = makeView(myTablo, cursorX, cursorY);
  }

  else if (buttonState[2] == HIGH && buttonState[2] != buttonState_old[2] && (cursorY+viewHigh < tabloHigh))
  {
	  cursorY++;
	  myView = makeView(myTablo, cursorX, cursorY);
  }

  else if (buttonState[3] == HIGH && buttonState[3] != buttonState_old[3] && cursorY > 0)
  {
	  cursorY--;
	  myView = makeView(myTablo, cursorX, cursorY);
  }

  buttonState_old[0] = buttonState[0];
  buttonState_old[1] = buttonState[1];
  buttonState_old[2] = buttonState[2];
  buttonState_old[3] = buttonState[3];



  output(myView);
}


int getHigh(String str) {
  int count = 0;
  for (int i = 0 ; i < str.length() ; i++) {
    if (str[i] == '\\' && str[i+1] == 'n') {
      count++;
      break;
    }
  }
  return count;
}

int getWidth(String str) {
  int count = 0;
  for (int i = 0 ; i < str.length() ; i++) {
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
  x = sizeof(localTablo)/tabloWidth;
  Serial.print("Tablo High: ");
  Serial.println(x);

  if (x > 0) {
    y = sizeof(localTablo.wert[0]);
    Serial.print("Tablo Width: ");
    Serial.println(y);
    
  }
  if (x > 0 && y > 0 ) {
    for (int i = 0 ; i < x ; i++) {
      for (int j = 0 ; j < y ; j++) {
        Serial.print(localTablo.wert[i][j]);
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
  x = sizeof(localView)/16;  //durch view länge
  Serial.print("View High: ");
  Serial.println(x);

  if (x > 0) {
    y = sizeof(localView.wert[0]);
    Serial.print("View Width: ");
    Serial.println(y);
    
  }
  
  if (x > 0 && y > 0 ) {
    for (int i = 0 ; i < x ; i++) {
      for (int j = 0 ; j < y ; j++) {
        Serial.print(localView.wert[i][j]);
        Serial.print(" ");
      }
        Serial.println();
    }
  }  
}


