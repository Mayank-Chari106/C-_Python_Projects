#include <iostream>
using namespace std;

int addRecursive(int a, int b, int carry = 0)
{
    // Base case
    if (a == 0 && b == 0 && carry == 0)
        return 0;

    int digit1 = a % 10;
    int digit2 = b % 10;
    int sum = digit1 + digit2 + carry;
    int resultDigit = sum % 10;
    int newCarry = sum / 10;

    // Recursive call 
    int remaining = addRecursive(a / 10, b / 10, newCarry);

    return remaining * 10 + resultDigit;
}

int main()
{
    int num1, num2;

    cout << "Enter first N-digit number: ";
    cin >> num1;
    cout << "Enter second N-digit number: ";
    cin >> num2;
    int result = addRecursive(num1, num2);
    cout << "Sum = " << result << endl;

    return 0;
}