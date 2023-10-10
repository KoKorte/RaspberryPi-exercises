#include <signal.h>
#include <stdio.h>
#include <pigpio.h>

//Katodit
const int d4 = 6;
const int d3 = 13;
const int d2 = 16;
const int d1 = 26;

//Anodit
//Luodaan muuttujat vaaka viivat
//a = ylä vaaka, b = keski vaaka, c = ala vaaka
const int a = 17;
const int b = 1;
const int c = 23;
	
//Luodaan muuttujat pysty viivat vasemmalta oikealle, ylhäältä alas
const int d = 25;
const int e = 27;
const int f = 24;
const int g = 22;
	
//Luodaan muuttuja pisteelle
const int p = 5;

// https://stackoverflow.com/questions/24931456/how-does-sig-atomic-t-actually-work
volatile sig_atomic_t signal_received = 0;

// Signaalin käsittelijä
void sigint_handler (int signal) {
	signal_received = signal;
}

//Luodaan funktiot numeroille
void num_0()
{
	gpioWrite(a, PI_HIGH);
	gpioWrite(b, PI_LOW);
	gpioWrite(c, PI_HIGH);
	
	gpioWrite(d, PI_HIGH);
	gpioWrite(e, PI_HIGH);
	gpioWrite(f, PI_HIGH);
	gpioWrite(g, PI_HIGH);
	
	gpioWrite(p, PI_LOW);
}

void num_1()
{
	gpioWrite(a, PI_LOW);
	gpioWrite(b, PI_LOW);
	gpioWrite(c, PI_LOW);
	
	gpioWrite(d, PI_LOW);
	gpioWrite(e, PI_HIGH);
	gpioWrite(f, PI_LOW);
	gpioWrite(g, PI_HIGH);
	
	gpioWrite(p, PI_LOW);
}

void num_2()
{
	gpioWrite(a, PI_HIGH);
	gpioWrite(b, PI_HIGH);
	gpioWrite(c, PI_HIGH);
	
	gpioWrite(d, PI_LOW);
	gpioWrite(e, PI_HIGH);
	gpioWrite(f, PI_HIGH);
	gpioWrite(g, PI_LOW);
	
	gpioWrite(p, PI_LOW);
}

void num_3()
{
	gpioWrite(a, PI_HIGH);
	gpioWrite(b, PI_HIGH);
	gpioWrite(c, PI_HIGH);
	
	gpioWrite(d, PI_LOW);
	gpioWrite(e, PI_HIGH);
	gpioWrite(f, PI_LOW);
	gpioWrite(g, PI_HIGH);
	
	gpioWrite(p, PI_LOW);
}

void num_4()
{
	gpioWrite(a, PI_LOW);
	gpioWrite(b, PI_HIGH);
	gpioWrite(c, PI_LOW);
	
	gpioWrite(d, PI_HIGH);
	gpioWrite(e, PI_HIGH);
	gpioWrite(f, PI_LOW);
	gpioWrite(g, PI_HIGH);
	
	gpioWrite(p, PI_LOW);
}

void num_5()
{
	gpioWrite(a, PI_HIGH);
	gpioWrite(b, PI_HIGH);
	gpioWrite(c, PI_HIGH);
	
	gpioWrite(d, PI_HIGH);
	gpioWrite(e, PI_LOW);
	gpioWrite(f, PI_LOW);
	gpioWrite(g, PI_HIGH);
	
	gpioWrite(p, PI_LOW);
}

void num_6()
{
	gpioWrite(a, PI_HIGH);
	gpioWrite(b, PI_HIGH);
	gpioWrite(c, PI_HIGH);
	
	gpioWrite(d, PI_HIGH);
	gpioWrite(e, PI_LOW);
	gpioWrite(f, PI_HIGH);
	gpioWrite(g, PI_HIGH);
	
	gpioWrite(p, PI_HIGH);
}

void num_7()
{
	gpioWrite(a, PI_HIGH);
	gpioWrite(b, PI_LOW);
	gpioWrite(c, PI_LOW);
	
	gpioWrite(d, PI_LOW);
	gpioWrite(e, PI_HIGH);
	gpioWrite(f, PI_LOW);
	gpioWrite(g, PI_HIGH);
	
	gpioWrite(p, PI_LOW);
}

void num_8()
{
	gpioWrite(a, PI_HIGH);
	gpioWrite(b, PI_HIGH);
	gpioWrite(c, PI_HIGH);
	
	gpioWrite(d, PI_HIGH);
	gpioWrite(e, PI_HIGH);
	gpioWrite(f, PI_HIGH);
	gpioWrite(g, PI_HIGH);
	
	gpioWrite(p, PI_LOW);
}

