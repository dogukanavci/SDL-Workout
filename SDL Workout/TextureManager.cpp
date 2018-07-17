//
//  TextureManager.cpp
//  SDL Workout
//
//  Created by Doğukan Avcı on 12/07/2018.
//  Copyright © 2018 dogukan avci. All rights reserved.
//

#include "TextureManager.hpp"

std::string adress=("/Users/dogukanavci/Desktop/summerTraining/summerTraining/SDL Workout/Assets/");
SDL_Texture *TextureManager::LoadTexture(std::string fileName){
    SDL_Surface *surf=IMG_Load((adress+(fileName)).c_str());
    std::string h=(adress+(fileName));
    SDL_Texture *tex=SDL_CreateTextureFromSurface(Game::renderer, surf);
    SDL_FreeSurface(surf);
    return tex;
}
void TextureManager::Draw(SDL_Texture *texture,SDL_Rect srcR,SDL_Rect desR){
    SDL_RenderCopy( Game::renderer,texture, &srcR, &desR);
}
