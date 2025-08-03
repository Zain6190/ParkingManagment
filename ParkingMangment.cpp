 #include <iostream>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <fstream>
#include <sstream>
using namespace std;
class Vehicle {
protected:
    string licensePlate;
    time_t entryTime;

public:
    Vehicle(string& plate) : licensePlate(plate) {
        entryTime = time(nullptr);
    }

    virtual double calculateFee() const = 0; 
    const string& getLicensePlate() const { return licensePlate; }
};


class Car : public Vehicle {
public:
    Car(string& plate) : Vehicle(plate) {}

    double calculateFee() const override {
        
        const double hourlyRate = 2.0;

     
        const double durationHours = 3.5; 

        return hourlyRate * durationHours;
    }
};

class Bike : public Vehicle {
public:
    Bike(string& plate) : Vehicle(plate) {}

    double calculateFee() const override {
        
        const double hourlyRate = 1.0;

      
        const double durationHours = 2.0; 

        return hourlyRate * durationHours;
    }
};

class Truck : public Vehicle {
public:
    Truck(string& plate) : Vehicle(plate) {}

    double calculateFee() const override {
      
        const double hourlyRate = 5.0;

        
        const double durationHours = 4.0; 

        return hourlyRate * durationHours;
    }
};

// Parking lot management
class ParkingLot {
private:
    vector<Vehicle*> vehicles;
    static const int MAX_CAPACITY = 100; 

public:
    ParkingLot() {
        vehicles.reserve(MAX_CAPACITY);
    }

    void parkVehicle(Vehicle* vehicle) {
        if (vehicles.size() >= MAX_CAPACITY) {
            throw runtime_error("Parking lot is full!");
        }
        vehicles.push_back(vehicle);
    }

    const vector<Vehicle*>& getVehicles() const {
        return vehicles;
    }

    
    void loadRecordsFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            throw runtime_error("Failed to open file for reading!");
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string plate, type;
            time_t entry, exit;
            getline(ss, plate, ',');
            getline(ss, type, ',');
            ss >> entry;
            ss >> exit;

            Vehicle* vehicle = nullptr;
            if (type == "Car") {
                vehicle = new Car(plate);
            } else if (type == "Bike") {
                vehicle = new Bike(plate);
            } else if (type == "Truck") {
                vehicle = new Truck(plate);
            }

            vehicles->setExitTime(exit);
            vehicles.push_back(vehicle);
        }

        file.close();
    }
};
int main() {
    ParkingLot parkingLot;

    try {
    	  parkingLot.loadRecordsFromFile("parking_records.txt");
        while (true) {
            cout << "Menu:\n";
            cout << "1. Park a vehicle\n";
            cout << "2. View parked vehicles\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1: {
                    cout << "Enter vehicle type (1 for Car, 2 for Bike, 3 for Truck): ";
                    int vehicleType;
                    cin >> vehicleType;
                    
                    cout << "Enter license plate: ";
                    string plate;
                    cin >> plate;

                    Vehicle* newVehicle = nullptr;
                    if (vehicleType == 1) {
                        newVehicle = new Car(plate);
                    } 
					else if (vehicleType == 2) {
                        newVehicle = new Bike(plate);
                    } 
					else if (vehicleType == 3) {
                        newVehicle = new Truck(plate);
                    } 
					else {
                        cout << "Invalid vehicle type!\n";
                        continue;
                    }

                    parkingLot.parkVehicle(newVehicle);
                    break;
                }
                case 2:
                    cout << "Parked vehicles:\n";
                    for (const auto& vehicle : parkingLot.getVehicles()) {
                        cout << "License Plate: " << vehicle->getLicensePlate()
                                  << ", Fee: $" << vehicle->calculateFee() << std::endl;
                    }
                    break;
                case 3:
                    cout << "Exiting. Have a great day!\n";
                    return 0;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        }
    } catch (const std::exception& e) {
       cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}