#include<iostream>
#include<random>

using namespace std;

class BingoGame {
private:
    int bingoCnt = 0;
    int exBingoCnt[10];
    int count = 1;
    int input_row, input_col;
    int dy[4] = { 0, 0, -1, 1 };
    int dx[4] = { -1, 1, 0, 0 };

    int threerow[5] = { 0, };
    int threecol[5] = { 0, };
    int threedig[2] = { 0, };


public:
    char bingo_map[5][5];
    BingoGame() {}
    BingoGame(int a) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                bingo_map[i][j] = ' ';
            }
        }
    }
    void showGround(char bingo_map[5][5]) {
        cout << "  ┏━━━━━┳━━━━━┳━━━━━┳━━━━━┳━━━━━┓\n"
             << "  ┃  " << bingo_map[0][0] << " " << " ┃ " << bingo_map[0][1] << " " << "  ┃  " << bingo_map[0][2] << " " << " ┃  " << bingo_map[0][3] << " " << " ┃ " << " " << bingo_map[0][4] << " " << " ┃\n"
             << "  ┣━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫\n"
             << "  ┃  " << bingo_map[1][0] << " " << " ┃ " << bingo_map[1][1] << " " << "  ┃  " << bingo_map[1][2] << " " << " ┃  " << bingo_map[1][3] << " " << " ┃ " << " " << bingo_map[1][4] << " " << " ┃\n"
             << "  ┣━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫\n"
             << "  ┃  " << bingo_map[2][0] << " " << " ┃ " << bingo_map[2][1] << " " << "  ┃  " << bingo_map[2][2] << " " << " ┃  " << bingo_map[2][3] << " " << " ┃ " << " " << bingo_map[2][4] << " " << " ┃\n"
             << "  ┣━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫\n"
             << "  ┃  " << bingo_map[3][0] << " " << " ┃ " << bingo_map[3][1] << " " << "  ┃  " << bingo_map[3][2] << " " << " ┃  " << bingo_map[3][3] << " " << " ┃ " << " " << bingo_map[3][4] << " " << " ┃\n"
             << "  ┣━━━━━╋━━━━━╋━━━━━╋━━━━━╋━━━━━┫\n"
             << "  ┃  " << bingo_map[4][0] << " " << " ┃ " << bingo_map[4][1] << " " << "  ┃  " << bingo_map[4][2] << " " << " ┃  " << bingo_map[4][3] << " " << " ┃ " << " " << bingo_map[4][4] << " " << " ┃\n"
             << "  ┗━━━━━┻━━━━━┻━━━━━┻━━━━━┻━━━━━┛\n";
    }

    void turn() {
        cout << count << "번째 차례" << endl;
        if (count != 0 && count % 3 == 0) {
            cout << count << "번째 차례. 빙고를 완성하지 못할 경우 실패" << endl;
        }
        cout << "좌표 입력 (0~4) : ";
        cin >> input_row >> input_col;

        if (input_row >= 0 && input_row < 5 && input_col >= 0 && input_col < 5) {
            if (bingo_map[input_row][input_col] == 'S') {
                bingo_map[input_row][input_col] = '*';
            }
            else if (bingo_map[input_row][input_col] == 'O') {
                bingo_map[input_row][input_col] = ' ';
            }
            else if (bingo_map[input_row][input_col] == ' ') {
                bingo_map[input_row][input_col] = 'O';
            }
            for (int i = 0; i < 4; i++) {
                int ty = input_row + dy[i];
                int tx = input_col + dx[i];
                if (ty < 0 || tx < 0 || ty > 4 || tx > 4)
                    continue;
                else {
                    if (bingo_map[ty][tx] == 'S')
                        bingo_map[ty][tx] = '*';
                    else if (bingo_map[ty][tx] == 'O')
                        bingo_map[ty][tx] = ' ';
                    else if (bingo_map[ty][tx] == ' ')
                        bingo_map[ty][tx] = 'O';
                }
            }
        }
        else{
            cout << "좌표의 범위가 잘못되었습니다." << endl;
            return;
        }
    }
    bool CheckingBingo() {
        for (int i = 0; i < 5; i++) {
            bool isBingo = true;
            int tmp = 0;

            for (int j = 0; j < 5; j++) {
                if (bingo_map[i][j] == 'X')
                    tmp++;
                if(tmp == 5)
                    break;
            }
            for (int j = 0; j < 5; j++) {
                if (bingo_map[i][j] != 'O' && bingo_map[i][j] != 'X') {
                    isBingo = false;
                    break;
                }
            }

            if (isBingo) {
                for (int j = 0; j < 5; j++)
                    bingo_map[i][j] = 'X';
                threerow[i]++;
            }
        }

        for (int j = 0; j < 5; j++) {
            bool isBingo = true;
            int tmp = 0;

            for (int i = 0; i < 5; i++) {
                if (bingo_map[i][j] == 'X')
                    tmp++;
                if (tmp == 5)
                    break;
            }
            for (int i = 0; i < 5; i++) {
                if (bingo_map[i][j] != 'O' && bingo_map[i][j] != 'X') {
                    isBingo = false;
                    break;
                }
            }
            if (isBingo) {
                for (int i = 0; i < 5; i++) {
                    bingo_map[i][j] = 'X';
                }
                threecol[j]++;
            }
        }
        bool isDiagonalBingo1 = true;
        for (int i = 0; i < 5; i++) {
            if (bingo_map[i][i] != 'O' && bingo_map[i][i] != 'X') {
                isDiagonalBingo1 = false;
                break;
            }
            for (int j = 0; j < 5; j++)
                if (bingo_map[j][j] == 'X')
                    break;
        }

        if (isDiagonalBingo1) {
            for (int i = 0; i < 5; i++)
                bingo_map[i][i] = 'X';
            threedig[0]++;
            return true;
        }

        bool isDiagonalBingo2 = true;
        for (int i = 0; i < 5; i++) {
            if (bingo_map[i][4 - i] != 'O' && bingo_map[i][4 - i] != 'X'){
                isDiagonalBingo2 = false;
                break;
            }
            for (int j = 0; j < 5; j++)
                if (bingo_map[j][4 - j] == 'X')
                    break;
        }

        if (isDiagonalBingo2) {
            for (int i = 0; i < 5; i++) {
                bingo_map[i][4 - 1] = 'X';
            }
            threedig[1]++;
            return true;
        }
        return true;
    }
    bool showTime() {
        int rowcheck = 0;
        int colcheck = 0;
        int allfalse = 0;
        int tmp = 0;
        if (count != 0 && count % 3 == 0) {
            if (exBingoCnt[count] == exBingoCnt[count - 1])
                return true;
            for (int i = 0; i < 4; i++) {
                rowcheck = 0;
                colcheck = 0;
                int a_row = input_row + dy[i];
                int a_col = input_col + dx[i];
                if (a_row < 0 || a_col < 0 || a_row > 4 || a_col > 4) {
                    tmp++;
                    continue;
                }
                for (int j = 0; j < 5; j++) {
                    if (bingo_map[a_row][j] == 'X')
                        rowcheck++;
                }
                if (rowcheck == 5) {
                    count++;
                    return false;
                }
                else
                    allfalse++;
                for (int j = 0; j < 5; j++) {
                    if (bingo_map[j][a_col] == 'X')
                        colcheck++;
                }
                if (colcheck == 5) {
                    count++;
                    return false;
                }
                else
                    allfalse++;
                if (allfalse == (8 - (tmp * 2)))
                    return true;
            }
        }
        count++;
        return false;
    }
    bool threebingocount() {
        bingoCnt = 0;
        for (int i = 0; i < 5; i++) {
            if (threerow[i] > 0)
                bingoCnt++;
            if (threecol[i] > 0)
                bingoCnt++;
        }
        if (threedig[0] > 0)
            bingoCnt++;
        if (threedig[1] > 0)
            bingoCnt++;
        exBingoCnt[count] = bingoCnt;

        if (bingoCnt >= 3)
            return true;
        else
            return false;
    }
};

