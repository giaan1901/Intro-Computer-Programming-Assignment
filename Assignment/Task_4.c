#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

void maximizeHappiestScore(char input[]);

int main() {
    char input[100] = "QKihOhjV";
    maximizeHappiestScore(input);
}

//solve

const int maxN = 1e6 + 7;

bool isPrime[1000007];
int happy_score[1000007], cnt_vowel[1007], cnt_consonants;

bool isPower_two(int x) {
    int cnt = 0, sum = 0;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }

    for (int i = 0; i < 20; i++) {
        if ((sum >> i) & 1) cnt++;
    }
    return cnt == 1 ? true : false;
}

void sieve_era() {
    for (int i = 2; i < maxN; i++) isPrime[i] = true;

    for (int i = 2; i < sqrt(maxN); i++) {
        if (isPrime[i]) {
            for (int j = i*i; j < maxN; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

bool isVowel(char x) {
    if (x == 'u' || x == 'e' || x == 'o' || x == 'a' || x == 'i') return true;
    if (x == 'U' || x == 'E' || x == 'O' || x == 'A' || x == 'I') return true;
    return false;
}

void sort(char input[]) {
    int n = strlen(input);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (input[i] < input[j]) {
                char temp = input[i];
                input[i] = input[j];
                input[j] = temp;
            }
        }
    }
}

int max(int a, int b) {
    return a > b ? a : b;
}

int dp[95][12000];

void maximizeHappiestScore(char input[]) {
    //initialize:
    int sum = 0, happiest_score = 0, index = 0;
    int n = strlen(input);
    char happy_str[100];
    sieve_era();

    //prepare:
    for (int i = 0; i < n; i++) {
        if (!isVowel(input[i])) {
            cnt_consonants++;
        } else {
            sum += input[i];
            happy_str[index] = input[i];
            index++;
        }
    }
    happy_str[index + 1] = '\0';

    sort(happy_str);

    //non consonants
    if (cnt_consonants == 0) {
        if (!isPrime[sum] || !isPower_two(sum)) {
            sum = 0;
            strcpy(input, "");
        } 
        happiest_score = sum;

        if (happiest_score > 100) printf("Happiest String: %s\nHappiest Score: %d (Happy)", happy_str, happiest_score);
        else printf("Happiest String: %s\nHappiest Score: %d (Unhappy)", happy_str, happiest_score);
        return;
    }

    //dp solving
    for (int i = 0; i <= n; i++) {
        int asc;
        if (i > 0) asc = happy_str[i - 1];
        for (int j = 0; j <= sum; j++) {
            if (i == 0 || j == 0) dp[i][j] = 0;
            else if (j < asc)  dp[i][j] = dp[i - 1][j];
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - asc] + asc);
            }
        }
    }

    //query
    for (int i = sum; i >= 0; i++) {
        if (isPrime[dp[n][i]] && isPower_two(dp[n][i])) {
            happiest_score = dp[n][i];
            break;
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= sum; j++) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }

    if (happiest_score > 100) printf("Happiest String: %s\nHappiest Score: %d (Happy)", happy_str, happiest_score);
    else printf("Happiest String: %s\nHappiest Score: %d (Unhappy)", happy_str, happiest_score);
}