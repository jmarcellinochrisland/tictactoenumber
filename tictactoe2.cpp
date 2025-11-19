#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class TicTacToe {
private:
    vector<char> board;
    char currentPlayer;
    int scoreX, scoreO, scoreDraw;

    void displayBoard() {
        cout << "       SELAMAT BERMAIN TIC TAC TOE GAME\n";
        
        cout << "  Posisi Kotak:        Papan Permainan:\n";
        cout << "   1 | 2 | 3            " << board[0] << " | " << board[1] << " | " << board[2] << "\n";
        cout << "  -----------          -----------\n";
        cout << "   4 | 5 | 6            " << board[3] << " | " << board[4] << " | " << board[5] << "\n";
        cout << "  -----------          -----------\n";
        cout << "   7 | 8 | 9            " << board[6] << " | " << board[7] << " | " << board[8] << "\n";
        cout << "\n";
    }

    void displayScore() {
        cout << "=================================\n";
        cout << "           SKOR\n";
        cout << "=================================\n";
        cout << "  Player 1 (X): " << scoreX << "\n";
        cout << "  Player 2 (O): " << scoreO << "\n";
        cout << "  Seri        : " << scoreDraw << "\n";
        cout << "=================================\n\n";
    }

    bool checkWin() {
        // Kombinasi menang
        int winCombinations[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Horizontal
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Vertikal
            {0, 4, 8}, {2, 4, 6}              // Diagonal
        };

        for (int i = 0; i < 8; i++) {
            if (board[winCombinations[i][0]] == currentPlayer &&
                board[winCombinations[i][1]] == currentPlayer &&
                board[winCombinations[i][2]] == currentPlayer) {
                return true;
            }
        }
        return false;
    }

    bool checkDraw() {
        for (char cell : board) {
            if (cell == ' ') {
                return false;
            }
        }
        return true;
    }

    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    TicTacToe() : board(9, ' '), currentPlayer('X'), scoreX(0), scoreO(0), scoreDraw(0) {}

    void play() {
        bool playAgain = true;
        
        while (playAgain) {
            resetBoard();
            bool gameActive = true;

            while (gameActive) {
                displayScore();
                displayBoard();

                // Tampilkan giliran pemain
                int playerNum = (currentPlayer == 'X') ? 1 : 2;
                cout << "Giliran Player " << playerNum << " (" << currentPlayer << ")\n";
                cout << "Pilih kotak (1-9): ";

                int choice;
                cin >> choice;

                // Validasi input
                if (cin.fail() || choice < 1 || choice > 9) {
                    clearInputBuffer();
                    cout << "\n Input tidak valid! Pilih angka 1-9.\n";
                    cout << "Tekan Enter untuk melanjutkan...";
                    cin.get();
                    continue;
                }

                int index = choice - 1;

                // Cek apakah kotak sudah diisi
                if (board[index] != ' ') {
                    cout << "\n Kotak sudah terisi! Pilih kotak lain.\n";
                    cout << "Tekan Enter untuk melanjutkan...";
                    clearInputBuffer();
                    cin.get();
                    continue;
                }

                // Isi kotak
                board[index] = currentPlayer;

                // Cek kemenangan
                if (checkWin()) {
                    displayScore();
                    displayBoard();
                    cout << " SELAMAT! ANDA MEMENANGKAN PERMAINAN ! " << playerNum << " (" << currentPlayer << ") MENANG! \n\n";
                    
                    if (currentPlayer == 'X') {
                        scoreX++;
                    } else {
                        scoreO++;
                    }
                    gameActive = false;
                }
                // Cek seri
                else if (checkDraw()) {
                    displayScore();
                    displayBoard();
                    cout << " PERMAINAN SERI! \n\n";
                    scoreDraw++;
                    gameActive = false;
                }
                // Ganti pemain
                else {
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                }
            }

            // Tanya main lagi
            char response;
            cout << "Main lagi? (y/n): ";
            cin >> response;
            playAgain = (response == 'y' || response == 'Y');
            
            if (playAgain) {
                currentPlayer = 'X'; // Reset ke Player 1
            } else {
                cout << "Anda Pengecut" << endl;
            }
        }

        cout << "\n=================================\n";
        cout << "   TERIMA KASIH SUDAH BERMAIN!\n";
        cout << "=================================\n";
        displayScore();
    }

private:
    void resetBoard() {
        board = vector<char>(9, ' ');
    }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}
