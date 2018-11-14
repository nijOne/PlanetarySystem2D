#ifndef Star_HPP
#define Star_HPP

#include "CelestialBody.hpp"


class Star : public CelestialBody {
    public:

    Star(string name, Scalar color, double massInSunMass){

        this->name = name;
        this->color = color;
        this->mass = massInSunMass*MASSOfSun;
        this->posX = 0;
        this->posY = 0;
    }
};

#endif