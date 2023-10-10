#include <signal.h>
#include <stdio.h>
#include <pigpio.h>

//Luodaan muuttujat vaaka viivat
//a = ylä vaaka, b = keski vaaka, c = ala vaaka
const int a = 22;
const int b = 27;
const int c = 25;
	
//Luodaan muuttujat pysty viivat vasemmalta oikealle, ylhäältä alas
const int d = 17;
const int e = 24;
const int f = 23;
const int g = 16;
	
//Luodaan muuttuja pisteelle
const int p = 26;

// https://stackoverflow.com/questions/24931456/how-does-sig-atomic-t-actually-work
volatile sig_atomic_t signal_received = 0;

// Signaalin käsittelijä
void sigint_handler (int signal) {
	signal_received = signal;
}

//Luodaan funktio joka muuttaa pinnit output tilaan
void setup()
{
	gpioSetMode(a, PI_OUTPUT);
	gpioSetMode(b, PI_OUTPUT);
	gpioSetMode(c, PI_OUTPUT);
	gpioSetMode(d, PI_OUTPUT);
	gpioSetMode(e, PI_OUTPUT);
	gpioSetMode(f, PI_OUTPUT);
	gpioSetMode(g, PI_OUTPUT);
	gpioSetMode(p, PI_OUTPUT);
}

//Luodaan funktiot numeroille
void nolla()
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

void yksi()
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

void kaksi()
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

void kolme()
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

void nelja()
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

void viisi()
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

void kuusi()
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

void seitseman()
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

void kahdeksan()
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

void yhdeksan()
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


//Luodaan funktio, joka nollaa numeron 9 jälkeen
void loppu()
{
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


int main()
{	
	printf("\n\nPress ctrl+c to exit\n");
	// Jos raspberryn initialisaatio epäonnistuu, tulostetaan virhe
	if (gpioInitialise() == PI_INIT_FAILED) {
		printf("\n\nERROR: Initialization failed\n");	
		return 1;
	}
	setup();
	signal(SIGINT, sigint_handler);
	while (!signal_received)
	{
		nolla();
		time_sleep(1);
		
		yksi();
		time_sleep(1);
		
		kaksi();
		time_sleep(1);
		
		kolme();
		time_sleep(1);
		
		nelja();
		time_sleep(1);
		
		viisi();
		time_sleep(1);
		
		kuusi();
		time_sleep(1);
		
		seitseman();
		time_sleep(1);
		
		kahdeksan();
		time_sleep(1);
		
		yhdeksan();
		time_sleep(1);
		break;
	}
	loppu();
	
	gpioTerminate();
	printf("\n");
	
	return 0;
}
