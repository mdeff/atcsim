/* 
 * File:   Points.h
 * Author: michael
 *
 * Created on 23. mai 2013, 13:13
 */

#ifndef POINTS_H
#define	POINTS_Henum CardinalPoints


// Forward declarations (no header includes) (namespace pollution, build time).
class Surface;


namespace Score {
  
  void addPoints(float points);
  float getPoints();
  void render(Surface& displaySurf);
  
}


#endif	/* POINTS_H */

