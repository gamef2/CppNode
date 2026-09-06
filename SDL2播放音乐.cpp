#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<string>
#include<vector>
#include<iostream>

using namespace std;

const int Width=640,Height=480;
const int Button_Width=300,Button_Height=200,Total_Button=4;
SDL_Window* gWindow;
SDL_Renderer* gRenderer;
SDL_Texture* gTexture;

SDL_Rect gSprintClips[Total_Button];

Mix_Music* gMusic;
Mix_Chunk* gChunk[Total_Button];

void LoadImg(const string& str)
{
    SDL_Surface* loadedSurface=IMG_Load(str.c_str());
    SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0,255,255));
    gTexture=SDL_CreateTextureFromSurface(gRenderer,loadedSurface);
    SDL_FreeSurface(loadedSurface);
}
int main(int argc,char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
    gWindow=SDL_CreateWindow("SDL Tutorial",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,Width,Height,SDL_WINDOW_SHOWN);

    gRenderer=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(gRenderer,255,255,255,255);

    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);

    LoadImg("button.png");

    /* 设置精灵与音乐 */

    vector<string> MusicName= {"up.wav","down.wav","left.wav","right.wav"};
    for(int i=0; i<Total_Button; ++i)
    {
        gSprintClips[i]= {0,i*200,Button_Width,Button_Height};
        gChunk[i]=Mix_LoadWAV(MusicName[i].c_str());
    }
    gMusic=Mix_LoadMUS("music.wav");
    vector<SDL_Point> mPosition{{0,0},{Width-Button_Width,0},
        {0,Height-Button_Height},{Width-Button_Width,Height-Button_Height}};


    bool quit=false;
    SDL_Event e;

    int mCurSprite[Total_Button]= {0};

    while(!quit)
    {
        int Music_Cnt=0;
        while(SDL_PollEvent(&e))
        {

            if(e.type==SDL_QUIT||
                    (e.type==SDL_KEYDOWN&&e.key.keysym.sym==SDLK_ESCAPE))
                quit=true;
            else if(e.type==SDL_MOUSEMOTION||e.type==SDL_MOUSEBUTTONDOWN||e.type==SDL_MOUSEBUTTONUP)
            {
                int x,y;
                SDL_GetMouseState(&x,&y);
                for(int i=0; i<Total_Button; ++i)
                {
                    if(x<mPosition[i].x||x>mPosition[i].x+gSprintClips[i].w||
                            y<mPosition[i].y||y>mPosition[i].y+gSprintClips[i].h)
                    {
                        mCurSprite[i]=0;
                        if(e.type==SDL_MOUSEBUTTONDOWN)
                            Music_Cnt++;
                    }
                    else
                    {
                        switch(e.type)
                        {
                        case SDL_MOUSEMOTION:
                            mCurSprite[i]=1;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            mCurSprite[i]=2;
                            break;
                        case SDL_MOUSEBUTTONUP:
                            mCurSprite[i]=3;
                            break;
                        }
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(gRenderer,255,0,255,255);
        SDL_RenderClear(gRenderer);
        bool playMusic=false;
        for(int i=0; i<Total_Button; ++i)
        {
            SDL_Rect Clips= {gSprintClips[mCurSprite[i]].x,gSprintClips[mCurSprite[i]].y,
                             Button_Width,Button_Height
                            };

            SDL_Rect renderQuad= {mPosition[i].x,mPosition[i].y,Button_Width,Button_Height};

            SDL_RenderCopyEx(gRenderer,gTexture,&Clips,&renderQuad,0,&mPosition[i],SDL_FLIP_NONE);
            if(mCurSprite[i]==2)
            {
                Mix_HaltChannel(0);
                Mix_PlayChannel(-1,gChunk[i],0);
                playMusic=true;
            }
        }
        if(Music_Cnt==Total_Button)
        {
            if(Mix_PlayingMusic()==0)
                Mix_PlayMusic(gMusic,-1);
            else
            {
                if(Mix_PausedMusic()==1)
                    Mix_ResumeMusic();
                else
                {
                    Mix_PauseMusic();
                }
            }
            Music_Cnt=0;
        }
        SDL_RenderPresent(gRenderer);
    }

    SDL_DestroyTexture(gTexture);
    for(int i=0; i<Total_Button; ++i)
        Mix_FreeChunk(gChunk[i]);

    Mix_FreeMusic(gMusic);

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
