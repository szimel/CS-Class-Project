#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    // variable declaration
    int playerPoints = 100;

    // menu options
    const int DisplayLeft = 1;
    const int DisplayRight = 2;
    const int Guess = 3; 
    const int Change = 4;
    const int Quit = 5;

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
            cout << "Your name can only have alphabets or spaces. Enter again: ";
            getline(cin, playerName);
            i = 0;
        }

        // capitalize the first letter of the last name
        if (playerName[i] == ' ') {
            playerName[i + 1] = toupper(playerName[i + 1]);
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

    // main game loop
    // while (true) {
        
    // }
    return 0;
}