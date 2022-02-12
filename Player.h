#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <cmath>
#include <iostream>

enum class SquareType { Wall, Dots, Pacman, Treasure, Enemies, Empty, 
PowerfulPacman, Trap, EnemySpecialTreasure };

struct Position {
    int row;
    int col;
// already implemented for you!
    bool operator==(const Position &other) {
        return (row == other.row && col == other.col);
    }
};

class Player {
    public:
    // TODO: implement
        Player(const std::string name, const bool is_human);  // constructor
        // These are already implemented for you
        std::string get_name() const {return name_; }  // inline member function
        int get_points() const {return points_; }  // inline member function
        Position get_position() const {return pos_; }  // inline member function
        bool is_human() const {return is_human_; }  // inline member function
        bool hasTreasure() const {return has_Treasure_; }  // inline member function
        bool isDead() const {return isDead_;}  // inline member function
        int get_lives() {return lives_;}
        void subtract_life() {lives_=lives_-1;}
        // TODO: implement the following functions
        // You MUST implement the following functions
        void ChangePoints(const int x){points_+=x;};
        // set a new position for this player
        void SetPosition(Position pos){pos_=pos;};
        // sets a player's treasure possession to true or false if the player owns a treasure
        void setHasTreasure(bool treas){has_Treasure_=treas;};
        //checks if the enemy is dead
        void setIsDead();
        // You may want to implement these functions as well
        // ToRelativePosition is a function we used to translate positions
        // into direction s relative to the player (up, down, etc)
        std::string ToRelativePosition(Position other); // how am I supposed to translate
        // Convert this player to a string representation of their name and points
        //(std::string, std::string) Stringify(){return(name_, to_string(points_))}; // should I include another library for to_string
        // You may add other functions as needed/wanted
        void set_prev(SquareType prevS){prev_ = prevS;}
        SquareType get_prev(){return prev_;}
    private:
        int lives_;
        SquareType prev_;
        std::string name_;
        int points_;
        Position pos_;
        bool is_human_;
        bool has_Treasure_;
        bool isDead_;
        // You may add other fields as needed
}; // class Player
#endif  // _PLAYER_H_}; // class Player