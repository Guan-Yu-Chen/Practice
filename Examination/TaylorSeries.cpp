#include <iostream>
#include <cmath>
using namespace std;

const double ERROR = 10e-6;
const double Center = 0.5;
long long factorial(int);
double taylor(int, double);
double derivative(int);

int main()
{
    double input;
    cout << "calculate cos(x)\nx = ";
    cin >> input;
    double remainder;
    double value = 0;
    int i = -1;
    do
    {
        i++;
        value += taylor(i, input);
        remainder = abs(cos(input) - value);
    } while (remainder > ERROR);

    cout << "cos( " << input << " ) = " << value << endl;
    cout << "n = " << i << endl;
    

}

long long factorial(int x)
{
    long long product = 1;
    for(int i = 1; i <= x; i++)
        product *= i;

    return product;
}

double taylor(int n, double x)
{
    return derivative(n) * pow((x - Center), n) / factorial(n);
}

double derivative(int degree)
{
    if(degree % 4 == 0)
        return cos(Center);
    else if(degree % 4 == 1)
        return (-1) * sin(Center);
    else if(degree % 4 == 2)
        return (-1) * cos(Center);
    else
        return sin(Center);
}
