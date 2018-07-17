
#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "Ecs.hpp"
#include "Components.hpp"

//GameObject *player;
//GameObject *bear;
GameObject *pawnw1;
GameObject *pawnw2;
GameObject *pawnw3;
GameObject *pawnw4;
GameObject *pawnw5;
GameObject *pawnw6;
GameObject *pawnw7;
GameObject *pawnw8;
GameObject *pawnb1;
GameObject *pawnb2;
GameObject *pawnb3;
GameObject *pawnb4;
GameObject *pawnb5;
GameObject *pawnb6;
GameObject *pawnb7;
GameObject *pawnb8;
GameObject *knightw1;
GameObject *knightw2;
GameObject *knightb1;
GameObject *knightb2;
GameObject *bishopw1;
GameObject *bishopw2;
GameObject *bishopb1;
GameObject *bishopb2;
GameObject *queenw;
GameObject *queenb;
GameObject *checkw;
GameObject *checkb;
GameObject *rockb1;
GameObject *rockb2;
GameObject *rockw1;
GameObject *rockw2;


Map *map;
SDL_Renderer* Game::renderer=nullptr;

Manager manager;
auto& newPlayer(manager.addEntity());

Game::Game(){
    
}

Game::~Game(){
    
}
void Game::Init(const char *title,int x,int y,int width,int height,bool fullScreen){
    int flags=0;
    if(fullScreen){
        flags=SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING)==0) {
        window=SDL_CreateWindow(title, x, y, width, height, flags);
        if(window){
            std::cout<<"Successfully created window"<<std::endl;
        }
        renderer=SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout<<"Successfully created renderer"<<std::endl;
        }
        isRunning=true;
    }
    else{
        isRunning=false;
    }
    
    pawnb1=new GameObject("pawns.png",0,80,0);
    pawnb2=new GameObject("pawns.png",80,80,0);
    pawnb3=new GameObject("pawns.png",160,80,0);
    pawnb4=new GameObject("pawns.png",240,80,0);
    pawnb5=new GameObject("pawns.png",320,80,0);
    pawnb6=new GameObject("pawns.png",400,80,0);
    pawnb7=new GameObject("pawns.png",480,80,0);
    pawnb8=new GameObject("pawns.png",560,80,0);
    pawnw1=new GameObject("pawns.png",0,480,1);
    pawnw2=new GameObject("pawns.png",80,480,1);
    pawnw3=new GameObject("pawns.png",160,480,1);
    pawnw4=new GameObject("pawns.png",240,480,1);
    pawnw5=new GameObject("pawns.png",320,480,1);
    pawnw6=new GameObject("pawns.png",400,480,1);
    pawnw7=new GameObject("pawns.png",480,480,1);
    pawnw8=new GameObject("pawns.png",560,480,1);
    knightb1=new GameObject("Knights.png",80,0,0);
    knightb2=new GameObject("Knights.png",480,0,0);
    knightw1=new GameObject("Knights.png",80,560,1);
    knightw2=new GameObject("Knights.png",480,560,1);
    bishopb1=new GameObject("Bishops.png",160,0,0);
    bishopb2=new GameObject("Bishops.png",400,0,0);
    bishopw1=new GameObject("Bishops.png",160,560,1);
    bishopw2=new GameObject("Bishops.png",400,560,1);
    queenb=new GameObject("Queens.png",320,0,0);
    queenw=new GameObject("Queens.png",320,560,1);
    checkb=new GameObject("Checks.png",240,0,0);
    checkw=new GameObject("Checks.png",240,560,1);
    rockb1=new GameObject("Rocks.png",0,0,0);
    rockb2=new GameObject("Rocks.png",560,0,0);
    rockw1=new GameObject("Rocks.png",0,560,1);
    rockw2=new GameObject("Rocks.png",560,560,1);
    
    //player=new GameObject("player.png",0,0,1);
    //bear=new GameObject("bear.png",60,30,1184);
    map=new Map();
    
    //newPlayer.addComponent<PositionComponent>();
    //newPlayer.getComponent<PositionComponent>().setPos(500, 500);
}
void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning=false;
            break;
            
        default:
            break;
    }
}
void Game::update (){
    pawnb1->Update();
    pawnb2->Update();
    pawnb3->Update();
    pawnb4->Update();
    pawnb5->Update();
    pawnb6->Update();
    pawnb7->Update();
    pawnb8->Update();
    pawnw1->Update();
    pawnw2->Update();
    pawnw3->Update();
    pawnw4->Update();
    pawnw5->Update();
    pawnw6->Update();
    pawnw7->Update();
    pawnw8->Update();
    knightb1->Update();
    knightb2->Update();
    knightw1->Update();
    knightw2->Update();
    bishopb1->Update();
    bishopb2->Update();
    bishopw1->Update();
    bishopw2->Update();
    queenb->Update();
    queenw->Update();
    checkb->Update();
    checkw->Update();
    rockb1->Update();
    rockb2->Update();
    rockw1->Update();
    rockw2->Update();
    //player->Update();
    //bear->Update();
    manager.update();
  /*  std::cout<< newPlayer.getComponent<PositionComponent>().x()<<" "<<newPlayer.getComponent<PositionComponent>().y()<<std::endl;*/
}
void Game::render(){
    SDL_RenderClear(renderer);
    map->DrawMap();
    
    pawnb1->Render();
    pawnb2->Render();
    pawnb3->Render();
    pawnb4->Render();
    pawnb5->Render();
    pawnb6->Render();
    pawnb7->Render();
    pawnb8->Render();
    pawnw1->Render();
    pawnw2->Render();
    pawnw3->Render();
    pawnw4->Render();
    pawnw5->Render();
    pawnw6->Render();
    pawnw7->Render();
    pawnw8->Render();
    knightb1->Render();
    knightb2->Render();
    knightw1->Render();
    knightw2->Render();
    bishopb1->Render();
    bishopb2->Render();
    bishopw1->Render();
    bishopw2->Render();
    queenb->Render();
    queenw->Render();
    checkb->Render();
    checkw->Render();
    rockb1->Render();
    rockb2->Render();
    rockw1->Render();
    rockw2->Render();
    //player->Render();
    //bear->Render();
    SDL_RenderPresent(renderer);
}
void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout<<"Cleared the game"<<std::endl;
}
bool Game::running(){
    
    return isRunning;
}

