#ifndef CelestialBody_HPP
#define CelestialBody_HPP

#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>
#include <map>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class CelestialBody{
    public:

    string name;
    Scalar color;

    double posX = 0, posY = 0;                                  // [m]
    double mass = 0;                                            // [kg]

    double distanceFromSource = 0;                              // [m]
    double semiMajorAxis = 0;                                   // [m]
    double eccentricy = 0;                                      // 

    double dt = 86400;	                                        // [s] // jeden dzien w sekundach
    double omega = 0;                                           // [stopnie]

    constexpr static double MASSOfEarth = 5.97219e24;           // [kg]
    constexpr static double GRAVConst = 6.67408e-11;            // [m^3/(kg*s^2)];
    constexpr static double MASSOfSun = 1.98855e30;             // [kg]
    constexpr static double ASTRONOMICALUnit = 1.49598e11;      // [m]

    double ORBITPeriodCONST =  0;                               //

    double periodT = 0;                                         //
};

#endif