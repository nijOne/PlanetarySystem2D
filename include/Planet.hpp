#ifndef Planet_HPP
#define Planet_HPP

#include "Satellite.hpp"
#include "CelestialBody.hpp"
#include "vector"
#include "map"


class Planet : public CelestialBody {
    public:

    CelestialBody *source = nullptr;

    vector<Satellite*> satellitesPTR;
    map<string, Satellite*> satelliteMAP;


    Planet(string name, double a, double e, double m, CelestialBody* source, double omega) {//`~~~?

        this->name = name;
        this->mass = m;
        this->semiMajorAxis = a * ASTRONOMICALUnit;
        this->eccentricy = e;
        this->source = source;
        this->omega = omega;

        calcPeriod();
    }

    void addSatellite(string SatelliteName, double a, double e, double m, double omega) {
        
        satellitesPTR.push_back(new Satellite(SatelliteName, a, e, m, this, omega));satelliteMAP[SatelliteName] = satellitesPTR.back();
    }

    void calcDistanceAndPosition(int dayCount) {

        double theta = dayCount * calcThetaFromTimeGap();
        distanceFromSource = semiMajorAxis * (1 - pow(eccentricy,2)) / ( 1 + eccentricy * cos(theta*M_PI/180));
        posX = source->posX + distanceFromSource * cos((omega + theta)*M_PI/180) / ASTRONOMICALUnit;
        posY = source->posY + distanceFromSource * sin((omega + theta)*M_PI/180) / ASTRONOMICALUnit;
    }

    void calcPeriod() {

        this->ORBITPeriodCONST =  4.0*M_PI*M_PI/(GRAVConst * source->mass );
        this->periodT =  sqrt(pow(semiMajorAxis,3)*ORBITPeriodCONST);
    }

    double calcThetaFromTimeGap() {

        return dt * 360 / periodT;
    }

    std::string returnPosition() {

        std::stringstream ss;
        ss << posX  << " " << posY  << ";";

        return ss.str();
    }
};

#endif
