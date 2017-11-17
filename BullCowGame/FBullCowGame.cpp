#include "FBullCowGame.h"
#include <map>

#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }


int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const {	return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset() {

	constexpr int32 MAX_TRIES = 5;
	const FString HIDDEN_WORD = "planet";
	bGameIsWon = false;

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	return;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	if (Word.length() == 1) { return true; }
	TMap<char, bool> LetterSeen;

	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		} else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const {
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {

	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	} else if (!IsLowerCase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	} else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	} else {
		return EGuessStatus::OK;
	}

	return EGuessStatus::OK;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {

	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				} else {
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	} else {
		bGameIsWon = false;
	}

	return BullCowCount;
}
