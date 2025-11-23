/*
Programmer: Lavrenty "Larry" Orlov
Class: CptS 121; Lab Section 10L
Programming Assignment: Programming Assignment 5 - The Game of Yahtzee
Date: 10/27/2025
Description: This is a text-based version of a dice game called Yahtzee involving features like handling user input in Command Prompt, 
logical decision-making, checking for valid user input, numerical combination calculations, and random number generation.
*/

#include "Yahtzee.h"

// Prints menu at start of the game
// Preconditions: none!
void print_menu(void)
{
	printf("**********************************************************************************************\n");
	printf("Welcome to the game of Yahtzee, designed by Computer Science student Lavrenty \"Larry\" Orlov!\n");
	printf("**********************************************************************************************\n");
	printf("\n");
	printf("Main menu:\n");
	printf("1. Print game context and rules!\n");
	printf("2. Start a game of Yahtzee! :D\n");
	printf("3. Exit!\n");
}

// Central function responsible for controlling the flow of the program,
// including options the user can select like printing menu, playing the
// game, and exiting the program.
// Preconditions: none!
void program_running(void)
{
	int user_decision = 0, valid = 0, game_over = 0;

	srand(time(NULL));
	
	do
	{
		do
		{
			system("cls");
			print_menu();
			user_decision = get_menu_choice();
			valid = is_input_valid(user_decision);
		} while (!valid);

		switch (user_decision)
		{
		case DISPLAY_RULES: print_game_rules();
			break;
		case PLAY:
			game_over = 0;
			play_the_game(game_over);
			break;
		case QUIT: printf("Thanks for playing Yahtzee! See ya next time :D\n");
			break;
		}


	} while (user_decision != QUIT);
}

// Scan and return the user's entered number for their menu choice
// Preconditions: The user had just entered an integer value
int get_menu_choice(void)
{
	int user_choice = 0;
	scanf("%d", &user_choice);
	return user_choice;
}

// Checks whether user input is within the range of possible options in main menu
// Preconditions: The user had just entered an integer value
int is_input_valid(int user_choice)
{
	return !(user_choice < DISPLAY_RULES || user_choice > QUIT);
}

// Prints game context and rules to the screen
// Preconditions: none!
void print_game_rules(void)
{
	system("cls");
	printf("******************************************\n");
	printf("Context and rules for the game of Yahtzee!\n");
	printf("******************************************\n");

	printf("\n");

	printf("Context:\n");

	printf("\n");
	
	printf("Yahtzee is a dice game that was invented by Milton Bradley and Edwin S. Lowe in 1956.\n");
	printf("The challenge of the game is to outduel the other player by scoring the most points.\n");
	printf("Points are obtained by rolling five 6-sided die across thirteen rounds.\n");
	printf("During each round, each player may roll the dice up to three times to make one of\n");
	printf("the possible scoring combinations. Once a combination has been achieved by the player,\n");
	printf("it may not be used again in future rounds.\n");

	printf("\n");

	printf("Note: Usually, the Yahtzee combination may be used as many times as the player makes\n");
	printf("the combination throughout the game. But in this case, Larry's CS professor told him\n");
	printf("that it is okay for the Yahtzee combination to follow the same rules as other\n");
	printf("combinations in the game. So, in this version of the game, the Yahtzee combination\n");
	printf("may only be used once :)\n");
	
	printf("\n");
	
	printf("Each scoring combination has different point totals. Some of these totals are achieved\n");
	printf("through the accumulation of points across rolls and some are obtained as fixed sequences of values.\n");
	
	printf("\n");
	
	printf("Rules:\n");

	printf("\n");
	
	printf("The scorecard used for Yahtzee is composed of two sections. A upper section and a\n");
	printf("lower section. A total of thirteen boxes or thirteen scoring combinations are divided\n");
	printf("amongst the sections. The upper section consists of boxes that are scored by summing\n");
	printf("the value of the dice matching the faces of the box. If a player rolls four 3's, then the\n");
	printf("score placed in the 3's box is the sum of the dice which is 12. Once a player has\n");
	printf("chosen to score a box, it may not be changed and the combination is no longer in play\n");
	printf("for future rounds. If the sum of the scores in the upper section is greater than or\n");
	printf("equal to 63, then 35 more points are added to the players overall score as a bonus.\n");
	printf("The lower section contains a number of poker like combinations. See the table provided below:\n");

	printf("\n");
	
	printf("Name:                        Combination:                     Score:\n");
	printf("-Three-of-a-kind             Three dice with the same face    Sum of all face values on the 5 dice\n");
	printf("-Four-of-a-kind              Four dice with the same face     Sum of all face values on the 5 dice\n");
	printf("-Full house **               One pair and a three-of-a-kind   25\n");
	printf("-Small straight ***          A sequence of four dice          30\n");
	printf("-Large straight ***          A sequence of five dice          40\n");
	printf("-Yahtzee (five-of-a-kind) ** Five dice with the same face     50\n");
	printf("-Chance (May be used         Catch-all combination            Sum of all face values on the 5 dice\n");
	printf("for any sequence of 5 dice)\n");

	printf("\n");

	printf("Note: Players need to select one of the combination options for each round of the game.\n");
	printf("So, even if you're not able to score a combination for your current round, you still need to\n");
	printf("select one of the combinations. Then, you'll receive zero points for that round :)\n");

	printf("\n");

	printf("** If you roll five-of-a-kind and already use the Yahtzee combination, you may use full house for that round!\n");

	printf("\n");
	
	printf("*** A small straight means rolling a sequence of four consecutive dice like 1-2-3-4 or 2-3-4-5,\n");
	printf("while a large straight is a sequence of five consecutive dice (1-2-3-4-5 or 2-3-4-5-6. If you've\n");
	printf("already used the large straight combination and get another large straight, you may use small straight\n");
	printf("for that round!\n");

	printf("\n");
	
	printf("Ready to give this game a try? :D\n");

	printf("\n");

	system("pause");
}

