/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

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

static std::random_device rgen;
static std::mt19937 mgen(rgen());

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Texture wrapper class
class LTexture {

    public:

        //Initializes variables
        LTexture();

        //Deallocates memory
        ~LTexture();

        //Loads image at specified path
        bool loadFromFile(std::string path );

        //#ifdef _SDL_TTF_H
        //Creates image from font string
        bool loadFromRenderedText( int f, std::string textureText, SDL_Color textColor );
        //#endif

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );

        //Renders texture at given point
        void render( int x, int y, int w = 0, int h = 0, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

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

int randomNumber(const int &start, const int &end);


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
TTF_Font *gLargeFont;
TTF_Font *gLargeAccentFont;
TTF_Font *gMediumFont;
TTF_Font *gSmallFont;
//musics
Mix_Music *gMusic = NULL;
//animations
const int BG_ANIMATION_FRAMES = 3;
SDL_Rect gBgClips[ BG_ANIMATION_FRAMES ];
LTexture gBgSheetTexture;


//*****START******//
//textures
LTexture gStartTexture;
LTexture gStartDetailTexture;
LTexture gKeysTexture;
//animations
const int WALKING_ANIMATION_FRAMES = 8;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
LTexture gSpriteSheetTexture;
const int PULSE_ANIMATION_FRAMES = 8;
SDL_Rect gPulseClips[ WALKING_ANIMATION_FRAMES ];
LTexture gPulseSheetTexture;
Mix_Chunk *gSnare;
Mix_Chunk *gHigh;
Mix_Chunk *gMedium;
Mix_Chunk *gLow;
Mix_Chunk *gClap;
Mix_Chunk *gBell;
Mix_Chunk *gRise;
Mix_Chunk *gFall;


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
const int DYING_ANIMATION_FRAMES = 8;
SDL_Rect gDyingClips[ DYING_ANIMATION_FRAMES ];
LTexture gDyingSheetTexture;
const int SMOKE_ANIMATION_FRAMES = 8;
SDL_Rect gSmokeClips[ SMOKE_ANIMATION_FRAMES ];
LTexture gSmokeSheetTexture;
const int FLASH_ANIMATION_FRAMES = 16;
SDL_Rect gFlashClips[ FLASH_ANIMATION_FRAMES ];
LTexture gFlashSheetTexture;


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

bool LTexture::loadFromFile(std::string path )
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

//#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(int f, std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();

    SDL_Surface* textSurface = NULL;

    //Render text surface
    if(f == 0){
        textSurface = TTF_RenderText_Solid( gLargeFont, textureText.c_str(), textColor );
    } else if(f==1){
        textSurface = TTF_RenderText_Solid( gLargeAccentFont, textureText.c_str(), textColor );
    } else if(f==2) {
        textSurface = TTF_RenderText_Solid( gMediumFont, textureText.c_str(), textColor );
    } else {
        textSurface = TTF_RenderText_Solid( gSmallFont, textureText.c_str(), textColor );
    }
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    //Return success
    return mTexture != NULL;
}
//#endif

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, int w, int h, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{

    SDL_Rect renderQuad;

    //Set rendering space and render to screen
    if(w == 0 || h == 0) {
        renderQuad = {x, y, mWidth, mHeight};
    } else {
        renderQuad = {x, y, w, h};
    }

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth() {
    return mWidth;
}

int LTexture::getHeight() {
    return mHeight;
}

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }

                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }

                //Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia(int c)
{
    //Loading success flag
    bool success = true;

    switch (c) {
        case 0:
            std::cout << "Something's wrong" << std::endl;
            success = false;
            break;

        case 1: //Load starting scene media
            if (!loadStartMedia()) {
                printf("Failed to load media!\n");
                success = false;
            }
            break;

        case 2: //Load ending scene media
            if (!loadEndMedia()) {
                printf("Failed to load ending scene media!\n");
                success = false;
            }
            break;
    };

    return success;
}

