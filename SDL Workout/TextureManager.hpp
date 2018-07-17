//
//  TextureManager.hpp
//  SDL Workout
//
//  Created by Doğukan Avcı on 12/07/2018.
//  Copyright © 2018 dogukan avci. All rights reserved.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <stdio.h>
#include <string>
#include "Game.hpp"

class TextureManager{
public:
    static SDL_Texture *LoadTexture(std::string fileName);
    static void Draw(SDL_Texture *texture,SDL_Rect srcR,SDL_Rect desR);
private:
};

#endif /* TextureManager_hpp */
