#ifndef PlanetarySystem_HPP
#define PlanetarySystem_HPP

#include "CelestialBody.hpp"
#include "Star.hpp"
#include "Planet.hpp"
#include "Satellite.hpp"

using namespace std;
using namespace cv;

class PlanetarySystem {
    public:

    Mat *imagePTR;
    string name = "";
    CelestialBody* sourceStar = nullptr;
    vector<Planet*> planetsPTR;
    map<string, Planet*> planetsMAP;

    int zoom = 200;

    float dayCount = 0;

    PlanetarySystem (string name) {

        this->name = name;
    }

    void setSource (string name, Scalar color, double mass) {

        this->sourceStar = new Star(name, color, mass);
    }

    void addPlanet (string name, Scalar color, double semiMajorAxis, double eccentricy, double massInEarthMass, double omega ) {
    
        planetsPTR.push_back(new Planet(name, color, semiMajorAxis, eccentricy, massInEarthMass, sourceStar, omega));
        planetsMAP[name] = planetsPTR.back();
    }

    void addSatelliteToPlanet (string satelliteName, string planetName, Scalar color, double semiMajorAxis, double eccentricy, double massInEarthMass, int axisMultiplier, double omega ) {

        planetsMAP[planetName]->addSatellite(satelliteName, color, semiMajorAxis, eccentricy, massInEarthMass, axisMultiplier, omega);
    }

    void setImagePointer(Mat* image) {

        imagePTR = image;
    }

    Point windowCoords( double positionX, double positionY) {
    
        return Point((imagePTR->cols/2 + (int)zoom*positionX), ( imagePTR->rows/2) + (int)zoom*positionY);    
    }

    void placeBodiesOnImage() {
        
        circle(*imagePTR, windowCoords(sourceStar->posX, sourceStar->posY), 30, sourceStar->color, -1);

        for (vector<Planet*>::iterator itP = planetsPTR.begin(); itP != planetsPTR.end(); itP++) {

            (*itP)->calcDistanceAndPosition(dayCount);
            circle(*imagePTR, windowCoords( (*itP)->posX , (*itP)->posY), 15, (*itP)->color, -1);   

            if( !(*itP)->satellitesPTR.empty()) {
                for( vector<Satellite*>::iterator itS = (*itP)->satellitesPTR.begin(); itS != (*itP)->satellitesPTR.end(); itS++) {

                    (*itS)->calcDistanceAndPosition(dayCount); 
                    circle(*imagePTR, windowCoords( (*itS)->posX , (*itS)->posY), 5, (*itS)->color, -1);   
                }
            }
        }
    } 

    void daysPerFrame(float n) {

        dayCount += n;
    }

    void zoomIn() {

        zoom += 10;  
    }

    void zoomOut() {

        if(zoom > 10) { zoom -= 10; }
        else { cout << "Unable to zoom out." << endl; }
    }
};
#endif