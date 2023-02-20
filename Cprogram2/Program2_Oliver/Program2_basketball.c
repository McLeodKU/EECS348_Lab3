#include <stdio.h>
#include <stdbool.h>

#define MAX_SCORE 100

int results[MAX_SCORE][2];
int results_count;

bool is_duplicate(int twos, int threes) {
    for (int i = 0; i < results_count; i++) {
        if (results[i][0] == twos && results[i][1] == threes) {
            return true;
        }
    }
    return false;
}

void print_combination(int score, int twos, int threes) {
    if (score == 0) {
        if (!is_duplicate(twos, threes)) {
            results[results_count][0] = twos;
            results[results_count][1] = threes;
            results_count++;
            printf("Number of two's scored: %d Number of three's scored: %d\n", twos, threes);
        }
        return;
    }

    if (score >= 2) {
        print_combination(score - 2, twos + 1, threes);
    }

    if (score >= 3) {
        print_combination(score - 3, twos, threes + 1);
    }
}

int main() {
    int score;
    printf("Enter the score: ");
    scanf("%d", &score);
    print_combination(score, 0, 0);
    return 0;
}
