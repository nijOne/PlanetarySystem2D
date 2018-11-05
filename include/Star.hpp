#ifndef Star_HPP
#define Star_HPP

#include "CelestialBody.hpp"


class Star : public CelestialBody {
    public:

    Star(string name, double n){

        this->name = name;
        this->mass = n*MASSOfSun;
        this->posX = 0;
        this->posY = 0;
    }

};

#endif