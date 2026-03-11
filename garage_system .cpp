#include <iostream>
#include <string>
using namespace std;

// Structure to store customer details
struct Customer {
    string customerID;
    string name;
};

// Structure to store car details
struct Car {
    string carID;
    string carModel;
    string licensePlate;
    string sparePartID;  // Manager will assign this
    bool washed;
    bool maintained;
};

// Structure to store maintenance details
struct Maintenance {
    bool washed;
    bool maintained;
};

// Structure to store performance details
struct Performance {
    bool isRunning; // True if car is running, false otherwise
};

// Structure to store manager details
struct Manager {
    string managerID;
    string managerName;
};

// Function to add a customer
void addCustomer(Customer customers[], Car cars[], int& customerCount, int& carCount, int& sparePartCounter) {
    Customer customer;
    Car car;

    cout << "Enter Customer Name: ";
    cin >> customer.name;  // Using the customer's name as the ID
    customer.customerID = customer.name;
    cout << "Enter Car Model: ";
    cin >> car.carModel;
    cout << "Enter License Plate: ";
    cin >> car.licensePlate;

    // Manager assigns a unique Spare Part ID based on the sparePartCounter
    car.sparePartID = "SP" + to_string(sparePartCounter++);
    car.carID = "CAR" + to_string(carCount++);

    car.washed = false;
    car.maintained = false;

    customers[customerCount] = customer;
    cars[customerCount] = car;
    customerCount++;

    cout << "Customer with ID " << customer.customerID << " has been added with Car ID " << car.carID << " and Spare Part ID " << car.sparePartID << ".\n";
}

// Function to manage customer requests (washing, maintaining, and checking performance)
void manageRequests(Maintenance& maintenance, Car& car, Performance& performance) {
    int choice;
    cout << "Customer, choose the service:\n";
    cout << "1. Wash Car\n";
    cout << "2. Maintain Car\n";
    cout << "3. Check Car Performance (Is it Running?)\n";
    cin >> choice;

    switch (choice) {
        case 1:
            maintenance.washed = true;
            car.washed = true;
            cout << "Car washed.\n";
            break;
        case 2:
            maintenance.maintained = true;
            car.maintained = true;
            // After maintenance, performance is still not running until verified
            cout << "Car maintained. Please verify the spare part ID.\n";
            break;
        case 3:
            cout << "The car is currently " << (performance.isRunning ? "running." : "not running.") << endl;
            break;
        default:
            cout << "Invalid choice.\n";
            break;
    }
}

// Function for customer to verify spare part ID (manager assigns this)  
void verifySparePart(Car& car, Performance& performance) {
    string inputSparePartID;
    cout << "Customer, please verify if your car's spare part is unchanged.\n";
    cout << "Enter the spare part ID to check if it has changed: ";
    cin >> inputSparePartID;

    if (inputSparePartID == car.sparePartID) {
        cout << "Spare part ID verified. Car service completed. Car is now running.\n";
        performance.isRunning = true;  // Car is running after correct verification and tell spare part is not changed
    } else {
        cout << "Spare part ID does not match. Car is not running. Contact the manager\n";
        performance.isRunning = false; // Car is not running after incorrect verification and tell the spare part has been changed
    }
}

// Function to show car details by car ID
void showCarDetails(const Car cars[], const Customer customers[], int customerCount, const Performance& performance) {
    string carID;
    cout << "Enter Car ID: ";
    cin >> carID;

    // Loop through customers to find the car with the matching carID
    for (int i = 0; i < customerCount; ++i) {
        if (cars[i].carID == carID) {
            cout << "Customer ID: " << customers[i].customerID << endl;
            cout << "Car ID: " << cars[i].carID << endl;
            cout << "Car Model: " << cars[i].carModel << endl;
            cout << "License Plate: " << cars[i].licensePlate << endl;
            cout << "Spare Part ID: " << cars[i].sparePartID << endl;

            // Display the status of washing and maintenance
            cout << "Washed: " << (cars[i].washed ? "Yes" : "No") << endl;
            cout << "Maintained: " << (cars[i].maintained ? "Yes" : "No") << endl;

            // Show the performance (running or not running)
            cout << "Performance: " << (performance.isRunning ? "Running" : "Not Running") << endl;
            return;
        }
    }

    // If no car is found with the given carID
    cout << "Car ID not found.\n";
}

// Function to show manager details
void showManagerDetails(const Manager& manager) {
    cout << "Manager ID: " << manager.managerID << endl;
    cout << "Manager Name: " << manager.managerName << endl;
}

// Function to display menu and get user choice
int displayMenu() {
    int choice;
    cout << "\nGarage Management System\n";
    cout << "1. Add Customer\n";
    cout << "2. Manage Requests\n";
    cout << "3. Show Car Details\n";
    cout << "4. Show Manager Details\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// Main function
int main() {
    const int MAX_CUSTOMERS = 100;
    Car cars[MAX_CUSTOMERS];
    Customer customers[MAX_CUSTOMERS];
    Maintenance maintenance;
    Performance performance;  // Track performance of cars (running or not)
    Manager manager = {"1", "BIRHANU"};  // Assigning a sample Manager

    int sparePartCounter = 1; // Start assigning Spare Part IDs from SP1
    int carCount = 1;         // Start assigning Car IDs from CAR1
    int customerCount = 0;    // Keep track of the number of customers

    while (true) {
        int choice = displayMenu();  // Display menu for options

        switch (choice) {
            case 1:
                addCustomer(customers, cars, customerCount, carCount, sparePartCounter);
                break;
            case 2: {
                string carID;
                cout << "Enter Car ID for the service: ";
                cin >> carID;
                for (int i = 0; i < customerCount; ++i) {
                    if (cars[i].carID == carID) {
                        manageRequests(maintenance, cars[i], performance);
                        // If maintenance was chosen, verify the spare part
                        if (maintenance.maintained) {
                            verifySparePart(cars[i], performance);  // Verify spare part after maintenance
                        }
                        break;
                    }
                }
                break;
            }
            case 3:
                showCarDetails(cars, customers, customerCount, performance);
                break;
            case 4:
                showManagerDetails(manager);
                break;
            case 5:
                cout << "Exiting the system.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}


