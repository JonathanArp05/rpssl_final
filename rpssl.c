#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINNING_SCORE 5

// Enum for shapes
typedef enum {
    ROCK = 0,
    LIZARD,
    SCISSORS,
    PAPER,
    SPOCK,
    SHAPE_COUNT
} Shape;

// Shape names with emojis
const char* shape_names[] = {
    "🪨", "🦎", "✂️", "🗒️", "🖖"
};

// Outcome matrix: 0 = tie, 1 = player wins, -1 = agent wins
int outcome_matrix[SHAPE_COUNT][SHAPE_COUNT] = {
    // ROCK outcomes
    {0, 1, -1, -1, 1},   // Rock vs (Rock,Lizard,Scissors,Paper,Spock)
    // LIZARD outcomes
    {-1, 0, -1, 1, 1},   // Lizard
    {1, 1, 0, -1, -1},   // Scissors
    {1, -1, 1, 0, -1},   // Paper
    {-1, -1, 1, 1, 0}    // Spock
};

// Show menu
void show_menu() {
    printf("Welcome to 🪨  ✂️  🗒️  🖖  🦎 !\n");
    printf("(s) Single player\n");
    printf("(e) Exit\n");
    printf("Select an item: ");
}

// Show shapes
void show_shapes() {
    printf("\nSelect a shape:\n");
    printf("0🪨  || 1🦎  || 2✂️  || 3🗒️  || 4🖖 : ");
}

// Get menu choice
char get_menu_choice() {
    char c;
    while (1) {
        c = getchar();
        while (getchar() != '\n'); // clear buffer
        if (c == 's' || c == 'e') return c;
        printf("❌ Invalid menu choice. Try again: ");
    }
}

// Get shape choice
int get_shape_choice() {
    int choice;
    while (1) {
        if (scanf("%d", &choice) == 1) {
            while (getchar() != '\n'); // clear buffer
            if (choice >= 0 && choice < SHAPE_COUNT) {
                return choice;
            } else {
                printf("❌ Shape key %d does not exist. Try again.\n", choice);
                show_shapes();
            }
        } else {
            while (getchar() != '\n'); // clear buffer
            printf("❌ Invalid input. Enter a number.\n");
            show_shapes();
        }
    }
}

int main() {
    srand((unsigned int)time(NULL));
    int player_score = 0, agent_score = 0;

    show_menu();
    char menu_choice = get_menu_choice();

    if (menu_choice == 'e') {
        printf("Exiting game. Goodbye!\n");
        return 0;
    }

    printf("Starting game 🎉\n");

    while (player_score < WINNING_SCORE && agent_score < WINNING_SCORE) {
        show_shapes();
        int player_choice = get_shape_choice();
        int agent_choice = rand() % SHAPE_COUNT;

        printf("Agent: %d\n", agent_choice);

        int result = outcome_matrix[player_choice][agent_choice];
        if (result == 1) {
            player_score++;
        } else if (result == -1) {
            agent_score++;
        }

        printf("👫:🤖  %d:%d\n\n", player_score, agent_score);
    }

    if (player_score == WINNING_SCORE) {
        printf("👫 You won!\n");
    } else {
        printf("🤖 Agent won!\n");
    }

    return 0;
}