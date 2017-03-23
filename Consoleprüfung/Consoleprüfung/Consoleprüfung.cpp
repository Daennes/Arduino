// Consoleprüfung.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"


void p1(int * x)
{
	x = x + 1;
}

void p2(int &x)
{
	x = x + 1;
}

void p3(int x)
{

}

int main()
{
	int x = 0;

	p1(&x);
	printf("%d", x);
	p2(x);
	printf("%d", x);
	p3(x);
	printf("%d", x);

	//p2(x);




    return 0;
}

