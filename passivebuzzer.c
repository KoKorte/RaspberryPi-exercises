#include <signal.h>
#include <stdio.h>
#include <pigpio.h>

// https://stackoverflow.com/questions/24931456/how-does-sig-atomic-t-actually-work
volatile sig_atomic_t signal_received = 0;

const int SUMMERI = 16;

// Signaalin käsittelijä
void sigint_handler (int signal) {
	signal_received = signal;
}

int main()
{	
	// int val = 0, test = 0;
	printf("\n\nPress ctrl+c to exit\n");
	// Jos raspberryn initialisaatio epäonnistuu, tulostetaan virhe
	if (gpioInitialise() == PI_INIT_FAILED) 
	{
		printf("\n\nERROR: Initialization failed\n");	
		return 1;
	}
	signal(SIGINT, sigint_handler);
	while (!signal_received) 
	{
		//Luodaan for looppi jossa summeri komponentti piippaa 5 kertaa
		for (int i = 0; i < 5; i++)
		{
			gpioSetMode(SUMMERI, PI_OUTPUT);
			gpioWrite(SUMMERI, PI_HIGH);	
			time_sleep(1);
			
			gpioWrite(SUMMERI, PI_LOW);	
			gpioSetMode(SUMMERI, PI_INPUT);
			time_sleep(1);
		}

	}
	
	gpioWrite(SUMMERI, PI_LOW);	
	gpioSetMode(SUMMERI, PI_INPUT);

	gpioTerminate();
	printf("\n");
	
	return 0;
}
