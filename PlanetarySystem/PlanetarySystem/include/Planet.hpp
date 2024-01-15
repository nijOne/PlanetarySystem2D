#ifndef Planet_HPP
#define Planet_HPP

#include "Satellite.hpp"
#include "CelestialBody.hpp"



class Planet : public CelestialBody {
    public:

    Planet(string name, CelestialBody* source, CelestialBody::Color color, double semiMajorAxis, double eccentricy, double massInEarthMass, double omega) {//`~~~?

        this->name = name;
        this->color = color;
        this->mass = massInEarthMass * MASSOfEarth;
        this->semiMajorAxis = semiMajorAxis * ASTRONOMICALUnit;
        this->eccentricy = eccentricy;
        this->source = source;
        this->omega = omega;

        calcPeriodWRT(source->mass, this->semiMajorAxis);
    }
};

#endif
