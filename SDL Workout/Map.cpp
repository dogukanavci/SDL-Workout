//
//  Map.cpp
//  SDL Workout
//
//  Created by Doğukan Avcı on 12/07/2018.
//  Copyright © 2018 dogukan avci. All rights reserved.
//

#include "Map.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"

/*int level1[20][25]={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,2,1,2,1,2,1,2,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,2,1,2,1,2,1,2,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,2,1,2,1,2,1,2,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,2,1,2,1,2,1,2,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,2,1,2,1,2,1,2,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,2,1,2,1,2,1,2,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,2,1,2,1,2,1,2,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,2,1,2,1,2,1,2,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};*/
int level1[8][8]={
    {2,1,2,1,2,1,2,1},
    {1,2,1,2,1,2,1,2},
    {2,1,2,1,2,1,2,1},
   {1,2,1,2,1,2,1,2},
    {2,1,2,1,2,1,2,1},
    {1,2,1,2,1,2,1,2},
    {2,1,2,1,2,1,2,1},
    {1,2,1,2,1,2,1,2}
};

Map::Map(){
    dirt=TextureManager::LoadTexture("dirt.png");
    grass=TextureManager::LoadTexture("grass.png");
    water=TextureManager::LoadTexture("water.png");
    square1=TextureManager::LoadTexture("square1.png");
    square2=TextureManager::LoadTexture("Square3.png");
    LoadMap(level1);
    srcR.x=0;
    srcR.y=0;
    desR.x=0;
    desR.y=0;
    srcR.h=desR.h=80;
    srcR.w=desR.w=80;
}

