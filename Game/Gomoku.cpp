#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum Stone {Empty, BlackStone, WhiteStone};
enum Status {Continue, BlackWin, WhiteWin, Draw};
enum Player {BlackPlayer, WhitePlayer};

class Gomoku
{
public:
    Gomoku() : board(15, vector< Stone >(15, Empty))
    {
        nowPlayer = BlackPlayer;
        gameStatus = Continue;
        lastStonePos = {0, 0};
        round = 1;
    }

    void game()
    {
        for( ; round < 256; round++)
        {
            printBoard();
            playerMove();
            updateStatus();
            if(gameStatus != Continue)
                break;
            endRound();
        }
            cleanSrceen();
            printBoard();
            printResult();

    }
    void printBoard()
    {
        char c = 'A';
        printNumberLine();
        for(int i = 0; i < 15 ; i++)
        {
            cout << " " << c++ << "  ";
            for(int j = 0; j < 15; j++)
                cout << printStone(board[i][j]) << "   ";
            printEmptyLine();
        }
    }
    
    void playerMove()
    {
        bool isPosAvailable = true;
        string input;
        do
        {
            cout << ((nowPlayer == BlackPlayer) ? "Black" : "White") << "'s turn: ";
            cin >> input;
            checkPosition(input, isPosAvailable);

            if(isPosAvailable)
                updateBoard(input, lastStonePos);
            else
                cout << "Wrong input! This position is not available!" << endl;
        } while (!isPosAvailable);
        
    }

    void updateStatus()
    {
        bool win = (checkColumn(lastStonePos) ||
                    checkRow(lastStonePos) ||
                    checkTopLeft2BottomRight(lastStonePos) ||
                    checkTopRight2BottomLeft(lastStonePos));
        if(win)
        {
            gameStatus = (nowPlayer == BlackPlayer) ? BlackWin : WhiteWin;
        }
        else if(round == 255)
            gameStatus = Draw;
    }

    void endRound()
    {
        switchPlayer();
        cleanSrceen();
    }

    void printResult()
    {
        if(gameStatus == BlackWin)
            cout << "Black win!" << endl;
        else if(gameStatus == WhiteWin)
            cout << "White win!" << endl;
        else
            cout << "Draw!" << endl;

        cout << "total round: " << round << endl;
    }

private:
    vector< vector< Stone > > board;
    Status gameStatus; 
    Player nowPlayer;
    vector< int > lastStonePos;
    int round;
    const char blackStone = 'O';
    const char whiteStone = 'X';
    const char emptyStone = '\'';

    char printStone(Stone s)
    {
        if(s == BlackStone)
            return blackStone;
        else if(s == WhiteStone)
            return whiteStone;
        else
            return emptyStone;
    }
    void printNumberLine()
    {
        cout << "    ";
        for(int i = 1; i < 10; i++)
            cout << i << "   ";
        for(int i = 10; i < 16; i++)
            cout << i << "  ";
        cout << endl;
    }
    void printEmptyLine()
    {
        for(int i = 0; i < 64; i++)
            cout << " ";
        cout << endl;
    }

    void checkPosition(string input, bool &b)
    {
        b = (checkInput(input) && checkEmptyStone(input));
    }
    bool checkInput(string input)
    {
        return (checkLength(input) &&
                checkFirstCharacter(input) &&
                checkNumber(input));
    }
    bool checkLength(string s)
    {
        int l = s.length();
        return (l == 2 || l == 3);
    }
    bool checkFirstCharacter(string s)
    {
        char c = s[0];
        return (((c > 64 && c < 80) || (c > 96 && c < 112)));
    }
    bool checkNumber(string s)
    {
    int l = s.length();
    char n1 = s[1];
    char n2 = s[2];
    if(l == 2)
        return !(n1 < 49 || n1 > 57);
    else if(l == 3 && n1 == '1')
        return !(n2 < 48 || n2 > 53);
    else
        return false;
    }
    bool checkEmptyStone(string s)
    {
        int pos[2] = {0, 0};
        pos[0] = (s[0] - 65) % 32;
        if(s.length() == 2)
            pos[1] = s[1] - 49;
        else
            pos[1] = s[2] - 49 + 10;
        
        return (board[pos[0]][pos[1]] == Empty);
    }