void num_9()
{
	gpioWrite(a, PI_HIGH);
	gpioWrite(b, PI_HIGH);
	gpioWrite(c, PI_LOW);
	
	gpioWrite(d, PI_HIGH);
	gpioWrite(e, PI_HIGH);
	gpioWrite(f, PI_LOW);
	gpioWrite(g, PI_HIGH);
	
	gpioWrite(p, PI_HIGH);
}

void setup()
{
	gpioSetMode(d4, PI_OUTPUT);
	gpioSetMode(d3, PI_OUTPUT);
	gpioSetMode(d2, PI_OUTPUT);
	gpioSetMode(d1, PI_OUTPUT);
	
	gpioSetMode(a, PI_OUTPUT);
	gpioSetMode(b, PI_OUTPUT);
	gpioSetMode(c, PI_OUTPUT);
	gpioSetMode(d, PI_OUTPUT);
	gpioSetMode(e, PI_OUTPUT);
	gpioSetMode(f, PI_OUTPUT);
	gpioSetMode(g, PI_OUTPUT);
	gpioSetMode(p, PI_OUTPUT);
}

void loppu()
{
	gpioSetMode(d4, PI_INPUT);
	gpioWrite(d4, PI_LOW);
	gpioSetMode(d3, PI_INPUT);
	gpioWrite(d3, PI_LOW);
	gpioSetMode(d2, PI_INPUT);
	gpioWrite(d2, PI_LOW);
	gpioSetMode(d1, PI_INPUT);
	gpioWrite(d1, PI_LOW);
	
	gpioSetMode(a, PI_INPUT);
	gpioWrite(a, PI_LOW);
	gpioSetMode(b, PI_INPUT);
	gpioWrite(b, PI_LOW);
	gpioSetMode(c, PI_INPUT);
	gpioWrite(c, PI_LOW);
	gpioSetMode(d, PI_INPUT);
	gpioWrite(d, PI_LOW);
	gpioSetMode(e, PI_INPUT);
	gpioWrite(e, PI_LOW);
	gpioSetMode(f, PI_INPUT);
	gpioWrite(f, PI_LOW);
	gpioSetMode(g, PI_INPUT);
	gpioWrite(g, PI_LOW);
	gpioSetMode(p, PI_INPUT);
	gpioWrite(p, PI_LOW);
}
/*
void display()
{
	gpioWrite(d1, PI_HIGH);
	gpioWrite(d2, PI_HIGH);
	gpioWrite(d3, PI_HIGH);
	gpioWrite(d4, PI_HIGH);
}
*/
void change(int var)
{
	switch(var)
	{
		case 1:
			gpioWrite(d1, PI_LOW);
			gpioWrite(d2, PI_HIGH);
			gpioWrite(d3, PI_HIGH);
			gpioWrite(d4, PI_HIGH);
			break;
		case 2:
			gpioWrite(d1, PI_HIGH);
			gpioWrite(d2, PI_LOW);
			gpioWrite(d3, PI_HIGH);
			gpioWrite(d4, PI_HIGH);
			break;
		case 3:
			gpioWrite(d1, PI_HIGH);
			gpioWrite(d2, PI_HIGH);
			gpioWrite(d3, PI_LOW);
			gpioWrite(d4, PI_HIGH);
			break;
		case 4:
			gpioWrite(d1, PI_HIGH);
			gpioWrite(d2, PI_HIGH);
			gpioWrite(d3, PI_HIGH);
			gpioWrite(d4, PI_LOW);
			break;
		default:
			gpioWrite(d1, PI_HIGH);
			gpioWrite(d2, PI_HIGH);
			gpioWrite(d3, PI_HIGH);
			gpioWrite(d4, PI_HIGH);
			break;
	}
}

int main()
{
	printf("\n\nPress ctrl+c to exit\n");
	// Jos raspberryn initialisaatio epäonnistuu, tulostetaan virhe
	if (gpioInitialise() == PI_INIT_FAILED) {
		printf("\n\nERROR: Initialization failed\n");	
		return 1;
	}
	setup();
//	display();
	signal(SIGINT, sigint_handler);
	while (!signal_received)
	{
		
			change(1);
			num_1();
			time_sleep(1);
		
			change(2);
			num_2();
			time_sleep(1);
		
			change(3);
			num_3();
			time_sleep(1);
		
			change(4);
			num_4();
			time_sleep(1);
			break;
		
	}
	loppu();
	
	gpioTerminate();
	printf("\n");

	return 0;
}
