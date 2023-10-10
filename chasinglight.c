#include <signal.h>
#include <stdio.h>
#include <pigpio.h>

// Määritellään käsiteltävät gpio pinnit
// Terminaalikomento pinout näyttää raspberryn pinnien järjestyksen
const int LED[] = {16,24,23,22,27};
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
	// Käännetään pinnit input-moodista output-moodiin
	for (int i=0; i<5; i++) {
		gpioSetMode(LED[i], PI_OUTPUT);
	}
	// Haetaan signaalia		
	signal(SIGINT, sigint_handler);
	// Niin kauan kuin signaalia ei ole saatu
	while (!signal_received) {
		for (int i=0; i<5; i++) {
			// Laitetaan led päälle
			gpioWrite(LED[i], PI_HIGH);
			// Odotetaan sekunti
			time_sleep(0.2);
			// Laitetaan led pois päältä
			gpioWrite(LED[i], PI_LOW);
		}
		for (int i=3; i>0; i--) {
			// Laitetaan led päälle
			gpioWrite(LED[i], PI_HIGH);
			// Odotetaan sekunti
			time_sleep(0.2);
			// Laitetaan led pois päältä
			gpioWrite(LED[i], PI_LOW);
		}
		
	}
	// Palautetaan pinni takaisin input-moodiin	
	for (int i=0;i<5;i++) {
		gpioSetMode(LED[i], PI_INPUT);
	}
	// Katkaistaan gpio-käsittely
	gpioTerminate();
	printf("\n");
	
	return 0;
}
// Suoritettava terminaalissa sudo-komennon kera
