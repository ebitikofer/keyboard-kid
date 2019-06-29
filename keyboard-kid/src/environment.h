#pragma once

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <cstdio>
#include <string>
#include <cmath>
#include <random>
#include <iostream>
#include "texture.h"

static std::random_device rgen;
static std::mt19937 mgen(rgen());

class environment {

public:
  //Screen dimension constants
  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;

  int run();

  //Starts up SDL and creates window
  bool init();

  //Loads media
  bool loadStartMedia();
  bool loadEndMedia();
  bool loadMedia(int c);

  //Frees media and shuts down SDL
  void closeStart();
  void closeEnd();
  void close();

  int randomNumber(const int& start, const int& end);


  //*****GLOBAL*****//
  //window
  SDL_Window* gWindow = NULL;
  //renderer
  SDL_Renderer* gRenderer;
  //textures
  LTexture gTitle1Texture;
  LTexture gTitle1DetailTexture;
  LTexture gTitle2Texture;
  LTexture gTitle2DetailTexture;
  //fonts
  TTF_Font* gLargeFont;
  TTF_Font* gLargeAccentFont;
  TTF_Font* gMediumFont;
  TTF_Font* gSmallFont;
  //musics
  Mix_Music* gMusic = NULL;
  //animations
  static const int BG_ANIMATION_FRAMES = 3;
  SDL_Rect gBgClips[BG_ANIMATION_FRAMES];
  LTexture gBgSheetTexture;


  //*****START******//
  //textures
  LTexture gStartTexture;
  LTexture gStartDetailTexture;
  LTexture gKeysTexture;
  //animations
  static const int WALKING_ANIMATION_FRAMES = 8;
  SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
  LTexture gSpriteSheetTexture;
  static const int PULSE_ANIMATION_FRAMES = 8;
  SDL_Rect gPulseClips[WALKING_ANIMATION_FRAMES];
  LTexture gPulseSheetTexture;
  Mix_Chunk* gSnare;
  Mix_Chunk* gHigh;
  Mix_Chunk* gMedium;
  Mix_Chunk* gLow;
  Mix_Chunk* gClap;
  Mix_Chunk* gBell;
  Mix_Chunk* gRise;
  Mix_Chunk* gFall;


  //*****END*****//
  //Rendered ending scene texture
  LTexture gRestartTexture;
  LTexture gRestartDetailTexture;
  LTexture gQuitTexture;
  LTexture gQuitDetailTexture;
  LTexture gArrowTexture;
  LTexture gBgTexture;
  /*
  LTexture gFinalBgTexture;
  LTexture gFinalBgDetailTexture;
  LTexture gFinalMgTexture;
  LTexture gFinalMgDetailTexture;
  LTexture gFinalFgTexture;
  LTexture gFinalFgDetailTexture;
  LTexture gFinalChTexture;
  LTexture gFinalChDetailTexture;
  LTexture gFinalBdTexture;
  LTexture gFinalBdDetailTexture;
  LTexture gFinalCgTexture;
  LTexture gFinalCgDetailTexture;
  LTexture gFinalLpTexture;
  LTexture gFinalLpDetailTexture;
  */

  //animations
  static const int DYING_ANIMATION_FRAMES = 8;
  SDL_Rect gDyingClips[DYING_ANIMATION_FRAMES];
  LTexture gDyingSheetTexture;
  static const int SMOKE_ANIMATION_FRAMES = 8;
  SDL_Rect gSmokeClips[SMOKE_ANIMATION_FRAMES];
  LTexture gSmokeSheetTexture;
  static const int FLASH_ANIMATION_FRAMES = 16;
  SDL_Rect gFlashClips[FLASH_ANIMATION_FRAMES];
  LTexture gFlashSheetTexture;

};