#include <signal.h>
#include <stdio.h>
#include <pigpio.h>

//Määritetään red, green, blue pinnit
const int r = 27;
const int g = 17;
const int b = 22;


// https://stackoverflow.com/questions/24931456/how-does-sig-atomic-t-actually-work
volatile sig_atomic_t signal_received = 0;

// Signaalin käsittelijä
void sigint_handler (int signal) {
	signal_received = signal;
}

void setup()
{
	gpioSetMode(r, PI_OUTPUT);
	gpioSetMode(g, PI_OUTPUT);
	gpioSetMode(b, PI_OUTPUT);
}

void end()
{
	gpioSetMode(r, PI_INPUT);
	gpioWrite(r, PI_LOW);
	gpioSetMode(g, PI_INPUT);
	gpioWrite(g, PI_LOW);
	gpioSetMode(b, PI_INPUT);
	gpioWrite(b, PI_LOW);
}

int main()
{
	printf("\n\nPress ctrl+c to exit\n");
	// Jos raspberryn initialisaatio epäonnistuu, tulostetaan virhe
	if (gpioInitialise() == PI_INIT_FAILED) 
	{
		printf("\n\nERROR: Initialization failed\n");	
		return 1;
		
	}
	// Haetaan signaalia		
	signal(SIGINT, sigint_handler);
	// Niin kauan kuin signaalia ei ole saatu
	while (!signal_received) {
		//Pelkkä punainen
		gpioWrite(r, PI_HIGH);
		time_sleep(1);
		gpioWrite(r, PI_LOW);
		
		//Punainen ja vihreä yhdessä
		gpioWrite(r, PI_HIGH);
		time_sleep(1);	
		gpioWrite(g, PI_HIGH);
		time_sleep(1);
		gpioWrite(r, PI_LOW);
		gpioWrite(g, PI_LOW);
		
		//Pelkkä vihreä
		gpioWrite(g, PI_HIGH);
		time_sleep(1);
		gpioWrite(g, PI_LOW);
		
		//Vihreä ja sininen yhdessä
		gpioWrite(g, PI_HIGH);
		time_sleep(1);	
		gpioWrite(b, PI_HIGH);
		time_sleep(1);
		gpioWrite(g, PI_LOW);
		gpioWrite(b, PI_LOW);
		
		//Pelkkä sininen
		gpioWrite(b, PI_HIGH);
		time_sleep(1);
		gpioWrite(b, PI_LOW);
		
		//Sininen ja punainen yhdessä
		gpioWrite(b, PI_HIGH);
		time_sleep(1);	
		gpioWrite(r, PI_HIGH);
		time_sleep(1);
		gpioWrite(b, PI_LOW);
		gpioWrite(r, PI_LOW);
		}
	
	end();	
	gpioTerminate();
	printf("\n");

	return 0;
}