// Function responsible for controlling the flow of the game
// Preconditions: none!
void play_the_game(int game_over)
{
	// Scorecard array uses size 14 to count combination numbers from index 1 to 13
	// Frequency table uses size 7 to count dice sides from index 1-6
	int current_player = 0, rounds_played = 0, rolls = 0,
		player_one_scorecard[14] = { 0 },
		player_two_scorecard[14] = { 0 },
		dice[5] = { 0 }, freq_table[7] = { 0 },
		continue_current_player_round = 0, roll_usage_decision = 0,
		roll_current_die = 0, combination_choice = 0, player_one_points = 0,
		player_two_points = 0, points_earned_this_round = 0, potential_round_points = 0,
		combination_earned = 0, combination_search_attempted = 0, 
		p1_uppper_section_score_card = 0, p2_uppper_section_score_card = 0;
	
	printf("We're about to start an epic game of Yahtzee! Ready when you are :D\n");
	system("pause");
	
	do
	{
		rounds_played = 1;
		init_scorecard(player_one_scorecard, 14);
		init_scorecard(player_two_scorecard, 14);
		
		while (rounds_played < 14)
		{
			current_player = 1;

			while (current_player <= 2)
			{
				system("cls");

				printf("\n");
				printf("Round #%d", rounds_played);

				printf("\n");
				printf("Player #%d:\n", current_player);

				printf("\n");
				printf("Player 1 has %d points!\n", player_one_points);
				printf("Player 2 has %d points!\n", player_two_points);

				printf("\n");
				print_current_scorecard(player_one_scorecard, player_two_scorecard, current_player, 14);

				printf("\n");
				printf("Please press enter any key to roll your five dice!\n");
				system("pause");

				continue_current_player_round = 1;
				rolls = 0;
				init_frequency_table(freq_table, 7);
				combination_search_attempted = 0;

				while (continue_current_player_round)
				{
					printf("\n");
					printf("Roll #%d:\n", rolls + 1);
					roll_dice(dice, 5);

					printf("\n");
					for (int i = 0; i < 5; i++)
					{
						printf("Die %d: %d\n", i + 1, dice[i]);
					}

					printf("\n");

					rolls++;

					determine_dice_frequencies(dice, freq_table, 7);

					for (int i = 1; i < 7; i++)
					{
						printf("Number of %ds rolled: %d\n", i, freq_table[i]);
					}

					printf("\n");

					continue_current_player_round = 0;

					while (rolls < 3)
					{
						printf("Would you like to use this dice roll for one of the game combinations? ");
						roll_usage_decision = ask_yes_no();

						if (roll_usage_decision == 1)
						{
							combination_search_attempted = 1;
							printf("Let's see what combination you'd like to use :)\n");

							combination_choice = ask_for_combination();

							switch (combination_choice)
							{
							case 1:
							case 2:
							case 3:
							case 4:
							case 5:
							case 6:
								potential_round_points = sum_of_same_dice_sides(freq_table, combination_choice);
								printf("\n");
								printf("Potential round points: %d\n", potential_round_points);
								if (current_player == 1)
								{
									if (player_one_scorecard[combination_choice] == -1)
									{
										printf("\n");
										printf("You've now used combination type %d for this game!\n", combination_choice);
										points_earned_this_round = potential_round_points;
										player_one_scorecard[combination_choice]++;
										p1_uppper_section_score_card += potential_round_points;
									}
									else
									{
										printf("\n");
										printf("Uh-oh... you've already used combination type %d!\n", combination_choice);
										points_earned_this_round = 0;
									}
								}
								else
								{
									if (player_two_scorecard[combination_choice] == -1)
									{
										printf("\n");
										printf("You've now used combination type %d for this game!\n", combination_choice);
										points_earned_this_round = potential_round_points;
										player_two_scorecard[combination_choice]++;
										p2_uppper_section_score_card += potential_round_points;
									}
									else
									{
										printf("\n");
										printf("Uh-oh... you've already used combination type %d!\n", combination_choice);
										points_earned_this_round = 0;
									}
								}
								rolls = 3;
								break;
							case 7:
								potential_round_points = sum_all_face_values(dice);
								printf("\n");
								printf("Potential round points: %d\n", potential_round_points);

								combination_earned = is_three_of_a_kind(freq_table);
								printf("Combination earned: %d", combination_earned);

								if (current_player == 1)
								{
									if (player_one_scorecard[combination_choice] == -1 && combination_earned)
									{
										printf("\n");
										printf("You've now used combination type %d for this game!\n", combination_choice);
										points_earned_this_round = potential_round_points;
										player_one_scorecard[combination_choice]++;
									}
									else
									{
										printf("\n");
										printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
										points_earned_this_round = 0;
									}
								}
								else
								{
									if (player_two_scorecard[combination_choice] == -1 && combination_earned)
									{
										printf("\n");
										printf("You've now used combination type %d for this game!\n", combination_choice);
										points_earned_this_round = potential_round_points;
										player_two_scorecard[combination_choice]++;
									}
									else
									{
										printf("\n");
										printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
										points_earned_this_round = 0;
									}
								}
								rolls = 3;
								break;
							case 8:
								potential_round_points = sum_all_face_values(dice);
								printf("\n");
								printf("Potential round points: %d\n", potential_round_points);

								combination_earned = is_four_of_a_kind(freq_table);
								printf("Combination earned: %d", combination_earned);

								if (current_player == 1)
								{
									if (player_one_scorecard[combination_choice] == -1 && combination_earned)
									{
										printf("\n");
										printf("You've now used combination type %d for this game!\n", combination_choice);
										points_earned_this_round = potential_round_points;
										player_one_scorecard[combination_choice]++;
									}
									else
									{
										printf("\n");
										printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
										points_earned_this_round = 0;
									}
								}
								else
								{
									if (player_two_scorecard[combination_choice] == -1 && combination_earned)
									{
										printf("\n");
										printf("You've now used combination type %d for this game!\n", combination_choice);
										points_earned_this_round = potential_round_points;
										player_two_scorecard[combination_choice]++;
									}
									else
									{
										printf("\n");
										printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
										points_earned_this_round = 0;
									}
								}
								rolls = 3;
								break;
							case 9:
								potential_round_points = 25;
								printf("\n");
								printf("Potential round points: %d\n", potential_round_points);

								combination_earned = is_full_house(freq_table);
								printf("Combination earned: %d", combination_earned);

								if (current_player == 1)
								{
									if (player_one_scorecard[combination_choice] == -1 && combination_earned)
									{
										printf("\n");
										printf("You've now used combination type %d for this game!\n", combination_choice);
										points_earned_this_round = potential_round_points;
										player_one_scorecard[combination_choice]++;
									}
									else
									{
										printf("\n");
										printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
										points_earned_this_round = 0;
									}
								}
								else
								{
									if (player_two_scorecard[combination_choice] == -1 && combination_earned)
									{
										printf("\n");
										printf("You've now used combination type %d for this game!\n", combination_choice);
										points_earned_this_round = potential_round_points;
										player_two_scorecard[combination_choice]++;
									}
									else
									{
										printf("\n");
										printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
										points_earned_this_round = 0;
									}
								}
								rolls = 3;
								break;
							case 10:
								potential_round_points = 30;
								printf("\n");
								printf("Potential round points: %d\n", potential_round_points);

								combination_earned = is_small_straight(freq_table);
								printf("Combination earned: %d", combination_earned);

								if (current_player == 1)
								{
									if (player_one_scorecard[combination_choice] == -1 && combination_earned)
									{
										printf("\n");
										printf("You've now used combination type %d for this game!\n", combination_choice);
										points_earned_this_round = potential_round_points;
										player_one_scorecard[combination_choice]++;
									}
									else
									{
										printf("\n");
										printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
										points_earned_this_round = 0;
									}
								}
								else
								{
									if (player_two_scorecard[combination_choice] == -1 && combination_earned)
									{
										printf("\n");
										printf("You've now used combination type %d for this game!\n", combination_choice);
										points_earned_this_round = potential_round_points;
										player_two_scorecard[combination_choice]++;
									}
									else
									{
										printf("\n");
										printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
										points_earned_this_round = 0;
									}
								}
								rolls = 3;
								break;
							case 11:
								potential_round_points = 40;
								printf("\n");
								printf("Potential round points: %d\n", potential_round_points);

								combination_earned = is_large_straight(freq_table);
								printf("Combination earned: %d", combination_earned);

								if (current_player == 1)
								{
									if (player_one_scorecard[combination_choice] == -1 && combination_earned)
									{
										printf("\n");
										printf("You've now used combination type %d for this game!\n", combination_choice);
										points_earned_this_round = potential_round_points;
										player_one_scorecard[combination_choice]++;
									}
									else
									{
										printf("\n");
										printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
										points_earned_this_round = 0;
									}
								}
								else
								{
									if (player_two_scorecard[combination_choice] == -1 && combination_earned)
									{
										printf("\n");
										printf("You've now used combination type %d for this game!\n", combination_choice);
										points_earned_this_round = potential_round_points;
										player_two_scorecard[combination_choice]++;
									}
									else
									{
										printf("\n");
										printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
										points_earned_this_round = 0;
									}
								}
								rolls = 3;
								break;
							case 12:
								potential_round_points = 50;
								printf("\n");
								printf("Potential round points: %d\n", potential_round_points);

								combination_earned = is_yahtzee(freq_table);
								printf("Combination earned: %d", combination_earned);

								if (current_player == 1)
								{
									if (player_one_scorecard[combination_choice] == -1 && combination_earned)
									{
										printf("\n");
										printf("You've now used combination type %d for this game!\n", combination_choice);
										points_earned_this_round = potential_round_points;
										player_one_scorecard[combination_choice]++;
									}
									else
									{
										printf("\n");
										printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
										points_earned_this_round = 0;
									}
								}
								else
								{
									if (player_two_scorecard[combination_choice] == -1 && combination_earned)
									{
										printf("\n");
										printf("You've now used combination type %d for this game!\n", combination_choice);
										points_earned_this_round = potential_round_points;
										player_two_scorecard[combination_choice]++;
									}
									else
									{
										printf("\n");
										printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
										points_earned_this_round = 0;
									}
								}
								rolls = 3;
								break;
							case 13:
								potential_round_points = sum_all_face_values(dice);
								printf("\n");
								printf("Potential round points: %d\n", potential_round_points);
								if (current_player == 1)
								{
									if (player_one_scorecard[combination_choice] == -1)
									{
										printf("\n");
										printf("You've now used combination type %d for this game!\n", combination_choice);
										points_earned_this_round = potential_round_points;
										player_one_scorecard[combination_choice]++;
									}
									else
									{
										printf("\n");
										printf("Uh-oh... you've already used combination type %d!\n", combination_choice);
										points_earned_this_round = 0;
									}
								}
								else
								{
									if (player_two_scorecard[combination_choice] == -1)
									{
										printf("\n");
										printf("You've now used combination type %d for this game!\n", combination_choice);
										points_earned_this_round = potential_round_points;
										player_two_scorecard[combination_choice]++;
									}
									else
									{
										printf("\n");
										printf("Uh-oh... you've already used combination type %d!\n", combination_choice);
										points_earned_this_round = 0;
									}
								}
								rolls = 3;
								break;
							}
						}
						else
						{
							printf("Let's see which dice you'd like to re-roll :)\n");

							printf("\n");
							printf("Roll #%d:\n", rolls + 1);
							for (int i = 0; i < 5; i++)
							{
								printf("\n");
								printf("Would you like to roll die %d? ", i + 1);
								roll_current_die = ask_yes_no();
								if (roll_current_die == 1)
								{
									dice[i] = rand() % DIE_FACES + 1;
									printf("New value for die %d: %d\n", i + 1, dice[i]);
								}
								else
								{
									printf("Keeping value for die %d as: %d\n", i + 1, dice[i]);
								}
							}

							printf("\n");
							for (int i = 0; i < 5; i++)
							{
								printf("Die %d: %d\n", i + 1, dice[i]);
							}

							printf("\n");

							rolls++;

							determine_dice_frequencies(dice, freq_table, 7);

							for (int i = 1; i < 7; i++)
							{
								printf("Number of %ds rolled: %d\n", i, freq_table[i]);
							}
						}
					}
					if (!combination_search_attempted)
					{
						printf("\n");
						printf("Last chance to search for a combination in the current round!\n");

						combination_search_attempted = 1;
						printf("Let's see what combination you'd like to use :)\n");

						combination_choice = ask_for_combination();

						switch (combination_choice)
						{
						case 1:
						case 2:
						case 3:
						case 4:
						case 5:
						case 6:
							potential_round_points = sum_of_same_dice_sides(freq_table, combination_choice);
							printf("\n");
							printf("Potential round points: %d\n", potential_round_points);
							if (current_player == 1)
							{
								if (player_one_scorecard[combination_choice] == -1)
								{
									printf("\n");
									printf("You've now used combination type %d for this game!\n", combination_choice);
									points_earned_this_round = potential_round_points;
									player_one_scorecard[combination_choice]++;
									p1_uppper_section_score_card += potential_round_points;
								}
								else
								{
									printf("\n");
									printf("Uh-oh... you've already used combination type %d!\n", combination_choice);
									points_earned_this_round = 0;
								}
							}
							else
							{
								if (player_two_scorecard[combination_choice] == -1)
								{
									printf("\n");
									printf("You've now used combination type %d for this game!\n", combination_choice);
									points_earned_this_round = potential_round_points;
									player_two_scorecard[combination_choice]++;
									p2_uppper_section_score_card += potential_round_points;
								}
								else
								{
									printf("\n");
									printf("Uh-oh... you've already used combination type %d!\n", combination_choice);
									points_earned_this_round = 0;
								}
							}

							break;
						case 7:
							potential_round_points = sum_all_face_values(dice);
							printf("\n");
							printf("Potential round points: %d\n", potential_round_points);

							combination_earned = is_three_of_a_kind(freq_table);
							printf("Combination earned: %d", combination_earned);

							if (current_player == 1)
							{
								if (player_one_scorecard[combination_choice] == -1 && combination_earned)
								{
									printf("\n");
									printf("You've now used combination type %d for this game!\n", combination_choice);
									points_earned_this_round = potential_round_points;
									player_one_scorecard[combination_choice]++;
								}
								else
								{
									printf("\n");
									printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
									points_earned_this_round = 0;
								}
							}
							else
							{
								if (player_two_scorecard[combination_choice] == -1 && combination_earned)
								{
									printf("\n");
									printf("You've now used combination type %d for this game!\n", combination_choice);
									points_earned_this_round = potential_round_points;
									player_two_scorecard[combination_choice]++;
								}
								else
								{
									printf("\n");
									printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
									points_earned_this_round = 0;
								}
							}
							break;
						case 8:
							potential_round_points = sum_all_face_values(dice);
							printf("\n");
							printf("Potential round points: %d\n", potential_round_points);

							combination_earned = is_four_of_a_kind(freq_table);
							printf("Combination earned: %d", combination_earned);

							if (current_player == 1)
							{
								if (player_one_scorecard[combination_choice] == -1 && combination_earned)
								{
									printf("\n");
									printf("You've now used combination type %d for this game!\n", combination_choice);
									points_earned_this_round = potential_round_points;
									player_one_scorecard[combination_choice]++;
								}
								else
								{
									printf("\n");
									printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
									points_earned_this_round = 0;
								}
							}
							else
							{
								if (player_two_scorecard[combination_choice] == -1 && combination_earned)
								{
									printf("\n");
									printf("You've now used combination type %d for this game!\n", combination_choice);
									points_earned_this_round = potential_round_points;
									player_two_scorecard[combination_choice]++;
								}
								else
								{
									printf("\n");
									printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
									points_earned_this_round = 0;
								}
							}
							break;
						case 9:
							potential_round_points = 25;
							printf("\n");
							printf("Potential round points: %d\n", potential_round_points);

							combination_earned = is_full_house(freq_table);
							printf("Combination earned: %d", combination_earned);

							if (current_player == 1)
							{
								if (player_one_scorecard[combination_choice] == -1 && combination_earned)
								{
									printf("\n");
									printf("You've now used combination type %d for this game!\n", combination_choice);
									points_earned_this_round = potential_round_points;
									player_one_scorecard[combination_choice]++;
								}
								else
								{
									printf("\n");
									printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
									points_earned_this_round = 0;
								}
							}
							else
							{
								if (player_two_scorecard[combination_choice] == -1 && combination_earned)
								{
									printf("\n");
									printf("You've now used combination type %d for this game!\n", combination_choice);
									points_earned_this_round = potential_round_points;
									player_two_scorecard[combination_choice]++;
								}
								else
								{
									printf("\n");
									printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
									points_earned_this_round = 0;
								}
							}
							break;
						case 10:
							potential_round_points = 30;
							printf("\n");
							printf("Potential round points: %d\n", potential_round_points);

							combination_earned = is_small_straight(freq_table);
							printf("Combination earned: %d", combination_earned);

							if (current_player == 1)
							{
								if (player_one_scorecard[combination_choice] == -1 && combination_earned)
								{
									printf("\n");
									printf("You've now used combination type %d for this game!\n", combination_choice);
									points_earned_this_round = potential_round_points;
									player_one_scorecard[combination_choice]++;
								}
								else
								{
									printf("\n");
									printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
									points_earned_this_round = 0;
								}
							}
							else
							{
								if (player_two_scorecard[combination_choice] == -1 && combination_earned)
								{
									printf("\n");
									printf("You've now used combination type %d for this game!\n", combination_choice);
									points_earned_this_round = potential_round_points;
									player_two_scorecard[combination_choice]++;
								}
								else
								{
									printf("\n");
									printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
									points_earned_this_round = 0;
								}
							}
							break;
						case 11:
							potential_round_points = 40;
							printf("\n");
							printf("Potential round points: %d\n", potential_round_points);

							combination_earned = is_large_straight(freq_table);
							printf("Combination earned: %d", combination_earned);

							if (current_player == 1)
							{
								if (player_one_scorecard[combination_choice] == -1 && combination_earned)
								{
									printf("\n");
									printf("You've now used combination type %d for this game!\n", combination_choice);
									points_earned_this_round = potential_round_points;
									player_one_scorecard[combination_choice]++;
								}
								else
								{
									printf("\n");
									printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
									points_earned_this_round = 0;
								}
							}
							else
							{
								if (player_two_scorecard[combination_choice] == -1 && combination_earned)
								{
									printf("\n");
									printf("You've now used combination type %d for this game!\n", combination_choice);
									points_earned_this_round = potential_round_points;
									player_two_scorecard[combination_choice]++;
								}
								else
								{
									printf("\n");
									printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
									points_earned_this_round = 0;
								}
							}
							break;
						case 12:
							potential_round_points = 50;
							printf("\n");
							printf("Potential round points: %d\n", potential_round_points);

							combination_earned = is_yahtzee(freq_table);
							printf("Combination earned: %d", combination_earned);

							if (current_player == 1)
							{
								if (player_one_scorecard[combination_choice] == -1 && combination_earned)
								{
									printf("\n");
									printf("You've now used combination type %d for this game!\n", combination_choice);
									points_earned_this_round = potential_round_points;
									player_one_scorecard[combination_choice]++;
								}
								else
								{
									printf("\n");
									printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
									points_earned_this_round = 0;
								}
							}
							else
							{
								if (player_two_scorecard[combination_choice] == -1 && combination_earned)
								{
									printf("\n");
									printf("You've now used combination type %d for this game!\n", combination_choice);
									points_earned_this_round = potential_round_points;
									player_two_scorecard[combination_choice]++;
								}
								else
								{
									printf("\n");
									printf("Uh-oh... you've either already used combination type %d, or do not currently have it!\n", combination_choice);
									points_earned_this_round = 0;
								}
							}
							break;
						case 13:
							potential_round_points = sum_all_face_values(dice);
							printf("\n");
							printf("Potential round points: %d\n", potential_round_points);
							if (current_player == 1)
							{
								if (player_one_scorecard[combination_choice] == -1)
								{
									printf("\n");
									printf("You've now used combination type %d for this game!\n", combination_choice);
									points_earned_this_round = potential_round_points;
									player_one_scorecard[combination_choice]++;
								}
								else
								{
									printf("\n");
									printf("Uh-oh... you've already used combination type %d!\n", combination_choice);
									points_earned_this_round = 0;
								}
							}
							else
							{
								if (player_two_scorecard[combination_choice] == -1)
								{
									printf("\n");
									printf("You've now used combination type %d for this game!\n", combination_choice);
									points_earned_this_round = potential_round_points;
									player_two_scorecard[combination_choice]++;
								}
								else
								{
									printf("\n");
									printf("Uh-oh... you've already used combination type %d!\n", combination_choice);
									points_earned_this_round = 0;
								}
							}
							break;
						}

					}
				}

				if (current_player == 1)
				{
					player_one_points += points_earned_this_round;
					printf("You've earned %d points this round!\n", points_earned_this_round);
					printf("So, your point total is: %d\n", player_one_points);
				}
				else
				{
					player_two_points += points_earned_this_round;
					printf("You've earned %d points this round!\n", points_earned_this_round);
					printf("So, your point total is: %d\n", player_two_points);
				}

				current_player++;
				printf("\n");
				system("pause");
			}
			rounds_played++;
		}

		printf("\n");
		printf("Woo hoo, all 13 rounds have been played! Calculating upper sections\n");
		printf("of each player's scorecard to check for the bonus 35 points...\n");
		system("pause");

		printf("\n");
		printf("Player 1 has %d points in the upper section of their scorecard!\n", p1_uppper_section_score_card);
		printf("Player 2 has %d points in the upper section of their scorecard!\n", p2_uppper_section_score_card);
		system("pause");

		if (p1_uppper_section_score_card >= BONUS_MINIMUM_SUM)
		{
			player_one_points += BONUS_POINTS;
			printf("\n");
			printf("Player 1 gets the 35 bonus points!\n");
		}
		else
		{
			printf("\n");
			printf("No bonus points for Player 1...\n");
		}

		if (p2_uppper_section_score_card >= BONUS_MINIMUM_SUM)
		{
			player_two_points += BONUS_POINTS;
			printf("\n");
			printf("Player 2 gets the 35 bonus points!\n");
		}
		else
		{
			printf("\n");
			printf("No bonus points for Player 2...\n");
		}

		printf("\n");
		printf("And now... the moment you've been waiting for...\n");
		system("pause");

		printf("Player 1 earned %d total points!\n", player_one_points);
		printf("Player 2 earned %d total points!\n", player_two_points);

		if (player_one_points > player_two_points)
		{
			printf("\n");
			printf("And the winner is... Player 1! Congrats!! :D\n");
			system("pause");
		}
		else if (player_two_points > player_one_points)
		{
			printf("\n");
			printf("And the winner is... Player 2! Congrats!! :D\n");
			system("pause");
		}
		else
		{
			printf("\n");
			printf("Well what do you know... It's a tie! Friendship wins!! :D\n");
			system("pause");
		}

		printf("\n");
		printf("What a game! Returning to main menu :D\n");
		system("pause");
		game_over = 1;
	} while (!game_over);
}

