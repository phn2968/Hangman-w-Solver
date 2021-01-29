#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <random>
using namespace std;

#ifndef HANGMAN_CPP_INCLUDED
#define HANGMAN_CPP_INCLUDED

const char USCORE = '_';
const char PIPE = '|';
const char DASH = '-';
const char SPACE = ' ';
int WORDLENGTH = 0;

int getWordLength() {
    return WORDLENGTH;
}
//Precondition: words.txt is a text file filled with words, separated by \n
//Postcondition: all words in words.txt are placed into a vector of strings
vector<string> loadFile() {
    ifstream fstream;
    fstream.open("words.txt");
    string f;
    vector<string> wordList;
    while(fstream >> f) {
        if(f.back() == ',')
            f.pop_back();
        for(int i = 0; i < (int)f.length(); ++i) {
            towlower(f[i]);
        }
        wordList.push_back(f);
    }
    fstream.close();
    return wordList;
}

//Precondition: state must be between 0 and 5
//Postcondition: prints out the current hangman state according to how many fails is passed in
void drawMan(int state) {
    string states[][8] = {
       {"____________",
        "|          |",
        "|          |",
        "|           ",
        "|           ",
        "|           ",
        "|           ",
        "-----       ",
       },

       {"____________",
        "|          |",
        "|          |",
        "|          O",
        "|           ",
        "|           ",
        "|           ",
        "-----       ",
       },

       {"____________",
        "|          |",
        "|          |",
        "|          O",
        "|          |",
        "|           ",
        "|           ",
        "-----       ",
       },

       {"____________",
        "|          |",
        "|          |",
        "|          O",
        "|          |",
        "|         / ",
        "|           ",
        "-----       ",
       },

       {"____________",
        "|          |",
        "|          |",
        "|          O",
        "|          |",
        "|         / \\\n"
        "|           ",
        "-----       ",
       },

       {"____________",
        "|          |",
        "|          |",
        "|          O",
        "|         -|",
        "|         / \\",
        "|           ",
        "-----       ",
       },

       {"____________",
        "|          |",
        "|          |",
        "|          O",
        "|         -|-",
        "|         / \\",
        "|           ",
        "-----       ",
       }

    };

    for(string i: states[state]) {
        cout << i << endl;
    }
}

//Print out available letters
//Precondition: letters is filled with 26 booleans
//Postcondition: prints out all letters that haven't been used
void printLetters(vector<bool> letters) {
    for(int i = 0; i < (int)letters.size(); ++i) {
        if(letters[i] == 1)
            cout << (char)('a' + i) << " ";
    }
    cout << endl;
}

//Checks if letter is a valid entry
//Guess must be lowercase
bool validMove(char guess, vector<bool> letters) {
    if(guess < 97 || guess > 123) {
        cout << "This is not a valid character we can guess" << endl;
        return 0;
    }
    if(letters[guess-'a'] == 1) {
        return 1;
    }
    else {
        cout << "You have already guessed "<< guess << endl;
        return 0;
    }
    return 0;
}

bool goodMove(char guess, string toSolve, string& display) {
    bool valid = 0;
    for(int i = 0; i < (int)toSolve.length(); ++i) {
        if(toSolve[i] == guess) {
            display[i] = guess;
            valid = 1;
        }
    }
    return valid;
}

//Returns true if game was won, false if user had failed

bool playGame() {

    vector<string> wordList = loadFile(); //Consider redoing to this to a map, that way you can give a theme to the word
    vector<bool> letters(26, 1);
    int randNum = rand()%((int)wordList.size()-1) + 1;//Picks a random index from the wordList vector
    string toSolve = wordList[randNum]; //Selected word
    string display = toSolve; //Word that will display to the user
    WORDLENGTH = (int)display.length();
    for(char& c: display) {
        c = '_';
    }
    int fails = 0;
    bool gameDone = 0;
    char guess;
    while(fails < 6 && !gameDone) {
        cout << "\t\t\t" << display << "\n\n";
        drawMan(fails);
        printLetters(letters);

        //Any entry longer than one character will be ignored. Only the first char in any input will be considered. This is to prevent "overflow" on fails.
        cin >> guess;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(validMove(guess, letters)) {
            if(!goodMove(guess, toSolve, display)) {
                ++fails;
            }
            letters[guess-'a'] = 0; //All letters that were valid guesses will be marked used
        }
        if(display.find('_') == string::npos) {
            gameDone = 1;
        }
    }
    if(!gameDone) {
        drawMan(fails);
        cout << "The answer was " << toSolve << endl;
    }
    else {
        cout << "\t\t\t" << display << "\n\n";
    }

    return gameDone;
}



#endif // HANGMAN_CPP_INCLUDED

