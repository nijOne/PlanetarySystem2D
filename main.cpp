#include "include/PlanetarySystem.hpp"


// Planetary system simulation //  g++ main.cpp -o output `pkg-config --cflags --libs opencv`   
/* todo                                                  // ideas

	refractoring                                        
	                                                    ?background noise, with random generated color from a certain Temperature range
    	posZ !!
	... (soon to be discovered)                          stars colors based by the Wien's displacement law
	learn Unreal Engine            ?                     
	and use it to simulate effects ?
*/

using namespace std;
using namespace cv;

const int FRAME_HEIGHT = 1080;
const int FRAME_WIDTH = 1080;


  /*Scalar sunColor(51,204,255);
    Scalar mercuryColor(169,169,169);
    Scalar moonColor(150,150,150);
    Scalar venusColor(153,255,255);
    Scalar earthColor(255,153,51);
    Scalar marsColor(0,128,255);*/


int main() {

    int dayCount = 0;

    Mat image(FRAME_HEIGHT, FRAME_WIDTH, CV_8UC3, Scalar(0,0,0));

    namedWindow("System",CV_WINDOW_AUTOSIZE);

    PlanetarySystem solarSystem("Part of Solar System");

    double AU = CelestialBody::ASTRONOMICALUnit;

    solarSystem.setSource("Sun", 1.0);
    solarSystem.setImagePointer(&image);

    solarSystem.addPlanet("Mercury", 0.38709, 0.20563, 0.05528, 48.33);
    solarSystem.addPlanet("Venus", 0.72333, 0.00677, 0.81500, 76.68);
    solarSystem.addPlanet("Earth", 1.0, 0.01671, 1.0, 0);
    solarSystem.addPlanet("Mars", 1.52366, 0.09341, 0.10745, 49.58);

    solarSystem.addSatelliteToPlanet("Moon", "Earth", 0.00257, 0.0, 0.0123, 0);
    solarSystem.addSatelliteToPlanet("Phobos", "Mars", 9376e3/AU, 0.0151, 1.78477e-9, 20);
    solarSystem.addSatelliteToPlanet("Deimos", "Mars", 23463.2e3/AU, 0.00033, 0.247179e-9, 89);
    
    while(true){

        solarSystem.placeBodiesOnImage();

        imshow("System", image);

        char c = (char)waitKey(10);
        if(c == 27) break; 

        solarSystem.daysPerFrame(1);
    }

    destroyAllWindows();
    image.release();
    
    return 0;
}
