#pragma once

// Lazy Foo's LTexture class

/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

#include <SDL_image.h>
#include <string>

//Texture wrapper class
class LTexture {

public:

  //Initializes variables
  LTexture();

  //Deallocates memory
  ~LTexture();

  //Loads image at specified path
  bool loadFromFile(std::string path, SDL_Renderer* renderer);

  //#ifdef _SDL_TTF_H
  //Creates image from font string
  bool loadFromRenderedText(int f, std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* largeFont, TTF_Font* largeAccentFont, TTF_Font* mediumFont, TTF_Font* smallFont);
  //#endif

  //Deallocates texture
  void free();

  //Set color modulation
  void setColor(Uint8 red, Uint8 green, Uint8 blue);

  //Set blending
  void setBlendMode(SDL_BlendMode blending);

  //Set alpha modulation
  void setAlpha(Uint8 alpha);

  //Renders texture at given point
  void render(SDL_Renderer* renderer, int x, int y, int w = 0, int h = 0, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

  //Gets image dimensions
  int getWidth();
  int getHeight();

private:

  //The actual hardware texture
  SDL_Texture* mTexture;

  //Image dimensions
  int mWidth;
  int mHeight;

};