#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>


int isNumeric(const char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i]))
            return 0;
    }
    return 1;
}

int main() {
    int secretNumber, guess, attempts = 0;
    char input[100];

   
    srand(time(NULL));
    secretNumber = rand() % 100 + 1;  

    printf("Welcome to the Number Guessing Game!\n");
    printf("I'm thinking of a number between 1 and 100.\n");

    while (1) {
        printf("Enter your guess: ");
        fgets(input, sizeof(input), stdin);

        
        input[strcspn(input, "\n")] = 0;

       
        if (!isNumeric(input)) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        guess = atoi(input);
        attempts++;

        if (guess < secretNumber) {
            printf("Too low!\n");
        } else if (guess > secretNumber) {
            printf("Too high!\n");
        } else {
            printf("Congratulations! You guessed it in %d attempts.\n", attempts);
            break;
        }
    }

    return 0;
}
