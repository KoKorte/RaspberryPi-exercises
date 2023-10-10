#include <signal.h>
#include <stdio.h>
#include <pigpio.h>

// Määritellään käsiteltävä gpio pinni
// Terminaalikomento pinout näyttää raspberryn pinnien järjestyksen
const int LED_LEFT = 25;
const int LED_MID = 16;
const int LED_RIGHT = 26;
const int BUTTON_LEFT = 23;
const int BUTTON_MID = 22;
const int BUTTON_RIGHT = 27;
const int BUTTON_RESET = 24;


// https://stackoverflow.com/questions/24931456/how-does-sig-atomic-t-actually-work
volatile sig_atomic_t signal_received = 0;

// Signaalin käsittelijä
void sigint_handler (int signal) {
	signal_received = signal;
}

int main() {
	int left=0, mid=0, right=0, reset = 0;
	printf("\n\nPress ctrl+c to exit\n");
	// Jos raspberryn initialisaatio epäonnistuu, tulostetaan virhe
	if (gpioInitialise() == PI_INIT_FAILED) {
		printf("\n\nERROR: Initialization failed\n");	
		return 1;
	}
	// Käännetään pinni input-moodista output-moodiin
	gpioSetMode(LED_LEFT, PI_OUTPUT);
	gpioSetMode(LED_MID, PI_OUTPUT);
	gpioSetMode(LED_RIGHT, PI_OUTPUT);
	// Varmistetaan että valot on sammutettu
	gpioWrite(LED_LEFT, PI_LOW);
	gpioWrite(LED_MID, PI_LOW);
	gpioWrite(LED_RIGHT, PI_LOW);
	// Varmistetaan että napit ovat input moodissa
	gpioSetMode(BUTTON_LEFT, PI_INPUT);
	gpioSetMode(BUTTON_MID, PI_INPUT);
	gpioSetMode(BUTTON_RIGHT, PI_INPUT);
	gpioSetMode(BUTTON_RESET, PI_INPUT);
	// Varmistetaan että napit ovat up tilassa
	gpioSetPullUpDown(BUTTON_LEFT, PI_PUD_UP);
	gpioSetPullUpDown(BUTTON_MID, PI_PUD_UP);
	gpioSetPullUpDown(BUTTON_RIGHT, PI_PUD_UP);
	gpioSetPullUpDown(BUTTON_RESET, PI_PUD_UP);
	// Haetaan signaalia		
	signal(SIGINT, sigint_handler);
	// Niin kauan kuin signaalia ei ole saatu	
	while (!signal_received) {
		// Luetaan nappien tila
		left = gpioRead(BUTTON_LEFT);
		mid = gpioRead(BUTTON_MID);
		right = gpioRead(BUTTON_RIGHT);
		reset = gpioRead(BUTTON_RESET);
		// Vasenta nappia painaessa vain vasen led palaa
		if (left == 0) {
				gpioWrite(LED_LEFT, PI_HIGH);
				gpioWrite(LED_MID, PI_LOW);
				gpioWrite(LED_RIGHT, PI_LOW);
		}
		// Keskimmäistä nappia painaessa vain keskimmäinen led palaa
		if (mid == 0) {
				gpioWrite(LED_LEFT, PI_LOW);
				gpioWrite(LED_MID, PI_HIGH);
				gpioWrite(LED_RIGHT, PI_LOW);				
		}
		// Oikeinta nappia painaessa vain oikea led palaa
		if (right == 0) {
				gpioWrite(LED_LEFT, PI_LOW);
				gpioWrite(LED_MID, PI_LOW);
				gpioWrite(LED_RIGHT, PI_HIGH);
		}
		// Reset nappia painaessa kaikki ledit sammuu
		if (reset == 0) {
				gpioWrite(LED_LEFT, PI_LOW);
				gpioWrite(LED_MID, PI_LOW);
				gpioWrite(LED_RIGHT, PI_LOW);
		}		
	}
	
	// Varmistetaan että valot on sammutettu
	gpioWrite(LED_LEFT, PI_LOW);
	gpioWrite(LED_MID, PI_LOW);
	gpioWrite(LED_RIGHT, PI_LOW);
	// Palautetaan pinni takaisin input-moodiin	
	gpioSetMode(LED_LEFT, PI_INPUT);
	gpioSetMode(LED_MID, PI_INPUT);
	gpioSetMode(LED_RIGHT, PI_INPUT);
	// Palautetaan napit down tilaan
	gpioSetPullUpDown(BUTTON_LEFT, PI_PUD_DOWN);
	gpioSetPullUpDown(BUTTON_MID, PI_PUD_DOWN);
	gpioSetPullUpDown(BUTTON_RIGHT, PI_PUD_DOWN);
	gpioSetPullUpDown(BUTTON_LEFT, PI_PUD_DOWN);
	// Katkaistaan gpio-käsittely
	gpioTerminate();
	printf("\n");
	
	return 0;
}
// Suoritettava terminaalissa sudo-komennon kera
