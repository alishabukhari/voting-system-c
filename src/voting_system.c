#include <stdio.h>
#include <string.h>

typedef struct {
    char name[50];
    int votes;
    char symbol;
} Candidate;

Candidate candidates[10];
int candidateCount = 0;
char symbols[10] = {'!', '@', '#', '$', '%', '^', '&', '*', '~', '+'};
int symbolUsed[10] = {0};

// Function prototypes
void registerCandidates();
void displayCandidates();
void castVotes(int voterCount);
void displayResults();

int main() {
    int numVoters;

    printf("Enter the number of candidates: ");
    scanf("%d", &candidateCount);

    if (candidateCount <= 0 || candidateCount > 10) {
        printf("Invalid number of candidates. Exiting.\n");
        return 1;
    }

    registerCandidates();

    printf("Enter the number of voters: ");
    scanf("%d", &numVoters);

    if (numVoters <= 0) {
        printf("Invalid number of voters. Exiting.\n");
        return 1;
    }

    for (int i = 0; i < numVoters; i++) {
        castVotes(i + 1);
    }

    displayResults();

    return 0;
}

void registerCandidates() {
    for (int i = 0; i < candidateCount; i++) {
        printf("Enter name for candidate %d: ", i + 1);

        // Clear input buffer
        getchar(); // Consume leftover newline from previous input

        // Use fgets to read the candidate name
        fgets(candidates[i].name, sizeof(candidates[i].name), stdin);

        // Remove trailing newline character from name
        size_t len = strlen(candidates[i].name);
        if (len > 0 && candidates[i].name[len - 1] == '\n') {
            candidates[i].name[len - 1] = '\0';
        }

        printf("Available symbols: ");
        for (int j = 0; j < 10; j++) {
            if (!symbolUsed[j]) {
                printf("%c ", symbols[j]);
            }
        }
        printf("\nChoose a symbol for %s: ", candidates[i].name);

        char chosenSymbol;
        scanf(" %c", &chosenSymbol);

        int valid = 0;
        for (int j = 0; j < 10; j++) {
            if (symbols[j] == chosenSymbol && !symbolUsed[j]) {
                symbolUsed[j] = 1;
                candidates[i].symbol = chosenSymbol;
                candidates[i].votes = 0;
                valid = 1;
                break;
            }
        }

        if (!valid) {
            printf("Invalid symbol selected. Try again.\n");
            i--;
        }
    }
}

void displayCandidates() {
    printf("\nCandidates:\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%d. %s (%c)\n", i + 1, candidates[i].name, candidates[i].symbol);
    }
    printf("\n");
}

void castVotes(int voterNumber) {
    displayCandidates();
    printf("Voter %d, enter your choice (1-%d): ", voterNumber, candidateCount);

    int choice;
    scanf("%d", &choice);

    if (choice >= 1 && choice <= candidateCount) {
        candidates[choice - 1].votes++;
        printf("Vote recorded for %s (%c).\n", candidates[choice - 1].name, candidates[choice - 1].symbol);
    } else {
        printf("Invalid choice. Please vote again.\n");
        castVotes(voterNumber);
    }
}

void displayResults() {
    int maxVotes = 0;
    int winnerIndex = -1;
    int tie = 0;

    printf("\nElection Results:\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%s (%c): %d votes\n", candidates[i].name, candidates[i].symbol, candidates[i].votes);
        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
            winnerIndex = i;
            tie = 0;
        } else if (candidates[i].votes == maxVotes) {
            tie = 1;
        }
    }

    if (tie) {
        printf("\nThe election resulted in a tie.\n");
    } else if (winnerIndex != -1) {
        printf("\nThe winner is %s (%c) with %d votes!\n", candidates[winnerIndex].name, candidates[winnerIndex].symbol, maxVotes);
    } else {
        printf("\nNo votes were cast.\n");
    }
}