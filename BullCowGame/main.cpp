#include <iostream>
#include "FBullCowGame.h"

using FText = std::string;

void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int main() {
	do {
		BCGame.IsGameWon();
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	return 0;
}

void PrintIntro() {
	std::cout << "\n\nWelcome to Bulls and Cows!\n";
	std::cout << "Can you get the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	return;
}

FText GetValidGuess() {

	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::OK:
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word with unique letters.\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word with lowercase letters.\n";
			break;
		default:
			break;
		}
		std::cout << "\n";
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls: " << BullCowCount.Bulls << "\n";
		std::cout << "Cows: " << BullCowCount.Cows << "\n";
	}

	//TODO: sumarize game
	PrintGameSummary();

	return;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again with the same word? (Y/N) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'Y') || (Response[0] == 'y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Well done. You win!\n";
	} else {
		std::cout << "Better luck next time!\n";
	}
}
