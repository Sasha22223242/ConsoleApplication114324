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
            cout << "Підказка: відкривається літера " << word[i] << endl;
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "ukr");

    vector<pair<string, string>> questions = {
        {"Яка річка є найдовшою в світі?", "Амазонка"},
        {"Хто автор роману '1984'?", "Оруелл"},
        {"Яка планета є найбільшою в Сонячній системі?", "Юпітер"},
        {"Столиця Франції?", "Париж"}
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

    cout << "Питання: " << question << endl;
    cout << "Зашифроване слово: ";
    displayWord(word, revealed);

    time_t startTime = time(0); 

    while (!gameOver) {
        cout << "\nЩо ви хочете зробити?" << endl;
        cout << "1. Вгадати слово." << endl;
        cout << "2. Назвати літеру." << endl;
        cout << "3. Використати підказку." << endl;
        cout << "Вибір (1/2/3): ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Введіть ваше припущення: ";
            cin >> guessedWord;

            if (guessedWord == word) {
                cout << "Вітаємо! Ви вгадали слово!" << endl;
                gameOver = true;
            }
            else {
                cout << "Невірно! Спробуйте ще раз." << endl;
            }
            break;
        }
        case 2: {
            cout << "Введіть літеру: ";
            cin >> guessedLetter;

            bool found = false;
            for (size_t i = 0; i < word.length(); ++i) {
                if (word[i] == guessedLetter && !revealed[i]) {
                    revealed[i] = true;
                    found = true;
                }
            }

            if (found) {
                cout << "Правильно! Відкрита літерка: " << guessedLetter << endl;
            }
            else {
                cout << "Невірно! Літера не знайдена." << endl;
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
            cout << "Бажаєте використати підказку (y/n)? ";
            cin >> useHint;

            if (useHint == 'y' || useHint == 'Y') {
                timeSpent += 2;
                giveHint(word, revealed);
            }
            break;
        }
        default:
            cout << "Невірний вибір. Спробуйте ще раз." << endl;
        }

        if (gameOver) {
            timeSpent += static_cast<int>(difftime(time(0), startTime)); 
            cout << "\nЧас, витрачений на гру: " << timeSpent << " секунд." << endl;
            cout << "Гра завершена!" << endl;
        }
    }

    return 0;
}
