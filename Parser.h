/* 
 * File:   Parser.h
 * Author: michael
 *
 * Created on 31. mai 2013, 14:44
 */

#include <fstream>    // Stream class to read from files.
#include <memory>     // For C++11 unique_ptr.
#include <string>
#include <vector>


#ifndef PARSER_H
#define	PARSER_H


namespace ATCsim {  // Project ATCsim namespace.


// Forward declarations (no header includes) (namespace pollution, build time).
class Entity;


class Parser {

public:
 
  // Constructor takes the name of the file to parse.
  Parser(std::string filename);
  
  // Default : call base class'es destructor and destructors of all members.
  // Does not throw any exception (which is what we want for a dtor).
//  virtual ~Parser() noexcept(true) = default;
  virtual ~Parser() = default;
  
  void extract(std::vector< std::unique_ptr<Entity> >& entities);
  
protected:
  
private:
  
  std::ifstream configFile_;
  
  
  // Find the next tag (get pointer to the first character of the tag name).
  // Return false if there is other chars than whitespaces between actual position and tag.
  bool findTag();
  
  // Skip a comment tag (get pointer to the character ater '>').
  // Return true if a comment was read.
  bool skipComment();
  
  // Read a string until it encounters the terminaison character.
  // The firstCharCheck should return true when a valid first character is passed to it.
  std::string readString(int(*firstCharCheck)(int), int(*lastCharCheck)(int));
  
  // Extract the next tag name by going to it, skipping comments and reading it.
  // Return an empty string if there is still data (between tags) to read.
  std::string extractNextTagName();
  
  // Extract point vector.
  void extractPoints(std::vector<int16_t>& points);
  
  
  
  void extractSystem(std::vector< std::unique_ptr<Entity> >& entities);
  
  std::string extractForbiddenZones(std::vector< std::unique_ptr<Entity> >& entities);
  
  
  // Do not allow object copy or move by making copy / move constructor and
  // copy / move assignment operator private members.
  // It will fail to compile if somebody want to copy or move a Parser object.
  // Also prohibit default constructor usage.
  // Mark methods that won’t be implemented with '= delete' (C++11).
  Parser() = delete;
  Parser(const Parser& orig) = delete;
  Parser& operator=(const Parser& orig) = delete;
  Parser(Parser&& orig) = delete;
  Parser& operator=(Parser&& orig) = delete;
  
};


#endif	/* PARSER_H */


}  // End of project ATCsim namespace.

