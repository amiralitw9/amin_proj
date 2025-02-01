#include <iostream>
#include <cmath>
#include <iomanip> // For output formatting
#include <fstream>
#include <string>

using namespace std;

const double g = 9.81; // Gravitational acceleration (m/s^2)

// Function to compute angular frequency for small and large angles
double calculateNonlinearFrequency(double initialAngle, double length) {
    return sqrt(g / length) * (1 - pow(initialAngle, 2) / 16.0); // Nonlinear angular frequency
}

// Function to calculate angle for small angles (\( \theta < 15^\circ \))
double calculateSmallAngle(double initialAngle, double length, double time) {
    double omega = sqrt(g / length); // Small-angle frequency
    return initialAngle * cos(omega * time);
}

// Function to calculate angle for large angles (\( \theta \geq 15^\circ \)) using the nonlinear frequency
double calculateLargeAngle(double initialAngle, double length, double time) {
    double omega_nonlinear = calculateNonlinearFrequency(initialAngle, length);
    return initialAngle * cos(omega_nonlinear * time);
}

// Function to calculate potential energy
double calculatePotentialEnergy(double mass, double length, double angle) {
    return mass * g * length * (1 - cos(angle));
}

// Function to calculate kinetic energy
double calculateKineticEnergy(double mass, double length, double omega) {
    return 0.5 * mass * pow(length * omega, 2);
}

// Main function
int main() {
    double mass, length, angle, time;
    int caseNumber;
    string studentNumber;

    // Get student number
    cout << "Enter your student number: ";
    cin >> studentNumber;

    // Compute the second-to-last digit of the student number
    int secondLastDigit = studentNumber[studentNumber.length() - 2] - '0';

    // Open the length file
    ifstream lengthFile("length.txt");
    if (!lengthFile) {
        cerr << "Unable to open length.txt file!" << endl;
        return 1;
    }

    string header;
    getline(lengthFile, header); // Read the header of the file

    cout << "Enter case number (1-40): ";
    cin >> caseNumber;

    // Check if the case number satisfies the condition
    if (caseNumber % 10 == secondLastDigit) {
        bool caseFound = false;
        int caseFromFile;

        while (lengthFile >> caseFromFile >> length) {
            if (caseFromFile == caseNumber) {
                caseFound = true;
                break;
            }
        }

        if (caseFound) {
            cout << "Enter the mass of the pendulum (in grams): ";
            cin >> mass;
            cout << "Enter the initial angle (in degrees): ";
            cin >> angle;
            cout << "Enter the time at which to calculate the state of the pendulum (in seconds): ";
            cin >> time;

            // Convert angle to radians
            angle = angle * M_PI / 180.0;
            length *=.01 ;
            // Choose the calculation based on the angle size
            double newAngle;
            if (angle < 0.26) { // Small-angle approximation
                newAngle = calculateSmallAngle(angle, length, time);
            } else { // Large-angle using nonlinear frequency
                newAngle = calculateLargeAngle(angle, length, time);
            }

            // Compute the nonlinear angular frequency
            double omega_nonlinear = calculateNonlinearFrequency(angle, length);

            // Calculate energies
            double potentialEnergy = calculatePotentialEnergy(mass / 1000.0, length, newAngle); // Potential energy
            double kineticEnergy = calculateKineticEnergy(mass / 1000.0, length, omega_nonlinear); // Kinetic energy

            // Display results
            cout << fixed << setprecision(4);
            cout << "Final Angle: " << newAngle * 180.0 / M_PI << " degrees" << endl;
            cout << "Potential Energy: " << potentialEnergy << " J" << endl;
            cout << "Kinetic Energy: " << kineticEnergy << " J" << endl;
            cout << "Angular Velocity: " << omega_nonlinear << " rad/s" << endl;

            // Save results to file
            ofstream outputFile("pendulum_simulation_results.txt", ios::app);
            if (outputFile.is_open()) {
                if (outputFile.tellp() == 0) { // Add file header on first write
                    outputFile << left << setw(15) << "Case Number"
                               << setw(20) << "Length (m)"
                               << setw(25) << "Initial Angle (degrees)"
                               << setw(15) << "Time (s)"
                               << setw(25) << "Final Angle (degrees)"
                               << setw(20) << "Potential Energy (J)"
                               << setw(20) << "Kinetic Energy (J)"
                               << setw(20) << "Angular Velocity (rad/s)"
                               << endl;
                }

                outputFile << left << setw(15) << caseNumber
                           << setw(20) << length
                           << setw(25) << angle * 180.0 / M_PI
                           << setw(15) << time
                           << setw(25) << newAngle * 180.0 / M_PI
                           << setw(20) << potentialEnergy
                           << setw(20) << kineticEnergy
                           << setw(20) << omega_nonlinear
                           << endl;

                outputFile.close();
            }

            cout << "Results have been written to pendulum_simulation_results.txt" << endl;
        } else {
            cout << "The case number was not found in the file." << endl;
        }
    } else {
        cout << "The case number does not meet the condition for processing." << endl;
    }

    lengthFile.close();
    return 0;
}
