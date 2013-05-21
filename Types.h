/* 
 * File:   Types.h
 * Author: michael
 *
 * Created on 21. mai 2013, 11:07
 */

#ifndef TYPES_H
#define	TYPES_H


// Point structure represents entity position on the XY plane.
struct Point {
  float x, y;
  Point(float xInit, float yInit) : x(xInit), y(yInit) {}
};


struct EntityTypes {
  bool airplane;
  bool cloud;
  bool forbiddenZone;
//  EntityTypes() : airplane(false), cloud(false), forbiddenZone(false) {}
};


enum PosType {realPosition, simPosition};


#endif	/* TYPES_H */
