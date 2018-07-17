//
//  Map.hpp
//  SDL Workout
//
//  Created by Doğukan Avcı on 12/07/2018.
//  Copyright © 2018 dogukan avci. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include "Game.hpp"

class Map{
public:
    Map();
    ~Map();
    void LoadMap(int map[8][8]);
    void DrawMap();
private:
    SDL_Rect srcR,desR;
    
    SDL_Texture *dirt;
    SDL_Texture *grass;
    SDL_Texture *water;
    SDL_Texture *square1;
    SDL_Texture *square2;
    int map[8][8];
};

#endif /* Map_hpp */
