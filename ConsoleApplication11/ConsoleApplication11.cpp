#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <locale>  
#include <codecvt> 

using namespace std;

void displayWord(const string& word, const vector<bool>& revealed) {
    for (size_t i = 0; i < word.length(); ++i) {
        if (revealed[i]) {
            cout << word[i] << " ";
        }
        else {
            cout << "_ ";
        }
    }
    cout << endl;
}

void giveHint(string& word, vector<bool>& revealed) {
    for (size_t i = 0; i < word.length(); ++i) {
        if (!revealed[i]) {
            revealed[i] = true;
            cout << "ϳ������: ����������� ����� " << word[i] << endl;
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "ukr");

    vector<pair<string, string>> questions = {
        {"��� ���� � ��������� � ���?", "��������"},
        {"��� ����� ������ '1984'?", "������"},
        {"��� ������� � ��������� � ������� ������?", "�����"},
        {"������� �������?", "�����"}
    };

    srand(static_cast<unsigned int>(time(0))); 
    int index = rand() % questions.size(); 

    string question = questions[index].first;
    string word = questions[index].second;
    vector<bool> revealed(word.length(), false); 

    int timeSpent = 0;
    bool gameOver = false;
    string guessedWord;
    char guessedLetter;
    char useHint;
    bool wrongGuess = false;

    cout << "�������: " << question << endl;
    cout << "����������� �����: ";
    displayWord(word, revealed);

    time_t startTime = time(0); 

    while (!gameOver) {
        cout << "\n�� �� ������ �������?" << endl;
        cout << "1. ������� �����." << endl;
        cout << "2. ������� �����." << endl;
        cout << "3. ����������� �������." << endl;
        cout << "���� (1/2/3): ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "������ ���� ����������: ";
            cin >> guessedWord;

            if (guessedWord == word) {
                cout << "³����! �� ������� �����!" << endl;
                gameOver = true;
            }
            else {
                cout << "������! ��������� �� ���." << endl;
            }
            break;
        }
        case 2: {
            cout << "������ �����: ";
            cin >> guessedLetter;

            bool found = false;
            for (size_t i = 0; i < word.length(); ++i) {
                if (word[i] == guessedLetter && !revealed[i]) {
                    revealed[i] = true;
                    found = true;
                }
            }

            if (found) {
                cout << "���������! ³������ ������: " << guessedLetter << endl;
            }
            else {
                cout << "������! ˳���� �� ��������." << endl;
            }

            displayWord(word, revealed);

            gameOver = true;
            for (bool letter : revealed) {
                if (!letter) {
                    gameOver = false;
                    break;
                }
            }
            break;
        }
        case 3: {
            cout << "������ ����������� ������� (y/n)? ";
            cin >> useHint;

            if (useHint == 'y' || useHint == 'Y') {
                timeSpent += 2;
                giveHint(word, revealed);
            }
            break;
        }
        default:
            cout << "������� ����. ��������� �� ���." << endl;
        }

        if (gameOver) {
            timeSpent += static_cast<int>(difftime(time(0), startTime)); 
            cout << "\n���, ���������� �� ���: " << timeSpent << " ������." << endl;
            cout << "��� ���������!" << endl;
        }
    }

    return 0;
}
