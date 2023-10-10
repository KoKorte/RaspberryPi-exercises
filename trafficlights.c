#include <signal.h>
#include <stdio.h>
#include <pigpio.h>

// Määritellään käsiteltävä gpio pinni
// Terminaalikomento pinout näyttää raspberryn pinnien järjestyksen
const int redLED = 16; // punainen valo
const int yellowLED = 24; // keltainen valo
const int greenLED = 23; // vihreä valo

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
	gpioSetMode(redLED, PI_OUTPUT);
	gpioSetMode(yellowLED, PI_OUTPUT);
	gpioSetMode(greenLED, PI_OUTPUT);
	// Haetaan signaalia		
	signal(SIGINT, sigint_handler);
	// Niin kauan kuin signaalia ei ole saatu
	while (!signal_received) {
		// Tämän sisälle kaksi toimintoa joiden välissä yksi looppi pyörimään järjestyksessä
		// 1. päällä viisi sekunttia ja pois
		gpioWrite(redLED, PI_HIGH);
		// Odotetaan 5 sekuntia
		time_sleep(5);
		// Laitetaan led pois päältä
		gpioWrite(redLED, PI_LOW);
		// Odotetaan sekunti
		//time_sleep(1);
		// 2. vilkuttaa kolmesti ja pois
		for(int i=0; i<3; i++) {			
			// Laitetaan led päälle
			gpioWrite(yellowLED, PI_HIGH);
			// Odotetaan sekunti
			time_sleep(1);
			// Laitetaan led pois päältä
			gpioWrite(yellowLED, PI_LOW);
			if (i != 2) {
				time_sleep(1);
			}
		}
		// 3. päällä viisi sekunttia ja pois
		// Laitetaan led päälle
		gpioWrite(greenLED, PI_HIGH);
		// Odotetaan 5 sekuntia
		time_sleep(5);
		// Laitetaan led pois päältä
		gpioWrite(greenLED, PI_LOW);
		// Odotetaan sekunti
		//time_sleep(1);
		// 4. vilkuttaa kolmesti ja pois
		for(int i=0; i<3; i++) {			
			// Laitetaan led päälle
			gpioWrite(yellowLED, PI_HIGH);
			// Odotetaan sekunti
			time_sleep(1);
			// Laitetaan led pois päältä
			gpioWrite(yellowLED, PI_LOW);
			if (i != 2) {
				time_sleep(1);
			}
		}
	}
	// Palautetaan pinnit takaisin input-moodiin	
	gpioSetMode(redLED, PI_INPUT);
	gpioSetMode(yellowLED, PI_INPUT);
	gpioSetMode(greenLED, PI_INPUT);
	// Katkaistaan gpio-käsittely
	gpioTerminate();
	printf("\n");
	
	return 0;
}
// Suoritettava terminaalissa sudo-komennon kera