    void updateBoard(string input, vector< int > &lastPos)
    {
        lastPos[0] = (input[0] - 65) % 32;
        if(input.length() == 2)
            lastPos[1] = input[1] - 49;
        else
            lastPos[1] = input[2] - 49 + 10;

        board[lastPos[0]][lastPos[1]] = (nowPlayer == BlackPlayer) ? BlackStone : WhiteStone;
    }

    bool checkColumn(vector< int > lastPos)
    {
        vector< int > newPoint(2);
        int stoneNumber;
        Stone stone = (nowPlayer == BlackPlayer) ? BlackStone : WhiteStone;
        findNewPoint(lastPos, newPoint, -1, 0);

        for(int i = 0; (i <= (lastPos[0] - newPoint[0])) && (newPoint[0] + i < 11) ; i++)
        {
            stoneNumber = 0;
            for(int j = 0; j < 5; j++)
            {
                if(board[ newPoint[0] + i + j ][ newPoint[1] ] == stone)
                    stoneNumber++;
            }
            if(stoneNumber == 5)
                return true;
        }
        return false;
    }
    bool checkRow(vector< int > lastPos)
    {
        vector< int > newPoint(2);
        int stoneNumber;
        Stone stone = (nowPlayer == BlackPlayer) ? BlackStone : WhiteStone;
        findNewPoint(lastPos, newPoint, 0, -1);

        for(int i = 0; i <= ((lastPos[1] - newPoint[1])) && (newPoint[1] + i < 11) ; i++)
        {
            stoneNumber = 0;
            for(int j = 0; j < 5; j++)
            {
                if(board[ newPoint[0] ][ newPoint[1] + i + j ] == stone)
                    stoneNumber++;
            }
            if(stoneNumber == 5)
                return true;
        }

        return false;
    }
    bool checkTopLeft2BottomRight(vector< int > lastPos)
    {
        vector< int > newPoint(2);
        int stoneNumber;
        Stone stone = (nowPlayer == BlackPlayer) ? BlackStone : WhiteStone;
        findNewPoint(lastPos, newPoint, -1, -1);

        for(int i = 0; i <= (lastPos[0] - newPoint[0]) && (newPoint[0] + i < 11) && (newPoint[1] + i < 11) ; i++)
        {
            stoneNumber = 0;
            for(int j = 0; j < 5; j++)
            {
                if(board[ newPoint[0] + i + j ][ newPoint[1] + i + j ] == stone)
                    stoneNumber++;
            }
            if(stoneNumber == 5)
                return true;
        }

        return false;
    }
    bool checkTopRight2BottomLeft(vector< int > lastPos)
    {
        vector< int > newPoint(2);
        int stoneNumber;
        Stone stone = (nowPlayer == BlackPlayer) ? BlackStone : WhiteStone;
        findNewPoint(lastPos, newPoint, -1, 1);

        for(int i = 0; i <= (lastPos[0] - newPoint[0]) && (newPoint[0] + i < 11) && (newPoint[1] - i > 3) ; i++)
        {
            stoneNumber = 0;
            for(int j = 0; j < 5; j++)
            {
                if(board[ newPoint[0] + i + j ][ newPoint[1] - i - j ] == stone)
                    stoneNumber++;
            }
            cout << endl;
            if(stoneNumber == 5)
                return true;
        }

        return false;
    }

    void findNewPoint(vector< int > lp, vector< int > &np, int r, int c)
    {
        np[0] = lp[0];
        np[1] = lp[1];
        for(int i = 0; i < 4; i++)
        {
            if((np[0] + r >= 0) && (np[1] + c >= 0))
            {
                np[0] = np[0] + r;
                np[1] = np[1] + c;
            }
            else
                break;
        }
    }
    void switchPlayer()
    {
        nowPlayer = (nowPlayer == BlackPlayer) ? WhitePlayer : BlackPlayer;
    }
    void cleanSrceen()
    {
        cout << "\033[1J\033[H";
    }

};

int main()
{
    Gomoku g;
    g.game();
}
