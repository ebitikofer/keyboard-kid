/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

// This is not exactly Lazy Foo's code anymore and at one point it will be unrecognizable
// But until then I will keep the credit to Lazy Foo because it was heavilyy based on his tutorial

#include "environment.h"

int main(int argc, char* args[]) {

  environment e;

  e.run();

  ////Start up SDL and create window
  //if (!init())
  //{
  //  printf("Failed to initialize!\n");
  //}
  //else
  //{
  //  //Main loop flag
  //  bool exit = false;

  //  int current = 0, next = 1;

  //  while (!exit) {

  //    current = next;
  //    next = 0;

  //    //Load media
  //    if (!loadMedia(current)) {
  //      printf("Failed to load media!\n");
  //    }
  //    else {
  //      //Main loop flag
  //      bool quit = false, continu = true;

  //      bool d1 = false,
  //        d2 = false,
  //        d3 = false,
  //        d4 = false,
  //        d5 = false,
  //        d6 = false,
  //        d7 = false,
  //        d8 = false,
  //        d9 = false;

  //      //Event handler
  //      SDL_Event e;

  //      //Current animation frame
  //      int slowframe = 0;

  //      //Current animation frame
  //      int midframe = 0;

  //      //Current animation frame
  //      int fastframe = 0;

  //      //Current animation frame
  //      int longframe = 0;

  //      const int pulses = 5;

  //      int pulseX[pulses], pulseY[pulses], pulseF[pulses];

  //      for (int i = 0; i < pulses; i++) {
  //        pulseX[i] = 0;
  //        pulseY[i] = SCREEN_HEIGHT + 1;
  //        pulseF[i] = randomNumber(0, 8);
  //      }

  //      Mix_PlayMusic(gMusic, -1);

  //      //While application is running
  //      while (!quit) {
  //        //Handle events on queue
  //        while (SDL_PollEvent(&e) != 0) {
  //          //User requests quit
  //          if (e.type == SDL_QUIT) {
  //            quit = true;
  //            exit = true;
  //          }

  //          //Handle key downs
  //          else if (e.type == SDL_KEYDOWN) {
  //            switch (e.key.keysym.sym) {
  //              //Play high sound effect
  //            case SDLK_KP_1:
  //              if (!d1) {
  //                Mix_PlayChannel(-1, gSnare, 0);
  //                d1 = true;
  //              }
  //              break;

  //              //Play medium sound effect
  //            case SDLK_KP_2:
  //              if (!d2) {
  //                Mix_PlayChannel(-1, gHigh, 0);
  //                d2 = true;
  //              }
  //              break;

  //              //Play low sound effect
  //            case SDLK_KP_3:
  //              if (!d3) {
  //                Mix_PlayChannel(-1, gMedium, 0);
  //                d3 = true;
  //              }
  //              break;

  //              //Play scratch sound effect
  //            case SDLK_KP_4:
  //              if (!d4) {
  //                Mix_PlayChannel(-1, gLow, 0);
  //                d4 = true;
  //              }
  //              break;

  //              //Play high sound effect
  //            case SDLK_KP_5:
  //              if (!d5) {
  //                Mix_PlayChannel(-1, gClap, 0);
  //                d5 = true;
  //              }
  //              break;

  //              //Play medium sound effect
  //            case SDLK_KP_6:
  //              if (!d6) {
  //                Mix_PlayChannel(-1, gBell, 0);
  //                d6 = true;
  //              }
  //              break;

  //              //Play low sound effect
  //            case SDLK_KP_7:
  //              if (!d7) {
  //                Mix_PlayChannel(-1, gRise, 0);
  //                d7 = true;
  //              }
  //              break;

  //              //Play scratch sound effect
  //            case SDLK_KP_8:
  //              if (!d8) {
  //                Mix_PlayChannel(-1, gFall, 0);
  //                d8 = true;
  //              }
  //              break;

  //            case SDLK_KP_9:
  //              //If there is no music playing
  //              if (!d9) {
  //                if (Mix_PlayingMusic() == 0) {
  //                  //Play the music
  //                  Mix_PlayMusic(gMusic, -1);
  //                }
  //                //If music is being played
  //                else {
  //                  //If the music is paused
  //                  if (Mix_PausedMusic() == 1) {
  //                    //Resume the music
  //                    Mix_ResumeMusic();
  //                  }
  //                  //If the music is playing
  //                  else {
  //                    //Pause the music
  //                    Mix_PauseMusic();
  //                  }
  //                }
  //                d9 = true;
  //              }
  //              break;

  //              //case SDLK_KP_0:
  //              //Stop the music
  //              //    Mix_HaltMusic();
  //              //    break;

  //          //case SDLK_KP_ENTER:
  //              //Stop the music
  //              //Mix_HaltMusic();
  //              //break;
  //            }
  //          }

  //          //Handle key up
  //          else if (e.type == SDL_KEYUP) {
  //            switch (e.key.keysym.sym) {
  //            case SDLK_KP_1:
  //              d1 = false;
  //              break;

  //            case SDLK_KP_2:
  //              d2 = false;
  //              break;

  //            case SDLK_KP_3:
  //              d3 = false;
  //              break;

  //            case SDLK_KP_4:
  //              d4 = false;
  //              break;

  //            case SDLK_KP_5:
  //              d5 = false;
  //              break;

  //            case SDLK_KP_6:
  //              d6 = false;
  //              break;

  //            case SDLK_KP_7:
  //              d7 = false;
  //              break;

  //            case SDLK_KP_8:
  //              d8 = false;
  //              break;

  //            case SDLK_KP_9:
  //              d9 = false;
  //              break;

  //            case SDLK_KP_0:
  //              //Stop the music
  //              Mix_HaltMusic();
  //              break;

  //            case SDLK_RETURN:
  //              switch (current) {
  //              case 1:
  //                next = 2;
  //                quit = true;
  //                break;
  //              case 2:
  //                switch (continu) {
  //                case true:
  //                  next = 1;
  //                  break;
  //                case false:
  //                  next = 2;
  //                  exit = true;
  //                  break;
  //                };
  //                quit = true;
  //                break;
  //              };
  //              break;

  //            case SDLK_LEFT:
  //              //Move cursor
  //              continu = true;
  //              break;

  //            case SDLK_RIGHT:
  //              //Move cursor
  //              continu = false;
  //              break;

  //            }
  //          }
  //        }

  //        //Clear screen
  //        switch (current) {
  //        case 1:
  //          SDL_SetRenderDrawColor(gRenderer, 0x30, 0x00, 0x43, 0xFF);
  //          break;
  //        case 2:
  //          SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
  //          break;
  //        };
  //        SDL_RenderClear(gRenderer);

  //        //background start anim
  //        switch (current) {
  //        case 1:
  //          SDL_Rect* bgClip = &gBgClips[slowframe / 3];
  //          gBgSheetTexture.render(gRenderer, 0, 0, 0, 0, bgClip);
  //          break;
  //        };

  //        switch (current) {
  //        case 1:
  //          //Render current frame
  //          break;
  //        case 2:
  //          //Render current frame
  //          gBgTexture.render(gRenderer,
  //            200,
  //            (gTitle1Texture.getHeight() / 6) - 3 + (gTitle1Texture.getHeight() / 2));
  //          break;
  //        };

  //        SDL_Rect * detailClip = NULL;
  //        //detail start anim
  //        switch (current) {
  //        case 1:
  //          //Render current frame
  //          for (int i = 0; i < pulses; i++) {
  //            detailClip = &gPulseClips[pulseF[i] / 8];
  //            gPulseSheetTexture.render(gRenderer, pulseX[i], pulseY[i], 0, 0, detailClip);
  //          }
  //          break;
  //        case 2:
  //          //Render current frame
  //          //for (int i = 0; i < pulses; i++) {
  //          detailClip = &gFlashClips[fastframe / 16];
  //          gFlashSheetTexture.render(gRenderer,
  //            200,
  //            (gTitle1Texture.getHeight() / 6) - 3 + (gTitle1Texture.getHeight() / 2), 0, 0, detailClip);
  //          //}
  //          break;
  //        };

  //        //character start anim
  //        switch (current) {
  //        case 1:
  //          //Render current frame
  //          SDL_Rect* currentClip = &gSpriteClips[midframe / 8];
  //          gSpriteSheetTexture.render(gRenderer, (SCREEN_WIDTH - currentClip->w) / 2,
  //            (SCREEN_HEIGHT - currentClip->h) * 24 / 40, 0, 0, currentClip);
  //          break;
  //        };

  //        switch (current) {
  //        case 1:
  //          //Render current frame
  //          gTitle1Texture.render(gRenderer,
  //            (SCREEN_WIDTH - gTitle1Texture.getWidth()) / 2 + 3,
  //            /*( gTitle1Texture.getHeight() / 10 ) + */ -10);
  //          gTitle1DetailTexture.render(gRenderer,
  //            (SCREEN_WIDTH - gTitle1DetailTexture.getWidth()) / 2 + 3,
  //            /*( gTitle1Texture.getHeight() / 10 ) + */ -6);
  //          gTitle2Texture.render(gRenderer,
  //            ((SCREEN_WIDTH - gTitle1DetailTexture.getWidth()) / 4) +
  //            (gTitle1DetailTexture.getWidth() * 36 / 64),
  //            /*( gTitle1Texture.getHeight() / 10 ) + */
  //            gTitle1Texture.getHeight() - (gTitle2DetailTexture.getHeight() * 3 / 5));
  //          gTitle2DetailTexture.render(gRenderer,
  //            ((SCREEN_WIDTH - gTitle1DetailTexture.getWidth()) / 4) +
  //            (gTitle1DetailTexture.getWidth() * 36 / 64),
  //            /*( gTitle1Texture.getHeight() / 10 ) + */
  //            gTitle1Texture.getHeight() - (gTitle2DetailTexture.getHeight() * 3 / 5));
  //          gStartTexture.render(gRenderer,
  //            (SCREEN_WIDTH - gStartTexture.getWidth()) / 2,
  //            (SCREEN_HEIGHT - gStartTexture.getHeight() * 3 / 2));
  //          gStartDetailTexture.render(gRenderer,
  //            (SCREEN_WIDTH - gStartTexture.getWidth()) / 2,
  //            (SCREEN_HEIGHT - gStartTexture.getHeight() * 3 / 2 + 2));
  //          gKeysTexture.render(gRenderer,
  //            (SCREEN_WIDTH - gKeysTexture.getWidth()) / 2,
  //            (SCREEN_HEIGHT - gKeysTexture.getHeight()));
  //          break;
  //        case 2:
  //          //Render current frame
  //          gTitle1Texture.render(gRenderer,
  //            (SCREEN_WIDTH - gTitle1Texture.getWidth()) / 2 + 3,
  //            (gTitle1Texture.getHeight() / 6) - 3);
  //          gTitle1DetailTexture.render(gRenderer,
  //            (SCREEN_WIDTH - gTitle1DetailTexture.getWidth()) / 2 + 3,
  //            (gTitle1DetailTexture.getHeight() / 6));
  //          gTitle2Texture.render(gRenderer,
  //            ((SCREEN_WIDTH - gTitle1Texture.getWidth()) / 4) +
  //            (gTitle1Texture.getWidth() * 20 / 64),
  //            /*( gTitle1Texture.getHeight() / 10 ) + */
  //            //(SCREEN_HEIGHT - gTitle1Texture.getHeight() - (gTitle2Texture.getHeight() * 2 / 5)));
  //            (gTitle1Texture.getHeight() / 6) + gTitle1Texture.getHeight() * 27 / 16 - 3);
  //          gTitle2DetailTexture.render(gRenderer,
  //            ((SCREEN_WIDTH - gTitle1DetailTexture.getWidth()) / 4) +
  //            (gTitle1DetailTexture.getWidth() * 20 / 64),
  //            /*( gTitle1Texture.getHeight() / 10 ) + */
  //            //(SCREEN_HEIGHT - gTitle1Texture.getHeight() - (gTitle2Texture.getHeight() * 2 / 5) + 2 ));
  //            (gTitle1Texture.getHeight() / 6) + (gTitle1Texture.getHeight() * 27 / 16));
  //          gRestartTexture.render(gRenderer,
  //            (SCREEN_WIDTH * 1 / 3 - gQuitTexture.getWidth() / 2),
  //            (SCREEN_HEIGHT - gRestartTexture.getHeight() * 2 / 2));
  //          //gRestartDetailTexture.render(
  //          //        (SCREEN_WIDTH * 1 / 3 - gRestartTexture.getWidth() / 2),
  //          //        (SCREEN_HEIGHT - gRestartTexture.getHeight() * 3 / 2 + 2));
  //          gQuitTexture.render(gRenderer,
  //            (SCREEN_WIDTH * 2 / 3 - gQuitTexture.getWidth() / 2 - 1),
  //            (SCREEN_HEIGHT - gQuitTexture.getHeight() * 2 / 2));
  //          //gQuitDetailTexture.render(
  //          //        (SCREEN_WIDTH * 2 / 3 - gQuitTexture.getWidth() / 2),
  //          //        (SCREEN_HEIGHT - gQuitTexture.getHeight() * 3 / 2 + 2));
  //          switch (continu) {
  //          case true:
  //            gArrowTexture.render(gRenderer,
  //              (SCREEN_WIDTH * 1 / 3 - gQuitTexture.getWidth() / 2) -
  //              gArrowTexture.getWidth() * 2,
  //              (SCREEN_HEIGHT - gRestartTexture.getHeight() * 2 / 2));
  //            break;
  //          case false:
  //            gArrowTexture.render(gRenderer,
  //              (SCREEN_WIDTH * 2 / 3 - gQuitTexture.getWidth() / 2) -
  //              gArrowTexture.getWidth() * 2,
  //              (SCREEN_HEIGHT - gQuitTexture.getHeight() * 2 / 2));
  //            break;
  //          };
  //          break;
  //        };

  //        //Update screen
  //        SDL_RenderPresent(gRenderer);

  //        //Go to next frame
  //        ++slowframe;
  //        ++midframe;
  //        ++fastframe;
  //        ++longframe;

  //        for (int i = 0; i < pulses; i++) {
  //          ++pulseF[i];
  //          pulseX[i] += 2;
  //          --pulseY[i];
  //        }

  //        //Cycle animation
  //        if (slowframe / 3 >= BG_ANIMATION_FRAMES) {
  //          slowframe = 0;
  //        }

  //        //Cycle animation
  //        for (int i = 0; i < pulses; i++) {
  //          if (pulseF[i] / 8 >= PULSE_ANIMATION_FRAMES) {
  //            pulseF[i] = 0;
  //          }
  //        }

  //        if (midframe / 8 >= WALKING_ANIMATION_FRAMES) {
  //          midframe = 0;
  //          gStartTexture.setAlpha(255);
  //          gStartDetailTexture.setAlpha(255);
  //        }

  //        //Cycle animation
  //        if (fastframe / 16 >= FLASH_ANIMATION_FRAMES) {
  //          fastframe = 0;
  //          gStartTexture.setAlpha(0);
  //          gStartDetailTexture.setAlpha(0);
  //        }

  //        //Cycle animation
  //        for (int i = 0; i < pulses; i++) {
  //          if (pulseX[i] > SCREEN_WIDTH || pulseY[i] + 15 < 0) {
  //            longframe = 0;
  //            pulseX[i] = 0;
  //            pulseY[i] = randomNumber(0, 24) * 32 + 1;
  //          }
  //        }
  //      }
  //    }

  //    switch (current) {

  //    case 0:
  //      std::cout << "Something's wrong" << std::endl;
  //      break;

  //    case 1:
  //      closeStart();
  //      break;

  //    case 2:
  //      closeEnd();
  //      break;

  //    };
  //  }
  //}

  ////Free resources and close SDL
  //close();

  return 0;
}

