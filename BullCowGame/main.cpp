/* This is the console executable, that makes use of the BullCowClass.
   This acts as the view in a MVC pattern, and is responsible for all
   user interaction. For game logic, see the FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include "FBullCowGame.h"

// making it conform to Unreal types.
using FText = std::string;
using int32 = int;

void PrintIntro();
void AskForWordSize();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

// Game object that gets re-used.
FBullCowGame BCGame;

int main()
{
	do
	{
		PrintIntro();
		AskForWordSize();
		PlayGame();
	} while (AskToPlayAgain());

	std::cout << std::endl;
	return 0;
}

void PrintIntro()
{
	std::cout << "                                               ,-,--.  " << std::endl;
	std::cout << "    _..---.  .--.-. .-.-.  _.-.      _.-.    ,-.'-  _\\ " << std::endl;
	std::cout << "  .' .'.-. \\/==/ -|/=/  |.-,.'|    .-,.'|   /==/_ ,_.' " << std::endl;
	std::cout << " /==/- '=' /|==| ,||=| -|==|, |   |==|, |   \\==\\  \\    " << std::endl;
	std::cout << " |==|-,   ' |==|- | =/  |==|- |   |==|- |    \\==\\ -\\   " << std::endl;
	std::cout << " |==|  .=. \\|==|,  \\/ - |==|, |   |==|, |    _\\==\\ ,\\  " << std::endl;
	std::cout << " /==/- '=' ,|==|-   ,   /==|- `-._|==|- `-._/==/\\/ _ | " << std::endl;
	std::cout << "|==|   -   //==/ , _  .'/==/ - , ,/==/ - , ,|==\\ - , / " << std::endl;
	std::cout << "`-._`.___,' `--`..---'  `--`-----'`--`-----' `--`---'  " << std::endl;
	std::cout << "   ,---.      .-._                                     " << std::endl;
	std::cout << " .--.'  \\    /==/ \\  .-._  _,..---._                   " << std::endl;
	std::cout << " \\==\\-/\\ \\   |==|, \\/ /, /==/,   -  \\                  " << std::endl;
	std::cout << " /==/-|_\\ |  |==|-  \\|  ||==|   _   _\\                 " << std::endl;
	std::cout << " \\==\\,   - \\ |==| ,  | -||==|  .=.   |                 " << std::endl;
	std::cout << " /==/ -   ,| |==| -   _ ||==|,|   | -|                 " << std::endl;
	std::cout << "/==/-  /\\ - \\|==|  /\\ , ||==|  '='   /                 " << std::endl;
	std::cout << "\\==\\ _.\\=\\.-'/==/, | |- ||==|-,   _`/                  " << std::endl;
	std::cout << " `--`        `--`./  `--``-.`.____.'                   " << std::endl;
	std::cout << "   _,.----.     _,.---._            ,-.-.   ,-,--.     " << std::endl;
	std::cout << " .' .' -   \\  ,-.' , -  `. ,-..-.-./  \\==\\,-.'-  _\\    " << std::endl;
	std::cout << "/==/  ,  ,-' /==/_,  ,  - \\|, \\=/\\=|- |==/==/_ ,_.'    " << std::endl;
	std::cout << "|==|-   |  .|==|   .=.     |- |/ |/ , /==|==\\  \\       " << std::endl;
	std::cout << "|==|_   `-' \\==|_ : ;=:  - |\\, ,     _|==|\\==\\ -\\      " << std::endl;
	std::cout << "|==|   _  , |==| , '='     || -  -  , |==|_\\==\\ ,\\     " << std::endl;
	std::cout << "\\==\\.       /\\==\\ -    ,_ /  \\  ,  - /==//==/\\/ _ |    " << std::endl;
	std::cout << " `-.`.___.-'  '.='. -   .'   |-  /\\ /==/ \\==\\ - , /    " << std::endl;
	std::cout << "                `--`--''     `--`  `--`   `--`---'     " << std::endl;
	std::cout << "\nA fun old code-breaking word game.";
	std::cout << std::endl;
}

void AskForWordSize()
{
	int32 wordSize;
	FText response = "";
	do
	{
		std::cout << "What size of isogram would you like (3-8)? ";
		std::getline(std::cin, response);
		
		wordSize = std::atoi(response.c_str());


	} while (wordSize < 3 || wordSize > 8);

	BCGame.SetHiddenWordBySize(wordSize);

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
}

/// Plays a single game to completion.
void PlayGame()
{
	int maxTries = BCGame.GetMaxTries();
	
	FText guess = "";
	// loop asking for guesses while game 
	// is not won, and still tries left.
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		guess = GetValidGuess();

		// submit valid guess to game
		FBullCowCount bullCowCount = BCGame.SubmitValidGuess(guess);
		// print bulls/cows.
		std::cout << "Bulls: " << bullCowCount.Bulls;
		std::cout << ". Cows: " << bullCowCount.Cows;

		std::cout << std::endl << std::endl;
	}

	PrintGameSummary();
}

/// gets a valid guess from the player, loops until valid.
FText GetValidGuess()
{
	FText guess = "";
	EGuessStatus status = EGuessStatus::Invalid_Status;
	do
	{
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, guess);

		status = BCGame.CheckGuessValidity(guess);

		switch (status)
		{
			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter a word with no repeating letters.\n\n";
				break;
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Please enter the word in all lower case.\n\n";
				break;
			default:
				// assume guess is valid
				break;
		}
	} while (status != EGuessStatus::OK);

	return guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	FText response = "";
	std::getline(std::cin, response);

	return (response[0] == 'y' || response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "                                                        .---.                      " << std::endl;
		std::cout << "        ,---,                                          /. ./|  ,--,                " << std::endl;
		std::cout << "       /_ ./|   ,---.           ,--,               .--'.  ' ;,--.'|         ,---,  " << std::endl;
		std::cout << " ,---, |  ' :  '   ,'\\        ,'_ /|              /__./ \\ : ||  |,      ,-+-. /  | " << std::endl;
		std::cout << "/___/ \\.  : | /   /   |  .--. |  | :          .--'.  '   \\' .`--'_     ,--.'|'   | " << std::endl;
		std::cout << " .  \\  \\ ,' '.   ; ,. :,'_ /| :  . |         /___/ \\ |    ' ',' ,'|   |   |  ,\"' | " << std::endl;
		std::cout << "  \\  ;  `  ,''   | |: :|  ' | |  . .         ;   \\  \\;      :'  | |   |   | /  | | " << std::endl;
		std::cout << "   \\  \\    ' '   | .; :|  | ' |  | |          \\   ;  `      ||  | :   |   | |  | | " << std::endl;
		std::cout << "    '  \\   | |   :    |:  | : ;  ; |           .   \\    .\\  ;'  : |__ |   | |  |/  " << std::endl;
		std::cout << "     \\  ;  ;  \\   \\  / '  :  `--'   \\           \\   \\   ' \\ ||  | '.'||   | |--'   " << std::endl;
		std::cout << "      :  \\  \\  `----'  :  ,      .-./            :   '  |--\" ;  :    ;|   |/       " << std::endl;
		std::cout << "       \\  ' ;           `--`----'                 \\   \\ ;    |  ,   / '---'        " << std::endl;
		std::cout << "        `--`                                       '---\"      ---`-'               " << std::endl;
	}
	else
	{
		std::cout << ",--.   ,--.                                     " << std::endl;
		std::cout << " \\  `.'  /,---. ,--.,--.                        " << std::endl;
		std::cout << "  '.    /| .-. ||  ||  |                        " << std::endl;
		std::cout << "    |  | ' '-' ''  ''  '    ,---.               " << std::endl;
		std::cout << ",--.`--'  `---'  `----'     |   |           ,-. " << std::endl;
		std::cout << "|  |    ,---.  ,---.  ,---. |  .'    ,---. / .' " << std::endl;
		std::cout << "|  |   | .-. |(  .-' | .-. :|  |     '---'|  |  " << std::endl;
		std::cout << "|  '--.' '-' '.-'  `)\\   --.`--'     ,---.|  |  " << std::endl;
		std::cout << "`-----' `---' `----'  `----'.--.     '---' \\ '. " << std::endl;
		std::cout << "                            '--'            `-' " << std::endl;
	}
}
