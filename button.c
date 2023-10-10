#include <signal.h>
#include <stdio.h>
#include <pigpio.h>

// Määritellään käsiteltävä gpio pinni
// Terminaalikomento pinout näyttää raspberryn pinnien järjestyksen
const int LED = 16;
const int BUTTON = 24;

// https://stackoverflow.com/questions/24931456/how-does-sig-atomic-t-actually-work
volatile sig_atomic_t signal_received = 0;

// Signaalin käsittelijä
void sigint_handler (int signal) {
	signal_received = signal;
}

void is_lit(int *val) {
	if (*val == 0) {
		// lamppu päälle
		gpioWrite(LED, PI_HIGH);
	}
	else {
		// lamppu pois päältä
		gpioWrite(LED, PI_LOW);
	}
}

int main() {
	int val = 0, test = 0;
	printf("\n\nPress ctrl+c to exit\n");
	// Jos raspberryn initialisaatio epäonnistuu, tulostetaan virhe
	if (gpioInitialise() == PI_INIT_FAILED) {
		printf("\n\nERROR: Initialization failed\n");	
		return 1;
	}
	// Käännetään pinni input-moodista output-moodiin
	gpioSetMode(LED, PI_OUTPUT);
	gpioSetMode(BUTTON, PI_INPUT);
	gpioSetPullUpDown(BUTTON, PI_PUD_UP);
	// Haetaan signaalia		
	signal(SIGINT, sigint_handler);
	// Niin kauan kuin signaalia ei ole saatu	
	while (!signal_received) {
		// Luetaan napin tila
		val = gpioRead(BUTTON);
		// Jos napin tila on muuttunut
		if (val != test) {			
			//printf("\nnappi: %d",val);
			// Määritetään uusi testausarvo
			test = val;
			// Käydään funktiossa toimimassa napin käsittelemällä tavalla
			is_lit(&val);
			// Ootellaan sekuntti, jotta saadaan vain yksi toiminta ihmisen hitauden vuoksi
			time_sleep(1);
		}
		
	}
	// Palautetaan pinni takaisin input-moodiin	
	gpioSetMode(LED, PI_INPUT);
	// Katkaistaan gpio-käsittely
	gpioTerminate();
	printf("\n");
	
	return 0;
}
// Suoritettava terminaalissa sudo-komennon kera