class BoomChecker {
public:
    bool Star(char array[5][5]) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (array[i][j] == '*') {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> rnd(0, 4);

    int ver = 1;
    BingoGame game(ver);

    while (true) {
        int s_row = rnd(gen);
        int s_col = rnd(gen);

        game.bingo_map[s_row][s_col] = 'S';

        int b_row = rnd(gen);
        int b_col = rnd(gen);
        game.bingo_map[b_row][b_col] = 'O';

        if (game.bingo_map[s_row][s_col] != game.bingo_map[b_row][b_col])
            break;
        else {
            game.bingo_map[s_row][s_col] = ' ';
            game.bingo_map[b_row][b_col] = ' ';
        }
    }
    while (true) {
        game.showGround(game.bingo_map);
        BoomChecker checker;
        if (checker.Star(game.bingo_map)) {
            cout << "폭탄이 파괴되었습니다! 게임을 종료합니다.";
            break;
        }
        game.turn();
        game.CheckingBingo();
        if (game.threebingocount()) {
            game.showGround(game.bingo_map);
            cout << "3빙고 ! 게임을 종료합니다." << endl;
            break;
        }
        if (game.showTime()) {
            game.showGround(game.bingo_map);
            cout << "폭탄을 완성하지 못했습니다! 게임을 종료합니다.";
            break;
        }
    }
    return 0;
}