#ifndef HANGMAN_H
#define HANGMAN_H

/*
 * Hangman.h — Derived Game class for the Hangman game
 * Course: CSC-213 (Object Oriented Programming)
 * Description: Player guesses letters to uncover a hidden word within limited attempts.
 *              Word list is loaded from "words.txt" for better design (file handling / composition).
 *              Tracks per-session score (words solved).
 *
 * AI Disclosure: Code structure and logic written with assistance from Claude (Anthropic).
 *                All code has been reviewed and understood by the submitting student.
 */

#include "Game.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

class Hangman : public Game {
private:
    vector<string> wordList;

    // Hangman ASCII art stages (0 = fresh, 6 = dead)
    void drawHangman(int wrong) const {
        const string stages[7][7] = {
            {"  +---+  ", "  |   |  ", "      |  ", "      |  ", "      |  ", "      |  ", "========="},
            {"  +---+  ", "  |   |  ", "  O   |  ", "      |  ", "      |  ", "      |  ", "========="},
            {"  +---+  ", "  |   |  ", "  O   |  ", "  |   |  ", "      |  ", "      |  ", "========="},
            {"  +---+  ", "  |   |  ", "  O   |  ", " /|   |  ", "      |  ", "      |  ", "========="},
            {"  +---+  ", "  |   |  ", "  O   |  ", " /|\\  |  ", "      |  ", "      |  ", "========="},
            {"  +---+  ", "  |   |  ", "  O   |  ", " /|\\  |  ", " /    |  ", "      |  ", "========="},
            {"  +---+  ", "  |   |  ", "  O   |  ", " /|\\  |  ", " / \\  |  ", "      |  ", "========="}
        };
        cout << "\n";
        for (int i = 0; i < 7; i++)
            cout << stages[wrong][i] << "\n";
        cout << "\n";
    }

    void loadWords() {
        ifstream file("words.txt");
        if (file.is_open()) {
            string word;
            while (file >> word) {
                // Convert to uppercase for consistency
                transform(word.begin(), word.end(), word.begin(), ::toupper);
                wordList.push_back(word);
            }
            file.close();
        }
        // Fallback words if file not found
        if (wordList.empty()) {
            wordList = {"PROGRAMMING", "INHERITANCE", "POLYMORPHISM",
                        "ENCAPSULATION", "COMPUTER", "ALGORITHM",
                        "VARIABLE", "FUNCTION", "COMPILER", "OBJECT"};
        }
    }

    string pickWord() const {
        return wordList[rand() % wordList.size()];
    }

public:
    Hangman() : Game("Hangman") {
        srand((unsigned)time(nullptr));
        loadWords();
    }

    void play() override {
        cout << "\n========== HANGMAN ==========\n";
        cout << "Guess the hidden word, one letter at a time.\n";
        cout << "You have 6 wrong guesses before the man hangs!\n";

        bool keepPlaying = true;

        while (keepPlaying) {
            string secret = pickWord();
            string display(secret.size(), '_');
            vector<char> guessed;
            int wrongGuesses = 0;
            const int maxWrong = 6;

            while (wrongGuesses < maxWrong && display != secret) {
                drawHangman(wrongGuesses);

                // Show current word state
                cout << "Word: ";
                for (char c : display) cout << c << " ";
                cout << "\n";

                // Show guessed letters
                cout << "Guessed: ";
                for (char c : guessed) cout << c << " ";
                cout << "\n";
                cout << "Wrong guesses left: " << (maxWrong - wrongGuesses) << "\n";

                // Get input
                cout << "Enter a letter: ";
                char guess;
                cin >> guess;
                guess = toupper(guess);

                // Validate input
                if (!isalpha(guess)) {
                    cout << "Please enter a valid letter.\n";
                    continue;
                }
                if (find(guessed.begin(), guessed.end(), guess) != guessed.end()) {
                    cout << "You already guessed '" << guess << "'. Try another.\n";
                    continue;
                }

                guessed.push_back(guess);

                // Check if letter is in word
                bool found = false;
                for (int i = 0; i < (int)secret.size(); i++) {
                    if (secret[i] == guess) {
                        display[i] = guess;
                        found = true;
                    }
                }
                if (!found) {
                    wrongGuesses++;
                    cout << "Wrong! '" << guess << "' is not in the word.\n";
                } else {
                    cout << "Good guess!\n";
                }
            }

            drawHangman(wrongGuesses);

            if (display == secret) {
                cout << "*** YOU WIN! The word was: " << secret << " ***\n";
                score++;
            } else {
                cout << "*** GAME OVER! The word was: " << secret << " ***\n";
            }

            displayScore();

            cout << "\nPlay again? (y/n): ";
            char choice;
            cin >> choice;
            keepPlaying = (tolower(choice) == 'y');
        }
    }
};

#endif
