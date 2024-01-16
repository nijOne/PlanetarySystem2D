#ifndef PlanetarySystem_HPP
#define PlanetarySystem_HPP

#include "CelestialBody.hpp"
#include "Star.hpp"
#include "Planet.hpp"
#include "Satellite.hpp"
#include "unordered_map"
#include "memory"
#include "functional"
#include "algorithm"

using namespace std;

class PlanetarySystem {
    public:

    //Mat *imagePTR;
    string name = "";

    unordered_map<string, shared_ptr<Star>> starsMAP;
    unordered_map<string, shared_ptr<Planet>> planetsMAP;
    unordered_map<string, shared_ptr<Satellite>> satelitesMAP;
   //CelestialBody Coordinates center{ 0,0 };

    float dayCount = 0;

    PlanetarySystem (string name) {

        this->name = name;
    }

    void addStar(string name, CelestialBody::Color color, double mass) {

        starsMAP[name] = make_shared<Star>(name, color, mass);
    }

    void addPlanet(string planetName, string sourceName, CelestialBody::Color color, double semiMajorAxis, double eccentricy, double massInEarthMass, double omega ) {
    
        planetsMAP[planetName] = make_shared<Planet>(planetName, starsMAP[sourceName].get(), color, semiMajorAxis, eccentricy, massInEarthMass, omega);
    }

    void addSatellite(string satelliteName, string planetName, CelestialBody::Color color, double semiMajorAxis, double eccentricy, double massInEarthMass, double omega ) {

        satelitesMAP[satelliteName] = make_shared<Satellite>(satelliteName, planetsMAP[planetName].get(), color, semiMajorAxis, eccentricy, massInEarthMass, omega);
    }

    void adjustCoordinates() {

        if (!starsMAP.empty())
            for (auto& star : starsMAP) {
                if (!planetsMAP.empty())
                    for (auto& planet : planetsMAP)
                        planet.second->calcDistanceAndPosition(dayCount, star.second.get());
                if (!satelitesMAP.empty())
                    for (auto& satelite : satelitesMAP)
                        satelite.second->calcDistanceAndPosition(dayCount, satelite.second->source);
            }
    }

    //template<typename Object> 
    string printAllPlanets()    {
        stringstream ss;
        for (auto& planet : planetsMAP)
            ss << trackPlanet(planet.first) << "\n";

        return ss.str();
    }
    // fixme
    string trackPlanet(const string& planetName)
    {
        stringstream ss;
        planetsMAP[planetName]->printBasic(ss);
        return ss.str();
    }

    void daysPerFrame(int n) {

        dayCount += n;
    }

    //void zoomOut() {

    //    if(zoom > 10) { zoom -= 10; }
    //    else { cout << "Unable to zoom out." << endl; }
    //}
};
#endif