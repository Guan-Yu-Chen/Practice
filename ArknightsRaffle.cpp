#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int main() {
    system("chcp 65001");
    srand(time(0));
    
    vector<int> Jackpot(99);                //  記錄在第幾抽出貨的次數, 1-99抽
    double test_round = 1000000.0;          //  100萬次
    double Prob;                            //  抽獎機率
    long spend_times = 0;                   //  紀錄中獎100萬次花了幾抽

    for(int i = 0 ; i < test_round ; i++)
    {
        for(int j = 1 ; j <= 99 ; j++)
        {
            //  設定機率
            if(j > 50)
            {
                Prob = 0.02 + (j - 50) * 0.02;
            }
            else
            {
                Prob = 0.02;
            }
            
            //  模擬抽獎
            if(rand() / (double)RAND_MAX <= Prob)   //  中獎
            {
                Jackpot[j-1]++;                     //  記錄在第幾抽中獎
                break;
            }
        }
    }
    for(int i = 0 ; i < 99 ; i++)
    {
        spend_times += Jackpot[i] * (i+1);          //  計算中獎100萬次花了幾抽, 在第i抽中獎的次數 * i抽
    }

    cout << "期望值 = " << spend_times / test_round << " 抽" << endl;
    cout << "第N抽出貨的機率 :" << endl;
    for(int i = 0 ; i < 99 ; i++)
    {
        cout << "第" << i+1 << "抽: " << Jackpot[i] / test_round * 100 << "%\t\t";
        if((i+1) % 5 == 0)
        {
            cout << endl;
        }
    }

    return 0;
}
