#ifndef Star_HPP
#define Star_HPP

#include "CelestialBody.hpp"


class Star : public CelestialBody {
    public:

    Star(string name, CelestialBody::Color color, double massInSunMass){

        this->name = name;
        this->color = color;
        this->mass = massInSunMass*MASSOfSun;
    }
};

#endif