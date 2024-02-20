/* Tutorial 4 Jeopardy Project for SOFE 3950U: Operating Systems
 *
 * Group 14: Jason Stuckless, 100248154
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "questions.h"

// An array of 12 questions (4 for each category), initialized in initialize_game
// this may need to be a pointer if you want it set dynamically
question questions[NUM_QUESTIONS];

// Initializes the array of questions for the game
void initialize_game(void) {

    // initialize each question struct and assign it to the questions array
    strcpy(questions[0].category, categories[0]);
    strcpy(questions[0].question, "This programming language is named after a type of snake.");
    strcpy(questions[0].answer, "python");
    questions[0].value = 100;
    questions[0].answered = false;

    strcpy(questions[1].category, categories[0]);
    strcpy(questions[1].question, "The creator of the C programming language.");
    strcpy(questions[1].answer, "ritchie");
    questions[1].value = 200;
    questions[1].answered = false;

    strcpy(questions[2].category, categories[0]);
    strcpy(questions[2].question, "The second O in OOP represents this.");
    strcpy(questions[2].answer, "oriented");
    questions[2].value = 300;
    questions[2].answered = false;

    strcpy(questions[3].category, categories[0]);
    strcpy(questions[3].question, "This type of insect being found in a relay created the term 'bug'.");
    strcpy(questions[3].answer, "moth");
    questions[3].value = 400;
    questions[3].answered = false;

    strcpy(questions[4].category, categories[1]);
    strcpy(questions[4].question, "This type of algorithm arranges elements in a specific order.");
    strcpy(questions[4].answer, "sorting");
    questions[4].value = 100;
    questions[4].answered = false;

    strcpy(questions[5].category, categories[1]);
    strcpy(questions[5].question, "This type of algorithm finds a specific element or value in a collection of data.");
    strcpy(questions[5].answer, "search");
    questions[5].value = 200;
    questions[5].answered = false;

    strcpy(questions[6].category, categories[1]);
    strcpy(questions[6].question, "This algorithmic approach involves making locally optimal choices to find a global optimum.");
    strcpy(questions[6].answer, "greedy");
    questions[6].value = 300;
    questions[6].answered = false;

    strcpy(questions[7].category, categories[1]);
    strcpy(questions[7].question, "This characteristic of an algorithm ensures that it eventually terminates.");
    strcpy(questions[7].answer, "finiteness");
    questions[7].value = 400;
    questions[7].answered = false;

    strcpy(questions[8].category, categories[2]);
    strcpy(questions[8].question, "The Q in SQL stands for this.");
    strcpy(questions[8].answer, "query");
    questions[8].value = 100;
    questions[8].answered = false;

    strcpy(questions[9].category, categories[2]);
    strcpy(questions[9].question, "This SQL statement is used to extract data from a database.");
    strcpy(questions[9].answer, "select");
    questions[9].value = 200;
    questions[9].answered = false;

    strcpy(questions[10].category, categories[2]);
    strcpy(questions[10].question, "Non-relational databases are collectively referred to as this.");
    strcpy(questions[10].answer, "nosql");
    questions[10].value = 300;
    questions[10].answered = false;

    strcpy(questions[11].category, categories[2]);
    strcpy(questions[11].question, "This was the most popular DBMS used in 2023.");
    strcpy(questions[11].answer, "oracle");
    questions[11].value = 400;
    questions[11].answered = false;
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void) {
    // print categories and dollar values for each unanswered question in questions array
    printf("------------------------ JEOPARDY ------------------------\n");
    for (int j = 0; j < 3; j++) {
        printf("%s  |", categories[j]);
        for (int i = 0; i < 4; i++) {
            if (questions[i+(j*4)].answered == false)
                printf("  %d  |", questions[i+(j*4)].value);
            else
                printf("  ***  |");
        }
        printf("\n");
    }
    printf("----------------------------------------------------------\n");
}

// Displays the question for the category and dollar value
void display_question(char *category, int value) {
    // Fix user entry in case they use weird upper/lower case
    category[0] = toupper(category[0]);
    for(int i = 1; category[i]; i++)
        category[i] = tolower(category[i]);
    printf("%s for %d: ", category, value);
    for (int i = 0; i < 12; i++) {
        if (strcasecmp(category, questions[i].category) == 0) {
            if (value == questions[i].value) {
                printf("%s\n", questions[i].question);
                questions[i].answered = true;
            }
        }
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer) {
    // Look into string comparison functions
    for (int i = 0; i < 12; i++) {
        if (strcasecmp(category, questions[i].category) == 0) {
            if (value == questions[i].value) {
                questions[i].answered = true;
                if (strcasecmp(answer, questions[i].answer) == 0) {
                    printf("Correct!");
                    return true;
                }
                else
                    printf("Sorry, the correct answer is: %s\n", questions[i].answer);
            }
        }
    }
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value) {
    // lookup the question and see if it's already been marked as answered
    for (int i = 0; i < 12; i++) {
        if (strcasecmp(category, questions[i].category) == 0) {
            if (value == questions[i].value) {
                if (questions[i].answered == true)
                    return true;
            }
        }
    }
    return false;
}

// Returns true if the category exists
bool category_exists(char *category) {
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        if (!strcasecmp(categories[i], category))
            return true;
    }
    return false;
}

// Returns true if all the questions have been chosen
bool questions_done() {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (questions[i].answered == false)
            return false;
    }
    return true;
}