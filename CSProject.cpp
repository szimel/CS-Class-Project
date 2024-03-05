#include <iostream>
#include <string>
#include <cctype>
#include <ctime>
using namespace std;

int main() {
    // variable declaration
    int playerPoints = 100;
    int inputChoice;
    int inputGuess;
    int pointsAdded = 5;
    int pointsSubtracted = 5;
    bool isDisplayingLeft = false, isDisplayingRight = false;
    int displayRight = -1, displayLeft = -1;

    // menu options
    enum MenuOption {
        DisplayLeft = 1,
        DisplayRight,
        Guess,
        Change,
        Exit
    };

    // code that only needs to run once:
    // print out the header
    cout << "+-------------------------------------------------+" << endl;
    cout << "|         Computer Science and Engineering        |" << endl;
    cout << "|         CSCE 1040 - Computer Science II         |" << endl;
    cout << "|   Samuel Zimel scz0020 samuelzimel@my.unt.edu   |" << endl;
    cout << "+-------------------------------------------------+" << endl;

    // get user's name
    string playerName;
    cout << "Enter your name: ";
    getline(cin, playerName);

    // check if the name is valid && syntax
    for (int i = 0; i < playerName.length(); i++) {
        // capitalize the first letter of the name
        playerName[0] = toupper(playerName[0]);

        // if the name is not valid, ask for a new name
        if (!isalpha(playerName[i]) && playerName[i] != ' ') {
            cout << "Your name can only have alphabets or spaces. Enter again: " << endl;
            cout << "Enter your name: ";
            getline(cin, playerName);
            i = 0;
        }

        // capitalize the first letter of the last name
        if (playerName[i] == ' ') {
            playerName[i + 1] = toupper(playerName[i + 1]);
            i++;

        // lowercase the rest of the name
        } else if ((playerName[i] != ' ') && (i != 0)) {
            playerName[i] = tolower(playerName[i]);
        }
    }

    // junior and senior check
    if (playerName.length() >= 7 && (playerName.substr(playerName.length() - 7) == " Senior")) {
        playerName = playerName.substr(0, playerName.length() - 7) + ", Sr.";
    } else if (playerName.length() >= 7 && playerName.substr(playerName.length() - 7) == " Junior") {
        playerName = playerName.substr(0, playerName.length() - 7) + ", Jr.";
    }

    // welcome message
    cout << "Welcome " << playerName << endl;
    cout << displayRight << "          " << displayLeft << endl << endl;

    // generate two random numbers between 150 and 250, inclusive
    srand(time(0));
    int left = rand() % 101 + 150;
    int right = rand() % 101 + 250;

    // ensure bounds are correct
    while (left > right) {
        left = rand() % 101 + 150;
        right = rand() % 101 + 250;
    }

    // main game loop
    while (playerPoints >= 0) {
        // display menu: 
        cout << "Menu: " << endl;
        cout << "1. Display the left number" << endl;
        cout << "2. Display the right number" << endl;
        cout << "3. Guess a number in the range (inclusive)" << endl;
        cout << "4. Change numbers" << endl;
        cout << "5. Exit" << endl;

        // output the displays && get the user's choice
        cout << displayLeft << "          " << displayRight << endl;
        cout << "Your choice: ";
        cin >> inputChoice;

        switch(inputChoice) {
            case DisplayLeft:
                // make sure the user can only display the left number once
                if (isDisplayingLeft) {
                    cout << "You have already displayed the left number." << endl;
                    break;

                // make sure the user isn't displaying the right number
                } else if (isDisplayingRight) {
                    cout << "You have already displayed the right boundary, you cannot display both." << endl;
                    break;
                }
                // setting variables
                isDisplayingLeft = true;
                displayLeft = left;
                pointsAdded = 1;
                pointsSubtracted = 10;

                // output the left number
                cout << "You will only get 1 point for guessing correctly and lose 10 points for guessing incorrectly, now." << endl;
                cout << displayLeft << "          " << displayRight << endl;
                break;

            case DisplayRight:
                // make sure the user can only display the left number once
                if (isDisplayingLeft) {
                    cout << "You have already displayed the left boundary, you cannot display both." << endl;
                    break;

                // make sure the user isn't displaying the right number
                } else if (isDisplayingRight) {
                    cout << "You have already displayed the right number." << endl;
                    break;
                }
                // setting variables
                displayRight = right;
                isDisplayingRight = true;
                pointsAdded = 1;
                pointsSubtracted = 10;

                // output the right number
                cout << "You will only get 1 point for guessing correctly and lose 10 points for guessing incorrectly, now." << endl;
                cout << displayLeft << "          " << displayRight << endl;
                break;

            case Guess:
                // getting input from the user
                cout << "Enter your guess: ";
                cin >> inputGuess;
                cout << "Your choice: " << inputGuess << endl;

                // check if the guess is within the bounds
                if((inputGuess >= left) && (inputGuess <= right)) {
                    playerPoints += pointsAdded;
                    cout << "You guessed correctly. You get " << pointsAdded << " points." << endl;

                // if the user isn't within the bounds
                } else {
                    playerPoints -= pointsSubtracted;
                    cout << "You guessed incorrectly! You lose " << pointsSubtracted << " points." << endl;
                }

                cout << "Your remaining points = " << playerPoints << endl;
                cout << displayLeft << "          " << displayRight << endl;
                break;

            case Change:
                // subtracting point and output
                playerPoints -= 1;
                cout << "Your remaining points = " << playerPoints << endl;
                
                // making new boundaries
                cout << "Generating new boundaries." << endl;
                left = rand() % 101 + 150;
                right = rand() % 101 + 250;

                // ensure bounds are correct
                while (left > right) {
                    left = rand() % 101 + 150;
                    right = rand() % 101 + 250;
                }

                // resetting variables
                isDisplayingLeft = false;
                isDisplayingRight = false;
                displayRight = -1;
                displayLeft = -1;
                pointsAdded = 5;
                pointsSubtracted = 5;
                break;

            case Exit:
                cout << "Bye " << playerName << "!!!" << endl;
                return 0;

            default:
                cout << "Wrong choice. Enter again." << endl;
        }

        // formatting
        cout << endl;
    }
    // if the user runs out of points
    cout << "You are out of points." << endl;
    cout << "Bye " << playerName << "!!!" << endl;

    return 0;
}