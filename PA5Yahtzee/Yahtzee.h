/*
Programmer: Lavrenty "Larry" Orlov
Class: CptS 121; Lab Section 10L
Programming Assignment: Programming Assignment 5 - The Game of Yahtzee
Date: 10/27/2025
Description: This is a text-based version of a dice game called Yahtzee involving features like handling user input in Command Prompt,
logical decision-making, checking for valid user input, numerical combination calculations, and random number generation.
*/

#ifndef Yahtzee_H
#define Yahtzee_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DISPLAY_RULES 1
#define PLAY 2
#define QUIT 3
#define DIE_FACES 6

#define YES 1
#define NO 2

#define FIRST_COMBINATION 1
#define LAST_COMBINATION 13

#define BONUS_MINIMUM_SUM 63
#define BONUS_POINTS 35

// Prints menu at start of the game
// Preconditions: none!
void print_menu(void);

// Central function responsible for controlling the flow of the program,
// including options the user can select like printing menu, playing the
// game, and exiting the program.
// Preconditions: none!
void program_running(void);

// Scan and return the user's entered number for their menu choice
// Preconditions: The user had just entered an integer value
int get_menu_choice(void);

// Checks whether user input is within the range of possible options in main menu
// Preconditions: The user had just entered an integer value
int is_input_valid(int user_choice);

// Prints game context and rules to the screen
// Preconditions: none!
void print_game_rules(void);

// Function responsible for controlling the flow of the game
// Preconditions: none!
void play_the_game(int game_over);

// Set all values of a scorecard to default values of -1
// Preconditions: the scorecard contains integer values, and
// the size is at least one
void init_scorecard(int *scorecard_ptr, int size);

// Set all values of a frequency table to default values of 0
// Preconditions: The frequency table contains intger values, and
// the size is at least one
void init_frequency_table(int* frequency_table, int size);

// Randomly generates values and places them in an array of dice
// Preconditions: the dice array stores integer values and has
// a size of at least one
void roll_dice(int *dice_array, int size);

// Finds how many times each possible dice side has been found in the current roll
// Preconditions: The dice and frequency arrays store integer values, and the
// size of the dice array is at least one
void determine_dice_frequencies(int *dice_array, int *frequency_array, int dice_array_size);

// Finds how many times a target value repeats in an array of numbers
// Preconditions: The array stores integer values, and its size along with
// the target value are both integers. Size is at least one.
int find_number_of_occurrences(int *array_of_nums, int size, int target_value);

// Prints the scorecard for player 1 or player 2
// Preconditions: The two player scorecards store integer values, and the current_player and
// size variables are each integer values. Size is at least one.
void print_current_scorecard(int *scorecard_p1, int *scorecard_p2, int current_player, int size);

// Asks the user to type 1 for yes or 2 for now, then returns the result
// Preconditions: user enters an integer value
int ask_yes_no(void);

// Checks whether the user typed 1 for yes or 2 for now for their decision
// Preconditions: user enters an integer value
int is_yes_no_choice_valid(int user_choice);

// Asks user which of the 13 combinations they would like to use for current roll
// Preconditions: user enters an integer value
int ask_for_combination(void);

// Checks whether the user entered a value between 1 and 13 to use one of the combinations
// Preconditions: user enters an integer value
int combination_choice_valid(int user_choice);

// Calculates the sum of a specific side of dice from the five rolled dice
// Preconditions: frequency table stores integer values; the side to check
// is an integer value
int sum_of_same_dice_sides(int *frequency_table, int side_to_check);

// Checks whether the player has earned three of a kind
// Preconditions: frequency table stores integer values
int is_three_of_a_kind(int *frequency_table);

// Checks whether the player has earned four of a kind
// Preconditions: frequency table stores integer values
int is_four_of_a_kind(int *frequency_table);

// Checks whether the player has earned full house
// Preconditions: frequency table stores integer values
int is_full_house(int *frequency_table);

// Checks whether the player has earned small straight
// Preconditions: frequency table stores integer values
int is_small_straight(int *frequency_table);

// Checks whether the player has earned large straight
// Preconditions: frequency table stores integer values
int is_large_straight(int *frequency_table);

// Checks whether the player has earned yahtzee
// Preconditions: frequency table stores integer values
int is_yahtzee(int *frequency_table);

// Calculates the sum of the sides of all five dice rolled for the current round
// Preconditions: dice array contains integer values
int sum_all_face_values(int *dice_array);

#endif