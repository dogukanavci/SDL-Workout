//
//  ChessLogic.hpp
//  SDL Workout
//
//  Created by Doğukan Avcı on 20/07/2018.
//  Copyright © 2018 dogukan avci. All rights reserved.
//

#ifndef ChessLogic_hpp
#define ChessLogic_hpp

#include <stdio.h>
#include "GameObject.hpp"
class ChessLogic{
private:
    GameObject selectedGO;
public:
    bool pieceOnWay();
};

#endif /* ChessLogic_hpp */