// Set all values of a scorecard to default values of -1
// Preconditions: the scorecard contains integer values, and
// the size is at least one
void init_scorecard(int *scorecard_ptr, int size)
{
	int index = 0;

	while (index < size)
	{
		scorecard_ptr[index] = -1;
		index++;
	}
}

// Set all values of a frequency table to default values of 0
// Preconditions: The frequency table contains intger values, and
// the size is at least one
void init_frequency_table(int* frequency_table, int size)
{
	int index = 0;

	while (index < size)
	{
		frequency_table[index] = 0;
		index++;
	}
}

// Randomly generates values and places them in an array of dice
// Preconditions: the dice array stores integer values and has
// a size of at least one
void roll_dice(int *dice_array, int size)
{
	for (int die_count = 0; die_count < size; die_count++)
	{
		dice_array[die_count] = rand() % DIE_FACES + 1;
	}
}

// Finds how many times each possible dice side has been found in the current roll
// Preconditions: The dice and frequency arrays store integer values, and the
// size of the dice array is at least one
void determine_dice_frequencies(int* dice_array, int* frequency_array, int frequency_array_size)
{
	int occurrence_tracker = 0;
	for (int dice_side = 1; dice_side < frequency_array_size; dice_side++)
	{
		occurrence_tracker = find_number_of_occurrences(dice_array, 5, dice_side);
		frequency_array[dice_side] = occurrence_tracker;
	}
}

