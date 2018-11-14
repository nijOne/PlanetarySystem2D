#include "include/PlanetarySystem.hpp"
#include <sstream>

// Planetary system simulation //  g++ main.cpp -o output `pkg-config --cflags --libs opencv`   
/* todo                                                  // ideas & questions

    zoom confines ?
    posZ !!
	refractoring                                         
	destructors                                          ?background noise, with random generated color from a certain Temperature range
    OpenCV style buttons and trackbars ?
	... (soon to be discovered)                          stars colors based by the Wien's displacement law
	learn Unreal Engine            ?                     
	and use it to simulate effects ?                     
*/

using namespace std;
using namespace cv;

const int FRAME_HEIGHT = 800;
const int FRAME_WIDTH = 800;

Scalar sunColor(51,204,255);
Scalar mercuryColor(169,169,169);
Scalar moonColor(150,150,150);
Scalar venusColor(153,255,255);
Scalar earthColor(255,153,51);
Scalar marsColor(14,68,193);
Scalar jupiterColor(0,166,253);
Scalar saturnColor(170,232,238);
Scalar uranusColor(230,216,176);
Scalar neptuneColor(250,206,135);

int main() {

    int hoursPerFrame;
    int FPS;

    stringstream ss;

    cout << "Welcome to a simple 2D Solar System simulation." << endl;
    cout << "Once the similuation starts: " << endl << "Press ESC to quit, or SPACE to pause at current frame." << endl;
    cout << "Press I to zoom In or O to zoom Out." << endl;
    cout << "Press U to speed Up or D to slow Down time. It's also possible to change the direction of time. " << endl;

    cout << "To begin, please specify the number of hours per frame: " << endl;
    cin >> hoursPerFrame;
    cout << "And the FPS: " << endl;
    cin >> FPS;

    Mat image(FRAME_HEIGHT, FRAME_WIDTH, CV_8UC3, Scalar(0,0,0));

    Point textPositon( 50, 50);
    Scalar fontColor(255,255,255);
    int fontSize = 1;
    int fontThickness = 2;

    namedWindow("System",CV_WINDOW_AUTOSIZE);

    PlanetarySystem solarSystem("Part of Solar System");

    double AU = CelestialBody::ASTRONOMICALUnit;

    solarSystem.setSource("Sun", sunColor, 1.0);
    solarSystem.setImagePointer(&image);

    solarSystem.addPlanet("Mercury", mercuryColor, 0.38709, 0.20563, 0.05528, 48.33);
    solarSystem.addPlanet("Venus", venusColor, 0.72333, 0.00677, 0.81500, 76.68);
    solarSystem.addPlanet("Earth", earthColor, 1.0, 0.01671, 1.0, 0);
    solarSystem.addPlanet("Mars", marsColor, 1.52366, 0.09341, 0.10745, 49.58);
    solarSystem.addPlanet("Jupiter", jupiterColor, 5.20366, 0.04839, 317.83, 100.56);
    solarSystem.addPlanet("Saturn", saturnColor, 9.53707, 0.05415, 95.159, 113.72);
    solarSystem.addPlanet("Uranus", uranusColor, 19.19126, 0.04717, 14.536, 74.23);
    solarSystem.addPlanet("Neptune", neptuneColor, 30.06896, 0.00859, 17.147, 131.72);

    solarSystem.addSatelliteToPlanet("Moon", "Earth", moonColor, 0.00257, 0.0, 0.0123, 50, 0);
    solarSystem.addSatelliteToPlanet("Phobos", "Mars", moonColor, 9376e3/AU, 0.0151, 1.78477e-9, 500, 20);
    solarSystem.addSatelliteToPlanet("Deimos", "Mars", moonColor, 23463.2e3/AU, 0.00033, 0.247179e-9, 500, 89);
    
    while(true) {

        ss << "FramesPerSecond: " << FPS << " " << "HoursPerFrame: " << hoursPerFrame;

        image = Mat::zeros(image.size(), image.type());
        putText(image, ss.str(), textPositon, FONT_HERSHEY_SIMPLEX, fontSize, fontColor, fontThickness);
        
        solarSystem.placeBodiesOnImage();

        imshow("System", image);

        char c = (char)waitKey(1000/FPS);

        if(c == 27) break;                                          // ESC
        else if(c == 32) waitKey();                                 // SPACE
        else if(c == 111 || c == 79) solarSystem.zoomOut();         // O
        else if(c == 105 || c == 73) solarSystem.zoomIn();          // I
        else if(c == 68 || c == 100) hoursPerFrame -= 1;            // D   
        else if(c == 85 || c == 117) hoursPerFrame += 1;            // U

        solarSystem.daysPerFrame((float)hoursPerFrame / 24);

        ss.str("");
    }

    destroyAllWindows();
    image.release();
    
    return 0;
}
