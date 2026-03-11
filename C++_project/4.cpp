#include <iostream>
using namespace std;

class Complex {
private:
double real;
double imag;
public:
Complex(double r = 0, double i = 0) : real(r), imag(i) {}
// Overload + operator using a member function
Complex operator+(const Complex& other) const {
return Complex(real + other.real, imag + other.imag);
}
void display() const {
if (imag < 0)
cout << real << " - " << -imag << "i" << endl;
else
cout << real << " + " << imag << "i" << endl;
}
};

int main() {
Complex c1(3.5, 2.5);
Complex c2(1.5, 4.5);
Complex result = c1 + c2; // Uses overloaded + operator
cout << "Sum of complex numbers: ";
result.display();
return 0;
}
