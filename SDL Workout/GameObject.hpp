//
//  GameObject.hpp
//  SDL Workout
//
//  Created by Doğukan Avcı on 12/07/2018.
//  Copyright © 2018 dogukan avci. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include "Game.hpp"

class GameObject{
public:
    GameObject(std::string texture,int x,int y,int frameTotal);
    ~GameObject();
    void Update();
    void Render();
private:
    int xPos;
    int yPos;
    int frameTotal;
    SDL_Texture *objTex;
    SDL_Rect srcRect,desRec;
};


#endif /* GameObject_hpp */
