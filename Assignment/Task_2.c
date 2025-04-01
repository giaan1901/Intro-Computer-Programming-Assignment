#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calculateHappinessScore(char input[]);

int main () {
    char input[] = "Tiger";
    calculateHappinessScore(input);
}

//solve

int check(char x) {
    if (x == 'u' || x == 'e' || x == 'o' || x == 'a' || x == 'i') return 1;
    if (x == 'U' || x == 'E' || x == 'O' || x == 'A' || x == 'I') return 1;
    return 0; 
}

void calculateHappinessScore(char input[]) {
    int sum = 0;
    for (int i = 0; i < strlen(input); i++) {
        if (check(input[i])) {
            sum += input[i];
        }
    }
    if (sum > 100) printf("Happiness Score: %d (Happy)", sum);
    else printf("Happiness Score: %d (Unhappy)", sum);
}