// Finds how many times a target value repeats in an array of numbers
// Preconditions: The array stores integer values, and its size along with
// the target value are both integers. Size is at least one.
int find_number_of_occurrences(int *array_of_nums, int size, int target_num)
{
	int target_count = 0;

	for (int index = 0; index < size; index++)
	{
		if (array_of_nums[index] == target_num)
		{
			target_count++;
		}
	}

	return target_count;
}

// Prints the scorecard for player 1 or player 2
// Preconditions: The two player scorecards store integer values, and the current_player and
// size variables are each integer values. Size is at least one.
void print_current_scorecard(int *scorecard_p1, int *scorecard_p2, int current_player, int size)
{
	printf("Here's your current scorecard (-1 means not used; 0 means used!):\n");
	if (current_player == 1)
	{
		for (int i = 1; i < size; i++)
		{
			switch (i)
			{
			case 1:
				printf("1. Sum of 1's: %d\n", scorecard_p1[i]);
				break;
			case 2:
				printf("2. Sum of 2's: %d\n", scorecard_p1[i]);
				break;
			case 3:
				printf("3. Sum of 3's: %d\n", scorecard_p1[i]);
				break;
			case 4:
				printf("4. Sum of 4's: %d\n", scorecard_p1[i]);
				break;
			case 5:
				printf("5. Sum of 5's: %d\n", scorecard_p1[i]);
				break;
			case 6:
				printf("6. Sum of 6's: %d\n", scorecard_p1[i]);
				break;
			case 7:
				printf("7. Three-of-a-kind: %d\n", scorecard_p1[i]);
				break;
			case 8:
				printf("8. Four-of-a-kind: %d\n", scorecard_p1[i]);
				break;
			case 9:
				printf("9. Full house: %d\n", scorecard_p1[i]);
				break;
			case 10:
				printf("10. Small straight: %d\n", scorecard_p1[i]);
				break;
			case 11:
				printf("11. Large straight: %d\n", scorecard_p1[i]);
				break;
			case 12:
				printf("12. Yahtzee: %d\n", scorecard_p1[i]);
				break;
			case 13:
				printf("13. Chance: %d\n", scorecard_p1[i]);
				break;
			}
		}
	}
	else
	{
		for (int i = 1; i < size; i++)
		{
			switch (i)
			{
			case 1:
				printf("1. Sum of 1's: %d\n", scorecard_p2[i]);
				break;
			case 2:
				printf("2. Sum of 2's: %d\n", scorecard_p2[i]);
				break;
			case 3:
				printf("3. Sum of 3's: %d\n", scorecard_p2[i]);
				break;
			case 4:
				printf("4. Sum of 4's: %d\n", scorecard_p2[i]);
				break;
			case 5:
				printf("5. Sum of 5's: %d\n", scorecard_p2[i]);
				break;
			case 6:
				printf("6. Sum of 6's: %d\n", scorecard_p2[i]);
				break;
			case 7:
				printf("7. Three-of-a-kind: %d\n", scorecard_p2[i]);
				break;
			case 8:
				printf("8. Four-of-a-kind: %d\n", scorecard_p2[i]);
				break;
			case 9:
				printf("9. Full house: %d\n", scorecard_p2[i]);
				break;
			case 10:
				printf("10. Small straight: %d\n", scorecard_p2[i]);
				break;
			case 11:
				printf("11. Large straight: %d\n", scorecard_p2[i]);
				break;
			case 12:
				printf("12. Yahtzee: %d\n", scorecard_p2[i]);
				break;
			case 13:
				printf("13. Chance: %d\n", scorecard_p2[i]);
				break;
			}
		}
	}
	
}

