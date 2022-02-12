#include <iostream>
#include "Player.h"
#include <vector>
#include <cmath>
#include <stdlib.h>


Player::Player(const std::string name, const bool is_human){
    name_= name;
    is_human_=is_human;
    Position p;
    if(is_human){
        lives_ = 3;
        points_=0;
        p.row=0;
        p.col=0;
        pos_=p;
        has_Treasure_=false;
        isDead_=false;
        prev_ = SquareType::Empty;
    }
    else{// enemy
        lives_ = 1;
        points_=0;
        pos_.row = rand() % 10;
        pos_.col = rand() % 10;
        has_Treasure_=false;
        isDead_=false;
        prev_ = SquareType::Dots;
    }
}

std::string Player::ToRelativePosition(Position other){
    int otherR = other.row;
    int otherC = other.col;
    if(pos_.row==otherR && pos_.col > otherC){ // other player is left
        return "Another player is to your left";
    }
    if(pos_.row==otherR && pos_.col < otherC){ // other player is to your right
        return "Another player is to your right";
    }
    if(pos_.col==otherC && pos_.row > otherR){ // other player is below you
        return "Another player is below you";
    }
    if(pos_.col==otherC && pos_.row < otherR){ // other player is above you
        return "Another player is above you";
    }
    if(pos_.row > otherR && pos_.col > otherC){ // other player is your south east
        return "Another player is below you and to your left";
    }
    if(pos_.row < otherR && pos_.col >otherC){ // other player is your north east
        return "Another player is above you and to your left";
    }
    if(pos_.row > otherR && pos_.col < otherC){ // other player is your south west
        return "Another player is below you and to your right";
    }
    if(pos_.row < otherR && pos_.col < otherC){ // other player is your north west
        return "Another player is above you and to your right";
    }
    return "b";
}

void Player::setIsDead(){
    if(is_human_==true && lives_ == 0){
        isDead_=true;
    } 
    if(is_human_==false){
        isDead_=true;
    }
};