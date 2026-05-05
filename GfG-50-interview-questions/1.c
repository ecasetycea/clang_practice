// Find the largest number among 3 numbers

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
    int numbers[3];
    int indexOfLargest;
    bool exit = false;
    char exitCondition;

    while(!exit) {
        printf("Insert the three integer numbers in the format of 'a b c' and press enter\n");
        scanf("%d %d %d", numbers, numbers+1, numbers+2);

        indexOfLargest = 0;
        for(int i=0; i<3; i++) indexOfLargest = (numbers[i]>numbers[indexOfLargest]) ? i : indexOfLargest;

        printf("The largest number is number %c: %d!\n", (char)(0x61 + indexOfLargest), numbers[indexOfLargest]);
        printf("Calculate more? [y/N]: ");

        // consume new line "\n" character from before
        // can't use " %c" formating in scanf because the default behaviour of
        // not inputting anything breaks
        getchar();
        scanf("%c", &exitCondition);
        exit = (exitCondition == 'y' || exitCondition == 'Y') ? false : true; // exit by default

        // new line for cleaner reading
        if(!exit) printf("\n");
    }
    return 0;
}