// Asks the user to type 1 for yes or 2 for now, then returns the result
// Preconditions: user enters an integer value
int ask_yes_no(void)
{
	int user_decision = 0, valid = 0;
	do
	{
		printf("1 means yes; 2 means no :D\n");
		scanf("%d", &user_decision);
		printf("You chose: %d!\n", user_decision);
		valid = is_yes_no_choice_valid(user_decision);
	} while (!valid);
	return user_decision;
}

// Checks whether the user typed 1 for yes or 2 for now for their decision
// Preconditions: user enters an integer value
int is_yes_no_choice_valid(int user_choice)
{
	return !(user_choice < YES || user_choice > NO);
}

// Asks user which of the 13 combinations they would like to use for current roll
// Preconditions: user enters an integer value
int ask_for_combination(void)
{
	int user_decision = 0, valid = 0;
	do
	{
		printf("\n");
		printf("Enter a number 1-13 for the combination you'd like to use!\n");
		printf("Caution: If you enter a combination you've already used or that\n");
		printf("does not exist, you'll earn 0 points for the current round :D\n");
		scanf("%d", &user_decision);
		printf("You chose: %d!\n", user_decision);
		valid = combination_choice_valid(user_decision);
	} while (!valid);
	return user_decision;
}

// Checks whether the user entered a value between 1 and 13 to use one of the combinations
// Preconditions: user enters an integer value
int combination_choice_valid(int user_choice)
{
	return !(user_choice < FIRST_COMBINATION || user_choice > LAST_COMBINATION);
}

