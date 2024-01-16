

#include "PlanetarySystem.h"


// Planetary system simulation //  g++ main.cpp -o output `pkg-config --cflags --libs opencv`   
/* todo                                                  // ideas & questions

    zoom confines ?
    posZ !!
    refractoring
    destructors                                          ?background noise, with random generated color from a certain Temperature range
    OpenCV style buttons and trackbars ?
    ... (soon to be discovered)                          stars colors based by the Wien's displacement law
    learn OpenGL
    and use it to simulate effects
*/

using namespace std;

const int FRAME_HEIGHT = 800;
const int FRAME_WIDTH = 800;


CelestialBody::Color sunColor({ 51,204,255});
CelestialBody::Color mercuryColor({ 169,169,169 });
CelestialBody::Color moonColor({ 150,150,150 });
CelestialBody::Color venusColor({ 153,255,255 });
CelestialBody::Color earthColor({ 255,153,51 });
CelestialBody::Color marsColor({ 14,68,193 });
CelestialBody::Color jupiterColor({ 0,166,253 });
CelestialBody::Color saturnColor({ 170,232,238 });
CelestialBody::Color uranusColor({ 230,216,176 });
CelestialBody::Color neptuneColor({ 250,206,135 });

void run()
{



    stringstream ss;

    // cout << "Welcome to a simple 2D Solar System simulation." << endl;
    // cout << "Once the similuation starts: " << endl << "Press ESC to quit, or SPACE to pause at current frame." << endl;
    // cout << "Press I to zoom In or O to zoom Out." << endl;
    // cout << "Press U to speed Up or D to slow Down time. It's also possible to change the direction of time. " << endl;
    // cout << "To begin, please specify the number of hours per frame: " << endl;
    // cin >> hoursPerFrame;
    // cout << "And the FPS: " << endl;
    // cin >> FPS;

    int fontSize = 1;
    int fontThickness = 2;
    int hoursPerFrame = 24;
    int FPS = 24;
    PlanetarySystem solarSystem("Part of Solar System");
    solarSystem.daysPerFrame(hoursPerFrame / 24);
    const auto& AU = ASTRONOMICALUnit;

    solarSystem.addStar("Sun", sunColor, 1.0);
    solarSystem.addPlanet("Mercury", "Sun", mercuryColor, 0.38709, 0.20563, 0.05528, 48.33);
    solarSystem.addPlanet("Venus", "Sun", venusColor, 0.72333, 0.00677, 0.81500, 76.68);
    solarSystem.addPlanet("Earth", "Sun", earthColor, 1.0, 0.01671, 1.0, 0);
    solarSystem.addPlanet("Mars", "Sun", marsColor, 1.52366, 0.09341, 0.10745, 49.58);
    solarSystem.addPlanet("Jupiter", "Sun", jupiterColor, 5.20366, 0.04839, 317.83, 100.56);
    solarSystem.addPlanet("Saturn", "Sun", saturnColor, 9.53707, 0.05415, 95.159, 113.72);
    solarSystem.addPlanet("Uranus", "Sun", uranusColor, 19.19126, 0.04717, 14.536, 74.23);
    solarSystem.addPlanet("Neptune", "Sun", neptuneColor, 30.06896, 0.00859, 17.147, 131.72);
    solarSystem.addSatellite("Moon", "Earth", moonColor, 0.00257, 0.0, 0.0123, 0);
    solarSystem.addSatellite("Phobos", "Mars", moonColor, 9376e3 / AU, 0.0151, 1.78477e-9, 20); 
    solarSystem.addSatellite("Deimos", "Mars", moonColor, 23463.2e3 / AU, 0.00033, 0.247179e-9, 89);

    while(true) {

        ss << "FramesPerSecond: " << FPS << " " << "HoursPerFrame: " << hoursPerFrame;

        solarSystem.adjustCoordinates();

        //cout << "\r " <<  << "%" << flush;
        //string str = ("\r" + solarSystem.printAllPlanets() + "___%");
        //cout << str;
 
        cout << solarSystem.trackPlanet("Earth") + "\r";
        cout << solarSystem.printAllPlanets() << "\033[2J" << flush ;

        solarSystem.daysPerFrame(FPS);
    }
}

int main(int argc, char** argv) {
    //cout << "HelloWorld!!" << endl;

    run();
    return 0;
}
