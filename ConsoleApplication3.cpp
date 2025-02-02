#include <iostream>
#include <cmath>
#include <iomanip> 
#include <fstream>
#include <string>

using namespace std;

const double gravity = 9.81;
const double M_PI = 3.14;

// تابعی برای محاسبه فرکانس زاویه‌ای برای زوایای کوچک و بزرگ
double getNonlinearFrequency(double startAngle, double pendulumLength)
{
    return sqrt(gravity / pendulumLength) * (1 - pow(startAngle, 2) / 16.0); // فرکانس زاویه‌ای غیرخطی
}

// تابعی برای محاسبه زاویه برای زوایای کوچکتر از ۱۵ درجه
double getSmallAngle(double startAngle, double pendulumLength, double currentTime)
{
    double smallAngleFrequency = sqrt(gravity / pendulumLength); // فرکانس زاویه‌ای برای زوایای کوچک
    return startAngle * cos(smallAngleFrequency * currentTime);
}

// تابعی برای محاسبه زاویه برای زوایای بزرگ با استفاده از فرکانس غیرخطی
double getLargeAngle(double startAngle, double pendulumLength, double currentTime)
{
    double nonlinearFrequency = getNonlinearFrequency(startAngle, pendulumLength);
    return startAngle * cos(nonlinearFrequency * currentTime);
}

// تابعی برای محاسبه انرژی پتانسیل
double getPotentialEnergy(double pendulumMass, double pendulumLength, double currentAngle)
{
    return pendulumMass * gravity * pendulumLength * (1 - cos(currentAngle));
}

// تابعی برای محاسبه انرژی جنبشی
double getKineticEnergy(double pendulumMass, double pendulumLength, double angularVelocity)
{
    return 0.5 * pendulumMass * pow(pendulumLength * angularVelocity, 2);
}

// تابع اصلی
int main()
{
    double mass, length, angle, time;
    int caseNumber;
    string studentNumber;

    // دریافت شماره دانشجویی
    cout << "Student number: ";
    cin >> studentNumber;

    // بررسی دومین رقم سمت راست شماره دانشجویی
    int secondLastDigit = studentNumber[studentNumber.length() - 2] - '0';

    // باز کردن فایل طول‌ها
    ifstream lengthFile("length.txt");
    if (!lengthFile)
    {
        cerr << "Unable to open length.txt file!" << endl;
        return 1;
    }

    string header;
    getline(lengthFile, header); // خواندن هدر فایل

    cout << "Enter case number (1-40): ";
    cin >> caseNumber;

    // بررسی شرطی که برای کیس نامبر گذاشتیم
    if (caseNumber % 10 == secondLastDigit)
    {
        bool caseFound = false;
        int caseFromFile;

        while (lengthFile >> caseFromFile >> length)
        {
            if (caseFromFile == caseNumber)
            {
                caseFound = true;
                break;
            }
        }

        if (caseFound)
        {
            cout << "Mass of the pendulum (in grams): ";
            cin >> mass;
            cout << "Initial angle (in degrees): ";
            cin >> angle;
            cout << "Time which want to calculate the state of the pendulum (in seconds): ";
            cin >> time;

            // تبدیل زاویه به رادیان
            angle = angle * M_PI / 180.0;
            length *= .01;

            double finalAngle;
            if (angle < 0.26)
            { // زمانی که زاویه کوچکتر از ۱۵ درجه باشد
                finalAngle = getSmallAngle(angle, length, time);
            }
            else { // زاویه بزرگتر از ۱۵ درجه
                finalAngle = getLargeAngle(angle, length, time);
            }

            // بررسی فرکانس زاویه‌ای غیرخطی
            double nonlinearFrequency = getNonlinearFrequency(angle, length);

            // محاسبه انرژی
            double potentialEnergy = getPotentialEnergy(mass / 1000.0, length, finalAngle); // انرژی پتانسیل
            double kineticEnergy = getKineticEnergy(mass / 1000.0, length, nonlinearFrequency); // انرژی جنبشی


            cout << fixed << setprecision(4);
            cout << "Final Angle: " << finalAngle * 180.0 / M_PI << " degrees" << endl;
            cout << "Potential Energy: " << potentialEnergy << " J" << endl;
            cout << "Kinetic Energy: " << kineticEnergy << " J" << endl;
            cout << "Angular Velocity: " << nonlinearFrequency << " rad/s" << endl;

            // ذخیره نتایج در فایل
            ofstream outputFile("pendulum_simulation_results.txt", ios::app);

            if (outputFile.is_open())
            {
                if (outputFile.tellp() == 0)
                {
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
                    << setw(25) << finalAngle * 180.0 / M_PI
                    << setw(20) << potentialEnergy
                    << setw(20) << kineticEnergy
                    << setw(20) << nonlinearFrequency
                    << endl;

                outputFile.close();
            }

            cout << "Now you can see the results in pendulum_simulation_results.txt" << endl;
        }
        else
        {
            cout << "The case number could not be found in the file." << endl;
        }
    }
    else
    {
        cout << "The case number does not meet the condition which we say for processing." << endl;
    }

    lengthFile.close();
    return 0;
}