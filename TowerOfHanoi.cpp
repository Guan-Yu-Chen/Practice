#include <iostream>
#include <cmath>
using namespace std;

char Rod[4] = {' ','A', 'B', 'C'};

void moveDisk(int level, int r1, int r2)
{
    if(level == 1)
    {
        cout << "disk 1, from " << Rod[r1] << " to " << Rod[r2] << endl;
    }
    else
    {
        moveDisk(level - 1, r1, (r1^r2));
        cout << "disk " << level << ", from " << Rod[r1] << " to " << Rod[r2] << endl;
        moveDisk(level - 1, (r1^r2), r2);
    }
}

int main()
{
    int n;
    cout << "Enter the number of the disks:";
    cin >> n;
    cout << endl;

    moveDisk(n, 1, 3);

    cout << endl;
    cout << "It takes " << pow(2, n) - 1 << " steps to move." << endl;
}
