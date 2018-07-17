//
//  Components.hpp
//  SDL Workout
//
//  Created by Doğukan Avcı on 13/07/2018.
//  Copyright © 2018 dogukan avci. All rights reserved.
//

#ifndef Components_hpp
#define Components_hpp

#include <stdio.h>
#include "Ecs.hpp"

class PositionComponent : public Component{
private:
    int xPos;
    int yPos;
public:
    virtual ~PositionComponent(){}
    int x(){return xPos;}
    int y(){return yPos;}
    
    void init() override {
        xPos=0;
        yPos=0;
    }
    void update() override{
        xPos++;
        yPos++;
    }
    void draw() override{
        
    }
    void setPos(int x,int y){
        xPos=x;
        yPos=y;
    }
};

#endif /* Components_hpp */
