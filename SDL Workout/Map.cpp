//
//  Map.cpp
//  SDL Workout
//
//  Created by Doğukan Avcı on 12/07/2018.
//  Copyright © 2018 dogukan avci. All rights reserved.
//

#include "Map.hpp"
#include "TextureManager.hpp"

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
