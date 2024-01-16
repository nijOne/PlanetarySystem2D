#ifndef CelestialBody_HPP
#define CelestialBody_HPP

#include <iostream>
#include <map>
#include <math.h>
#include <sstream>
#include <vector>
#include <optional>
#include <iomanip> 
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

constexpr static double MASSOfEarth = 5.97219e24;           // [kg]
constexpr static double GRAVConst = 6.67408e-11;            // [m^3/(kg*s^2)];
constexpr static double MASSOfSun = 1.98855e30;             // [kg]
constexpr static double ASTRONOMICALUnit = 1.49598e11;      // [m]
constexpr static double M_PI = 3.1415;


struct CelestialBody{

    struct Color
    {
        int red;
        int green;
        int blue;

        Color(int red, int green, int blue)
            : red(red), green(green), blue(blue) {};
    };
    struct Coordinates
    {
        double x;
        double y;

        friend ostream& operator<<(ostream& output, const Coordinates& coords)
        {
            //if (coords.x >= 0) output << " ";
            output << setprecision(4) << scientific << coords.x << ", ";
            if (coords.y >= 0) output << " ";
            output << setprecision(4) << scientific << setw(10) << coords.y;

            return output;
        }
    };
    string name;
    CelestialBody::Color color{ 0, 0, 0 };
    CelestialBody::Coordinates coords{ 0, 0 };

    double mass = 0;                                            // [kg]
    double distanceFromSource = 0;                              // [m]
    double semiMajorAxis = 0;                                   // [m]
    double eccentricy = 0;                                      // 

    double dt = 86400;	                                        // [s] // jeden dzien w sekundach
    double omega = 0;                                           // [stopnie]
    double orbitPeriod = 0;                               //
    double periodT = 0;


    //void calcDistanceAndPosition(float dayCount, CelestialBody& source)
    //{

    //}
    template<typename Body>
    void calcDistanceAndPosition(double dayCount, Body* majorSource) {
        
        double theta = dayCount * calcThetaFromTimeGap(calcPeriodWRT(majorSource->mass, semiMajorAxis));
        distanceFromSource = semiMajorAxis * (1 - pow(eccentricy, 2)) / (1 + eccentricy * cos(theta * M_PI / 180));
        //cout << __func__ << "distanceFromSource" << distanceFromSource << endl;
        this->coords.x = /*majorSource->coords.x +*/ distanceFromSource * cos((omega + theta) * M_PI / 180) / ASTRONOMICALUnit;
        this->coords.y =/* majorSource->coords.y +*/ distanceFromSource * sin((omega + theta) * M_PI / 180) / ASTRONOMICALUnit;
        //printBasic();
        
    }

    double calcPeriodWRT(double mass, double semiMajorAxis) {

        orbitPeriod = 4.0 * M_PI * M_PI / (GRAVConst * mass);
        periodT = sqrt(pow(semiMajorAxis, 3) * orbitPeriod);
        return periodT;
    }

    double calcThetaFromTimeGap(double periodT) {

        return dt * 360 / periodT;

    }

    void printBasic(ostream& output)
    {
        output << fixed << setw(12) << this->name << "[" << setw(12) << this->coords << "]";
    }
    CelestialBody* source = nullptr;
//protected:
   
    virtual ~CelestialBody() = default;
};

#endif