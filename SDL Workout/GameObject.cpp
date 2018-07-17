//
//  GameObject.cpp
//  SDL Workout
//
//  Created by Doğukan Avcı on 12/07/2018.
//  Copyright © 2018 dogukan avci. All rights reserved.
//

#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(std::string texture,int x,int y,int frame){
    xPos=x;
    frameTotal=frame;
    yPos=y;
    objTex=TextureManager::LoadTexture(texture);
}
GameObject::~GameObject(){
    
}
void GameObject::Update(){
    //xPos++;
    //yPos++;
    //h,w 128 for Sman
    srcRect.h=32;
    srcRect.w=32;
    srcRect.x=frameTotal*32;
    //srcRect.x=((xPos*32)%frameTotal);
    srcRect.y=0;
    
    desRec.x=xPos;
    desRec.y=yPos;
    desRec.w=srcRect.w*2;
    desRec.h=srcRect.h*2;
}
void GameObject::Render(){
    SDL_RenderCopy(Game::renderer, objTex, &srcRect, &desRec);
}
