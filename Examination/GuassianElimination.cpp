#include <iostream>
#include <ctime>
using namespace std;

const int ROW = 2;
const int COLUMN = ROW + 1;

void setMatrix(double m[ROW][COLUMN])
{
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COLUMN; j++)
        {
            m[i][j] = rand() % 19 - 9;
        }
    }
}

void printMatrix(double m[ROW][COLUMN])
{
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COLUMN; j++)
        {
            cout << m[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    //set number
    double matrix[ROW][COLUMN] = {};
    srand(time(0));
    setMatrix(matrix);
    printMatrix(matrix);

    //solve problem
    double number;

    for(int i = 0; i < (COLUMN-1); i++)
    {
        number = matrix[i][i];              //n Ri
        for(int j = 0; j < COLUMN; j++)
        {
            matrix[i][j] /= number;
        }

        for(int j = 0; j < ROW; j++)        //Rj + nRi
        {
            if(j != i)
            {
                number = matrix[j][i];
                for(int k = 0; k < COLUMN; k++)
                {
                    matrix[j][k] -= (number * matrix[i][k]);
                }
            }
        }
    }

    //print answer
    printMatrix(matrix);
}
