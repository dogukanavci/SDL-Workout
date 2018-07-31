
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
std::vector <GameObject*> gameObjects;
int order=1;
int check=0; //0=no check,1=black checked,2=white checked
GameObject *selectedGameObject;

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
        (pawnb1=new GameObject("pawns.png",0,80,1,0));
        (pawnb2=new GameObject("pawns.png",80,80,1,0));
        (pawnb3=new GameObject("pawns.png",160,80,1,0));
        (pawnb4=new GameObject("pawns.png",240,80,1,0));
        (pawnb5=new GameObject("pawns.png",320,80,1,0));
        (pawnb6=new GameObject("pawns.png",400,80,1,0));
        (pawnb7=new GameObject("pawns.png",480,80,1,0));
        (pawnb8=new GameObject("pawns.png",560,80,1,0));
        (pawnw1=new GameObject("pawns.png",0,480,1,1));
        (pawnw2=new GameObject("pawns.png",80,480,1,1));
        (pawnw3=new GameObject("pawns.png",160,480,1,1));
        (pawnw4=new GameObject("pawns.png",240,480,1,1));
        (pawnw5=new GameObject("pawns.png",320,480,1,1));
        (pawnw6=new GameObject("pawns.png",400,480,1,1));
        (pawnw7=new GameObject("pawns.png",480,480,1,1));
        (pawnw8=new GameObject("pawns.png",560,480,1,1));
        (knightb1=new GameObject("Knights.png",80,0,2,0));
        (knightb2=new GameObject("Knights.png",480,0,2,0));
        (knightw1=new GameObject("Knights.png",80,560,2,1));
        (knightw2=new GameObject("Knights.png",480,560,2,1));
        (bishopb1=new GameObject("Bishops.png",160,0,3,0));
        (bishopb2=new GameObject("Bishops.png",400,0,3,0));
        (bishopw1=new GameObject("Bishops.png",160,560,3,1));
        (bishopw2=new GameObject("Bishops.png",400,560,3,1));
        (queenb=new GameObject("Queens.png",240,0,5,0));
        (queenw=new GameObject("Queens.png",240,560,5,1));
        (checkb=new GameObject("Checks.png",320,0,6,0));
        (checkw=new GameObject("Checks.png",320,560,6,1));
        (rockb1=new GameObject("Rocks.png",0,0,4,0));
        (rockb2=new GameObject("Rocks.png",560,0,4,0));
        (rockw1=new GameObject("Rocks.png",0,560,4,1));
        (rockw2=new GameObject("Rocks.png",560,560,4,1));
    gameObjects.push_back(pawnb1);
    gameObjects.push_back(pawnb2);
    gameObjects.push_back(pawnb3);
    gameObjects.push_back(pawnb4);
    gameObjects.push_back(pawnb5);
    gameObjects.push_back(pawnb6);
    gameObjects.push_back(pawnb7);
    gameObjects.push_back(pawnb8);
    gameObjects.push_back(pawnw1);
    gameObjects.push_back(pawnw2);
    gameObjects.push_back(pawnw3);
    gameObjects.push_back(pawnw4);
    gameObjects.push_back(pawnw5);
    gameObjects.push_back(pawnw6);
    gameObjects.push_back(pawnw7);
    gameObjects.push_back(pawnw8);
    gameObjects.push_back(knightb1);
    gameObjects.push_back(knightb2);
    gameObjects.push_back(knightw1);
    gameObjects.push_back(knightw2);
    gameObjects.push_back(bishopb1);
    gameObjects.push_back(bishopb2);
    gameObjects.push_back(bishopw1);
    gameObjects.push_back(bishopw2);
    gameObjects.push_back(rockb1);
    gameObjects.push_back(rockb2);
    gameObjects.push_back(rockw1);
    gameObjects.push_back(rockw2);
    gameObjects.push_back(queenb);
    gameObjects.push_back(queenw);
    gameObjects.push_back(checkb);
    gameObjects.push_back(checkw);
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
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button==SDL_BUTTON_LEFT){
                int k=-1;
                if(order==0 || order==1){
                for(int i=0;i<32;i++){
                    int x=gameObjects[i]->getX();
                    int y=gameObjects[i]->getY();
                    if(event.button.x/80==x/80 && event.button.y/80==y/80){
                        k=i;
                    }
                }
                    if (k==-1) {
                        break;
                    }
                    if(gameObjects[k]->getFT()==order){
                    int pieces[32][5];
                        for(int i=0;i<32;i++){
                            pieces[i][0]=gameObjects[i]->getX()/80;
                            pieces[i][1]=gameObjects[i]->getY()/80;
                            pieces[i][2]=gameObjects[i]->getFT();
                            pieces[i][3]=gameObjects[i]->getType();
                            pieces[i][4]=gameObjects[i]->getPlayed();
                        }
                    map->UpdateMap(gameObjects[k]->getType(), gameObjects[k]->getX()/80, gameObjects[k]->getY()/80,gameObjects[k]->getFT(),gameObjects[k]->getPlayed(),pieces);
                    selectedGameObject=gameObjects[k];
                    order=2;
                    }
                    
                }
                else if (order==2){
                    int control=0;
                    std::vector <int> zeros=map->getMap();
                    for(int ctr=0;ctr<zeros.size();ctr=ctr+2){
                        if(zeros.at(ctr)==event.button.x/80 && zeros.at(ctr+1)==event.button.y/80){
                            control=1;
                        }
                    }
                    if(map->getSquareTexValue(event.button.x/80, event.button.y/80)==3){
                        if(event.button.x/80==2)
                            control=2;
                        //long rook
                        else
                            control=3;
                        //short rook
                    }
                    for(int i=0;i<32;i++){
                        int x=gameObjects[i]->getX();
                        int y=gameObjects[i]->getY();
                        if(event.button.x/80==x/80 && event.button.y/80==y/80){
                            k=i;
                        }
                    }
                    if(k!=-1 && gameObjects[k]!=selectedGameObject && control==1){
                        gameObjects[k]->Dead();
                        gameObjects.erase(gameObjects.begin()+k);
                    }
                    if(control!=0){
                        if (control==2 && check==0) {
                            if(selectedGameObject->getFT()==0)
                                rockb1->UpdateCoordinates((event.button.x/80+1)*80, (event.button.y/80)*80);
                            else
                                rockw1->UpdateCoordinates((event.button.x/80+1)*80, (event.button.y/80)*80);
                        }
                        if (control==3 && check==0) {
                            if(selectedGameObject->getFT()==0)
                                rockb2->UpdateCoordinates((event.button.x/80-1)*80, (event.button.y/80)*80);
                            else
                                rockw2->UpdateCoordinates((event.button.x/80-1)*80, (event.button.y/80)*80);
                        }
                if (check==0) {
                selectedGameObject->UpdateCoordinates((event.button.x/80)*80,(event.button.y/80)*80);
                selectedGameObject->setPlayed();
                }
                else{
                    if(selectedGameObject->getFT()==0){
                        int x=selectedGameObject->getX();
                        int y=selectedGameObject->getY();
                        selectedGameObject->UpdateCoordinates((event.button.x/80)*80,(event.button.y/80)*80);
                        if (checkb->causesCheckThreat(checkb,gameObjects)==1) {
                            selectedGameObject->UpdateCoordinates((x/80)*80,(y/80)*80);
                            SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_INFORMATION,"Wrong move", "You are checked!", window);
                            order=selectedGameObject->getFT();
                            map->Reset();
                            break;
                        }
                        else{
                            selectedGameObject->setPlayed();
                            check=0;
                        }
                    }
                    if(selectedGameObject->getFT()==1){
                        int x=selectedGameObject->getX();
                        int y=selectedGameObject->getY();
                        selectedGameObject->UpdateCoordinates((event.button.x/80)*80,(event.button.y/80)*80);
                        if (checkw->causesCheckThreat(checkw,gameObjects)==2) {
                            selectedGameObject->UpdateCoordinates((x/80)*80,(y/80)*80);
                            SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_INFORMATION,"Wrong move", "You are checked!", window);
                            order=selectedGameObject->getFT();
                            map->Reset();
                            break;
                        }
                        else{
                            selectedGameObject->setPlayed();
                            check=0;
                        }
                    }
                }
                if(selectedGameObject->getFT()==0 && check==0){
                    check=checkw->causesCheckThreat(checkw,gameObjects);
                    std::cout<<"check state is "<<check<<std::endl;
                }
                else if(selectedGameObject->getFT()==1 && check==0){
                    check=checkb->causesCheckThreat(checkb,gameObjects);
                    std::cout<<"check state is "<<check<<std::endl;
                }
                map->Reset();
                order=(selectedGameObject->getFT()+1)%2;
                }
                if(gameObjects[k]==selectedGameObject){
                    order=selectedGameObject->getFT();
                    map->Reset();
                }
            }
        }
            break;
            
        default:
            break;
    }
}
void Game::update (){
    for(int i=0;i<gameObjects.size();i++){
        gameObjects[i]->Update();
    }
    
    //player->Update();
    //bear->Update();
    manager.update();
  /*  std::cout<< newPlayer.getComponent<PositionComponent>().x()<<" "<<newPlayer.getComponent<PositionComponent>().y()<<std::endl;*/
}
void Game::render(){
    SDL_RenderClear(renderer);
    map->DrawMap();
    for(int i=0;i<gameObjects.size();i++){
        gameObjects[i]->Render();
    }
    
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

