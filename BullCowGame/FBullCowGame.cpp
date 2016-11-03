#pragma once
#include "FBullCowGame.h"
#include <map>
#include <time.h>

#define TMap std::map

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return CurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}

void FBullCowGame::Reset()
{
	srand((unsigned int)time(NULL));

	const FString HIDDEN_3_LETTER_WORDS[13] = { "yes", "lap", "you", "lit", "put", "cat", "fat", "top", "wet", "lop", "kid", "men", "key" };
	const FString HIDDEN_4_LETTER_WORDS[13] = { "ache", "bash", "bike", "chew", "ding", "edit", "fart", "glue", "item", "lace", "nail", "posh", "wick" };
	const FString HIDDEN_5_LETTER_WORDS[13] = { "acute", "borks", "candy", "debut", "fancy", "gipsy", "glute", "horde", "juicy", "lefty", "paste", "quark", "salty" };
	const FString HIDDEN_6_LETTER_WORDS[13] = { "planet", "anchor", "bistro", "cougar", "feisty", "grumpy", "jargon", "laughs", "minute", "opaque", "peachy", "rogues", "shower" };
	const FString HIDDEN_7_LETTER_WORDS[13] = { "archive", "carbine", "dustbin", "flirted", "hideous", "jingler", "lockjaw", "naughty", "portals", "rafting", "seaworm", "tickled", "violent" };
	const FString HIDDEN_8_LETTER_WORDS[13] = { "antirock", "birdcage", "chompers", "dialogue", "exalting", "forehand", "grateful", "housefly", "lacework", "mousepad", "pickaxes", "sharping", "twinkles" };

	int32 idx = rand() % 13;

	switch (SelectedSize)
	{
	case 3:
			HiddenWord = HIDDEN_3_LETTER_WORDS[idx];
		break;
	case 4:
			HiddenWord = HIDDEN_4_LETTER_WORDS[idx];
		break;
	case 5:
			HiddenWord = HIDDEN_5_LETTER_WORDS[idx];
		break;
	case 6:
			HiddenWord = HIDDEN_6_LETTER_WORDS[idx];
		break;
	case 7:
			HiddenWord = HIDDEN_7_LETTER_WORDS[idx];
		break;
	case 8:
			HiddenWord = HIDDEN_8_LETTER_WORDS[idx];
		break;
	default:
			HiddenWord = HIDDEN_4_LETTER_WORDS[idx];
		break;
	}

	CurrentTry = 1;
	bGameIsWon = false;

	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	// if the guess is isn't an isogram, return error. 
	if (!IsIsogram(guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(guess))
	{
		// if guess isn't all lower case, return error.
		return EGuessStatus::Not_Lowercase;
	}
	else if(guess.length() != GetHiddenWordLength())
	{
		// if guess length is wrong, return error.
		return EGuessStatus::Wrong_Length;
	}

	// otherwise, return ok
	return EGuessStatus::OK;
}

/// Receives valid guess, and incriments try #, and returns Counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	CurrentTry++;
	FBullCowCount counts;
	int32 wordLength = HiddenWord.length(); // assuming lenghts are the same, since valid.

	// loop thru all letters in hidden word
	for (int32 i = 0; i < wordLength; i++)
	{
		// compare letter to guess
		for (int32 j = 0; j < wordLength; j++)
		{
			// if they match then
			if (guess[j] == HiddenWord[i])
			{
				if (i == j)	// incriment bull if in same place
					counts.Bulls++;
				else // inc cows if not
					counts.Cows++;
			}
		}
	}

	if (counts.Bulls == wordLength)
		bGameIsWon = true;
	else
		bGameIsWon = false;

	return counts;
}

void FBullCowGame::SetHiddenWordBySize(int32 wordSize)
{
	SelectedSize = wordSize;
	Reset();
}

bool FBullCowGame::IsIsogram(FString guess) const
{
	// treat 0 and 1 letter words as isograms.
	if (guess.length() <= 1) return true;

	// create map
	TMap<char, bool> charHash;

	// go thru each char in guess
	for(auto c : guess)
	{
		c = tolower(c); // set to lowercase.
		
		if (!charHash[c]) // haven't seen letter
			charHash[c] = true;
		else // seen letter already
			return false;
	}
		
	return true;
}

bool FBullCowGame::IsLowerCase(FString guess) const
{
	for (auto c : guess)
	{
		if (!islower(c))
			return false;
	}
	return true;
}
