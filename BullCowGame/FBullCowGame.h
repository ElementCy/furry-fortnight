/* Main Game for Bull & Cow Game.
   Grabs a random word of a size that is selected from the player,
   And then calculates the number of Bulls and Cows for the player's guess.
   Game over when player runs out of tries.
*/
#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);
	void SetHiddenWordBySize(int32);


private:
	int32 CurrentTry;
	FString HiddenWord;
	bool bGameIsWon;
	int32 SelectedSize;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};