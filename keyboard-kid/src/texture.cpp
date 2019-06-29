#include <SDL.h>
#include <SDL_ttf.h>
#include "texture.h"

bool LTexture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
  //Get rid of preexisting texture
  free();

  //The final texture
  SDL_Texture* newTexture = NULL;

  //Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL)
  {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  }
  else
  {
    //Color key image
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == NULL)
    {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
      //Get image dimensions
      mWidth = loadedSurface->w;
      mHeight = loadedSurface->h;
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  //Return success
  mTexture = newTexture;
  return mTexture != NULL;
}

//#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(int f, std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* largeFont, TTF_Font* largeAccentFont, TTF_Font* mediumFont, TTF_Font* smallFont)
{
  //Get rid of preexisting texture
  free();

  SDL_Surface* textSurface = NULL;

  //Render text surface
  if (f == 0) {
    textSurface = TTF_RenderText_Solid(largeFont, textureText.c_str(), textColor);
  }
  else if (f == 1) {
    textSurface = TTF_RenderText_Solid(largeAccentFont, textureText.c_str(), textColor);
  }
  else if (f == 2) {
    textSurface = TTF_RenderText_Solid(mediumFont, textureText.c_str(), textColor);
  }
  else {
    textSurface = TTF_RenderText_Solid(smallFont, textureText.c_str(), textColor);
  }
  if (textSurface == NULL)
  {
    printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
  }
  else
  {
    //Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (mTexture == NULL)
    {
      printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
      //Get image dimensions
      mWidth = textSurface->w;
      mHeight = textSurface->h;
    }

    //Get rid of old surface
    SDL_FreeSurface(textSurface);
  }

  //Return success
  return mTexture != NULL;
}
//#endif

LTexture::LTexture()
{
  //Initialize
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

LTexture::~LTexture()
{
  //Deallocate
  free();
}

void LTexture::free()
{
  //Free texture if it exists
  if (mTexture != NULL)
  {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
  //Modulate texture rgb
  SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
  //Set blending function
  SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
  //Modulate texture alpha
  SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{

  SDL_Rect renderQuad;

  //Set rendering space and render to screen
  if (w == 0 || h == 0) {
    renderQuad = { x, y, mWidth, mHeight };
  }
  else {
    renderQuad = { x, y, w, h };
  }

  //Set clip rendering dimensions
  if (clip != NULL)
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  //Render to screen
  SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth() {
  return mWidth;
}

int LTexture::getHeight() {
  return mHeight;
}
