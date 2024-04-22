#include <iostream>
#include <string>
#include <cctype>
#include <ctime>
#include <iomanip>
using namespace std;

//global var for matrix size
const int SIZE = 5;

// format the name
string formatName(string playerName) {
    bool isFirst = true;
    // check for first letter of each word and capitalize it
    for (int i = 0; i < playerName.length(); ++i) {
        if (isFirst && isalpha(playerName[i])) {
            playerName[i] = toupper(playerName[i]);
            isFirst = false;
        } else if (isalpha(playerName[i])) {
            playerName[i] = tolower(playerName[i]);
        }

        if (playerName[i] == ' ') {
            isFirst = true;
        }
    }

    // junior and senior check
    if (playerName.length() >= 7 && (playerName.substr(playerName.length() - 7) == " Senior")) {
        playerName = playerName.substr(0, playerName.length() - 7) + ", Sr.";
    } else if (playerName.length() >= 7 && playerName.substr(playerName.length() - 7) == " Junior") {
        playerName = playerName.substr(0, playerName.length() - 7) + ", Jr.";
    }

    return playerName;
}

// outputs the bounds matrix
void showBounds(int displayedBounds[2]) {
    cout << displayedBounds[0] << "       " << displayedBounds[1] << endl;
}

// gets the name from the user => send it to be formatted
string getName() {
    string name;
    bool isValid;
    // loop that checks if the name is valid
    while(!isValid) {
        cout << "Enter your name: ";
        getline(cin, name);

        isValid = true;
        for (size_t i = 0; i < name.length(); ++i) {
            char ch = name[i];
            if (!isalpha(ch) && !isspace(ch)) {
                cout << "Invalid input. Only letters and spaces are allowed" << endl;
                isValid = false;
                break;
            }
        }
    }

    // format valid name
    return formatName(name);
}

// creates a matrix of -1's
void genShowMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = -1;
        }
    }
}

// displays the matrix
void showMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << setw(6) << matrix[i][j];
        }
        cout << endl;
    }
}

// initialize the matrix with random numbers between lower and upper bounds
void genHideMatrix(int matrix[SIZE][SIZE], int lower, int upper) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = lower + rand() % (upper - lower + 1);
        }
    }
}

// displays the left integer in the top left corner
void setDisplayLeft(int displayedBounds[2], int lowerBound, int& pointsAdded, int& pointsLost) {
    // check edge cases
    if (displayedBounds[0] == lowerBound) {
        cout << "You have already displayed the lower bounds." << endl;
        showBounds(displayedBounds);
        return;
    } else if (displayedBounds[1] != -1) {
        displayedBounds[1] = -1;
    }

    // updated values
    pointsAdded = 1;
    pointsLost = 10;
    displayedBounds[0] = lowerBound;

    cout << "A correct guess will only earn 1 point, and an incorrect guess will lose 10 points." << endl;
    showBounds(displayedBounds);
}

// displays the right integer in the bottom right corner
void setDisplayRight(int displayedBounds[2], int upperBound, int& pointsAdded, int& pointsLost) {
    // check edge cases
    if (displayedBounds[1] == upperBound) {
        cout << "You have already displayed the upper bounds." << endl;
        showBounds(displayedBounds);
        return;
    } else if (displayedBounds[0] != -1) {
        displayedBounds[0] = -1;
    }

    // updated values
    pointsAdded = 1;
    pointsLost = 10;
    displayedBounds[1] = upperBound;

    cout << "A correct guess will only earn 1 point, and an incorrect guess will lose 10 points." << endl;
    showBounds(displayedBounds); 
}

// eliminates the row and column of the guessed number
void eliminate(int visible[SIZE][SIZE], int hidden[SIZE][SIZE], int row, int col) {
    for (int i = 0; i < SIZE; i++) {
        visible[row][i] = 0; 
        visible[i][col] = 0; 
        hidden[row][i] = 0; 
        hidden[i][col] = 0;
    }
}

// checks if all elements in the matrix are 0
bool allZeros(const int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] != 0) {
                return false; 
            }
        }
    }
    // if it's gotten to this point, all elements are 0
    return true;
}

