#include <iostream>
using namespace std;

// Forward declaration of class B
class B;
class A {
private:
 int numA;
public:
 A(int a) : numA(a) {}
 // Declare friend function that can access private members of A and B
 friend int addNumbers(A, B);
};
class B {
private:
 int numB;
public:
 B(int b) : numB(b) {}
 // Declare same friend function inside B class
 friend int addNumbers(A, B);
};
// Definition of friend function
int addNumbers(A aObj, B bObj) {
 // Accessing private members of both A and B
 return aObj.numA + bObj.numB;
}
int main() {
 A objA(10);
 B objB(20);
 cout << "Sum of private members: " << addNumbers(objA, objB) << endl;
 return 0;
}
