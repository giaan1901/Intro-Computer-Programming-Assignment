#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

int findHappinestNumber(char input[]);

int main () {
    printf("%d", findHappinestNumber("13,89,45,67,53"));
}

//solve

#define maxN 10005

bool isPrime[maxN], isHappy[maxN];
char str_num[maxN][200];
int num[maxN], sum_digit[maxN];

void Prime() {
    for (int i = 2; i < maxN; i++) isPrime[i] = true;

    for (int i = 2; i < sqrt(maxN); i++) {
        if (isPrime[i]) {
            for (int j = i*i; j < maxN; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

bool PowerTwo(int x) {
    int cnt = 0;
    for (int i = 0; i < 9; i++) {
        cnt += (x >> i) & 1;
    } 
    return cnt == 1 ? true : false;
}

void split_Number(char input[]) {
    //segmentation fault
    char *token = strtok(input, ",");
    int index = 0;

    while (token != NULL) {
        strcpy(str_num[index], token);
        token = strtok(NULL, ",");
        index++;
    }

    for (int i = 0; i < index; i++) {
        for (int j = 0; j < 200; j++) {
            if (str_num[i][j] == '\0') break;
            num[i] = num[i]*10 +  (str_num[i][j] - 48);
            sum_digit[i] += str_num[i][j] - 48;
        }
    }
}

int findHappinestNumber(char input[]) {
    Prime();
    char text[500] = "\0";
    strcpy(text, input);
    split_Number(text);
    int happiest_number = 0;
    for (int i = 0; i < maxN; i++) {
        if (isPrime[num[i]] && PowerTwo(sum_digit[i])) 
            isHappy[i] = true; 
    }
    for (int i = 0; i < maxN; i++) {
        if (isHappy[i] && happiest_number < num[i]) {
            happiest_number = num[i];
        }
    }
    return happiest_number;
}