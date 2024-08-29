#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

const int ROW = 52;
const int COLUMN = 72;

// Track class definition
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

    void printRace() {
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

// Car class definition
class Car {
private:
    int xVelocity, yVelocity;
    int xPosition, yPosition;

public:
    Car(int x, int y) : xVelocity(0), yVelocity(0), xPosition(x), yPosition(y) {}

    void updatePosition(int xAcc, int yAcc, const Track &track) {
        xVelocity += xAcc;
        yVelocity += yAcc;
        xPosition += xVelocity;
        yPosition += yVelocity;
    }

    int getXPosition() const {
        return xPosition;
    }

    int getYPosition() const {
        return yPosition;
    }

    bool hasCrashed(const Track &track) const {
        if (xPosition < 0 || xPosition >= COLUMN || yPosition < 0 || yPosition >= ROW) {
            return true;
        }
        if (track.getCell(xPosition, yPosition) == 'X') {
            return true;
        }
        return false;
    }

    bool hasFinished() const {
        return (yPosition == 51 && xPosition >= 65 && xPosition < 71);
    }
};

int main() {
    Track track;
    Car car(1, 1);

    int counter = 0; // counter for seconds

    track.setCell(car.getXPosition(), car.getYPosition(), '0');
    track.printRace();

    while (true) {
        int xAcceleration, yAcceleration;
        cout << "Horizontal and vertical acceleration (-1, 0, 1): ";
        cin >> xAcceleration >> yAcceleration;

        if (xAcceleration < -1 || xAcceleration > 1 || yAcceleration < -1 || yAcceleration > 1) {
            cout << "Invalid acceleration values!" << endl;
            continue;
        }

        counter++;

        // Clear previous car position
        track.setCell(car.getXPosition(), car.getYPosition(), ' ');

        // Update car's position
        car.updatePosition(xAcceleration, yAcceleration, track);

        // Check for crash
        if (car.hasCrashed(track)) {
            track.setCell(car.getXPosition(), car.getYPosition(), '0');
            track.printRace();
            cout << "Crashed after " << counter << " seconds" << endl;
            return 0;
        }

        // Place car in the new position
        track.setCell(car.getXPosition(), car.getYPosition(), '0');
        track.printRace();

        // Check if the car finished the race
        if (car.hasFinished()) {
            track.setCell(car.getXPosition(), car.getYPosition(), '0');
            track.printRace();
            cout << "You finished the race in " << counter << " seconds!" << endl;
            return 0;
        }
    }

    return 0;
}
