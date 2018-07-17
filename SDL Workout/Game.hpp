
#ifndef Game_hpp
#define Game_hpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
class Game{
public:
    Game();
    ~Game();
    void Init(const char *title,int x,int y,int width,int height,bool fullScreen);
    void handleEvents();
    void update ();
    void render();
    void clean();
    bool running();
    static SDL_Renderer *renderer;
private:
    bool isRunning;
    SDL_Window *window;
};


#endif /* Game_hpp */
