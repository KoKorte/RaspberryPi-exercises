#include <signal.h>
#include <stdio.h>
#include <pigpio.h>

// Määritellään käsiteltävä gpio pinni
// Terminaalikomento pinout näyttää raspberryn pinnien järjestyksen
const int LED = 16;
// https://stackoverflow.com/questions/24931456/how-does-sig-atomic-t-actually-work
volatile sig_atomic_t signal_received = 0;

// Signaalin käsittelijä
void sigint_handler (int signal) {
	signal_received = signal;
}
	

int main() {
	printf("\n\nPress ctrl+c to exit\n");
	// Jos raspberryn initialisaatio epäonnistuu, tulostetaan virhe
	if (gpioInitialise() == PI_INIT_FAILED) {
		printf("\n\nERROR: Initialization failed\n");	
		return 1;
	}
	// Käännetään pinni input-moodista output-moodiin
	gpioSetMode(LED, PI_OUTPUT);
	// Haetaan signaalia		
	signal(SIGINT, sigint_handler);
	// Niin kauan kuin signaalia ei ole saatu
	while (!signal_received) {
		// Laitetaan led päälle
		gpioWrite(LED, PI_HIGH);
		// Odotetaan sekunti
		time_sleep(1);
		// Laitetaan led pois päältä
		gpioWrite(LED, PI_LOW);
		// Odotetaan sekunti
		time_sleep(1);
	}
	// Palautetaan pinni takaisin input-moodiin	
	gpioSetMode(LED, PI_INPUT);
	// Katkaistaan gpio-käsittely
	gpioTerminate();
	printf("\n");
	
	return 0;
}
// Suoritettava terminaalissa sudo-komennon kera
