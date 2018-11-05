#ifndef PlanetarySystem_HPP
#define PlanetarySystem_HPP

#include "CelestialBody.hpp"
#include "Star.hpp"
#include "Planet.hpp"
#include "Satellite.hpp"

#include <vector>
#include <map>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class PlanetarySystem {
    public:

    Mat *imagePTR;
    string name = "";
    CelestialBody* sourceStar = nullptr;
    vector<Planet*> planetsPTR;
    map<string, Planet*> planetsMAP;

    int dayCount = 0;

    PlanetarySystem (string name) {

        this->name = name;
    }

    void setSource (string name, double mass) {

        this->sourceStar = new Star(name, mass);
    }

    void addPlanet (string name, double a, double e, double m, double omega ) {
    
        this->planetsPTR.push_back(new Planet(name, a, e, m, sourceStar, omega));
        this->planetsMAP[name] = planetsPTR.back();
    }

    void addSatelliteToPlanet (string satelliteName, string planetName, double a, double e, double m, double omega ) {

        this->planetsMAP[planetName]->addSatellite(satelliteName, a, e, m, omega);
    }

    void setImagePointer(Mat* image){

        this->imagePTR = image;
    }

    Point windowCoords( double positionX, double positionY){
    
        return Point((imagePTR->cols/2 + (int)200*positionX), ( (int)200*positionY + imagePTR->rows/2));    
    }

    void placeBodiesOnImage() {
        
        circle(*imagePTR, windowCoords( sourceStar->posX, sourceStar->posY), 30, Scalar(255,255,255), -1);

        vector<Planet*>::iterator itP;
        vector<Satellite*>::iterator itS;

        for (itP = planetsPTR.begin(); itP != planetsPTR.end(); itP++){

            (*itP)->calcDistanceAndPosition(dayCount);
            circle(*imagePTR, windowCoords( (*itP)->posX , (*itP)->posY), 15, Scalar(255,255,255), -1);   

            if( !(*itP)->satellitesPTR.empty()) {
                for( itS = (*itP)->satellitesPTR.begin(); itS != (*itP)->satellitesPTR.end(); itS++) {

                    (*itS)->calcDistanceAndPosition(dayCount); 
                    circle(*imagePTR, windowCoords( (*itS)->posX , (*itS)->posY), 5, Scalar(255,0,0), -1);   
                }
            }
        }
    } 

    void daysPerFrame(int n) {

        dayCount += n;
    }
};
#endif