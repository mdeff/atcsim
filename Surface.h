/* 
 * File:   Surface.h
 * Author: michael
 *
 * Created on 24. mars 2013, 14:04
 */

#ifndef SURFACE_H
#define	SURFACE_H


#include <cstdint>   // Definitions of uint8_t and int16_t.
#include <string>
#include <vector>


// Forward declarations (no header includes) (namespace pollution, build time).
// This struct is defined in SDL header (global namespace, not ATCsim).
struct SDL_Surface;


namespace ATCsim {  // Project ATCsim namespace.


class Surface {
  
public:
  
  // There is no default constructor.
  Surface() = delete;
  // Define some constructors.
  Surface(int weight, int height);
  Surface(int weight, int height, int colorDepth);
  Surface(const char* file);
  Surface(std::string text, uint8_t red, uint8_t green, uint8_t blue,
          std::string font, int size);
  
  // Use a custom destructor (we have to free the SDL_Surface).
  // Do not throw any exception (which is what we want for a dtor).
  virtual ~Surface() noexcept(true);
   
  int getWidth() const;
  int getHeight() const;
  
  void blit(const Surface& srcSurf, int16_t x, int16_t y);
  void blit(const Surface& srcSurf, int16_t x, int16_t y, int16_t x2, int16_t y2,
            uint16_t w, uint16_t h);
  
//  void makeTransparent(uint8_t r, uint8_t g, uint8_t b);
  
//  SDL_Surface* getPointer() const;
  
  void flip();
  
  void drawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                     uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  
  void drawFilledRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                           uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  
  void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, 
                uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  
  void drawPolygon(const std::vector<int16_t>& x, const std::vector<int16_t>& y,
                   uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  
  void drawFilledPolygon(const std::vector<int16_t>& x, const std::vector<int16_t>& y,
                         uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  
protected:
  
private:
  
//  Surface(SDL_Surface* surface);
  
  SDL_Surface* surface_;
  
  // Do not allow object copy or move by making copy / move constructor and
  // copy / move assignment operator private members.
  // It will fail to compile if somebody want to copy or move a Surface object.
  // Mark methods that won’t be implemented with '= delete' (C++11).
  // We should deal with SDL_Surface copy and don't need to at the moment.
  Surface(const Surface& orig) = delete;
  Surface& operator=(const Surface& orig) = delete;
  Surface(Surface&& orig) = delete;
  Surface& operator=(Surface&& orig) = delete;
 
};
  

}  // End of project ATCsim namespace.


#endif	/* SURFACE_H */

