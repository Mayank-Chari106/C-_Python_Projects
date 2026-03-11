#include <iostream>
#include <string>

using namespace std;

class Student {
private:
string name;
int rollNumber;
int age;
public:
// Setter functions
void setName(const string& n) {
name = n;
}
void setRollNumber(int r) {
rollNumber = r;
}
void setAge(int a) {
age = a;
}
// Getter functions
string getName() const {
return name;
}
int getRollNumber() const {
return rollNumber;
}
int getAge() const {
return age;
}
};
int main() {
Student s;
// Setting values
s.setName("Mayank");
s.setRollNumber(31);
s.setAge(19);
// Getting and displaying values
cout << "Student Details:" << endl;
cout << "Name: " << s.getName() << endl;
cout << "Roll Number: " << s.getRollNumber() << endl;
cout << "Age: " << s.getAge() << endl;
return 0;
}