// function to guess a number in the matrix
void guess(int hidden[SIZE][SIZE], int visible[SIZE][SIZE], int pointsAdded, int pointsLost, int& points) {
    // print matrix
    showMatrix(visible);

    // get user input
    int input;
    cout << "Enter your guess: ";
    cin >> input;

    // check if the guess is in the matrix
    bool matchFound = false; // using bool to address the rare edge case where the same number is in the matrix twice
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (hidden[i][j] == input) {
                eliminate(visible, hidden, i, j);
                points += pointsAdded;
                matchFound = true;
                cout << "You guessed correctly. You get " << pointsAdded << " points." << endl;
            }
        }
    }

    if (!matchFound) {
        cout << "No match found. You lose " << pointsLost <<  " points." << endl;
        points -= pointsLost;
    }
    cout << "Your remaining points: " << points << endl;
}


void initialize(int hidden[SIZE][SIZE], int visible[SIZE][SIZE], int& lowerBound, int& upperBound, int displayedBounds[2]) {
    // use time so it's truly random
    srand(time(0));

    // Generate bounds
    lowerBound = 150 + rand() % 100; 
    upperBound = 250 + rand() % 100;

    // Initialize matrices
    genHideMatrix(hidden, lowerBound, upperBound);
    genShowMatrix(visible);

    // reset the displayed bounds
    displayedBounds[0] = -1;
    displayedBounds[1] = -1;
}

int main() {
    // Variable declarations
    int points = 100;
    int pointsAdded = 5;
    int pointsLost = 5;
    int lowerBound, upperBound;
    int displayedBounds[2] = {-1, -1};
    int hidden[SIZE][SIZE];
    int visible[SIZE][SIZE];
    int choice;
    bool gameOver = false;
    // menu options
    const int DisplayLeft = 1;
    const int DisplayRight = 2;
    const int Guess = 3;
    const int Reset = 4;
    const int Exit = 5;

    // intro
    cout << "+-------------------------------------------------+" << endl;
    cout << "|         Computer Science and Engineering        |" << endl;
    cout << "|         CSCE 1040 - Computer Science II         |" << endl;
    cout << "|   Samuel Zimel scz0020 samuelzimel@my.unt.edu   |" << endl;
    cout << "+-------------------------------------------------+" << endl;

    // get the player's name
    string playerName = getName();
    cout << "Welcome to the game, " << playerName << endl;

    initialize(hidden, visible, lowerBound, upperBound, displayedBounds);

    // game loop
    while (!gameOver && points > 0) {
        cout << "\n1. Display Left Number\n";
        cout << "2. Display Right Number\n";
        cout << "3. Guess a number in between\n";
        cout << "4. Reset the game\n";
        cout << "5. Exit\n";
        cout << "What do you want to do? ";
        cin >> choice;

        switch (choice) {
            case DisplayLeft:
                setDisplayLeft(displayedBounds, lowerBound, pointsAdded, pointsLost);
                break;
            case DisplayRight:
                setDisplayRight(displayedBounds, upperBound, pointsAdded, pointsLost);
                break;
            case Guess:
                guess(hidden, visible, pointsAdded, pointsLost, points);
                showBounds(displayedBounds);

                if (allZeros(hidden)) {
                    cout << "Congratulations! You have cleared the matrix." << endl;
                    cout << "Do you want to play another game (1-yes, 0-no)? ";
                    cin >> choice;
                    if (choice == 1) {
                        // reset game
                        initialize(hidden, visible, lowerBound, upperBound, displayedBounds);

                        // reset points
                        points = 100; 
                        pointsAdded = 5;
                        pointsLost = 5;
                    } else {
                        gameOver = true;
                    }
                }
                showMatrix(visible);
                break;
            case Reset:
                initialize(hidden, visible, lowerBound, upperBound, displayedBounds);

                // Remove a point for resetting the game
                points -= 1;

                // reset the points added and lost
                pointsAdded = 5;
                pointsLost = 5;

                cout << "Game has been reset. Your remaining points: " << points << endl;
                break;
            case Exit:
                gameOver = true;
                break;
            default:
                cout << "Invalid choice, please try again.\n";
                break;
        }

        if (points <= 0) {
            cout << "Game over! You have run out of points.\n";
        }
    }

    cout << "Goodbye, " << playerName << "! Your final points balance is " << points << ".\n";

    return 0;
}
