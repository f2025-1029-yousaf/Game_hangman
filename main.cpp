

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Hangman.h"
#include "Anagram.h"

using namespace std;

int main() {
    srand((unsigned)time(nullptr));

    cout << "======================================\n";
    cout << "   Welcome to PuzzleChallenge Hub!    \n";
    cout << "======================================\n";
    cout << "A random game will be selected for you each round.\n\n";

    // -------------------------------------------------------
    // Polymorphism: array of base-class pointers pointing to
    // different derived-class objects
    // -------------------------------------------------------
    const int NUM_GAMES = 2;
    Game* games[NUM_GAMES] = {
        new Hangman(),
        new Anagram()
    };

    bool keepPlaying = true;

    while (keepPlaying) {
        // Randomly pick a game using base-class pointer
        int index = rand() % NUM_GAMES;
        Game* selected = games[index];

        cout << "\n>>> Randomly selected: " << selected->getName() << " <<<\n";

        // Polymorphic call — runs the overridden play() of the derived class
        selected->play();

        cout << "\n--------------------------------------\n";
        cout << "Play another game? (y/n): ";
        char choice;
        cin >> choice;
        keepPlaying = (tolower(choice) == 'y');
    }

    // Final scores
    cout << "\n========== FINAL SCORES ==========\n";
    for (int i = 0; i < NUM_GAMES; i++) {
        games[i]->displayScore();
    }

    // Clean up — delete heap-allocated objects
    for (int i = 0; i < NUM_GAMES; i++) {
        delete games[i];
    }

    cout << "\nThanks for playing! Goodbye.\n";
    return 0;
}
