#ifndef Planet_HPP
#define Planet_HPP

#include "Satellite.hpp"
#include "CelestialBody.hpp"



class Planet : public CelestialBody {
    public:

    CelestialBody *source = nullptr;

    vector<Satellite*> satellitesPTR;
    map<string, Satellite*> satelliteMAP;


    Planet(string name, Scalar color, double semiMajorAxis, double eccentricy, double massInEarthMass, CelestialBody* source, double omega) {//`~~~?

        this->name = name;
        this->color = color;
        this->mass = massInEarthMass * CelestialBody::MASSOfEarth;
        this->semiMajorAxis = semiMajorAxis * ASTRONOMICALUnit;
        this->eccentricy = eccentricy;
        this->source = source;
        this->omega = omega;

        calcPeriod();
    }

    void addSatellite(string SatelliteName, Scalar color, double semiMajorAxis, double eccentricy, double massInEarthMass, int axisMultiplier,  double omega) {
        
        satellitesPTR.push_back(new Satellite(SatelliteName, color, semiMajorAxis, eccentricy, massInEarthMass, this, axisMultiplier, omega));
        satelliteMAP[SatelliteName] = satellitesPTR.back();
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
