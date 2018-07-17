#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.hpp"
using namespace std;
int getImage();

Game *game=nullptr;
int main(int argc, const char * argv[]) {
    game= new Game();
    const int FPS=60;
    const int frameDelay=1000/FPS;
    Uint32 frameStart;
    cout<<"chess game"<<endl;
    int frameTime;
    game->Init("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
    while (game->running()) {
        frameStart=SDL_GetTicks();
        
        game->handleEvents();
        game->update();
        game->render();
        
        frameTime=SDL_GetTicks()-frameStart;
        if(frameDelay>frameTime){
            SDL_Delay(frameDelay-frameTime);
        }
    }
    game->clean();
    return 0;
}


int getImage(){
    const int WIDTH=800;
    const int HEIGHT=600;
    SDL_Surface *imageSurface=NULL;
    SDL_Surface *windowSurface=NULL;
    
    if(SDL_Init( SDL_INIT_EVERYTHING)<0){
        cout<<"SDL could not be started"<<SDL_GetError()<<endl;
    }
    SDL_Window *window=SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    windowSurface=SDL_GetWindowSurface(window);
    
    if(window==NULL){
        cout<<"Could not open the window "<<endl;
        return EXIT_FAILURE;
    }
    if(!(IMG_Init(IMG_INIT_PNG) && IMG_INIT_PNG)){
        cout<<"could not initialize"<<IMG_GetError()<<endl;
        return 1;
    }
    SDL_Event windowEvent;
    imageSurface=IMG_Load("/Users/dogukanavci/Desktop/summerTraining/summerTraining/SDL Workout/Assets/SMan.png");
    if(imageSurface==NULL){
        cout<<"could not load image"<<SDL_GetError() <<endl;
    }
    
    while(true){
        if(SDL_PollEvent(&windowEvent)){
            if(SDL_QUIT==windowEvent.type){
                break;
            }
        }
        SDL_BlitSurface(imageSurface,NULL,windowSurface,NULL);
        SDL_UpdateWindowSurface(window);
    }
    SDL_FreeSurface(imageSurface);
    SDL_FreeSurface(windowSurface);
    imageSurface=NULL;
    windowSurface=NULL;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
