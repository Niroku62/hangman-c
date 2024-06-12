#include<stdio.h>
#include<string.h>

int main() {
	// create secret word
    char secretWord[128];
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
				++foundCharactersCounter;
				printf("\ncharacter %c found!\n", guessedCharacter);
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
				printf("\ncharacter not found!\nremaining attemps: %d\n", (7 - livesCounter));
				printf("\nlist of wrong characters:%s\n\n", wrongCharacters);
				break;
			}
		}

		//check win and loss condition
		if(foundCharactersCounter == stringLength) {
			printf("\nYou Win!\n");
			break;
		}
		if(livesCounter == 7) {
			printf("\nYou Lose!\n");
			break;
		}
	}
    return 0;
}