void Map::LoadMap(int mapMake[8][8]){
    for(int i=0;i<8;i++){
        for(int ctr=0;ctr<8;ctr++){
            map[i][ctr]=mapMake[i][ctr];
        }
    }
}
void Map::DrawMap(){
    int type=0;
    for(int i=0;i<8;i++){
        for(int ctr=0;ctr<8;ctr++){
            type=map[i][ctr];
            desR.x=ctr*80;
            desR.y=i*80;
            switch (type) {
                case 0:
                    TextureManager::Draw(water, srcR, desR);
                    break;
                case 1:
                    TextureManager::Draw(square1, srcR, desR);
                    break;
                case 2:
                    TextureManager::Draw(square2, srcR, desR);
                    break;
                default:
                    break;
            }
        }
    }
}
void Map::Reset(){
    for(int i=0;i<8;i++){
        for(int ctr=0;ctr<8;ctr++){
            level1[i][ctr]=((ctr+((i+1)%2))%2+1);
        }
    }
    LoadMap(level1);
    DrawMap();
}
void  Map::UpdateMap(int pieceType, int x,int y,int fTotal,int pieces[32][4]){
    int ctr=0;
    int danger=0;
    //ctr 1= 1 move blocked pawn,2= 2 move blocked pawn,3-10=blocked knight
    for (int i=0; i<32; i++) {
        //pawn
        if(pieceType==1){
            if((((y+1)==pieces[i][1] && (x+1)==pieces[i][0])|| ((y+1)==pieces[i][1] && (x-1)==pieces[i][0])
            ||((y-1)==pieces[i][1]   && (x+1)==pieces[i][0])|| ((y-1)==pieces[i][1] && (x-1)==pieces[i][0]))
            && fTotal!=pieces[i][2])
            level1[pieces[i][1]][pieces[i][0]]=0;
            if((((y+1-fTotal*2)==pieces[i][1])|| (y+2-fTotal*4)==pieces[i][1]) && (x)==pieces[i][0])
            ctr=(pieces[i][1]-y)/(1-fTotal*2);
        }
        //knight
        if(pieceType==2 && pieces[i][2]==fTotal){
            if(ctr==0)
                ctr=1;
            if((y-2)==pieces[i][1] && (x+1)==pieces[i][0])
                ctr=ctr*2;
            if((y-2)==pieces[i][1] && (x-1)==pieces[i][0])
                ctr=ctr*3;
            if((y+2)==pieces[i][1] && (x+1)==pieces[i][0])
                ctr=ctr*5;
            if((y+2)==pieces[i][1] && (x-1)==pieces[i][0])
                ctr=ctr*7;
            if((y-1)==pieces[i][1] && (x+2)==pieces[i][0])
                ctr=ctr*11;
            if((y-1)==pieces[i][1] && (x-2)==pieces[i][0])
                ctr=ctr*13;
            if((y+1)==pieces[i][1] && (x+2)==pieces[i][0])
                ctr=ctr*17;
            if((y+1)==pieces[i][1] && (x-2)==pieces[i][0])
                ctr=ctr*19;
        }
        //bishop and partial queen
        if(pieceType==3 || pieceType==5){
            for(int cnt=8;cnt>0;cnt--){
                if((x+cnt)==pieces[i][0] && (y+cnt)==pieces[i][1] && ((ctr%512%64%8==0) || (ctr%512%64%8>cnt)) ){
                    ctr=(ctr-(ctr%512%64%8))+cnt;
                    if (pieces[i][2]!=fTotal) {
                        ctr=(ctr-(ctr%512%64%8))+cnt+1;
                    }
                }
                if((x+cnt)==pieces[i][0] && (y-cnt)==pieces[i][1] && ((((ctr%512%64)-ctr%512%64%8)==0) || (((ctr%512%64)-ctr%512%64%8)/8>cnt))){
                    ctr=(ctr-(ctr%512%64)+ctr%512%64%8)+cnt*8;
                    if (pieces[i][2]!=fTotal) {
                        ctr=(ctr-(ctr%512%64)+ctr%512%64%8)+(1+cnt)*8;
                    }
                }
                if((x-cnt)==pieces[i][0] && (y+cnt)==pieces[i][1] && ((((ctr%512)-ctr%512%64)==0) || (((ctr%512)-ctr%512%64)/64>cnt))){
                    ctr=(ctr-(ctr%512)+ctr%512%64)+cnt*64;
                    if (pieces[i][2]!=fTotal) {
                        ctr=(ctr-(ctr%512)+ctr%512%64)+(1+cnt)*64;
                    }
                }
                if((x-cnt)==pieces[i][0] && (y-cnt)==pieces[i][1] && (((ctr-ctr%512)==0) || ((ctr-ctr%512)/512>cnt)) ){
                    ctr=ctr%512+cnt*512;
                    if (pieces[i][2]!=fTotal) {
                        ctr=ctr%512+(1+cnt)*512;
                    }
                }
            }
        }
        //Rock
        if(pieceType==4){
            for(int cnt=8;cnt>0;cnt--){
                if((x+cnt)==pieces[i][0] && (y)==pieces[i][1] && ((ctr%512%64%8==0) || (ctr%512%64%8>cnt)) ){
                    ctr=(ctr-(ctr%512%64%8))+cnt;
                    if (pieces[i][2]!=fTotal) {
                        ctr=(ctr-(ctr%512%64%8))+cnt+1;
                    }
                }
                if((x-cnt)==pieces[i][0] && (y)==pieces[i][1] && ((((ctr%512%64)-ctr%512%64%8)==0) || (((ctr%512%64)-ctr%512%64%8)/8>cnt))){
                    ctr=(ctr-(ctr%512%64)+ctr%512%64%8)+cnt*8;
                    if (pieces[i][2]!=fTotal) {
                        ctr=(ctr-(ctr%512%64)+ctr%512%64%8)+(1+cnt)*8;
                    }
                }
                if((x)==pieces[i][0] && (y+cnt)==pieces[i][1] && ((((ctr%512)-ctr%512%64)==0) || (((ctr%512)-ctr%512%64)/64>cnt))){
                    ctr=(ctr-(ctr%512)+ctr%512%64)+cnt*64;
                    if (pieces[i][2]!=fTotal) {
                        ctr=(ctr-(ctr%512)+ctr%512%64)+(1+cnt)*64;
                    }
                }
                if((x)==pieces[i][0] && (y-cnt)==pieces[i][1] && (((ctr-ctr%512)==0) || ((ctr-ctr%512)/512>cnt)) ){
                    ctr=ctr%512+cnt*512;
                    if (pieces[i][2]!=fTotal) {
                        ctr=ctr%512+(1+cnt)*512;
                    }
                }
            }
        }
        //check
        if(pieceType==6){
            if(pieces[i][2]==fTotal){
            if(ctr==0)
                ctr=1;
            if((y+1)==pieces[i][1] && (x+1)==pieces[i][0])
                ctr=ctr*2;
            if((y)==pieces[i][1] && (x+1)==pieces[i][0])
                ctr=ctr*3;
            if((y-1)==pieces[i][1] && (x+1)==pieces[i][0])
                ctr=ctr*5;
            if((y+1)==pieces[i][1] && (x)==pieces[i][0])
                ctr=ctr*7;
            if((y-1)==pieces[i][1] && (x)==pieces[i][0])
                ctr=ctr*11;
            if((y+1)==pieces[i][1] && (x-1)==pieces[i][0])
                ctr=ctr*13;
            if((y)==pieces[i][1] && (x-1)==pieces[i][0])
                ctr=ctr*17;
            if((y-1)==pieces[i][1] && (x-1)==pieces[i][0])
                ctr=ctr*19;
            }
            else{
                for(int cnt=0;cnt<8;cnt++){
                   // if((y+1+cnt)==pieces[i][1] && (x+1+cnt)==pieces[i][0] && (pieces[i][3]==3 || pieces[i][3]==5) && )
                }
            }
            
        }

    }
    //pawn
    if(pieceType==1){
        if (fTotal==0) {
            if(ctr!=1){
            level1[y+1][x]=0;
            if(y==1 && ctr!=2)
                level1[y+2][x]=0;
            }
        }
        if (fTotal==1) {
            if(ctr!=1){
            level1[y-1][x]=0;
            if(y==6 && ctr!=2)
                level1[y-2][x]=0;
            }
        }
    }
    //knight
    else if(pieceType==2){
        double ctrD=(double) ctr;
        if((y-1)>-1 &&  (y-1)<8){
            if((x+2)>-1 && (x+2)<8 && (fmod(ctrD/11,1.0)!=0))
                level1[y-1][x+2]=0;
            if((x-2)>-1 && (x-2)<8 && (fmod(ctrD/13,1.0)!=0))
                level1[y-1][x-2]=0;
        }
        if((y+1)>-1 &&  (y+1)<8){
            if((x+2)>-1 && (x+2)<8 && (fmod(ctrD/17,1.0)!=0))
                level1[y+1][x+2]=0;
            if((x-2)>-1 && (x-2)<8 && (fmod(ctrD/19,1.0)!=0))
                level1[y+1][x-2]=0;
        }
        if((y-2)>-1 &&  (y-2)<8){
            if((x+1)>-1 && (x+1)<8 && (fmod(ctrD/2,1.0)!=0))
                level1[y-2][x+1]=0;
            if((x-1)>-1 && (x-1)<8 && (fmod(ctrD/3,1.0)!=0))
                level1[y-2][x-1]=0;
        }
        if((y+2)>-1 &&  (y+2)<8){
            if((x+1)>-1 && (x+1)<8 && (fmod(ctrD/5,1.0)!=0))
                level1[y+2][x+1]=0;
            if((x-1)>-1 && (x-1)<8 && (fmod(ctrD/7,1.0)!=0))
                level1[y+2][x-1]=0;
        }
    }

    //bishop
    else if(pieceType==3){
        for(int i=1;i<9;i++){
            if(x+i>-1 && x+i<8 && y+i>-1 && y+i<8 && ((i<ctr%512%64%8) || 0==ctr%512%64%8))
                level1[y+i][x+i]=0;
            if(x+i>-1 && x+i<8 && y-i>-1 && y-i<8 && ((i<((ctr%512%64)-ctr%512%64%8)/8)|| (((ctr%512%64)-ctr%512%64%8)/8)==0))
                level1[y-i][x+i]=0;
            if(x-i>-1 && x-i<8 && y+i>-1 && y+i<8 && ((i<((ctr%512)-ctr%512%64)/64)|| (((ctr%512)-ctr%512%64)/64)==0))
                level1[y+i][x-i]=0;
            if(x-i>-1 && x-i<8 && y-i>-1 && y-i<8 && ((i<((ctr-ctr%512))/512)|| (((ctr-ctr%512))/512)==0))
                level1[y-i][x-i]=0;
        }
    }

    //rock
    else if(pieceType==4){
        for(int i=1;i<9;i++){
            if(x+i>-1 && x+i<8 && ((i<ctr%512%64%8) || 0==ctr%512%64%8))
              level1[y][x+i]=0;
            if(x-i>-1 && x-i<8 && ((i<((ctr%512%64)-ctr%512%64%8)/8)|| (((ctr%512%64)-ctr%512%64%8)/8)==0))
                level1[y][x-i]=0;
            if(y+i>-1 && y+i<8 && ((i<((ctr%512)-ctr%512%64)/64)|| (((ctr%512)-ctr%512%64)/64)==0))
                level1[y+i][x]=0;
            if(y-i>-1 && y-i<8 && ((i<((ctr-ctr%512))/512)|| (((ctr-ctr%512))/512)==0))
                level1[y-i][x]=0;
        }
    }

    //queen
    else if(pieceType==5){
        for(int i=1;i<9;i++){
            if(x+i>-1 && x+i<8 && y+i>-1 && y+i<8 && ((i<ctr%512%64%8) || 0==ctr%512%64%8))
                level1[y+i][x+i]=0;
            if(x+i>-1 && x+i<8 && y-i>-1 && y-i<8 && ((i<((ctr%512%64)-ctr%512%64%8)/8)|| (((ctr%512%64)-ctr%512%64%8)/8)==0))
                level1[y-i][x+i]=0;
            if(x-i>-1 && x-i<8 && y+i>-1 && y+i<8 && ((i<((ctr%512)-ctr%512%64)/64)|| (((ctr%512)-ctr%512%64)/64)==0))
                level1[y+i][x-i]=0;
            if(x-i>-1 && x-i<8 && y-i>-1 && y-i<8 && ((i<((ctr-ctr%512))/512)|| (((ctr-ctr%512))/512)==0))
                level1[y-i][x-i]=0;
        }
        ctr=0;
    for (int i=0; i<32; i++) {
        for(int cnt=8;cnt>0;cnt--){
            if((x+cnt)==pieces[i][0] && (y)==pieces[i][1] && ((ctr%512%64%8==0) || (ctr%512%64%8>cnt)) ){
                ctr=(ctr-(ctr%512%64%8))+cnt;
                if (pieces[i][2]!=fTotal) {
                    ctr=(ctr-(ctr%512%64%8))+cnt+1;
                }
            }
            if((x-cnt)==pieces[i][0] && (y)==pieces[i][1] && ((((ctr%512%64)-ctr%512%64%8)==0) || (((ctr%512%64)-ctr%512%64%8)/8>cnt))){
                ctr=(ctr-(ctr%512%64)+ctr%512%64%8)+cnt*8;
                if (pieces[i][2]!=fTotal) {
                    ctr=(ctr-(ctr%512%64)+ctr%512%64%8)+(1+cnt)*8;
                }
            }
            if((x)==pieces[i][0] && (y+cnt)==pieces[i][1] && ((((ctr%512)-ctr%512%64)==0) || (((ctr%512)-ctr%512%64)/64>cnt))){
                ctr=(ctr-(ctr%512)+ctr%512%64)+cnt*64;
                if (pieces[i][2]!=fTotal) {
                    ctr=(ctr-(ctr%512)+ctr%512%64)+(1+cnt)*64;
                }
            }
            if((x)==pieces[i][0] && (y-cnt)==pieces[i][1] && (((ctr-ctr%512)==0) || ((ctr-ctr%512)/512>cnt)) ){
                ctr=ctr%512+cnt*512;
                if (pieces[i][2]!=fTotal) {
                    ctr=ctr%512+(1+cnt)*512;
                }
            }
        }
    }
        for(int i=1;i<9;i++){
            if(x+i>-1 && x+i<8 && ((i<ctr%512%64%8) || 0==ctr%512%64%8))
                level1[y][x+i]=0;
            if(x-i>-1 && x-i<8 && ((i<((ctr%512%64)-ctr%512%64%8)/8)|| (((ctr%512%64)-ctr%512%64%8)/8)==0))
                level1[y][x-i]=0;
            if(y+i>-1 && y+i<8 && ((i<((ctr%512)-ctr%512%64)/64)|| (((ctr%512)-ctr%512%64)/64)==0))
                level1[y+i][x]=0;
            if(y-i>-1 && y-i<8 && ((i<((ctr-ctr%512))/512)|| (((ctr-ctr%512))/512)==0))
                level1[y-i][x]=0;
            }
    }

    //check
    else if(pieceType==6){
        double ctrD=(double) ctr;
        if(x-1>-1 && x-1<8){
            if(y-1>-1 && y-1<8 && (fmod(ctrD/19,1.0)!=0))
                level1[y-1][x-1]=0;
            if(y>-1 && y<8 && (fmod(ctrD/17,1.0)!=0))
                level1[y][x-1]=0;
            if(y+1>-1 && y+1<8 && (fmod(ctrD/13,1.0)!=0))
                level1[y+1][x-1]=0;
        }
        if(x>-1 && x<8){
            if(y-1>-1 && y-1<8 && (fmod(ctrD/11,1.0)!=0))
                level1[y-1][x]=0;
            if(y+1>-1 && y+1<8 && (fmod(ctrD/7,1.0)!=0))
                level1[y+1][x]=0;
        }
        if(x+1>-1 && x+1<8){
            if(y-1>-1 && y-1<8 && (fmod(ctrD/5,1.0)!=0))
                level1[y-1][x+1]=0;
            if(y>-1 && y<8 && (fmod(ctrD/3,1.0)!=0))
                level1[y][x+1]=0;
            if(y+1>-1 && y+1<8 && (fmod(ctrD/2,1.0)!=0))
                level1[y+1][x+1]=0;
        }
    }
    LoadMap(level1);
    DrawMap();
}
