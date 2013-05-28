/* 
 * File:   Types.h
 * Author: michael
 *
 * Created on 21. mai 2013, 11:07
 */

#ifndef TYPES_H
#define	TYPES_H


#include <string>


// Point structure represents entity position on the XY plane.
struct Point {
  float x, y;
  Point() : x(), y() {}
  Point(float xInit, float yInit) : x(xInit), y(yInit) {}
  Point(int xInit, int yInit) : x(float(xInit)), y(float(yInit)) {}
};


// Airplane status (real and simulated collisions, out status).
struct AirplaneStatus {
  bool outRight;
  bool outWrong;
  bool airplaneSimCollision;
  bool forbiddenZoneSimCollision;
  bool airwaySimCollision;
  bool cloudSimCollision;
  bool airplaneRealCollision;
  bool forbiddenZoneRealCollision;
  bool airwayRealCollision;
  bool cloudRealCollision;
};


// Is used to inform a method to use the real or simulated entity position.
enum PosType {realPosition, simPosition};


// Cardinal points from which airplanes enter and quit simulation.
enum CardinalPoints {N, S, E, W};

struct CardinalPoint {
  
  enum CardinalPoints cardinalPoint;
  
  CardinalPoint(enum CardinalPoints point) : cardinalPoint(point) {}
  
  Point getPosition() const {
    Point ret;
    switch(cardinalPoint) {
      default:
      case N: ret = Point(359,      0+15); break;
      case S: ret = Point(382,    551-15); break;
      case E: ret = Point(800-15, 470);    break;
      case W: ret = Point(  0+15, 383);    break;
    }
    return ret;
  }
  
  std::string toString() const {
    std::string ret;
    switch(cardinalPoint) {
      default:
      case N: ret = "North"; break;
      case S: ret = "Sud";   break;
      case E: ret = "East";  break;
      case W: ret = "West";  break;
    }
    return ret;
  }
  
};


#endif	/* TYPES_H */

