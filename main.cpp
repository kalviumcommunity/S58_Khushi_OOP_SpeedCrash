#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

const int ROW = 52;
const int COLUMN = 72;

// Initilizing Class as Track
class Track {
private:
    char grid[ROW][COLUMN];

public:
    Track() {
        initRace();
    }

    void initRace() {
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COLUMN; j++) {
                if (i == 0 || i == 51) { // top and bottom boundaries
                    grid[i][j] = (j < 71) ? 'X' : 'F'; // finish line
                } else if (j == 0 || j == 71) { // left and right boundaries
                    grid[i][j] = 'X';
                } else if (i >= 1 && i <= 35 && j >= 10 && j <= 29) { // left barrier
                    grid[i][j] = 'X';
                } else if (i >= 16 && i <= 50 && j >= 40 && j <= 64) { // right barrier
                    grid[i][j] = 'X';
                } else {
                    grid[i][j] = ' ';
                }
            }
        }
    }

    void printRace() const {
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COLUMN; j++) {
                cout << grid[i][j];
            }
            cout << endl;
        }
    }

    char getCell(int x, int y) const {
        return grid[y][x];
    }

    void setCell(int x, int y, char value) {
        grid[y][x] = value;
    }
};

// initilizing Car as a Class
class Car {
private:
    int xPosition;
    int yPosition;
    int xVelocity;
    int yVelocity;

    static int totalCars;     // Static variable to track the total number of cars
    static int totalCrashes;  // Static variable to track the total number of crashes   

public:

    Car(int x, int y) : xPosition(x), yPosition(y), xVelocity(0), yVelocity(0) {
        // Increasing the cout when a car is initialized 
        totalCars++;
        };
    ~Car() {
        // Decrement the count when a car is destroyed
        totalCars--;  
    }
    void updatePosition(int xAcc, int yAcc, const Track &track) {
        this->xVelocity += xAcc;
        this->yVelocity += yAcc;
        this->xPosition += xVelocity;
        this->yPosition += yVelocity;
    }

    int getXPosition() const {
        return xPosition;
    }

    int getYPosition() const {
        return yPosition;
    }

    bool hasCrashed(const Track &track) const {
       if (xPosition < 0 || xPosition >= COLUMN || yPosition < 0 || yPosition >= ROW || track.getCell(xPosition, yPosition) == 'X') {
            // Increment crash count if the car has crashed
            totalCrashes++;  
            return true;
        }
        return false;
        }

    bool hasFinished() const {
        return (yPosition == 51 && xPosition >= 65 && xPosition < 71);
    }
    static int getTotalCars() {
    return totalCars;
}

    static int getTotalCrashes() {
        return totalCrashes;
    }

};


// Initialize static variables 
int Car::totalCars = 0;
int Car::totalCrashes = 0;

int main() {
    // Initilizing track as a dynamic object using new
    Track* track = new Track();
    
    // Initilizing cars as dynamic objects
    Car* cars[] = {new Car(1, 1), new Car(2, 1)};

    int counter = 0; // counter for seconds

    // Initialize track with the first car's position where car is represented as "0"
    track->setCell(cars[0]->getXPosition(), cars[0]->getYPosition(), '0');
    track->printRace();

    while (true) {
        int xAcceleration, yAcceleration;
        cout << "Horizontal and vertical acceleration (-1, 0, 1): ";
        cin >> xAcceleration >> yAcceleration;

        if (xAcceleration < -1 || xAcceleration > 1 || yAcceleration < -1 || yAcceleration > 1) {
            cout << "Invalid acceleration values!" << endl;
            continue;
        }

        counter++;

        // Clearing previous car position by replacing it with " "
        track->setCell(cars[0]->getXPosition(), cars[0]->getYPosition(), ' ');

        // Updating car's position
        cars[0]->updatePosition(xAcceleration, yAcceleration, *track);

        // Checking if car has crash
        if (cars[0]->hasCrashed(*track)) {
            track->setCell(cars[0]->getXPosition(), cars[0]->getYPosition(), '0');
            track->printRace();
            cout << "Crashed after " << counter << " seconds" << endl;
            cout << "Total Crashes: " << Car::getTotalCrashes() << endl;
            // Clean up dynamically allocated memory
            delete track;
            delete cars[0];
            delete cars[1];

            return 0;
        }

        // Placing car in the new position as "0"
        track->setCell(cars[0]->getXPosition(), cars[0]->getYPosition(), '0');
        track->printRace();

        // Checking if the car has reached the finish line
        if (cars[0]->hasFinished()) {
            track->setCell(cars[0]->getXPosition(), cars[0]->getYPosition(), '0');
            track->printRace();
            cout << "You finished the race in " << counter << " seconds!" << endl;
            cout << "Total Crashes: " << Car::getTotalCrashes() << endl;
            
            // Clean up dynamically allocated memory
            delete track;
            delete cars[0];
            delete cars[1];

            return 0;
        }
    }

    // Clean up dynamically allocated memory in case of any terminance 
    delete track;
    delete cars[0];
    delete cars[1];

    return 0;
}
