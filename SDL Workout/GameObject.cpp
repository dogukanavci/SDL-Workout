//
//  GameObject.cpp
//  SDL Workout
//
//  Created by Doğukan Avcı on 12/07/2018.
//  Copyright © 2018 dogukan avci. All rights reserved.
//

#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(std::string texture,int x,int y,int chessType,int frame){
    xPos=x;
    frameTotal=frame;
    type=chessType;
    yPos=y;
    played=false;
    objTex=TextureManager::LoadTexture(texture);
}
GameObject::~GameObject(){
    
}
void GameObject::UpdateCoordinates(int x,int y){
    xPos=x;
    yPos=y;
}
void GameObject::Update(){
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
int table[8][8]={
    {2,1,2,1,2,1,2,1},
    {1,2,1,2,1,2,1,2},
    {2,1,2,1,2,1,2,1},
    {1,2,1,2,1,2,1,2},
    {2,1,2,1,2,1,2,1},
    {1,2,1,2,1,2,1,2},
    {2,1,2,1,2,1,2,1},
    {1,2,1,2,1,2,1,2}
};
int GameObject::causesCheckThreat(GameObject* obj,std::vector <GameObject*> gameObjects){
    int pieceType=obj->type;
    int ctr=0;
    int fTotal=obj->frameTotal;
    int x=obj->xPos/80;
    int y=obj->yPos/80;
    for(int i=0;i<gameObjects.size();i++){
        GameObject* myObj=gameObjects[i];
        if(gameObjects[i]->type==6 && gameObjects[i]->frameTotal!=fTotal)
            continue;
        //pawn
        if(pieceType==1){
            if((((y+1)==gameObjects[i]->yPos/80 && (x+1)==gameObjects[i]->xPos/80)|| ((y+1)==gameObjects[i]->yPos/80 && (x-1)==gameObjects[i]->xPos/80)
                ||((y-1)==gameObjects[i]->yPos/80   && (x+1)==gameObjects[i]->xPos/80)|| ((y-1)==gameObjects[i]->yPos/80 && (x-1)==gameObjects[i]->xPos/80))
               && fTotal!=gameObjects[i]->frameTotal)
                table[gameObjects[i]->yPos/80][gameObjects[i]->xPos/80]=0;
            if((((y+1-fTotal*2)==gameObjects[i]->yPos/80)|| (y+2-fTotal*4)==gameObjects[i]->yPos/80) && (x)==gameObjects[i]->xPos/80)
                ctr=(gameObjects[i]->yPos/80-y)/(1-fTotal*2);
        }
        //knight
        if(pieceType==2 && gameObjects[i]->frameTotal==fTotal){
            if(ctr==0)
                ctr=1;
            if((y-2)==gameObjects[i]->yPos/80 && (x+1)==gameObjects[i]->xPos/80)
                ctr=ctr*2;
            if((y-2)==gameObjects[i]->yPos/80 && (x-1)==gameObjects[i]->xPos/80)
                ctr=ctr*3;
            if((y+2)==gameObjects[i]->yPos/80 && (x+1)==gameObjects[i]->xPos/80)
                ctr=ctr*5;
            if((y+2)==gameObjects[i]->yPos/80 && (x-1)==gameObjects[i]->xPos/80)
                ctr=ctr*7;
            if((y-1)==gameObjects[i]->yPos/80 && (x+2)==gameObjects[i]->xPos/80)
                ctr=ctr*11;
            if((y-1)==gameObjects[i]->yPos/80 && (x-2)==gameObjects[i]->xPos/80)
                ctr=ctr*13;
            if((y+1)==gameObjects[i]->yPos/80 && (x+2)==gameObjects[i]->xPos/80)
                ctr=ctr*17;
            if((y+1)==gameObjects[i]->yPos/80 && (x-2)==gameObjects[i]->xPos/80)
                ctr=ctr*19;
        }
        //bishop and partial queen
        if(pieceType==3 || pieceType==5){
            for(int cnt=8;cnt>0;cnt--){
                if((x+cnt)==gameObjects[i]->xPos/80 && (y+cnt)==gameObjects[i]->yPos/80 && ((ctr%512%64%8==0) || (ctr%512%64%8>cnt)) ){
                    ctr=(ctr-(ctr%512%64%8))+cnt;
                    if (gameObjects[i]->frameTotal!=fTotal) {
                        ctr=(ctr-(ctr%512%64%8))+cnt+1;
                    }
                }
                if((x+cnt)==gameObjects[i]->xPos/80 && (y-cnt)==gameObjects[i]->yPos/80 && ((((ctr%512%64)-ctr%512%64%8)==0) || (((ctr%512%64)-ctr%512%64%8)/8>cnt))){
                    ctr=(ctr-(ctr%512%64)+ctr%512%64%8)+cnt*8;
                    if (gameObjects[i]->frameTotal!=fTotal) {
                        ctr=(ctr-(ctr%512%64)+ctr%512%64%8)+(1+cnt)*8;
                    }
                }
                if((x-cnt)==gameObjects[i]->xPos/80 && (y+cnt)==gameObjects[i]->yPos/80 && ((((ctr%512)-ctr%512%64)==0) || (((ctr%512)-ctr%512%64)/64>cnt))){
                    ctr=(ctr-(ctr%512)+ctr%512%64)+cnt*64;
                    if (gameObjects[i]->frameTotal!=fTotal) {
                        ctr=(ctr-(ctr%512)+ctr%512%64)+(1+cnt)*64;
                    }
                }
                if((x-cnt)==gameObjects[i]->xPos/80 && (y-cnt)==gameObjects[i]->yPos/80 && (((ctr-ctr%512)==0) || ((ctr-ctr%512)/512>cnt)) ){
                    ctr=ctr%512+cnt*512;
                    if (gameObjects[i]->frameTotal!=fTotal) {
                        ctr=ctr%512+(1+cnt)*512;
                    }
                }
            }
        }
        //Rock
        if(pieceType==4){
            for(int cnt=8;cnt>0;cnt--){
                if((x+cnt)==gameObjects[i]->xPos/80 && (y)==gameObjects[i]->yPos/80 && ((ctr%512%64%8==0) || (ctr%512%64%8>cnt)) ){
                    ctr=(ctr-(ctr%512%64%8))+cnt;
                    if (gameObjects[i]->frameTotal!=fTotal) {
                        ctr=(ctr-(ctr%512%64%8))+cnt+1;
                    }
                }
                if((x-cnt)==gameObjects[i]->xPos/80 && (y)==gameObjects[i]->yPos/80 && ((((ctr%512%64)-ctr%512%64%8)==0) || (((ctr%512%64)-ctr%512%64%8)/8>cnt))){
                    ctr=(ctr-(ctr%512%64)+ctr%512%64%8)+cnt*8;
                    if (gameObjects[i]->frameTotal!=fTotal) {
                        ctr=(ctr-(ctr%512%64)+ctr%512%64%8)+(1+cnt)*8;
                    }
                }
                if((x)==gameObjects[i]->xPos/80 && (y+cnt)==gameObjects[i]->yPos/80 && ((((ctr%512)-ctr%512%64)==0) || (((ctr%512)-ctr%512%64)/64>cnt))){
                    ctr=(ctr-(ctr%512)+ctr%512%64)+cnt*64;
                    if (gameObjects[i]->frameTotal!=fTotal) {
                        ctr=(ctr-(ctr%512)+ctr%512%64)+(1+cnt)*64;
                    }
                }
                if((x)==gameObjects[i]->xPos/80 && (y-cnt)==gameObjects[i]->yPos/80 && (((ctr-ctr%512)==0) || ((ctr-ctr%512)/512>cnt)) ){
                    ctr=ctr%512+cnt*512;
                    if (gameObjects[i]->frameTotal!=fTotal) {
                        ctr=ctr%512+(1+cnt)*512;
                    }
                }
            }
        }
        //check
        if(pieceType==6){
            if(ctr==0)
                ctr=1;
            if(gameObjects[i]->frameTotal==fTotal){
                if((y)==gameObjects[i]->yPos/80 && (x+2)==gameObjects[i]->xPos/80)
                    ctr=ctr*23;
                if((y)==gameObjects[i]->yPos/80 && (x-2)==gameObjects[i]->xPos/80)
                    ctr=ctr*29;
                //for regular movement
                if((y+1)==gameObjects[i]->yPos/80 && (x+1)==gameObjects[i]->xPos/80)
                    ctr=ctr*2;
                if((y)==gameObjects[i]->yPos/80 && (x+1)==gameObjects[i]->xPos/80)
                    ctr=ctr*3;
                //also for rook
                if((y-1)==gameObjects[i]->yPos/80 && (x+1)==gameObjects[i]->xPos/80)
                    ctr=ctr*5;
                if((y+1)==gameObjects[i]->yPos/80 && (x)==gameObjects[i]->xPos/80)
                    ctr=ctr*7;
                if((y-1)==gameObjects[i]->yPos/80 && (x)==gameObjects[i]->xPos/80)
                    ctr=ctr*11;
                if((y+1)==gameObjects[i]->yPos/80 && (x-1)==gameObjects[i]->xPos/80)
                    ctr=ctr*13;
                if((y)==gameObjects[i]->yPos/80 && (x-1)==gameObjects[i]->xPos/80)
                    ctr=ctr*17;
                //also for rook
                if((y-1)==gameObjects[i]->yPos/80 && (x-1)==gameObjects[i]->xPos/80)
                    ctr=ctr*19;
            }
            else{
                if(gameObjects[i]->type!=1){
                    gameObjects[i]->causesCheckThreat(gameObjects[i],gameObjects);
                }
                else{
                    if (gameObjects[i]->xPos/80>0 &&  gameObjects[i]->xPos/80<9 && gameObjects[i]->yPos/80+2*fTotal>0 && gameObjects[i]->yPos/80+2*fTotal<9) {
                        table[gameObjects[i]->yPos/80-1+2*fTotal][gameObjects[i]->xPos/80-1]=0;
                    }
                    if (gameObjects[i]->xPos/80>-2 &&  gameObjects[i]->xPos/80<7 && gameObjects[i]->yPos/80+2*fTotal>0 && gameObjects[i]->yPos/80+2*fTotal<9) {
                        table[gameObjects[i]->yPos/80-1+2*fTotal][gameObjects[i]->xPos/80+1]=0;
                    }
                }
            }
            
        }
        
    }
    //pawn
    if(pieceType==1){
        if (fTotal==0) {
            if(ctr!=1){
                table[y+1][x]=0;
                if(y==1 && ctr!=2)
                    table[y+2][x]=0;
            }
        }
        if (fTotal==1) {
            if(ctr!=1){
                table[y-1][x]=0;
                if(y==6 && ctr!=2)
                    table[y-2][x]=0;
            }
        }
    }
    //knight
    else if(pieceType==2){
        double ctrD=(double) ctr;
        if((y-1)>-1 &&  (y-1)<8){
            if((x+2)>-1 && (x+2)<8 && (fmod(ctrD/11,1.0)!=0))
                table[y-1][x+2]=0;
            if((x-2)>-1 && (x-2)<8 && (fmod(ctrD/13,1.0)!=0))
                table[y-1][x-2]=0;
        }
        if((y+1)>-1 &&  (y+1)<8){
            if((x+2)>-1 && (x+2)<8 && (fmod(ctrD/17,1.0)!=0))
                table[y+1][x+2]=0;
            if((x-2)>-1 && (x-2)<8 && (fmod(ctrD/19,1.0)!=0))
                table[y+1][x-2]=0;
        }
        if((y-2)>-1 &&  (y-2)<8){
            if((x+1)>-1 && (x+1)<8 && (fmod(ctrD/2,1.0)!=0))
                table[y-2][x+1]=0;
            if((x-1)>-1 && (x-1)<8 && (fmod(ctrD/3,1.0)!=0))
                table[y-2][x-1]=0;
        }
        if((y+2)>-1 &&  (y+2)<8){
            if((x+1)>-1 && (x+1)<8 && (fmod(ctrD/5,1.0)!=0))
                table[y+2][x+1]=0;
            if((x-1)>-1 && (x-1)<8 && (fmod(ctrD/7,1.0)!=0))
                table[y+2][x-1]=0;
        }
    }
    
    //bishop
    else if(pieceType==3){
        for(int i=1;i<9;i++){
            if(x+i>-1 && x+i<8 && y+i>-1 && y+i<8 && ((i<ctr%512%64%8) || 0==ctr%512%64%8))
                table[y+i][x+i]=0;
            if(x+i>-1 && x+i<8 && y-i>-1 && y-i<8 && ((i<((ctr%512%64)-ctr%512%64%8)/8)|| (((ctr%512%64)-ctr%512%64%8)/8)==0))
                table[y-i][x+i]=0;
            if(x-i>-1 && x-i<8 && y+i>-1 && y+i<8 && ((i<((ctr%512)-ctr%512%64)/64)|| (((ctr%512)-ctr%512%64)/64)==0))
                table[y+i][x-i]=0;
            if(x-i>-1 && x-i<8 && y-i>-1 && y-i<8 && ((i<((ctr-ctr%512))/512)|| (((ctr-ctr%512))/512)==0))
                table[y-i][x-i]=0;
        }
    }
    
    //rock
    else if(pieceType==4){
        for(int i=1;i<9;i++){
            if(x+i>-1 && x+i<8 && ((i<ctr%512%64%8) || 0==ctr%512%64%8))
                table[y][x+i]=0;
            if(x-i>-1 && x-i<8 && ((i<((ctr%512%64)-ctr%512%64%8)/8)|| (((ctr%512%64)-ctr%512%64%8)/8)==0))
                table[y][x-i]=0;
            if(y+i>-1 && y+i<8 && ((i<((ctr%512)-ctr%512%64)/64)|| (((ctr%512)-ctr%512%64)/64)==0))
                table[y+i][x]=0;
            if(y-i>-1 && y-i<8 && ((i<((ctr-ctr%512))/512)|| (((ctr-ctr%512))/512)==0))
                table[y-i][x]=0;
        }
    }
    
    //queen
    else if(pieceType==5){
        for(int i=1;i<9;i++){
            if(x+i>-1 && x+i<8 && y+i>-1 && y+i<8 && ((i<ctr%512%64%8) || 0==ctr%512%64%8))
                table[y+i][x+i]=0;
            if(x+i>-1 && x+i<8 && y-i>-1 && y-i<8 && ((i<((ctr%512%64)-ctr%512%64%8)/8)|| (((ctr%512%64)-ctr%512%64%8)/8)==0))
                table[y-i][x+i]=0;
            if(x-i>-1 && x-i<8 && y+i>-1 && y+i<8 && ((i<((ctr%512)-ctr%512%64)/64)|| (((ctr%512)-ctr%512%64)/64)==0))
                table[y+i][x-i]=0;
            if(x-i>-1 && x-i<8 && y-i>-1 && y-i<8 && ((i<((ctr-ctr%512))/512)|| (((ctr-ctr%512))/512)==0))
                table[y-i][x-i]=0;
        }
        ctr=0;
        for (int i=0; i<gameObjects.size(); i++) {
            //if(gameObjects[i]->type==6 && gameObjects[i]->frameTotal!=fTotal)
                //continue;
            for(int cnt=8;cnt>0;cnt--){
                if((x+cnt)==gameObjects[i]->xPos/80 && (y)==gameObjects[i]->yPos/80 && ((ctr%512%64%8==0) || (ctr%512%64%8>cnt)) ){
                    ctr=(ctr-(ctr%512%64%8))+cnt;
                    if (gameObjects[i]->frameTotal!=fTotal) {
                        ctr=(ctr-(ctr%512%64%8))+cnt+1;
                    }
                }
                if((x-cnt)==gameObjects[i]->xPos/80 && (y)==gameObjects[i]->yPos/80 && ((((ctr%512%64)-ctr%512%64%8)==0) || (((ctr%512%64)-ctr%512%64%8)/8>cnt))){
                    ctr=(ctr-(ctr%512%64)+ctr%512%64%8)+cnt*8;
                    if (gameObjects[i]->frameTotal!=fTotal) {
                        ctr=(ctr-(ctr%512%64)+ctr%512%64%8)+(1+cnt)*8;
                    }
                }
                if((x)==gameObjects[i]->xPos/80 && (y+cnt)==gameObjects[i]->yPos/80 && ((((ctr%512)-ctr%512%64)==0) || (((ctr%512)-ctr%512%64)/64>cnt))){
                    ctr=(ctr-(ctr%512)+ctr%512%64)+cnt*64;
                    if (gameObjects[i]->frameTotal!=fTotal) {
                        ctr=(ctr-(ctr%512)+ctr%512%64)+(1+cnt)*64;
                    }
                }
                if((x)==gameObjects[i]->xPos/80 && (y-cnt)==gameObjects[i]->yPos/80 && (((ctr-ctr%512)==0) || ((ctr-ctr%512)/512>cnt)) ){
                    ctr=ctr%512+cnt*512;
                    if (gameObjects[i]->frameTotal!=fTotal) {
                        ctr=ctr%512+(1+cnt)*512;
                    }
                }
            }
        }
        for(int i=1;i<9;i++){
            if(x+i>-1 && x+i<8 && ((i<ctr%512%64%8) || 0==ctr%512%64%8))
                table[y][x+i]=0;
            if(x-i>-1 && x-i<8 && ((i<((ctr%512%64)-ctr%512%64%8)/8)|| (((ctr%512%64)-ctr%512%64%8)/8)==0))
                table[y][x-i]=0;
            if(y+i>-1 && y+i<8 && ((i<((ctr%512)-ctr%512%64)/64)|| (((ctr%512)-ctr%512%64)/64)==0))
                table[y+i][x]=0;
            if(y-i>-1 && y-i<8 && ((i<((ctr-ctr%512))/512)|| (((ctr-ctr%512))/512)==0))
                table[y-i][x]=0;
        }
    }
    
    //check
    else if(pieceType==6){
        double ctrD=(double) ctr;
        if(x-1>-1 && x-1<8){
            if(y-1>-1 && y-1<8 ){
                if((fmod(ctrD/19,1.0)!=0))
                    table[y-1][x-1]=0;
            }
            if(y>-1 && y<8 ){
                if((fmod(ctrD/17,1.0)!=0))
                    table[y][x-1]=0;
            }
            if(y+1>-1 && y+1<8 ){
                if((fmod(ctrD/13,1.0)!=0))
                    table[y+1][x-1]=0;
            }
        }
        if(x>-1 && x<8){
            if(y-1>-1 && y-1<8 ){
                if((fmod(ctrD/11,1.0)!=0))
                    table[y-1][x]=0;
            }
            if(y+1>-1 && y+1<8 ){
                if((fmod(ctrD/7,1.0)!=0))
                    table[y+1][x]=0;
            }
        }
        if(x+1>-1 && x+1<8){
            if(y-1>-1 && y-1<8){
                if((fmod(ctrD/5,1.0)!=0))
                    table[y-1][x+1]=0;
            }
            if(y>-1 && y<8 ){
                if((fmod(ctrD/3,1.0)!=0))
                    table[y][x+1]=0;
            }
            if(y+1>-1 && y+1<8 ){
                if((fmod(ctrD/2,1.0)!=0))
                    table[y+1][x+1]=0;
            }
        }
    }
    if(table[y][x]==0){
        if(pieceType==6){
            for(int i=0;i<8;i++){
                for(int ctr=0;ctr<8;ctr++){
                    table[i][ctr]=((ctr+((i+1)%2))%2+1);
                }
            }
        }
        if(fTotal==0){
            return 1;
        }
        else if(fTotal==1){
            return 2;
        }
        else{
            return 0;
        }
    }
    else{
        if(pieceType==6){
            for(int i=0;i<8;i++){
                for(int ctr=0;ctr<8;ctr++){
                    table[i][ctr]=((ctr+((i+1)%2))%2+1);
                }
            }
        }
        return 0;
    }
}
