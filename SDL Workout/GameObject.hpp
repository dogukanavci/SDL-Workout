//
//  GameObject.hpp
//  SDL Workout
//
//  Created by Doğukan Avcı on 12/07/2018.
//  Copyright © 2018 dogukan avci. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <iostream>
#include <vector>
#include "Game.hpp"
#include "Map.hpp"

class GameObject{
private:
    int xPos;
    int yPos;
    // type 1=pawn,2=knight,3=bishop,4=rock,5=queen,6=check,7=eatenblack,8=eatenwhite
    int type;
    int frameTotal;
    SDL_Texture *objTex;
    SDL_Rect srcRect,desRec;
    bool played;
public:
    GameObject(std::string texture,int x,int y,int chessType,int frameTotal);
    ~GameObject();
    void UpdateCoordinates(int x,int y);
    void Update();
    void Render();
    std::vector <GameObject*> findPieceType(int type);
    void Dead(){type=7+frameTotal;}
    void setType(int chessType) { type=chessType;}
    int getFT() {return frameTotal;}
    int getX() {return xPos;}
    int getType() {return type;}
    bool getPlayed() {return played;}
    void setPlayed() {played=true;}
    int getY() {return yPos;}
    int causesCheckThreat(GameObject* obj,std::vector <GameObject*> gameObjects);
};


#endif /* GameObject_hpp */
