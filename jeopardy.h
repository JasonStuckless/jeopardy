/* Tutorial 4 Jeopardy Project for SOFE 3950U: Operating Systems
 *
 * Group 14: Jason Stuckless, 100248154
 */
#ifndef JEOPARDY_H_
#define JEOPARDY_H_

#define MAX_LEN 256

// REPLACED: Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
// REPLACED: extern void tokenize(char *input, char **tokens);
// Function to replace tokenizer for simpler solution, that just returns the word after "What is " or "Who is "
// and removes the question mark at the end of the answer if one is entered.
char* extract_answer (char* answer_input);

// Displays the game results for each player, their name and final score, ranked from first to last place
extern void show_results(player *players, int num_players);

#endif /* JEOPARDY_H_ */