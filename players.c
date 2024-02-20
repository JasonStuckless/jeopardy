/* Tutorial 4 Jeopardy Project for SOFE 3950U: Operating Systems
 *
 * Group 14: Jason Stuckless, 100248154
 */
#include <string.h>
#include <stdio.h>
#include "players.h"

// Returns true if the player name matches one of the existing players
bool player_exists(player *players, int current_players, char *name) {
    for (int i = 0; i < (current_players-1); i++) {
        if (strcasecmp(name, players[i].name) == 0)
            return true;
    }
    return false;
}

// Go through the list of players and update the score for the 
// player given their name
void update_score(player *players, int num_players, char *name, int score) {
    for (int i = 0; i < num_players; i++) {
        if (strcasecmp(name, players[i].name) == 0)
            players[i].score += score;
    }
}

// Finds the winner of the game and congratulates them
void identify_winner(player *players, int num_players) {
    int leader = 0;
    int leading_score = 0;
    if (num_players != 1) {
        for (int i = 0; i < num_players; i++) {
            if (players[i].score > leading_score) {
                leading_score = players[i].score;
                leader = i;
            }
        }
    }
    printf("Congratulations %s, you are the winner!\n", players[leader].name);
}