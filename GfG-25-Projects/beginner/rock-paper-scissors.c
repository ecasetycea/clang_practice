#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


#define T_RED "\033[31m"
#define T_GREEN "\033[32m"
#define T_BLUE "\033[34m"
#define T_RESET "\033[0m"
#define T_RED_B_I "\033[1;4;31m"



enum move {
    ROCK,
    PAPER,
    SCISSORS,
    MAX_STATE
};


static int scorePlayer = 0;
static int scoreComputer = 0;


enum move getPlayerMove(void);
enum move getComputerMove(void);
void compareMoves(enum move pMov, enum move cMov);
void printScore(void);
bool checkWinCondition(void);


int main(int argc, char** argv) {
    bool play = true;

    printf("Welcome to Rock, Paper, Scissors! You're playing against the computer, best of five.'\n\n");

    while(play) {
        enum move playerMove = getPlayerMove();
        enum move computerMove = getComputerMove();
        compareMoves(playerMove, computerMove);
        printScore();
        if(checkWinCondition()) play = false;
    }


    return 0;
}

bool checkWinCondition() {
    printf("\n");

    if( scorePlayer < 3 && scoreComputer < 3) {
        printf(T_BLUE "Game continues!\n\n" T_RESET);
        return false;
    }
    else if(scorePlayer >= 3) printf(T_GREEN "Player wins!!" T_RESET "\n");
    else if(scoreComputer >= 3) printf(T_RED "Game over, computer wins!!" T_RESET "\n");

    printf("Thanks for playing!\n\n");
    return true;

}

void printScore() {
    char playerScoreColor[10];
    char computerScoreColor[10];

    if(scorePlayer == scoreComputer) {
        strcpy(playerScoreColor, T_BLUE);
        strcpy(computerScoreColor, T_BLUE);
    }
    else if(scorePlayer > scoreComputer) {
        strcpy(playerScoreColor, T_GREEN);
        strcpy(computerScoreColor, T_RED);
    }
    else {
        strcpy(playerScoreColor, T_RED);
        strcpy(computerScoreColor, T_GREEN);
    }

    printf(
        "\n"
        "Current score is:\n"
        "%s    Player: %d\n" T_RESET
        "%s    Computer: %d\n" T_RESET,
        playerScoreColor, scorePlayer,
        computerScoreColor, scoreComputer
    );
    return;
}

void compareMoves(enum move pMov, enum move cMov) {
    printf("\n" T_RED_B_I);

    if(pMov == cMov) {
        printf("It's a draw!\n");
    }
    else if( pMov == (cMov+1)%MAX_STATE ) {
        printf("Player wins a point!\n");
        scorePlayer++;
    }
    else {
        printf("Computer wins a point!\n");
        scoreComputer++;
    }

    printf(T_RESET);

    return;
}

enum move getComputerMove() {
    srand(time(0));
    enum move cMov = rand() % 3;

    printf("Computer played: ");

    switch(cMov) {
        case ROCK:
            printf(T_RED "Rock!");
            break;
        case PAPER:
            printf(T_GREEN "Paper!");
            break;
        case SCISSORS:
            printf(T_BLUE "Scissors!");
            break;
        default: ;
    }

    printf(T_RESET "\n");

    return cMov;
}

enum move getPlayerMove() {
    char buffer[100]; // handle text inputs without perma loop
    enum move eMove;

    while(true) {
        printf(
            "What's your move?\n"
            "1.) Rock\n"
            "2.) Paper\n"
            "3.) Scissors\n"
            "Enter number: "
        );

        scanf("%s", buffer);

        printf("\nYou played: ");

        switch(buffer[0]) {
            case '1':
                printf(T_RED "Rock!");
                eMove = ROCK;
                break;
            case '2':
                printf(T_GREEN "Paper!");
                eMove = PAPER;
                break;
            case '3':
                printf(T_BLUE "Scissors!");
                eMove = SCISSORS;
                break;
            default:
                printf(
                    T_RED_B_I "An invalid option" T_RESET
                    "\nPlease input a valid option.\n\n");
                continue;
        }

        printf(T_RESET "\n");

        return eMove;
    }
}
