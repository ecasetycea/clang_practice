#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bool isNumberString(char* string);
bool isPrime(int number);

int main(int argc, char* argv[]) {

    int number;

    // Check for given number at the start
    if(argc > 1) {

        // Handle negative numbers
        if( argv[1][0] == '-' ) {
            printf("Input starts with '-'. Negative numbers are NOT prime.\n");
            return 0;
        }

        // Handle text input
        if( !isNumberString(argv[1]) ) {
            printf("Error: Cannot interpret text input.\n");
            printf("Usage: '$ 02-is-prime.out' or '$ 02-is-prime.out <number>'\n");
            return 1;
        }

        // Pass input to program for calculation
        number = atoi(argv[1]);

    } else {

        // Take input from user if no number provided
        printf("Please enter a number: ");
        scanf("%d", &number);

    }

    // Print result
    if( isPrime(number) ) {
        printf("Number %d IS prime!\n", number);
    } else {
        printf("Number %d is NOT prime!\n", number);
    }

    return 0;
}


bool isNumberString(char* string) {
    for(int index=0; string[index]!='\0'; index++) {
        if(string[index] < 0x30 || string[index] > 0x39) return false;
    }
    return true;
}

bool isPrime(int number) {
    // Biggest unique divisor gives the number when squared
    int maxTested = (int) sqrt( number );

    // For most cases naivelly testing all numbers is faster than explicit prime
    // tests which most likely include factorials
    for(int i=2; i<maxTested+1; i++) {
        if(number%i == 0) return false;
    }

    return true;
}