// Calculates the sum of a specific side of dice from the five rolled dice
// Preconditions: frequency table stores integer values; the side to check
// is an integer value
int sum_of_same_dice_sides(int* frequency_table, int side_to_check)
{
	int number_of_repetitions = 0, sum_to_return = 0;

	number_of_repetitions = frequency_table[side_to_check];

	for (int i = 0; i < number_of_repetitions; i++)
	{
		sum_to_return += side_to_check;
	}

	return sum_to_return;
}

// Calculates the sum of the sides of all five dice rolled for the current round
// Preconditions: dice array contains integer values
int sum_all_face_values(int *dice_array)
{
	int sum_to_return = 0;

	for (int i = 0; i < 5; i++)
	{
		sum_to_return += dice_array[i];
	}

	return sum_to_return;
}

// Checks whether the player has earned three of a kind
// Preconditions: frequency table stores integer values
int is_three_of_a_kind(int *frequency_table)
{
	int are_there_three = 0;

	for (int i = 1; i < 7; i++)
	{
		if (frequency_table[i] >= 3)
		{
			are_there_three = 1;
		}
	}

	return are_there_three;
}

// Checks whether the player has earned four of a kind
// Preconditions: frequency table stores integer values
int is_four_of_a_kind(int* frequency_table)
{
	int are_there_four = 0;

	for (int i = 1; i < 7; i++)
	{
		if (frequency_table[i] >= 4)
		{
			are_there_four = 1;
		}
	}

	return are_there_four;
}

