#include <iostream>
#include <queue>
#include <string>
#include <sstream>
using namespace std;

struct Vehicle
{
    uint64_t vehicleID;   // 1 up to 10 billion
    uint16_t vehicleLevel; // 1 up to 10
    uint16_t nation;       // 1 up to 11

    Vehicle(uint64_t vehicleID, int vehicleLevel, int nation) : vehicleID(vehicleID), vehicleLevel(vehicleLevel), nation(nation) {}

    bool operator<(const Vehicle &v) const // we want to order the vehicles by level, and if they have the same level, by ID
    {
        if (vehicleLevel == v.vehicleLevel)
        {
            return vehicleID > v.vehicleID; // by ID
        }
        return vehicleLevel > v.vehicleLevel; // by level
    }
};

void populate(priority_queue<Vehicle> &vehicleQueue)
{
    uint16_t n; // number of nations 1-11
    uint32_t m; // number of vehicles 1 up to 10^5
    cin >> n;
    if (n < 1 || n > 11)
    {
        cout << "Number of Nations out of range. 1<=Nations<=11" << endl;
        exit(1);
    }
    cin >> m;
    if (m < 1 || m > 100000) // 10^5=100000
    {
        cout << "Number of Vehicles out of range. 1<=Vehicles<=100000" << endl;
        exit(1);
    }

    string vehicleString; // stores 101,1 for example
    string temp;          // temporary string to store the vehicle ID and level

    uint64_t vehicleID;   // 1 up to 10 billion
    uint16_t vehicleLevel; // 1 up to 10

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> vehicleString;

            stringstream vehicleStream(vehicleString);
            // treat entered string as a stream, to split the string at the comma
            getline(vehicleStream, temp, ','); // first is the vehicle ID
            vehicleID = stoi(temp);
            if (vehicleID < 1 || vehicleID > 10000000000) // 10^10=10000000000
            {
                cout << "Vehicle ID out of range. 1<=VehicleID<=1000" << endl;
                exit(1);
            }
            getline(vehicleStream, temp, ','); // second is the vehicle level
            vehicleLevel = stoi(temp);
            vehicleQueue.push(Vehicle(vehicleID, vehicleLevel, i));
        }
    }
}

void printVehicles(priority_queue<Vehicle> &vehicleQueue)
{
    while (!vehicleQueue.empty())
    {
        cout << vehicleQueue.top().vehicleID << " ";
        vehicleQueue.pop();
    }
}
int main()
{
    // Since we are combining our vehicles into one big list with vehicles of all nations, we don't need to store the vehicles in a map,
    // a class or struct is more appropriate
    priority_queue<Vehicle> vehicleQueue;

    populate(vehicleQueue);
    printVehicles(vehicleQueue); // print vehicles
    return 0;
}