bool loadStartMedia()
{
    //Loading success flag
    bool success = true;

    //Load sprite sheet texture
    if( !gBgSheetTexture.loadFromFile( "./res/imgs/background.png" ) )
    {
        printf( "Failed to load bg animation texture!\n" );
        success = false;
    }
    else {
        //Set bg clips
        gBgClips[0].x = 0;
        gBgClips[0].y = 0;
        gBgClips[0].w = 640;
        gBgClips[0].h = 480;

        gBgClips[1].x = 640;
        gBgClips[1].y = 0;
        gBgClips[1].w = 640;
        gBgClips[1].h = 480;

        gBgClips[2].x = 1280;
        gBgClips[2].y = 0;
        gBgClips[2].w = 640;
        gBgClips[2].h = 480;

    }

    //Load sprite sheet texture
    if( !gSpriteSheetTexture.loadFromFile( "./res/imgs/hover.png" ) )
    {
        printf( "Failed to load walking animation texture!\n" );
        success = false;
    }
    else {
        //Set sprite clips
        gSpriteClips[0].x = 0;
        gSpriteClips[0].y = 0;
        gSpriteClips[0].w = 128;
        gSpriteClips[0].h = 192;

        gSpriteClips[1].x = 128;
        gSpriteClips[1].y = 0;
        gSpriteClips[1].w = 128;
        gSpriteClips[1].h = 192;

        gSpriteClips[2].x = 256;
        gSpriteClips[2].y = 0;
        gSpriteClips[2].w = 128;
        gSpriteClips[2].h = 192;

        gSpriteClips[3].x = 384;
        gSpriteClips[3].y = 0;
        gSpriteClips[3].w = 128;
        gSpriteClips[3].h = 192;

        gSpriteClips[4].x = 512;
        gSpriteClips[4].y = 0;
        gSpriteClips[4].w = 128;
        gSpriteClips[4].h = 192;

        gSpriteClips[5].x = 640;
        gSpriteClips[5].y = 0;
        gSpriteClips[5].w = 128;
        gSpriteClips[5].h = 192;

        gSpriteClips[6].x = 768;
        gSpriteClips[6].y = 0;
        gSpriteClips[6].w = 128;
        gSpriteClips[6].h = 192;

        gSpriteClips[7].x = 896;
        gSpriteClips[7].y = 0;
        gSpriteClips[7].w = 128;
        gSpriteClips[7].h = 192;
    }

    //Load pulse sheet texture
    if( !gPulseSheetTexture.loadFromFile( "./res/imgs/bgpulse.png" ) )
    {
        printf( "Failed to load pulse animation texture!\n" );
        success = false;
    }
    else {
        //Set sprite clips
        gPulseClips[0].x = 0;
        gPulseClips[0].y = 0;
        gPulseClips[0].w = 30;
        gPulseClips[0].h = 15;

        gPulseClips[1].x = 30;
        gPulseClips[1].y = 0;
        gPulseClips[1].w = 30;
        gPulseClips[1].h = 15;

        gPulseClips[2].x = 60;
        gPulseClips[2].y = 0;
        gPulseClips[2].w = 30;
        gPulseClips[2].h = 15;

        gPulseClips[3].x = 90;
        gPulseClips[3].y = 0;
        gPulseClips[3].w = 30;
        gPulseClips[3].h = 15;

        gPulseClips[4].x = 120;
        gPulseClips[4].y = 0;
        gPulseClips[4].w = 30;
        gPulseClips[4].h = 15;

        gPulseClips[5].x = 150;
        gPulseClips[5].y = 0;
        gPulseClips[5].w = 30;
        gPulseClips[5].h = 15;

        gPulseClips[6].x = 180;
        gPulseClips[6].y = 0;
        gPulseClips[6].w = 30;
        gPulseClips[6].h = 15;

        gPulseClips[7].x = 210;
        gPulseClips[7].y = 0;
        gPulseClips[7].w = 30;
        gPulseClips[7].h = 15;
    }

    //Open the large font
    gLargeFont = TTF_OpenFont( "./res/fonts/discoduck.ttf", 115 );
    if( gLargeFont == NULL )
    {
        printf( "Failed to load l font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 255, 200, 0 };
        if( !gTitle1Texture.loadFromRenderedText( 0, "K3YB04RD", textColor ) ) {
            printf("Failed to render text texture!\n");
            success = false;
        }
    }
    //Open the large font detail
    gLargeFont = TTF_OpenFont( "./res/fonts/discoduckhalf.ttf", 115 );
    if( gLargeFont == NULL )
    {
        printf( "Failed to load l font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text detail
        SDL_Color textColor = { 0, 255, 255 };
        if( !gTitle1DetailTexture.loadFromRenderedText( 0, "K3YB04RD", textColor ) ) {
            printf("Failed to render text texture!\n");
            success = false;
        }
    }

    //Open the large accent font
    gLargeAccentFont = TTF_OpenFont( "./res/fonts/neon.ttf", 70 );
    if( gLargeAccentFont == NULL )
    {
        printf( "Failed to load m font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 255, 255, 255 };
        if( !gTitle2Texture.loadFromRenderedText( 1, "Kid", textColor ) ) {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }
    //Open the large accent font detail
    gLargeAccentFont = TTF_OpenFont( "./res/fonts/neon.ttf", 69 );
    if( gLargeAccentFont == NULL )
    {
        printf( "Failed to load m font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 255, 110, 210 };
        if( !gTitle2DetailTexture.loadFromRenderedText( 1, "Kid", textColor ) ) {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }

    //Open the medium font
    gMediumFont = TTF_OpenFont( "./res/fonts/medium.ttf", 40 );
    if( gMediumFont == NULL )
    {
        printf( "Failed to load l font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 255, 200, 0 };
        if( !gStartTexture.loadFromRenderedText( 2, "START", textColor ) ) {
            printf("Failed to render text texture!\n");
            success = false;
        }
    }
    //Open the medium font detail
    gMediumFont = TTF_OpenFont( "./res/fonts/mediumdetail.ttf", 36 );
    if( gMediumFont == NULL )
    {
        printf( "Failed to load l font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text detail
        SDL_Color textColor = { 0, 255, 255 };
        if( !gStartDetailTexture.loadFromRenderedText( 2, "START", textColor ) ) {
            printf("Failed to render text texture!\n");
            success = false;
        }
    }

    //Open the small font
    gSmallFont = TTF_OpenFont( "./res/fonts/lazy.ttf", 16 );
    if( gSmallFont == NULL )
    {
        printf( "Failed to load s font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 255, 110, 210 };
        if( !gKeysTexture.loadFromRenderedText( 3, "(1)snare(2)tom1(3)tom2(4)tom3  (5)clap(6)bell(7)rise(8)fall      (9)pause(0)stop", textColor ) ) {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }

    //Load music
    gMusic = Mix_LoadMUS( "./res/wavs/neatbeat.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    //Load sound effects
    gSnare = Mix_LoadWAV( "./res/wavs/snare.wav" );
    if( gSnare == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gHigh = Mix_LoadWAV( "./res/wavs/high.wav" );
    if( gHigh == NULL )
    {
        printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gMedium = Mix_LoadWAV( "./res/wavs/medium.wav" );
    if( gMedium == NULL )
    {
        printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gLow = Mix_LoadWAV( "./res/wavs/low.wav" );
    if( gLow == NULL )
    {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    //Load sound effects
    gClap = Mix_LoadWAV( "./res/wavs/clap.wav" );
    if( gClap == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gBell = Mix_LoadWAV( "./res/wavs/bell.wav" );
    if( gBell == NULL )
    {
        printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gRise = Mix_LoadWAV( "./res/wavs/rise.wav" );
    if( gRise == NULL )
    {
        printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    gFall = Mix_LoadWAV( "./res/wavs/fall.wav" );
    if( gFall == NULL )
    {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

bool loadEndMedia()
{
    //Loading success flag
    bool success = true;
/*
    //Load sprite sheet texture
    if( !gBgSheetTexture.loadFromFile( "./res/imgs/background.png" ) )
    {
        printf( "Failed to load bg animation texture!\n" );
        success = false;
    }
    else {
        //Set bg clips
        gBgClips[0].x = 0;
        gBgClips[0].y = 0;
        gBgClips[0].w = 640;
        gBgClips[0].h = 480;

        gBgClips[1].x = 640;
        gBgClips[1].y = 0;
        gBgClips[1].w = 640;
        gBgClips[1].h = 480;

        gBgClips[2].x = 1280;
        gBgClips[2].y = 0;
        gBgClips[2].w = 640;
        gBgClips[2].h = 480;

    }
*/

    //Load sprite sheet texture
    if( !gBgTexture.loadFromFile( "./res/imgs/backg.png" ) )
    {
        printf( "Failed to load bg animation texture!\n" );
        success = false;
    }
    else {
        //Set bg clips
    }
    //Load sprite sheet texture
    if( !gDyingSheetTexture.loadFromFile( "./res/imgs/hover.png" ) )
    {
        printf( "Failed to load walking animation texture!\n" );
        success = false;
    }
    else {
        //Set sprite clips
        gDyingClips[0].x = 0;
        gDyingClips[0].y = 0;
        gDyingClips[0].w = 128;
        gDyingClips[0].h = 192;

        gDyingClips[1].x = 128;
        gDyingClips[1].y = 0;
        gDyingClips[1].w = 128;
        gDyingClips[1].h = 192;

        gDyingClips[2].x = 256;
        gDyingClips[2].y = 0;
        gDyingClips[2].w = 128;
        gDyingClips[2].h = 192;

        gDyingClips[3].x = 384;
        gDyingClips[3].y = 0;
        gDyingClips[3].w = 128;
        gDyingClips[3].h = 192;

        gDyingClips[4].x = 512;
        gDyingClips[4].y = 0;
        gDyingClips[4].w = 128;
        gDyingClips[4].h = 192;

        gDyingClips[5].x = 640;
        gDyingClips[5].y = 0;
        gDyingClips[5].w = 128;
        gDyingClips[5].h = 192;

        gDyingClips[6].x = 768;
        gDyingClips[6].y = 0;
        gDyingClips[6].w = 128;
        gDyingClips[6].h = 192;

        gDyingClips[7].x = 896;
        gDyingClips[7].y = 0;
        gDyingClips[7].w = 128;
        gDyingClips[7].h = 192;
    }

    //Load flash sheet texture
    if( !gFlashSheetTexture.loadFromFile( "./res/imgs/bgflash.png" ) )
    {
        printf( "Failed to load flash animation texture!\n" );
        success = false;
    }
    else {
        //Set sprite clips
        gFlashClips[0].x = 0;
        gFlashClips[0].y = 0;
        gFlashClips[0].w = 240;
        gFlashClips[0].h = 240;

        gFlashClips[1].x = 240;
        gFlashClips[1].y = 0;
        gFlashClips[1].w = 240;
        gFlashClips[1].h = 240;

        gFlashClips[2].x = 480;
        gFlashClips[2].y = 0;
        gFlashClips[2].w = 240;
        gFlashClips[2].h = 240;

        gFlashClips[3].x = 720;
        gFlashClips[3].y = 0;
        gFlashClips[3].w = 240;
        gFlashClips[3].h = 240;

        gFlashClips[4].x = 960;
        gFlashClips[4].y = 0;
        gFlashClips[4].w = 240;
        gFlashClips[4].h = 240;

        gFlashClips[5].x = 1200;
        gFlashClips[5].y = 0;
        gFlashClips[5].w = 240;
        gFlashClips[5].h = 240;

        gFlashClips[6].x = 1440;
        gFlashClips[6].y = 0;
        gFlashClips[6].w = 240;
        gFlashClips[6].h = 240;

        gFlashClips[7].x = 1680;
        gFlashClips[7].y = 0;
        gFlashClips[7].w = 240;
        gFlashClips[7].h = 240;

        gFlashClips[8].x = 1920;
        gFlashClips[8].y = 0;
        gFlashClips[8].w = 240;
        gFlashClips[8].h = 240;

        gFlashClips[9].x = 2160;
        gFlashClips[9].y = 0;
        gFlashClips[9].w = 240;
        gFlashClips[9].h = 240;

        gFlashClips[10].x = 2400;
        gFlashClips[10].y = 0;
        gFlashClips[10].w = 240;
        gFlashClips[10].h = 240;

        gFlashClips[11].x = 2640;
        gFlashClips[11].y = 0;
        gFlashClips[11].w = 240;
        gFlashClips[11].h = 240;

        gFlashClips[12].x = 2880;
        gFlashClips[12].y = 0;
        gFlashClips[12].w = 240;
        gFlashClips[12].h = 240;

        gFlashClips[13].x = 3120;
        gFlashClips[13].y = 0;
        gFlashClips[13].w = 240;
        gFlashClips[13].h = 240;

        gFlashClips[14].x = 3360;
        gFlashClips[14].y = 0;
        gFlashClips[14].w = 240;
        gFlashClips[14].h = 240;

        gFlashClips[15].x = 3600;
        gFlashClips[15].y = 0;
        gFlashClips[15].w = 240;
        gFlashClips[15].h = 240;
    }

    //Open the large font
    gLargeFont = TTF_OpenFont( "./res/fonts/endlarge.ttf", 115 );
    if( gLargeFont == NULL )
    {
        printf( "Failed to load l font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 155, 0, 0 };
        if( !gTitle1Texture.loadFromRenderedText( 0, "GAME", textColor ) ) {
            printf("Failed to render text texture!\n");
            success = false;
        }
        //Render text
        if( !gTitle2Texture.loadFromRenderedText( 0, "OVER", textColor ) ) {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }
    //Open the large font detail
    gLargeFont = TTF_OpenFont( "./res/fonts/endlarge.ttf", 115 );
    if( gLargeFont == NULL )
    {
        printf( "Failed to load l font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text detail
        SDL_Color textColor = { 75, 0, 0 };
        if( !gTitle1DetailTexture.loadFromRenderedText( 0, "GAME", textColor ) ) {
            printf("Failed to render text texture!\n");
            success = false;
        }
        //Render text
        if( !gTitle2DetailTexture.loadFromRenderedText( 0, "OVER", textColor ) ) {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }

    //Open the large accent font
    gLargeAccentFont = TTF_OpenFont( "./res/fonts/neon.ttf", 70 );
    if( gLargeAccentFont == NULL )
    {
        printf( "Failed to load m font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else {
    }
    //Open the large accent font detail
    gLargeAccentFont = TTF_OpenFont( "./res/fonts/neon.ttf", 69 );
    if( gLargeAccentFont == NULL )
    {
        printf( "Failed to load m font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else {
    }

    //Open the medium font
    gMediumFont = TTF_OpenFont( "./res/fonts/medium.ttf", 40 );
    if( gMediumFont == NULL )
    {
        printf( "Failed to load l font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 255, 200, 0 };
        if( !gRestartTexture.loadFromRenderedText( 2, "RESTART", textColor ) ) {
            printf("Failed to render text texture!\n");
            success = false;
        }
        if( !gQuitTexture.loadFromRenderedText( 2, "QUIT", textColor ) ) {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }
    //Open the medium font detail
    gMediumFont = TTF_OpenFont( "./res/fonts/mediumdetail.ttf", 36 );
    if( gMediumFont == NULL )
    {
        printf( "Failed to load l font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text detail
        SDL_Color textColor = { 0, 255, 255 };
        if( !gRestartDetailTexture.loadFromRenderedText( 2, "RESTART", textColor ) ) {
            printf("Failed to render text texture!\n");
            success = false;
        }
        if( !gQuitDetailTexture.loadFromRenderedText( 2, "QUIT", textColor ) ) {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if( !gArrowTexture.loadFromRenderedText( 2, ">", textColor ) ) {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }

    //Open the small font
    gSmallFont = TTF_OpenFont( "./res/fonts/lazy.ttf", 16 );
    if( gSmallFont == NULL )
    {
        printf( "Failed to load s font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
    }

    //Load music
    gMusic = Mix_LoadMUS( "./res/wavs/neatbeat.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

void close()
{

    //closeStart();
    //closeEnd();

    //Free loaded image
    gBgSheetTexture.free();
    gSpriteSheetTexture.free();
    gPulseSheetTexture.free();
    gDyingSheetTexture.free();
    gFlashSheetTexture.free();
    gTitle1Texture.free();
    gTitle1DetailTexture.free();
    gTitle2Texture.free();
    gTitle2DetailTexture.free();
    gStartTexture.free();
    gStartDetailTexture.free();
    gRestartTexture.free();
    gRestartDetailTexture.free();
    gQuitTexture.free();
    gQuitDetailTexture.free();
    gArrowTexture.free();
    gKeysTexture.free();

    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;

    //Free global font
    TTF_CloseFont( gLargeFont );
    gLargeFont = NULL;
    TTF_CloseFont( gLargeAccentFont );
    gLargeAccentFont = NULL;
    TTF_CloseFont( gMediumFont );
    gMediumFont = NULL;
    TTF_CloseFont( gSmallFont );
    gSmallFont = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    gWindow = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

void closeStart()
{
    //Free loaded image
    gBgSheetTexture.free();
    gSpriteSheetTexture.free();
    gPulseSheetTexture.free();
    gTitle1Texture.free();
    gTitle1DetailTexture.free();
    gTitle2Texture.free();
    gTitle2DetailTexture.free();
    gStartTexture.free();
    gStartDetailTexture.free();
    gKeysTexture.free();


    //Free the sound effects
    Mix_FreeChunk( gSnare );
    Mix_FreeChunk( gHigh );
    Mix_FreeChunk( gMedium );
    Mix_FreeChunk( gLow );
    Mix_FreeChunk( gClap );
    Mix_FreeChunk( gBell );
    Mix_FreeChunk( gRise );
    Mix_FreeChunk( gFall );
    gSnare = NULL;
    gHigh = NULL;
    gMedium = NULL;
    gLow = NULL;
    gClap = NULL;
    gBell = NULL;
    gRise = NULL;
    gFall = NULL;

    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;

    //Free global font
    TTF_CloseFont( gLargeFont );
    gLargeFont = NULL;
    TTF_CloseFont( gLargeAccentFont );
    gLargeAccentFont = NULL;
    TTF_CloseFont( gMediumFont );
    gMediumFont = NULL;
    TTF_CloseFont( gSmallFont );
    gSmallFont = NULL;
}

void closeEnd()
{
    //Free loaded image
    gBgSheetTexture.free();
    gDyingSheetTexture.free();
    gSmokeSheetTexture.free();
    gFlashSheetTexture.free();
    gTitle1Texture.free();
    gTitle1DetailTexture.free();
    gTitle2Texture.free();
    gTitle2DetailTexture.free();
    gRestartTexture.free();
    gRestartDetailTexture.free();
    gQuitTexture.free();
    gQuitDetailTexture.free();
    gArrowTexture.free();
    /*
    gFinalBgTexture.free();
    gFinalBgDetailTexture.free();
    gFinalMgTexture.free();
    gFinalMgDetailTexture.free();
    gFinalFgTexture.free();
    gFinalFgDetailTexture.free();
    gFinalChTexture.free();
    gFinalChDetailTexture.free();
    gFinalBdTexture.free();
    gFinalBdDetailTexture.free();
    gFinalCgTexture.free();
    gFinalCgDetailTexture.free();
    gFinalLpTexture.free();
    gFinalLpDetailTexture.free();
    */

    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;

    //Free global font
    TTF_CloseFont( gLargeFont );
    gLargeFont = NULL;
    TTF_CloseFont( gLargeAccentFont );
    gLargeAccentFont = NULL;
    TTF_CloseFont( gMediumFont );
    gMediumFont = NULL;
    TTF_CloseFont( gSmallFont );
    gSmallFont = NULL;
}

int randomNumber(const int &start, const int &end) {
    std::uniform_int_distribution<int> totalroll(start, end);
    return totalroll(mgen);
}

int main( int argc, char* args[] ) {

    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Main loop flag
        bool exit = false;

        int current = 0, next = 1;

        while (!exit) {

            current = next;
            next = 0;

            //Load media
            if (!loadMedia(current)) {
                printf("Failed to load media!\n");
            } else {
                //Main loop flag
                bool quit = false, continu = true;

                bool d1 = false,
                        d2 = false,
                        d3 = false,
                        d4 = false,
                        d5 = false,
                        d6 = false,
                        d7 = false,
                        d8 = false,
                        d9 = false;

                //Event handler
                SDL_Event e;

                //Current animation frame
                int slowframe = 0;

                //Current animation frame
                int midframe = 0;

                //Current animation frame
                int fastframe = 0;

                //Current animation frame
                int longframe = 0;

                const int pulses = 5;

                int pulseX[pulses], pulseY[pulses], pulseF[pulses];

                for (int i = 0; i < pulses; i++) {
                    pulseX[i] = 0;
                    pulseY[i] = SCREEN_HEIGHT + 1;
                    pulseF[i] = randomNumber(0, 8);
                }

                Mix_PlayMusic(gMusic, -1);

                //While application is running
                while (!quit) {
                    //Handle events on queue
                    while (SDL_PollEvent(&e) != 0) {
                        //User requests quit
                        if (e.type == SDL_QUIT) {
                            quit = true;
                            exit = true;
                        }

                            //Handle key downs
                        else if (e.type == SDL_KEYDOWN) {
                            switch (e.key.keysym.sym) {
                                //Play high sound effect
                                case SDLK_KP_1:
                                    if (!d1) {
                                        Mix_PlayChannel(-1, gSnare, 0);
                                        d1 = true;
                                    }
                                    break;

                                    //Play medium sound effect
                                case SDLK_KP_2:
                                    if (!d2) {
                                        Mix_PlayChannel(-1, gHigh, 0);
                                        d2 = true;
                                    }
                                    break;

                                    //Play low sound effect
                                case SDLK_KP_3:
                                    if (!d3) {
                                        Mix_PlayChannel(-1, gMedium, 0);
                                        d3 = true;
                                    }
                                    break;

                                    //Play scratch sound effect
                                case SDLK_KP_4:
                                    if (!d4) {
                                        Mix_PlayChannel(-1, gLow, 0);
                                        d4 = true;
                                    }
                                    break;

                                    //Play high sound effect
                                case SDLK_KP_5:
                                    if (!d5) {
                                        Mix_PlayChannel(-1, gClap, 0);
                                        d5 = true;
                                    }
                                    break;

                                    //Play medium sound effect
                                case SDLK_KP_6:
                                    if (!d6) {
                                        Mix_PlayChannel(-1, gBell, 0);
                                        d6 = true;
                                    }
                                    break;

                                    //Play low sound effect
                                case SDLK_KP_7:
                                    if (!d7) {
                                        Mix_PlayChannel(-1, gRise, 0);
                                        d7 = true;
                                    }
                                    break;

                                    //Play scratch sound effect
                                case SDLK_KP_8:
                                    if (!d8) {
                                        Mix_PlayChannel(-1, gFall, 0);
                                        d8 = true;
                                    }
                                    break;

                                case SDLK_KP_9:
                                    //If there is no music playing
                                    if (!d9) {
                                        if (Mix_PlayingMusic() == 0) {
                                            //Play the music
                                            Mix_PlayMusic(gMusic, -1);
                                        }
                                            //If music is being played
                                        else {
                                            //If the music is paused
                                            if (Mix_PausedMusic() == 1) {
                                                //Resume the music
                                                Mix_ResumeMusic();
                                            }
                                                //If the music is playing
                                            else {
                                                //Pause the music
                                                Mix_PauseMusic();
                                            }
                                        }
                                        d9 = true;
                                    }
                                    break;

                                    //case SDLK_KP_0:
                                    //Stop the music
                                    //    Mix_HaltMusic();
                                    //    break;

                                //case SDLK_KP_ENTER:
                                    //Stop the music
                                    //Mix_HaltMusic();
                                    //break;
                            }
                        }

                            //Handle key up
                        else if (e.type == SDL_KEYUP) {
                            switch (e.key.keysym.sym) {
                                case SDLK_KP_1:
                                    d1 = false;
                                    break;

                                case SDLK_KP_2:
                                    d2 = false;
                                    break;

                                case SDLK_KP_3:
                                    d3 = false;
                                    break;

                                case SDLK_KP_4:
                                    d4 = false;
                                    break;

                                case SDLK_KP_5:
                                    d5 = false;
                                    break;

                                case SDLK_KP_6:
                                    d6 = false;
                                    break;

                                case SDLK_KP_7:
                                    d7 = false;
                                    break;

                                case SDLK_KP_8:
                                    d8 = false;
                                    break;

                                case SDLK_KP_9:
                                    d9 = false;
                                    break;

                                case SDLK_KP_0:
                                    //Stop the music
                                    Mix_HaltMusic();
                                    break;

                                case SDLK_RETURN:
                                    switch(current) {
                                        case 1:
                                            next = 2;
                                            quit = true;
                                            break;
                                        case 2:
                                            switch(continu) {
                                                case true:
                                                    next = 1;
                                                    break;
                                                case false:
                                                    next = 2;
                                                    exit = true;
                                                    break;
                                            };
                                            quit = true;
                                            break;
                                    };
                                    break;

                                case SDLK_LEFT:
                                    //Move cursor
                                    continu = true;
                                    break;

                                case SDLK_RIGHT:
                                    //Move cursor
                                    continu = false;
                                    break;

                            }
                        }
                    }

                    //Clear screen
                    switch(current) {
                        case 1:
                            SDL_SetRenderDrawColor(gRenderer, 0x30, 0x00, 0x43, 0xFF);
                            break;
                        case 2:
                            SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
                            break;
                    };
                    SDL_RenderClear(gRenderer);

                    //background start anim
                    switch(current) {
                        case 1:
                            SDL_Rect *bgClip = &gBgClips[slowframe / 3];
                            gBgSheetTexture.render(0, 0, 0, 0, bgClip);
                            break;
                    };

                    switch(current) {
                        case 1:
                            //Render current frame
                            break;
                        case 2:
                            //Render current frame
                            gBgTexture.render(
                                    200,
                                    ( gTitle1Texture.getHeight() / 6 ) - 3 + ( gTitle1Texture.getHeight() / 2 ));
                            break;
                    };

                    SDL_Rect *detailClip = NULL;
                    //detail start anim
                    switch(current) {
                        case 1:
                            //Render current frame
                            for (int i = 0; i < pulses; i++) {
                                detailClip = &gPulseClips[pulseF[i] / 8];
                                gPulseSheetTexture.render(pulseX[i], pulseY[i], 0, 0, detailClip);
                            }
                            break;
                        case 2:
                            //Render current frame
                            //for (int i = 0; i < pulses; i++) {
                                detailClip = &gFlashClips[fastframe / 16];
                                gFlashSheetTexture.render(
                                        200,
                                        ( gTitle1Texture.getHeight() / 6 ) - 3 + ( gTitle1Texture.getHeight() / 2 ), 0, 0, detailClip);
                            //}
                            break;
                    };

                    //character start anim
                    switch(current) {
                        case 1:
                            //Render current frame
                            SDL_Rect *currentClip = &gSpriteClips[midframe / 8];
                            gSpriteSheetTexture.render((SCREEN_WIDTH - currentClip->w) / 2,
                                                       (SCREEN_HEIGHT - currentClip->h) * 24 / 40, 0, 0, currentClip);
                            break;
                    };

                    switch(current) {
                        case 1:
                            //Render current frame
                            gTitle1Texture.render(
                                    (SCREEN_WIDTH - gTitle1Texture.getWidth()) / 2 + 3,
                                    /*( gTitle1Texture.getHeight() / 10 ) + */ -10);
                            gTitle1DetailTexture.render(
                                    (SCREEN_WIDTH - gTitle1DetailTexture.getWidth()) / 2 + 3,
                                    /*( gTitle1Texture.getHeight() / 10 ) + */ -6);
                            gTitle2Texture.render(
                                    ((SCREEN_WIDTH - gTitle1DetailTexture.getWidth()) / 4) +
                                    (gTitle1DetailTexture.getWidth() * 36 / 64),
                                    /*( gTitle1Texture.getHeight() / 10 ) + */
                                    gTitle1Texture.getHeight() - (gTitle2DetailTexture.getHeight() * 3 / 5));
                            gTitle2DetailTexture.render(
                                    ((SCREEN_WIDTH - gTitle1DetailTexture.getWidth()) / 4) +
                                    (gTitle1DetailTexture.getWidth() * 36 / 64),
                                    /*( gTitle1Texture.getHeight() / 10 ) + */
                                    gTitle1Texture.getHeight() - (gTitle2DetailTexture.getHeight() * 3 / 5));
                            gStartTexture.render(
                                    (SCREEN_WIDTH - gStartTexture.getWidth()) / 2,
                                    (SCREEN_HEIGHT - gStartTexture.getHeight() * 3 / 2));
                            gStartDetailTexture.render(
                                    (SCREEN_WIDTH - gStartTexture.getWidth()) / 2,
                                    (SCREEN_HEIGHT - gStartTexture.getHeight() * 3 / 2 + 2));
                            gKeysTexture.render(
                                    (SCREEN_WIDTH - gKeysTexture.getWidth()) / 2,
                                    (SCREEN_HEIGHT - gKeysTexture.getHeight()));
                            break;
                        case 2:
                            //Render current frame
                            gTitle1Texture.render(
                                    (SCREEN_WIDTH - gTitle1Texture.getWidth()) / 2 + 3,
                                    ( gTitle1Texture.getHeight() / 6 ) - 3);
                            gTitle1DetailTexture.render(
                                    (SCREEN_WIDTH - gTitle1DetailTexture.getWidth()) / 2 + 3,
                                    ( gTitle1DetailTexture.getHeight() / 6 ));
                            gTitle2Texture.render(
                                    ((SCREEN_WIDTH - gTitle1Texture.getWidth()) / 4) +
                                    (gTitle1Texture.getWidth() * 20 / 64),
                                    /*( gTitle1Texture.getHeight() / 10 ) + */
                                    //(SCREEN_HEIGHT - gTitle1Texture.getHeight() - (gTitle2Texture.getHeight() * 2 / 5)));
                                    ( gTitle1Texture.getHeight() / 6 ) + gTitle1Texture.getHeight() * 27 / 16 - 3);
                            gTitle2DetailTexture.render(
                                    ((SCREEN_WIDTH - gTitle1DetailTexture.getWidth()) / 4) +
                                    (gTitle1DetailTexture.getWidth() * 20 / 64),
                                    /*( gTitle1Texture.getHeight() / 10 ) + */
                                    //(SCREEN_HEIGHT - gTitle1Texture.getHeight() - (gTitle2Texture.getHeight() * 2 / 5) + 2 ));
                                    ( gTitle1Texture.getHeight() / 6 ) + ( gTitle1Texture.getHeight() * 27 / 16 ));
                            gRestartTexture.render(
                                    (SCREEN_WIDTH * 1 / 3 - gQuitTexture.getWidth() / 2),
                                    (SCREEN_HEIGHT - gRestartTexture.getHeight() * 2 / 2));
                            //gRestartDetailTexture.render(
                            //        (SCREEN_WIDTH * 1 / 3 - gRestartTexture.getWidth() / 2),
                            //        (SCREEN_HEIGHT - gRestartTexture.getHeight() * 3 / 2 + 2));
                            gQuitTexture.render(
                                    (SCREEN_WIDTH * 2 / 3 - gQuitTexture.getWidth() / 2 - 1),
                                    (SCREEN_HEIGHT - gQuitTexture.getHeight() * 2 / 2));
                            //gQuitDetailTexture.render(
                            //        (SCREEN_WIDTH * 2 / 3 - gQuitTexture.getWidth() / 2),
                            //        (SCREEN_HEIGHT - gQuitTexture.getHeight() * 3 / 2 + 2));
                            switch(continu) {
                                case true:
                                    gArrowTexture.render(
                                            (SCREEN_WIDTH * 1 / 3 - gQuitTexture.getWidth() / 2) -
                                            gArrowTexture.getWidth() * 2,
                                            (SCREEN_HEIGHT - gRestartTexture.getHeight() * 2 / 2));
                                    break;
                                case false:
                                    gArrowTexture.render(
                                            (SCREEN_WIDTH * 2 / 3 - gQuitTexture.getWidth() / 2) -
                                            gArrowTexture.getWidth() * 2,
                                            (SCREEN_HEIGHT - gQuitTexture.getHeight() * 2 / 2));
                                    break;
                            };
                            break;
                    };

                    //Update screen
                    SDL_RenderPresent(gRenderer);

                    //Go to next frame
                    ++slowframe;
                    ++midframe;
                    ++fastframe;
                    ++longframe;

                    for (int i = 0; i < pulses; i++) {
                        ++pulseF[i];
                        pulseX[i] += 2;
                        --pulseY[i];
                    }

                    //Cycle animation
                    if (slowframe / 3 >= BG_ANIMATION_FRAMES) {
                        slowframe = 0;
                    }

                    //Cycle animation
                    for (int i = 0; i < pulses; i++) {
                        if (pulseF[i] / 8 >= PULSE_ANIMATION_FRAMES) {
                            pulseF[i] = 0;
                        }
                    }

                    if (midframe / 8 >= WALKING_ANIMATION_FRAMES) {
                        midframe = 0;
                        gStartTexture.setAlpha(255);
                        gStartDetailTexture.setAlpha(255);
                    }

                    //Cycle animation
                    if (fastframe / 16 >= FLASH_ANIMATION_FRAMES) {
                        fastframe = 0;
                        gStartTexture.setAlpha(0);
                        gStartDetailTexture.setAlpha(0);
                    }

                    //Cycle animation
                    for (int i = 0; i < pulses; i++) {
                        if (pulseX[i] > SCREEN_WIDTH || pulseY[i] + 15 < 0) {
                            longframe = 0;
                            pulseX[i] = 0;
                            pulseY[i] = randomNumber(0, 24) * 32 + 1;
                        }
                    }
                }
            }

            switch (current) {

                case 0:
                    std::cout << "Something's wrong" << std::endl;
                    break;

                case 1:
                    closeStart();
                    break;

                case 2:
                    closeEnd();
                    break;

            };
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}

