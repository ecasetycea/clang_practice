#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define T_RED "\033[31m"
#define T_RED_B "\033[1;31m"
#define T_RED_B_I "\033[1;4;31m"
#define T_GREEN "\033[32m"
#define T_GREEN_B "\033[1;32m"
#define T_BLUE "\033[34m"
#define T_RESET "\033[0m"
#define T_UNDERLINE "\033[4m"



enum numberValidity {
    VALID,
    NEGATIVE,
    INVALID
};

enum dataType {
    DEPOSIT,
    INTEREST,
    TIME
};

typedef struct interestData {
    double deposit;
    double compoundedDeposit;
    double interest;
    double compoundInterest;
    long long time;
} interestData_t;


/* ========== FORWARD DECLARATIONS ========== */
enum numberValidity isStringDouble(char* string);
enum numberValidity isStringNumber(char* string);
void printErrorMessage(enum numberValidity STATUS, enum dataType ARG);
void getDataFromUser(interestData_t* idptr);
void printResults(interestData_t* idptr);



/* ========== PROGRAM ENTRY ========== */
int main(int argc, char* argv[]) {
    interestData_t id = {0.0, 0.0, 0};

    // Handle program arguments
    if(argc<4) {

        // If not enough provided go interactive
        getDataFromUser(&id);
    } else {

        // Check for validity of provided arguments
        if( isStringDouble(argv[1]) != VALID ) {
            printErrorMessage( isStringDouble(argv[1]), DEPOSIT);
            return 1;
        }
        if( isStringDouble(argv[2]) != VALID ) {
            printErrorMessage( isStringDouble(argv[2]), INTEREST);
            return 2;
        }
        if( isStringNumber(argv[3]) != VALID ) {
            printErrorMessage( isStringNumber(argv[3]), TIME);
            return 3;
        }

        char* endptr = NULL;
        id.deposit = strtod(argv[1], &endptr);
        id.interest = strtod(argv[2], &endptr);
        id.time = strtoll(argv[3], &endptr, 10);
    }


    // Calculate compounding
    id.compoundedDeposit = id.deposit;
    for(int i=0; i<id.time; i++) id.compoundedDeposit *= ( 1.0 + id.interest/100.0 );
    id.compoundInterest = id.compoundedDeposit - id.deposit;

    printResults(&id);

    return 0;
}

void printResults(interestData_t* idptr) {
    printf(
        "\n"
        "==== Initial Data ====\n"
        "Initial Deposit: %lf\n"
        "Interest: %lf%%\n"
        "Time Periods: %lld\n"
        "\n"
        "======= Results =======\n"
        "Final Deposit: %lf\n"
        "Compound Interest: %lf\n"
        "\n",

        idptr->deposit,
        idptr->interest,
        idptr->time,
        idptr->compoundedDeposit,
        idptr->compoundInterest
    );
}


void getDataFromUser(interestData_t* idptr) {
    printf("Enter the initial deposit: ");
    scanf(" %lf", &(idptr->deposit) );
    if(idptr->deposit < 0) {
        printErrorMessage(NEGATIVE, DEPOSIT);
        exit(1);
    }

    printf("Enter the interest: ");
    scanf(" %lf", &(idptr->interest) );
    if(idptr->interest < 0) {
        printErrorMessage(NEGATIVE, INTEREST);
        exit(2);
    }

    printf("Enter time (integer): ");
    scanf(" %lld", &(idptr->time) );
    if(idptr->time < 0) {
        printErrorMessage(NEGATIVE, TIME);
        exit(3);
    }
}

enum numberValidity isStringDouble(char* string) {
    int dotCounter = 0;
    for(int i=0; string[i] != '\0'; i++) {

        // check for invalid numbers
        if( string[i] < 0x2d // ascii '-', table is "-./0123456789"
            || string[i] > 0x39 // ascii '9'
            || string[i] == 0x2f // ascii '/'
        ) {
            return INVALID;
        }

        // check if there are multiple dots
        if(string[i] == '.') dotCounter++;
    }

    // invalidate multiple dot numbers
    if(dotCounter > 1) return INVALID;

    if(string[0] == '-') return NEGATIVE;

    return VALID;
}

enum numberValidity isStringNumber(char* string) {
    for(int i=0; string[i] != '\0'; i++) {
        if( (string[i] < 0x30 && string[i] != '-')
            || string[i] > 0x39
        ) {
            return INVALID;
        }
    }

    if(string[0] == '-') return NEGATIVE;

    return VALID;
}

void printErrorMessage(enum numberValidity STATUS, enum dataType ARG) {
    char errorType[9];
    char argType[9];

    switch(STATUS) {
        case VALID: // do nothing, include VALID in switch to remove gcc warning
        case NEGATIVE:
            sprintf(errorType, "negative");
            break;
        case INVALID:
            sprintf(errorType, "invalid");
            break;
    }

    switch(ARG) {
        case DEPOSIT:
            sprintf(argType, "deposit");
            break;
        case INTEREST:
            sprintf(argType, "interest");
            break;
        case TIME:
            sprintf(argType, "time");
            break;
    }

    printf(T_RED "Error: the " T_RED_B "\"%s\"" T_RESET T_RED " argument is "
        T_RED_B_I "%s" T_RESET ".\n", argType, errorType);
    printf("Usage: \"" T_GREEN_B "$ 03-compound-interest.out" T_RESET "\" or \""
        T_GREEN_B "$ 03-compound-interest.out "
        T_BLUE "<deposit> <interest> <time>" T_RESET "\"\n");
    printf("Deposit and interest are " T_UNDERLINE "decimal" T_RESET
        " numbers, while time is an " T_UNDERLINE "integer" T_RESET
        " number, all of them " T_UNDERLINE "non-negative" T_RESET ".\n");
}
