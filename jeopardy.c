/* Tutorial 4 Jeopardy Project for SOFE 3950U: Operating Systems
 *
 * Group 14: Jason Stuckless, 100248154
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
// REPLACED: Number of players set by players on game initialization
// REPLACED: #define NUM_PLAYERS 4

// Put global environment variables here
int num_players;

// REPLACED: Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
// REPLACED: void tokenize(char *input, char **tokens);
// Function to replace tokenizer for simpler solution, that just returns the word after "What is " or "Who is "
// and removes the question mark at the end of the answer if one is entered.
char* extract_answer (char* answer_input) {
    // Declare and allocate memory for temporary char array
    char* tmp = (char*)malloc(sizeof(char) * (strlen(answer_input) + 1));
    // Remove first word and first space, "What " or "Who "
    tmp = strchr(answer_input, ' ');
    memmove(tmp, tmp+1, strlen(tmp));
    // Remove "is" and second space
    tmp = strchr(tmp, ' ');
    memmove(tmp, tmp+1, strlen(tmp));
    // Remove question mark at the end of string if entered
    if (tmp[strlen(tmp)-1] == '?')
        tmp[strlen(tmp)-1] = '\0';
    return tmp;
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players) {
    printf("\nPLAYER SCORES:\n");
    for (int i = 0; i < num_players; i++) {
        printf("%s: %d\n", players[i].name, players[i].score);
    }
}

int main() {
    // Obtain number of players
    printf("--------------------\nWelcome to Jeopardy!\n--------------------\n\nHow many players are there?\n");
    scanf("%d", &num_players);
    // An array of players, may need to be a pointer if you want it set dynamically
    player players[num_players];
    // Input buffer and commands
    char buffer[BUFFER_LEN] = { 0 };
    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for player names AND initialize each of the players in the array
    char name[BUFFER_LEN];
    for (int i = 1; i <= num_players; i++) {
        strcpy(name, "");
        printf("Please enter the name for player %d: ", i);
        scanf("%s", name);
        if (player_exists(players, i, name)) {
            printf("Name already used by another player, please try again.\n");
            i--;
        } else {
            strcpy(players[i-1].name, name);
            players[i-1].score = 0;
        }
    }
    show_results(players, num_players);

    // Initialize variables for use in infinite game loop
    int active_player = 0;
    int value = 0;
    char category[BUFFER_LEN] = "";
    char answer[BUFFER_LEN] = "";

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL) {
        // Call functions from the questions and players source files
        display_categories();
        // User input category choice
        printf("%s, you're up! Please choose a category: ", players[active_player].name);
        scanf("%s", category);
        // Check if category entered is valid
        if (category_exists(category)) {
            // User input value choice
            printf("Pick a question value: ");
            scanf("%d", &value);
            // If value entered is valid display question
            if (value == 100 || value == 200 || value == 300 || value == 400) {
                // If question hasn't already been chosen, diplay question and get answer
                if (!already_answered(category, value)) {
                    display_question(category, value);
                    printf("%s, what is your answer? ", players[active_player].name);
                    scanf("%s", answer);
                    // Check if answer is correct, if so update score and show scoreboard
                    if (valid_answer(category, value, answer)) {
                        update_score(players, num_players, players[active_player].name, value);
                        show_results(players, num_players);
                    }
                    // Check if all questions have been answered, if so break loop
                    if (questions_done())
                        break;
                    // Increment active player
                    if (active_player == (num_players - 1))
                        active_player = 0;
                    else
                        active_player++;
                } else
                    printf("Question already answered, please pick a different question.\n");
            } else
                printf("Not a valid question value, please try again.\n");
        } else
            printf("Category does not exist, please try again.\n\n");
    }
    // Display the final results and exit
    printf("The game is over!\n");
    show_results(players, num_players);
    identify_winner(players, num_players);

    return EXIT_SUCCESS;
}