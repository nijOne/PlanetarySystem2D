#ifndef Satellite_HPP
#define Satellite_HPP

#include "CelestialBody.hpp"


class Satellite : public CelestialBody {
    public:

    Satellite(string name, CelestialBody* source, CelestialBody::Color color, double semiMajorAxis, double eccentricy, double massInEarthMass, double omega) {//`~~~?

        this->name = name;
        this->color = color;
        this->mass = massInEarthMass * MASSOfEarth;
        this->semiMajorAxis = semiMajorAxis * ASTRONOMICALUnit;
        this->eccentricy = eccentricy;
        this->source = source;
        this->omega = omega;

        calcPeriodWRT(source->mass, semiMajorAxis);
    }   
};

#endif