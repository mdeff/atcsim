/* 
 * File:   Constants.h
 * Author: michael
 *
 * Created on 13. avril 2013, 15:05
 */

#ifndef CONSTANTS_H
#define	CONSTANTS_H


//#include <string>


namespace ATCsim {  // Project ATCsim namespace.


// namespace Constants {


// Standard and bold fonts.
#define BOLDFONT "/usr/share/fonts/truetype/freefont/FreeSansBold.ttf"
//const std::string BOLDFONT = "/usr/share/fonts/truetype/freefont/FreeSansBold.ttf";
//const std::string STDFONT("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
//const std::string STDFONT("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");
#define STDFONT "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf"

// Define the window size. Background image resolution is 800*551.
//const unsigned int WINDOWXSIZE(1000);
//const unsigned int WINDOWYSIZE(551);

// Convert entity speed from km/h (around 800) to pixel/s (divided by SPEEDCONVERT).
const float SPEEDCONVERT(100.0f);//(20.0f);//

// Airplane cape change speed, in degree per second.
const float DELTAANGLE(5.0f);

// Define the number of ticks used to predict future collisions.
const unsigned int NTICKSCOL(400);

// Define the minimum distance (in pixels) between two airplanes
// before detecting a collision.
const unsigned int DMINCOL(20);

// Define the minimum vertical distance (altitude) between two airplanes
// before detecting a collision.
const unsigned int DMINVERTCOL(200);
  

}  // End of project ATCsim namespace.


#endif	/* CONSTANTS_H */

