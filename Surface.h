/* 
 * File:   Surface.h
 * Author: michael
 *
 * Created on 24. mars 2013, 14:04
 */

#ifndef SURFACE_H
#define	SURFACE_H

#include <string>
#include <vector>

// Forward declarations (no header including) (namespace pollution, build time).
struct SDL_Surface;

class Surface {
  
public:
  
//  Surface(SDL_Surface* surface);
  Surface(int weight, int height);
  Surface(int weight, int height, int colorDepth);
  Surface(const char* file);
  Surface(std::string text, uint8_t red, uint8_t green, uint8_t blue,
          std::string font, int size);
  
  virtual ~Surface();
   
  int getWidth();
  int getHeight();
  
  void blit(const Surface& srcSurf, int16_t x, int16_t y);
  void blit(const Surface& srcSurf, int16_t x, int16_t y, int16_t x2, int16_t y2,
            uint16_t w, uint16_t h);
  
  void makeTransparent(uint8_t r, uint8_t g, uint8_t b);
  
//  SDL_Surface* getPointer() const;
  
  void flip();
  
  void drawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                     uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  
  void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, 
                uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  
  void drawAaPolygon(const std::vector<int16_t>& x, const std::vector<int16_t>& y,
                     uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  
  void drawFilledPolygon(const std::vector<int16_t>& x, std::vector<int16_t>& y,
                         uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  
protected:
  
private:
  
  SDL_Surface* surface_;
  
  // Do not allow object copy by making copy constructor and operator= private
  // members. It will fail to compile if somebody want to copy a Surface object.
  // We should deal with SDL_Surface copy and don't need a copy operator
  // (at least for the moment).
  Surface(const Surface& orig);
  Surface operator=(const Surface& orig);
 
};

#endif	/* SURFACE_H */

