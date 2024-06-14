#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <mmsystem.h>
#include "ansi_codes.h"

#define PI 3.14159265358979323846
#define SAMPLE_RATE 44100

// AUDIO SETUP
// create waveform structures
WAVEFORMATEX wfx;
HWAVEOUT hWaveout;
WAVEHDR wh;

void play_sound(int duration, int frequency) {
	waveOutOpen(&hWaveout, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	// Initialize WAVEHDR structure
	memset(&wh, 0, sizeof(WAVEHDR));
	wh.dwBufferLength = duration * SAMPLE_RATE / 32 * sizeof(short); // Buffer for 1/32 second
	wh.lpData = (LPSTR)malloc(wh.dwBufferLength);

	double increment = 2.0 * PI * frequency / SAMPLE_RATE;
	short sample;

	// Prepare the header
	waveOutPrepareHeader(hWaveout, &wh, sizeof(WAVEHDR));

	for (int i = 0; i < duration * SAMPLE_RATE / 32; ++i) {
		sample = (short)(32767.0 * sin(i * increment));

		// Fill the buffer with current sample
		memcpy(wh.lpData + i * sizeof(short), &sample, sizeof(short));
	}
	
	// Write and play the buffer
	waveOutWrite(hWaveout, &wh, sizeof(WAVEHDR));

	int sleep_time = wh.dwBufferLength * 1000 / wfx.nAvgBytesPerSec;
	if (sleep_time < 1) {
		sleep_time = 1;
	}
	// Sleep for the duration of the buffer
	Sleep(sleep_time);

	// Clean up
	waveOutUnprepareHeader(hWaveout, &wh, sizeof(WAVEHDR));
	waveOutClose(hWaveout);

	free(wh.lpData);
}

void play_sound_start() {
	play_sound(2, 600);
	play_sound(4, 600);
	play_sound(4, 800);
	play_sound(8, 1000);
}

void play_sound_correct() {
	play_sound(3, 600);
	play_sound(3, 800);
	play_sound(3, 1000);
	play_sound(4, 1200);
}

void play_sound_wrong() {
	play_sound(3, 500);
	play_sound(3, 400);
	play_sound(8, 300);
}

void play_sound_win() {
	play_sound(4, 600);
	play_sound(4, 600);
	play_sound(6, 800);
	play_sound(8, 1000);
}

void play_sound_lose() {
	play_sound(6, 400);
	play_sound(8, 400);
	play_sound(16, 200);
}

int main() {
	ansi_codes_enable();
	// assign values to wfx struct
	wfx.nSamplesPerSec = SAMPLE_RATE;
	wfx.wBitsPerSample = 16;
	wfx.nChannels = 1;
	wfx.cbSize = 0;
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nBlockAlign = (wfx.wBitsPerSample * wfx.nChannels) / 8;
	wfx.nAvgBytesPerSec = wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

	//play_sound_start();

	// create secret word
	char secretWord[128];
	char * my_string = "hello";
	puts("type your secret word and hit enter!");
	scanf("%s", secretWord);

	// create int for secret word length
	int stringLength;
	stringLength = strlen(secretWord);

	// creates and prints playfield array
	char blankSpace[128] = {0};
	for(int i = 0; i < stringLength; ++i) {
		blankSpace[i] = '_';
	}
	blankSpace[stringLength] = '\0';
	printf("%s", blankSpace);

	// create variables to be used in the loop
	int foundCharactersCounter = 0;
	int livesCounter = 0;
	char wrongCharacters[8] = {0};
	char correctCharacters[128] = {0};
	char * checkCharacter = 0;

	puts("\n\nguess the secret word!");
	puts("-------------------------");

	// starts main game loop
	for(;;) {
		// get character from user input
		puts("enter your character");
		char guessedCharacter;
		scanf(" %c", &guessedCharacter);
		if((checkCharacter = strchr(correctCharacters, guessedCharacter)) !=NULL) {
			puts("character already found!");
			continue;
		}
		
		char * CharacterPosition = secretWord;
		CharacterPosition = strchr(CharacterPosition, guessedCharacter);
		// loop checks if secret word contains the guessed Character
		for(;;) {
			if(CharacterPosition != NULL) {
				correctCharacters[foundCharactersCounter] = guessedCharacter;
				correctCharacters[foundCharactersCounter + 1] = '\0';
				++foundCharactersCounter;
				printf("\n" BGB_GREEN FGN_BLACK "character %c found!" ANSI_RESET "\n", guessedCharacter);
				play_sound_correct();
				blankSpace[CharacterPosition - secretWord] = guessedCharacter;
				printf("\n%s\n\n", blankSpace);
				
				++CharacterPosition;
				CharacterPosition = strchr(CharacterPosition, guessedCharacter);
				if(CharacterPosition != NULL) {
				continue;
				}
				break;
			} else {
				wrongCharacters[livesCounter] 	= guessedCharacter;
				++livesCounter;
				printf("\n" BGB_CYAN FGN_BLACK "a" "character not found!""\n" ANSI_RESET);
				printf("remaining attemps: %d""\n", (7 - livesCounter));
				play_sound_wrong();
				printf("\nlist of wrong characters:%s\n\n", wrongCharacters);
				break;
			}
		}
		puts("-------------------------");
		
		//check win and loss condition
		if(foundCharactersCounter == stringLength) {
			printf("\n" BGB_YELLOW FGN_BLACK "You Win!" ANSI_RESET "\n");
			play_sound_win();
			break;
		}
		if(livesCounter == 7) {
			printf("\n" BGB_RED FGN_BLACK "You Lose!" ANSI_RESET "\n");
			play_sound_lose();
			break;
		}
	}
	return 0;
}