#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <limits>

using namespace std;

// ====================== BASE CLASS: PERSON ======================
class Person {
protected:
    string name;
    string phone;

public:
    Person(string n, string p) : name(n), phone(p) {}

    virtual void display() const {
        cout << "Name: " << name
             << "\nPhone: " << phone << endl;
    }

    string getName() const { return name; }
    string getPhone() const { return phone; }

    virtual ~Person() {}
};

// ====================== DERIVED CLASS: CUSTOMER ======================
class Customer : public Person {
private:
    string licenseNo;

public:
    Customer(string n, string p, string l) : Person(n, p), licenseNo(l) {}

    void display() const override {
        Person::display();
        cout << "License No: " << licenseNo << endl;
    }

    string getLicense() const { return licenseNo; }
};

// ====================== BASE CLASS: VEHICLE ======================
class Vehicle {
protected:
    int vehicleId;
    string model;
    double ratePerDay;
    bool available;

public:
    Vehicle(int id, string m, double rate)
        : vehicleId(id), model(m), ratePerDay(rate), available(true) {}

    virtual double calculateRent(int days) const {
        return ratePerDay * days;
    }

    virtual void display() const {
        cout << left << setw(10) << vehicleId
             << setw(15) << model
             << setw(10) << ratePerDay
             << setw(12) << (available ? "Yes" : "No");
    }

    int getVehicleId() const { return vehicleId; }
    bool isAvailable() const { return available; }
    void setAvailability(bool status) { available = status; }

    virtual ~Vehicle() {}
};

// ====================== DERIVED CLASS: CAR ======================
class Car : public Vehicle {
private:
    int seats;

public:
    Car(int id, string m, double rate, int s)
        : Vehicle(id, m, rate), seats(s) {}

    double calculateRent(int days) const override {
        return (ratePerDay * days) + 500;
    }

    void display() const override {
        Vehicle::display(); // No extra info column
        cout << endl;
    }
};

// ====================== DERIVED CLASS: BIKE ======================
class Bike : public Vehicle {
private:
    bool helmetIncluded;

public:
    Bike(int id, string m, double rate, bool helmet)
        : Vehicle(id, m, rate), helmetIncluded(helmet) {}

    void display() const override {
        Vehicle::display(); // No extra info column
        cout << endl;
    }
};

// ====================== RENTAL SYSTEM ======================
class RentalSystem {
private:
    vector<Vehicle*> vehicles;
    vector<Customer> customers;
    map<int, Customer*> rentedVehicles; // vehicleId -> Customer*

public:
    RentalSystem() {
        // Vehicles
        vehicles.push_back(new Car(101, "Swift", 2000, 5));
        vehicles.push_back(new Car(102, "Creta", 3500, 5));
        vehicles.push_back(new Car(103, "Innova", 4500, 7));
        vehicles.push_back(new Bike(201, "Activa", 800, true));
        vehicles.push_back(new Bike(202, "RoyalEnfield", 1500, false));
    }

    Customer* addCustomer() {
        string name, phone, license;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Phone: ";
        getline(cin, phone);
        cout << "Enter License No: ";
        getline(cin, license);

        customers.push_back(Customer(name, phone, license));
        cout << "Customer added successfully!\n";
        return &customers.back();
    }

    Customer* findCustomer(const string& name, const string& phone) {
        for (auto& c : customers) {
            if (c.getName() == name && c.getPhone() == phone)
                return &c;
        }
        return nullptr;
    }

    void showVehicles() {
        cout << "\nAvailable Vehicles:\n";
        cout << left << setw(10) << "ID"
             << setw(15) << "Model"
             << setw(10) << "Rate"
             << setw(12) << "Available" << endl;

        for (auto v : vehicles)
            v->display();
    }

    void rentVehicle() {
        string name, phone;
        showVehicles();

        cout << "\nEnter Customer Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        cout << "Enter Customer Phone: ";
        getline(cin, phone);

        Customer* customer = findCustomer(name, phone);
        if (!customer) {
            cout << "Customer not found, please register first.\n";
            customer = addCustomer();
        }

        int vid, days;
        cout << "Enter Vehicle ID: ";
        cin >> vid;
        cout << "Enter Days: ";
        cin >> days;

        for (auto v : vehicles) {
            if (v->getVehicleId() == vid && v->isAvailable()) {
                double bill = v->calculateRent(days);
                if (days >= 7) bill *= 0.9;

                v->setAvailability(false);
                rentedVehicles[vid] = customer;

                cout << "Vehicle rented successfully!\n";
                cout << "Total Amount: Rs. " << bill << endl;
                return;
            }
        }
        cout << "Vehicle not available!\n";
    }

    void returnVehicle() {
        int vid;
        cout << "\nEnter Vehicle ID to return: ";
        cin >> vid;

        auto it = rentedVehicles.find(vid);
        if (it != rentedVehicles.end()) {
            for (auto v : vehicles) {
                if (v->getVehicleId() == vid) {
                    v->setAvailability(true);
                    break;
                }
            }
            cout << "Vehicle returned successfully from " 
                 << it->second->getName() << "!\n";
            rentedVehicles.erase(it);
        } else {
            cout << "This vehicle was not rented!\n";
        }
    }

    ~RentalSystem() {
        for (auto v : vehicles)
            delete v;
    }
};

// ====================== MAIN FUNCTION ======================
int main() {
    RentalSystem system;
    int choice;

    do {
        cout << "\n========== CAR RENTAL SYSTEM ==========\n";
        cout << "1. Add Customer\n";
        cout << "2. Show Vehicles\n";
        cout << "3. Rent Vehicle\n";
        cout << "4. Return Vehicle\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: system.addCustomer(); break;
            case 2: system.showVehicles(); break;
            case 3: system.rentVehicle(); break;
            case 4: system.returnVehicle(); break;
            case 5: cout << "Thank you!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}