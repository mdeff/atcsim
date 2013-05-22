/* 
 * File:   Constants.h
 * Author: michael
 *
 * Created on 13. avril 2013, 15:05
 */

#ifndef CONSTANTS_H
#define	CONSTANTS_H


#include <cmath>    // For std::atan().
#include <string>


// Standard and bold fonts.
#define BOLDFONT "/usr/share/fonts/truetype/freefont/FreeSansBold.ttf"
//const std::string BOLDFONT = "/usr/share/fonts/truetype/freefont/FreeSansBold.ttf";
//const std::string STDFONT("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
const std::string STDFONT("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");

// Define the window size. Background image resolution is 800*551.
//const unsigned int WINDOWXSIZE(1000);
//const unsigned int WINDOWYSIZE(551);

// Pi is needed to convert from degrees to gradiant. We could also have used
// M_PI (defined in math.h) but it's not standard C++, althought POSIX.
const float PI = std::atan(1.0f) * 4.0f;

// Convert entity speed from km/h (around 800) to pixel/s (divided by SPEEDCONVERT).
const float SPEEDCONVERT(100.0f);

// Airplane cape can change by this angle (in degree) per second.
const float DELTAANGLE(0.03f);

// Define the number of ticks used to predict future collisions.
const unsigned int NTICKSCOL(400);

// Define the minimum distance (in pixels) between two airplanes
// before detecting a collision.
const unsigned int DMINCOL(20);

// Define the minimum vertical distance (altitude) between two airplanes
// before detecting a collision.
const unsigned int DMINVERTCOL(200);

#endif	/* CONSTANTS_H */

