/* 
 * File:   Parser.cpp
 * Author: michael
 * 
 * Created on 31. mai 2013, 14:44
 */

#include <cctype>     // For isalpha() and isdigit().
#include <exception>
#include <iostream>
#include <stdexcept>

#include "Airplane.h"
#include "Cloud.h"
#include "Entity.h"
#include "ForbiddenZone.h"
#include "Parser.h"



namespace ATCsim {  // Project ATCsim namespace.



Parser::Parser(std::string configFileName)
:
// Open the configuration file for read operations.
configFile_(configFileName, std::ios::in)
{
  // Check if the file is open.
  if (!configFile_.is_open()) {
    throw std::runtime_error("Unable to open configuation file.");
  }
}



void Parser::extract(std::vector< std::unique_ptr<Entity> >& entities) {
  
  try {
    
    if (extractNextTagName() == "System") {
      extractSystem(entities);
    } else {
      throw std::runtime_error("First level should be <System>.");
    }
    
    
    if (extractNextTagName() != "/System") {
      throw std::runtime_error("First level should be <System>.");
    }
    
    
    
    
    //  entities.push_back(std::unique_ptr<Entity> (
//          new ForbiddenZone({260, 360, 360, 260},
//                            {150, 150, 250, 250})));
//  entities.push_back(std::unique_ptr<Entity> (
//          new ForbiddenZone({480, 670, 690, 780, 670, 650},
//                            {150, 130,  20, 120, 130, 330})));
  
    // For the moment only forbidden zones are read in the configuration files.
    // Directly add clouds and airplanes.
    
    entities.push_back(std::unique_ptr<Entity > (
            new Cloud({540, 620, 770, 790, 700, 580},
                      {400, 350, 400, 500, 540, 500}, 124.2f, 200)));

    entities.push_back(std::unique_ptr<Entity > (
            new Airplane(1, "AA293", 8000, 260.4f, 800, Airplane::CardinalPoint(Airplane::N), Airplane::CardinalPoint(Airplane::S))));
    entities.push_back(std::unique_ptr<Entity > (
            new Airplane(2, "LX8829", 9811, 90.3f, 600, Airplane::CardinalPoint(Airplane::S), Airplane::CardinalPoint(Airplane::W))));
    entities.push_back(std::unique_ptr<Entity > (
            new Airplane(3, "DLH22", 7510, 166.8f, 700, Airplane::CardinalPoint(Airplane::E), Airplane::CardinalPoint(Airplane::S))));
    entities.push_back(std::unique_ptr<Entity > (
            new Airplane(4, "BER120", 7440, 20.3f, 400, Airplane::CardinalPoint(Airplane::W), Airplane::CardinalPoint(Airplane::E))));
  
  
  
  
//    tag = parseTag();
//    
//    switch (tag) {
//      
//    case Avion:
//      extraireAvion(/* ici des arguments utiles */);
//      break;
//      
//    default:
//    // traitement d'une balise inconnue
//    }
    
    
  } catch (std::exception& e) {
    throw std::runtime_error("Configuration extraction error: " + std::string(e.what()));
//    std::cerr << "Configuration extraction error: " << e.what() << std::endl;
  }
  
  
 // configFile_.close();
  
}



bool Parser::findTag() {
  
  char c;
  
  do {
    configFile_.get(c);
  } while (c != '<' && std::isspace(c));
  
  if (c == '<') {
    return true;
    
  // Return false if there is still data to be read.
  } else {
    configFile_.seekg(-1, std::ios::cur);
    return false;
  }
  
}



bool Parser::skipComment() {
  
  char c;
  configFile_.get(c);
  
  // If it's a comment tag, skip it.
  if (c == '!') {
    do {
      configFile_.get(c);
    } while (c != '>');
    return true;
  
  // Else decrement get pointer (we have read the tag name first character)
  } else {
    configFile_.seekg(-1, std::ios::cur);
    return false;
  }
  
}



std::string Parser::readString(int(*firstCharCheck)(int), int(*lastCharCheck)(int)) {
  
  std::string string;
  char c;
  
  do {
    configFile_.get(c);
  } while (!firstCharCheck(c));
  
  while (!lastCharCheck(c)) {
    string += c;
    configFile_.get(c);
  }
  
  return string;
  
}



int tagFirsCharCheck(int c) {return c == '/' || std::isalpha(c);}
int tagLastCharCheck(int c) {return c == '>';}

std::string Parser::extractNextTagName() {
    
  // Skip all the comments.
  do {
    // Return an empty string if there is still data to be read.
    if (!findTag())
      return "";
  } while (skipComment());
  
  // Read the tag name.
  return readString(&tagFirsCharCheck, &tagLastCharCheck);
  
}









void Parser::extractSystem(std::vector< std::unique_ptr<Entity> >& entities) {
  
  std::string tagName;
  
  tagName = extractNextTagName();
  if (tagName == "ForbiddenZones") {
    if (extractForbiddenZones(entities) != "/ForbiddenZones") {
      throw std::runtime_error("<ForbiddenZones> must be closed.");
    }
  } else {
      throw std::runtime_error("There must be a <ForbiddenZones> second level.");
  }
  
//  if (tagName == "Clouds") {
//    if (extractForbiddenZones(entities) != "/ForbiddenZones") {
//      throw std::runtime_error("<Clouds> must be closed.");
//    }
//  } else {
//      throw std::runtime_error("There must be a <Clouds> second level.");
//  }
  
}



std::string Parser::extractForbiddenZones(std::vector< std::unique_ptr<Entity> >& entities) {
  
  std::string tagName(extractNextTagName());
  
  while (tagName == "ForbiddenZone") {
    
    std::vector<int16_t> xPoints, yPoints;
    
    if (extractNextTagName() == "xPoints") {
      extractPoints(xPoints);
    } else {
      throw std::runtime_error("ForbiddenZone must contain an xPoints tag.");
    }
    
    if (extractNextTagName() == "yPoints") {
      extractPoints(yPoints);
    } else {
      throw std::runtime_error("ForbiddenZone must contain an yPoints tag.");
    }
    
    if (extractNextTagName() != "/ForbiddenZone") {
      throw std::runtime_error("<ForbiddenZone> must be closed.");
    }
    
    Entity* entity = new ForbiddenZone(xPoints,yPoints);
    entities.push_back(std::unique_ptr<Entity>(entity));
    
    tagName = extractNextTagName();
  }
  
  return tagName;
  
}



void Parser::extractPoints(std::vector<int16_t>& points) {
  
  std::string string, tagName(extractNextTagName());
  
  
  while (tagName == "") {
    string = readString(&std::isdigit, &std::isblank);
    points.push_back(std::atoi(string.c_str()));
    tagName = extractNextTagName();
  }
  
  if (tagName != "/xPoints" && tagName != "/yPoints") {
    throw std::runtime_error("<xPoints> and <yPoints> must be closed.");
  }
  
}



}  // End of project ATCsim namespace.

