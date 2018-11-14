#ifndef Satellite_HPP
#define Satellite_HPP

#include "CelestialBody.hpp"


class Satellite : public CelestialBody {
    public:

    CelestialBody *source = nullptr;

    Satellite(string name, Scalar color, double semiMajorAxis, double eccentricy, double massInEarthMass, CelestialBody* source, int axisMultiplier, double omega) {//`~~~?

        this->name = name;
        this->color = color;
        this->mass = massInEarthMass * CelestialBody::MASSOfEarth;
        this->semiMajorAxis = semiMajorAxis * ASTRONOMICALUnit;
        this->eccentricy = eccentricy;
        this->source = source;
        this->omega = omega;

        calcPeriod();

        this->semiMajorAxis *= axisMultiplier;
    }   

     void calcDistanceAndPosition(float dayCount) {

        double theta = dayCount * calcThetaFromTimeGap();
        distanceFromSource = semiMajorAxis * (1 - pow(eccentricy,2)) / ( 1 + eccentricy * cos(theta*M_PI/180));
        posX = source->posX + distanceFromSource * cos((omega + theta)*M_PI/180) / ASTRONOMICALUnit;
        posY = source->posY + distanceFromSource * sin((omega + theta)*M_PI/180) / ASTRONOMICALUnit;
    }

    void calcPeriod() {
 
        ORBITPeriodCONST =  4.0*M_PI*M_PI/(GRAVConst * source->mass );
        periodT =  sqrt(pow(semiMajorAxis,3)*ORBITPeriodCONST);
    }

    double calcThetaFromTimeGap() {

        return dt * 360 / periodT;
    }
};

#endif