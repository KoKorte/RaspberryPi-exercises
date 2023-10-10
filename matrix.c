#include <signal.h>
#include <stdio.h>
#include <pigpio.h>

//Määritellään vaakarivi x
const int xa = 0;
const int xb = 25;
const int xc = 1;
const int xd = 6;
const int xe = 20;
const int xf = 13;
const int xg = 27;
const int xh = 17;

//Määritellään pystyrivi y
const int ya = 19;
const int yb = 22;
const int yc = 26;
const int yd = 5;
const int ye = 23;
const int yf = 21;
const int yg = 24;
const int yh = 16;

//Luodaan x ja y arrayt
const char xarray[] = {xa,xb,xc,xd,xe,xf,xg,xh};
const char yarray[] = {ya,yb,yc,yd,ye,yf,yg,yh};

// https://stackoverflow.com/questions/24931456/how-does-sig-atomic-t-actually-work
volatile sig_atomic_t signal_received = 0;

// Signaalin käsittelijä
void sigint_handler (int signal) {
	signal_received = signal;
}

void start()
{
	gpioSetMode(xa, PI_OUTPUT);
	gpioSetMode(xb, PI_OUTPUT);
	gpioSetMode(xc, PI_OUTPUT);
	gpioSetMode(xd, PI_OUTPUT);
	gpioSetMode(xe, PI_OUTPUT);
	gpioSetMode(xf, PI_OUTPUT);
	gpioSetMode(xg, PI_OUTPUT);
	gpioSetMode(xh, PI_OUTPUT);
	
	gpioSetMode(ya, PI_OUTPUT);
	gpioSetMode(yb, PI_OUTPUT);
	gpioSetMode(yc, PI_OUTPUT);
	gpioSetMode(yd, PI_OUTPUT);
	gpioSetMode(ye, PI_OUTPUT);
	gpioSetMode(yf, PI_OUTPUT);
	gpioSetMode(yg, PI_OUTPUT);
	gpioSetMode(yh, PI_OUTPUT);
}

void end()
{
	gpioSetMode(xa, PI_INPUT);
	gpioSetMode(xa, PI_LOW);
	gpioSetMode(xb, PI_INPUT);
	gpioSetMode(xb, PI_LOW);
	gpioSetMode(xc, PI_INPUT);
	gpioSetMode(xc, PI_LOW);
	gpioSetMode(xd, PI_INPUT);
	gpioSetMode(xd, PI_LOW);
	gpioSetMode(xe, PI_INPUT);
	gpioSetMode(xe, PI_LOW);
	gpioSetMode(xf, PI_INPUT);
	gpioSetMode(xf, PI_LOW);
	gpioSetMode(xg, PI_INPUT);
	gpioSetMode(xg, PI_LOW);
	gpioSetMode(xh, PI_INPUT);
	gpioSetMode(xh, PI_LOW);
	
	gpioSetMode(ya, PI_INPUT);
	gpioSetMode(ya, PI_LOW);
	gpioSetMode(yb, PI_INPUT);
	gpioSetMode(yb, PI_LOW);
	gpioSetMode(yc, PI_INPUT);
	gpioSetMode(yc, PI_LOW);
	gpioSetMode(yd, PI_INPUT);
	gpioSetMode(yd, PI_LOW);
	gpioSetMode(ye, PI_INPUT);
	gpioSetMode(ye, PI_LOW);
	gpioSetMode(yf, PI_INPUT);
	gpioSetMode(yf, PI_LOW);
	gpioSetMode(yg, PI_INPUT);
	gpioSetMode(yg, PI_LOW);
	gpioSetMode(yh, PI_INPUT);
	gpioSetMode(yh, PI_LOW);
}



int main()
{	
	printf("\n\nPress ctrl+c to exit\n");
	// Jos raspberryn initialisaatio epäonnistuu, tulostetaan virhe
	if (gpioInitialise() == PI_INIT_FAILED) {
		printf("\n\nERROR: Initialization failed\n");	
		return 1;
	}
	//Asetetaan kaikki pinnit outputiksi
	start();
	while (!signal_received) 
	{
		gpioWrite(xa, PI_HIGH);
		gpioWrite(xb, PI_HIGH);
		gpioWrite(xc, PI_HIGH);
		gpioWrite(xd, PI_LOW);
		gpioWrite(xe, PI_LOW);
		gpioWrite(xf, PI_HIGH);
		gpioWrite(xg, PI_HIGH);
		gpioWrite(xh, PI_LOW);
		
		gpioWrite(ya, PI_LOW);
		gpioWrite(yb, PI_LOW);
		gpioWrite(yc, PI_LOW);
		gpioWrite(yd, PI_LOW);
		gpioWrite(ye, PI_LOW);
		gpioWrite(yf, PI_LOW);
		gpioWrite(yg, PI_LOW);
		gpioWrite(yh, PI_HIGH);
		time_sleep(1);
		break;
	}	

	//Asetetaan kaikki pinnit inputiksi
	end();
	gpioTerminate();
	printf("\n");
	return 0;
}