// Checks whether the player has earned yahtzee
// Preconditions: frequency table stores integer values
int is_yahtzee(int* frequency_table)
{
	int are_there_five = 0;

	for (int i = 1; i < 7; i++)
	{
		if (frequency_table[i] == 5)
		{
			are_there_five = 1;
		}
	}

	return are_there_five;
}

// Checks whether the player has earned full house
// Preconditions: frequency table stores integer values
int is_full_house(int* frequency_table)
{
	int are_there_two = 0;
	int are_there_three = 0;
	int full_house = 0;

	for (int i = 1; i < 7; i++)
	{
		if (frequency_table[i] == 2)
		{
			are_there_two = 1;
		}

		if (frequency_table[i] == 3)
		{
			are_there_three = 1;
		}
		
		if (frequency_table[i] == 5)
		{
			are_there_two = 1;
			are_there_three = 1;
		}
	}

	if (are_there_two && are_there_three)
	{
		full_house = 1;
	}

	return full_house;
}

// Checks whether the player has earned small straight
// Preconditions: frequency table stores integer values
int is_small_straight(int* frequency_table)
{
	int straight_met = 0;
	if (frequency_table[1] > 0 && frequency_table[2] > 0 && frequency_table[3] > 0 && frequency_table[4] > 0)
	{
		straight_met = 1;
	}
	else if (frequency_table[2] > 0 && frequency_table[3] > 0 && frequency_table[4] > 0 && frequency_table[5] > 0)
	{
		straight_met = 1;
	}
	else if (frequency_table[3] > 0 && frequency_table[4] > 0 && frequency_table[5] > 0 && frequency_table[6] > 0)
	{
		straight_met = 1;
	}

	return straight_met;
}

// Checks whether the player has earned large straight
// Preconditions: frequency table stores integer values
int is_large_straight(int* frequency_table)
{
	int straight_met = 0;
	if (frequency_table[1] > 0 && frequency_table[2] > 0 && frequency_table[3] > 0 && frequency_table[4] > 0 && frequency_table[5])
	{
		straight_met = 1;
	}
	else if (frequency_table[2] > 0 && frequency_table[3] > 0 && frequency_table[4] > 0 && frequency_table[5] > 0 && frequency_table[6])
	{
		straight_met = 1;
	}

	return straight_met;
}