#include <iostream>
#include <vector>
#include "Game.h"
#include <cmath>
#include <ctime>
#include <stdlib.h>

std::string SquareTypeStringify(SquareType sq){
    std::string em;
    switch(sq){
        case SquareType::Wall: 
            em = "❎";
            break;
        case SquareType::Dots:
            em = "🟨";
            break;
        case SquareType::Empty:
            em = "⬜";
            break;
        case SquareType::Pacman:
            em = "😁";
            break;
        case SquareType::Treasure:
            em = "🎁";
            break;
        case SquareType::PowerfulPacman:
            em = "😇";
            break;
        case SquareType::Enemies:
            em = "👻";
            break;
        case SquareType::EnemySpecialTreasure:
            em = "🍒";
            break;
        case SquareType::Trap:
            em = "🔥";
            break;
    }
    return em;
};

std::ostream& operator<<(std::ostream& os, const Board& b){
    for(int i=0; i<10; i++){
        for(int j=0;j<10;j++){
            os << SquareTypeStringify(b.arr_[i][j]);
        }
        os << std::endl;
    }
    return os;
};

Board::Board(){
    rows_=10;
    cols_=10;
    //set all the positions to pellets or dots for that matter
    for(int i=0;i<10;i++){
        for(int y=0;y<10;y++){ // might be a seg fault for goind past array bounds
            arr_[i][y]=SquareType::Dots;
        }
    }
    //hardcode the rest of the positions to walls
    arr_[4][0] = SquareType::Wall; // first row of walls
    arr_[5][0] = SquareType::Wall;
    arr_[6][0] = SquareType::Wall;
    arr_[7][0] = SquareType::Wall;
    arr_[8][0] = SquareType::Wall;
    arr_[2][1] = SquareType::Wall;// second row of walls
    arr_[3][1] = SquareType::Wall;
    arr_[5][1] = SquareType::Wall;
    arr_[8][1] = SquareType::Wall;
    arr_[2][2] = SquareType::Wall; // third row of walls
    arr_[3][2] = SquareType::Wall;
    arr_[5][2] = SquareType::Wall;
    arr_[8][2] = SquareType::Wall;
    arr_[5][3] = SquareType::Wall; // fourth row of walls
    arr_[6][3] = SquareType::Wall;
    arr_[8][3] = SquareType::Wall;
    arr_[1][4] = SquareType::Wall; // fifth row of walls
    arr_[2][4] = SquareType::Wall; 
    arr_[1][5] = SquareType::Wall; // sixth row of walls
    arr_[2][5] = SquareType::Wall;
    arr_[3][5] = SquareType::Wall;
    arr_[4][5] = SquareType::Wall;
    //7th row is all pellets
    arr_[5][7] = SquareType::Wall; //8th row of walls
    arr_[6][7] = SquareType::Wall;
    arr_[5][8] = SquareType::Wall; //9th row of walls
    arr_[6][8] = SquareType::Wall;
    arr_[7][8] = SquareType::Wall;
    arr_[8][8] = SquareType::Wall;
    arr_[9][8] = SquareType::Wall;
    arr_[5][9] = SquareType::Wall; //10th row of walls
    arr_[6][9] = SquareType::Wall;
    arr_[7][9] = SquareType::Wall;
    arr_[8][9] = SquareType::Wall;
    arr_[9][9] = SquareType::Wall;
    //set the top left corner to the pacman
    arr_[0][0] = SquareType::Pacman;
    //hardcoding for the two treasures
    srand((unsigned) time(0));
    int randomNumber;
    for(int j=0;j<10;j++){
        for(int k=0;k<10;k++){ // might be a seg fault for goind past array bounds
            if(arr_[j][k]==SquareType::Dots){
                randomNumber = rand() % 9;
                if(randomNumber==3){
                    arr_[j][k]=SquareType::Treasure;
                }
            }
        }
    }
    arr_[0][2]=SquareType::EnemySpecialTreasure;
    arr_[6][6]=SquareType::EnemySpecialTreasure;
    arr_[0][8]=SquareType::Trap;
    arr_[6][4]=SquareType::Trap;
}

SquareType Board::get_square_value(Position pos) const {
    return (arr_[pos.row][pos.col]); // return the squaretype at the specified position
}

int Board::get_pellets(){
    int pel = 0;
    for(int i=0; i<10; i++){
        for(int j=0;j<10;j++){
            if(arr_[i][j]==SquareType::Dots || arr_[i][j]==SquareType::Treasure){
                pel +=1;
            }
        }
    }
}


void Board::SetSquareValue(Position pos, SquareType value){
    arr_[pos.row][pos.col]=value; // set the arr_ squaretype value at specified position to specified value
}

std::vector<std::string> Board::GetMoves(Player *p){
    std::vector<std::string> possibleMoves;
    Position currPos = p->get_position();
    int currRow = currPos.row;
    int currCol = currPos.col;
    bool cantMoveUp = false;
    bool cantMoveDown = false;
    bool cantMoveEast = false;
    bool cantMoveWest = false;
    if(currRow==0){
        cantMoveUp=true;
    }
    if(currRow==9){
        cantMoveDown=true;
    }
    if(currCol==0){
        cantMoveEast=true;
    }
    if(currCol==9){
        cantMoveWest=true;
    }
    //try moving east
    if(cantMoveEast==false && arr_[currRow][currCol-1]!= SquareType::Wall){
        Position east;
        east.col=currCol-1;
        east.row=currRow;
        possibleMoves.push_back("left");
    }

    //try moving west
    if(cantMoveWest==false && arr_[currRow][currCol+1]!= SquareType::Wall){
        Position west;
        west.col=currCol+1;
        west.row=currRow;
        possibleMoves.push_back("right");
    }

    //try moving up
    if(cantMoveUp==false && arr_[currRow-1][currCol]!= SquareType::Wall){
        Position up;
        up.col=currCol;
        up.row=currRow-1;
        possibleMoves.push_back("up");
    }

    //try moving down
    if(cantMoveDown==false && arr_[currRow+1][currCol]!= SquareType::Wall){
        Position down;
        down.col=currCol;
        down.row=currRow+1;
        possibleMoves.push_back("down");
    }
    return possibleMoves;
}

//could change this to a void function
bool Board::MovePlayer(Player *p, Position pos, std::vector<Player*> enemylist){
    /* check for enemies pos
        check if pos==pellet
        check if pos==treasure
        check if pos==wall
        check if pos is out of bounds
    */
   //get the player's new previous position int val which corresponds to a squaretype value
    //int new_pos_s_val;
    // loop through enemylist to see if new position has one of the enemies in it
    //first check for out of bounds // kind of unncessary as is already handled in taketurn
    if(pos.col<0 || pos.col>9 || pos.row<0 ||pos.row>9){
        return false;
    }
    bool hasTres = p->hasTreasure();
    bool moveResult = true;
    for(int i=0;i<enemylist.size();i++){ 
        if(pos==enemylist[i]->get_position()){ // if we have a enemy at the newpos
            if(hasTres){ // kill enemy if pacman has a treasure 

                //check if enemy has treasure
                if(enemylist[i]->hasTreasure()){
                    SetSquareValue(p->get_position(), SquareType::Pacman); //set position to empty
                    enemylist[i]->setHasTreasure(false);
                    return true;
                }
                //enemy doesn't have treasure
                SetSquareValue(p->get_position(), SquareType::Empty); //set position to empty
                p->setHasTreasure(false); //renove treasure
                p->SetPosition(pos); // set new positioN
                enemylist[i]->setIsDead(); // kill enemy
                bool legalpos2 = false; 
                Position np_2;
                while(legalpos2==false){
                    np_2.row = rand() % 10;
                    np_2.col = rand() % 10;
                    if(get_square_value(np_2)!=SquareType::Enemies || get_square_value(np_2)!=SquareType::Wall || get_square_value(np_2)!=SquareType::Pacman || get_square_value(np_2)!=SquareType::PowerfulPacman){
                        legalpos2=true;
                        enemylist[i]->SetPosition(np_2);  
                    }
                }
                SetSquareValue(pos,SquareType::Pacman); // set new position squaretype to pacman
            }
            if(!hasTres){ // game over
                //SetSquareValue(enemylist[i]->get_position(), S
                //SetSquareValue(pos, SquareType::Enemies);
                SetSquareValue(p->get_position(), SquareType::Empty); //set position to empty
                p->subtract_life();
                if(p->get_lives()==0){
                    p->setIsDead();
                    SetSquareValue(p->get_position(), SquareType::Empty);
                    return true; // nothing on the board changes but the previous square val
                }
            }
            moveResult= true;
        }
    }

    // move to a position with a pellet
    if(get_square_value(pos)==SquareType::Dots){ 
        SetSquareValue(p->get_position(), SquareType::Empty);//set previous position to empty
        p->ChangePoints(1); //increment points and set new position
        p->SetPosition(pos);
        // if player is powerful pacman
        if(p->hasTreasure()){ // if player is powerful pacman
            SetSquareValue(pos, SquareType::PowerfulPacman);
        }
        if(p->hasTreasure()==false){ // regular pacman
            SetSquareValue(pos, SquareType::Pacman);
        }
        moveResult= true; //successful move
    }

    // moves to a position with a treasure
    if(get_square_value(pos)==SquareType::Treasure){ 
        SetSquareValue(p->get_position(), SquareType::Empty);//set previous position to empty
        p->ChangePoints(100); // increment points by 100
        p->SetPosition(pos); // set player position to pos
        if(p->hasTreasure()){
            SetSquareValue(pos, SquareType::PowerfulPacman); 
            moveResult= true; //successful move
        }
        else{
            p->setHasTreasure(true); // now has treasure
            SetSquareValue(pos, SquareType::PowerfulPacman); 
            moveResult= true; //successful move
        }
    }

    // moves to a position with a wall
    if(get_square_value(pos)==SquareType::Wall){
        //nothing happens
        moveResult= false;
    }
    //moves to a enemy special treasure
    if(get_square_value(pos)==SquareType::EnemySpecialTreasure){
        //nothing happens
        moveResult= false;
    }
    //moves to a trap
    if(get_square_value(pos)==SquareType::Trap){
        //nothing happens
        if(p->hasTreasure()){
            p->setHasTreasure(false);
            SetSquareValue(p->get_position(), SquareType::Pacman);
            return true;
        }
        p->subtract_life();
        if(p->get_lives()==0){
            p->setIsDead();
            SetSquareValue(p->get_position(), SquareType::Empty);
            return true; // nothing on the board changes but the previous square val
        }
    }

    //moves to position with empty
    if(get_square_value(pos)==SquareType::Empty){
        SetSquareValue(p->get_position(), SquareType::Empty);//set previous position to empty
        p->SetPosition(pos); // set player position to pos
        if(p->hasTreasure()==true){
            SetSquareValue(pos, SquareType::PowerfulPacman);
        }
        else{
            SetSquareValue(pos, SquareType::Pacman);
        }
        moveResult= true; //successful move
    }
    //return false;
    return moveResult;
}

//could change this to a void function
bool Board::MoveEnemy(Player *p, Player *enemy, int n){
    //moves out of bounds 
    Position pos = enemy->get_position();

    //first checker, if we aren't moving out of bounds (true - if in bounds) (false - otherwise)
    bool moveSuccess1 = false;

    //out of bounds flags
    bool x_right = false;
    bool x_left = false;
    bool x_down = false;
    bool x_up = false;

    //check if out of bounds

    //right
    if(pos.col+1 > 9){
        x_right=true;
    }
    //left
    if(pos.col-1 < 0){
        x_left=true;
    }
    //up
    if(pos.row-1 < 0){
        x_up=true;
    }
    //down
    if(pos.row+1 > 9){
        x_down=true;
    }


    // check n value and either return false if associated flag is true or set position of pos
    
    //move right
    if(n==0 && x_right!=true){
        moveSuccess1=true;
        pos.col = pos.col +1;
    }

    //move left
    if(n==1 && x_left!=true){
        moveSuccess1=true;
        pos.col = pos.col -1;
    }
    
    //move up
    if(n==2 && x_up!=true){
        moveSuccess1=true;
        pos.row = pos.row -1;
    }
    
    //move down
    if(n==3 && x_down!=true){
        moveSuccess1=true;
        pos.row = pos.row +1;
    }

    //check if moveSuccess is true, if so continue in function, else return false (out of bounds move)
    if(moveSuccess1==false){
        return false;
    }
    
    //check if move is to a wall, if so return false and leave function
    if(get_square_value(pos)==SquareType::Wall){
        return false;
    }
      
    //check if we move to pellet
    if(get_square_value(pos)==SquareType::Dots){
        //set previous position back to it's original squaretype
        SetSquareValue(enemy->get_position(), enemy->get_prev()); // ANIMATE: set the squaretype at the enemy's current pos back to it's original value
        enemy->set_prev(SquareType::Dots); // set enemy's prev_ (previous Square val) to Pellet
        SetSquareValue(pos, SquareType::Enemies); // ANIMATE: set the board at pos to Enemy
        enemy->SetPosition(pos); //update enemy's pos_ (position)
        return true; // move is successful
    }
        
    //check if we move to treasure
    if(get_square_value(pos)==SquareType::Treasure){
        //set previous position back to it's original squaretype
        SetSquareValue(enemy->get_position(), enemy->get_prev()); // ANIMATE: set the squaretype at the enemy's current pos back to it's original value
        enemy->set_prev(SquareType::Treasure); // set enemy's prev_ (previous Square val) to Pellet
        SetSquareValue(pos, SquareType::Enemies); // ANIMATE: set the board at pos to Enemy
        enemy->SetPosition(pos); //update enemy's pos_ (position)
        return true; // move is successful
    }
    //check if we move to to PP
    if(get_square_value(pos)==SquareType::PowerfulPacman){
        //set previous position back to it's original squaretype
        if(enemy->hasTreasure()){
            //enemy doesn't move on the board, but it's treasure is taken and the player becomes a pacman
            p->setHasTreasure(false); //remove treasure val of player p
            enemy->setHasTreasure(false);
            SetSquareValue(p->get_position(), SquareType::Pacman);
            return true;
        }
        //otherwise we execute the following
        SetSquareValue(enemy->get_position(), enemy->get_prev()); // ANIMATE: set the squaretype at the enemy's current pos back to it's original value
        enemy->setIsDead(); //kill enemy
        // while loop
        Position np_2;
        bool legalpos2 = false; 
        while(legalpos2==false){
            np_2.row = rand() % 10;
            np_2.col = rand() % 10;
            if(get_square_value(np_2)!=SquareType::Enemies || get_square_value(np_2)!=SquareType::Wall || get_square_value(np_2)!=SquareType::Pacman || get_square_value(np_2)!=SquareType::PowerfulPacman){
                    legalpos2=true;
                    enemy->SetPosition(np_2);  
            }
        }    
        p->setHasTreasure(false); //remove treasure val of player p
        SetSquareValue(pos, SquareType::Pacman); //change square value at pos from Powerful Pacman to Pacman
        return true; // move is successful
        // ****spawn new enemy
    }
    //check if we move to pacman
    if(get_square_value(pos)==SquareType::Pacman){
        SetSquareValue(enemy->get_position(), enemy->get_prev()); //ANIMATE: set previous position back to it's original squaretype
        enemy->SetPosition(pos); //update enemy's pos_ (position)
        SetSquareValue(pos, SquareType::Enemies); // ANIMATE: change square value at pos from pacman to enemy
        p->subtract_life(); // kill player
        if(p->get_lives()==0){
            p->setIsDead();
            SetSquareValue(p->get_position(), SquareType::Empty);
            return true; // nothing on the board changes but the previous square val
        }
        return true; // move is successful
    }
    //check if we move to an empty position
    if(get_square_value(pos)==SquareType::Empty){
        SetSquareValue(enemy->get_position(), enemy->get_prev()); //ANIMATE: set previous position back to it's original squaretype
        enemy->SetPosition(pos); //update enemy's pos_ (position)
        enemy->set_prev(SquareType::Empty); //update enemy's pos_ (position)
        SetSquareValue(pos, SquareType::Enemies);// ANIMATE: change square value at pos from empty to enemy
        return true; // move is successful
    }
    //must move somewhere else
    if(get_square_value(pos)==SquareType::Enemies){
        return false;
    }
    //moves to trap
    if(get_square_value(pos)==SquareType::Trap){
        SetSquareValue(enemy->get_position(), enemy->get_prev()); //ANIMATE: set previous position back to it's original squaretype
        enemy->SetPosition(pos); //update enemy's pos_ (position)
        enemy->set_prev(SquareType::Trap); //update enemy's pos_ (position)
        SetSquareValue(pos, SquareType::Enemies);// ANIMATE: change square value at pos from trap to enemy
        return true; // move is successful
    }
    //moves to enemy special treasure
    if(get_square_value(pos)==SquareType::EnemySpecialTreasure){
        SetSquareValue(enemy->get_position(), enemy->get_prev()); //ANIMATE: set previous position back to it's original squaretype
        enemy->SetPosition(pos); //update enemy's pos_ (position)
        enemy->set_prev(SquareType::Dots); //update enemy's pos_ (position)
        SetSquareValue(pos, SquareType::Enemies);// ANIMATE: change square value at pos from empty to enemy
        enemy->setHasTreasure(true);
        return true; // move is successful
    }
} 

Game::Game(){
    board_ = new Board(); //put new board on the heap
    //create 3 players and put them on the heap
    Player * mP = new Player("Manny Pac", true);
    Player * e1 = new Player("Screams", false);
    Player * e2 = new Player("Nightmare", false);

    //flags for enemies spawning at illegal positions
    bool enemy1_is_at_illegal_pos = false;
    bool enemy2_is_at_illegal_pos = false;

    //reset enemy1 position until legal
    while(enemy1_is_at_illegal_pos==false){
        // set e1's position to random position
        Position np_1;
        np_1.row = rand() % 10;
        np_1.col = rand() % 10;
        e1->SetPosition(np_1);

        //enemy 1's position is legal
        if(board_->get_square_value(e1->get_position()) != SquareType::Wall && board_->get_square_value(e1->get_position()) != SquareType::Pacman && board_->get_square_value(e1->get_position()) != SquareType::PowerfulPacman && board_->get_square_value(e1->get_position()) != SquareType::Enemies){
            enemy1_is_at_illegal_pos=true;
        }
    }

    //reset enemy2 position until legal
    while(enemy2_is_at_illegal_pos==false){
        // set e1's position
        Position np_2;
        np_2.row = rand() % 10;
        np_2.col = rand() % 10;
        e2->SetPosition(np_2);

        //enemy 1's position is legal
        if(board_->get_square_value(e2->get_position()) != SquareType::Wall && board_->get_square_value(e2->get_position()) != SquareType::Pacman && board_->get_square_value(e2->get_position()) != SquareType::PowerfulPacman && board_->get_square_value(e2->get_position()) != SquareType::Enemies){
            enemy2_is_at_illegal_pos=true;
        }
    }

    //now set e1 and e2s' respective prev_ vals
    e1->set_prev(board_->get_square_value(e1->get_position()));
    e2->set_prev(board_->get_square_value(e2->get_position()));
    
    //set the board at enemys'  positions to squaretype::enemy
    board_->SetSquareValue(e1->get_position(), SquareType::Enemies);
    board_->SetSquareValue(e2->get_position(), SquareType::Enemies);

    //initialize private members
    players_.push_back(mP);
    players_.push_back(e1);
    players_.push_back(e2); 
    for(int z=1;z<players_.size();z++){
        enemylist_.push_back(players_[z]);
    }  
    turn_count_=0;
    dots_count_=0;
    GameOver=false;
    std::cout << *board_;
}
//newGame() function goes here

void Game::GenerateReport(){
    Player *p = players_[0];
    std::cout << p->get_name() << " ended with " << p->get_lives() << " lives and " << p->get_points() << " points" << std::endl;
    if(board_->get_pellets()==0){
        std::cout << p->get_name() << " also ended up winning the game by successfully collecting all pellets and treasures." << std::endl;
    }
    if(board_->get_pellets()!=0){
        std::cout << p->get_name() << " did not successfully win the game ... Sorry, better luck next time" << std::endl;
    }
}


bool Game::TakeTurn(int n, Player *p, std::vector<Player*> enemylist){
    // std::vector<std::string> legalMoves = board_->GetMoves(p);
    // for(int i=0;i<legalMoves.size();i++){
    //     std::cout << "You can move: " << legalMoves[i]<< std::endl;
    // }
    // std::string inputP; 
    // std::cout << "Choose where you want to move (N,S,E,W) or Q to Quit" << std::endl;
    // std::cin >> inputP;
    // std::cout << "Choose where you want to move (N,S,E,W) or Q to Quit" << std::endl;
    bool moveResult = false;
    Position nP; //new position


    //return false if we are trying to move out of bounds
    /* north */
    if(n==1 && p->get_position().row -1 <0){
        return false;
    }
    /*south*/
    if(n==2 && p->get_position().row +1 >9){
        return false;
    }
    /*left*/
    if(n==3 && p->get_position().col -1 <0){
        return false;
    }
    /*right*/
    if(n==4 && p->get_position().col +1 >9){
        return false;
    }

    switch (n)
    {
    case 1:
        /* north */
        nP.col = p->get_position().col;
        nP.row = p->get_position().row -1;
        moveResult = board_->MovePlayer(p,nP, enemylist);
        break;
    case 2:
        /* south */
        nP.col = p->get_position().col;
        nP.row = p->get_position().row +1;
        moveResult = board_->MovePlayer(p,nP, enemylist);
        break;
    case 3:
        /* left */
        nP.col = p->get_position().col -1;
        nP.row = p->get_position().row;
        moveResult = board_->MovePlayer(p,nP, enemylist);
        break;
    case 4:
        /* right*/
        nP.col = p->get_position().col +1;
        nP.row = p->get_position().row;
        //std::cout << nP.col << " " << nP.row << std::endl;   
        moveResult = board_->MovePlayer(p,nP, enemylist);
        break;
    case 5:
        moveResult = true;
        GameOver=true;
    default:
        break;
    }
    return moveResult;
}

void Game::TakeTurnEnemy(Player *enemy){

    srand((unsigned) time(0));
    int randMove;
    bool move_is_ok = false;
    while (move_is_ok==false){
        randMove = rand() % 4 ;
        move_is_ok = board_->MoveEnemy(players_[0],enemy,randMove);
    }
}

bool Game::IsGameOver(){
    if(players_[0]->isDead() || board_->get_pellets()==0){
        GameOver=true;
    }
    return GameOver;
} 

std::vector<Player*> Game::getPlayers(){
    return players_;
}

void Game::PrintBoard(){
    std::cout << *board_;
}

void Game::simulateGame(){
    char c;
    std::vector<std::string> legalMoves = board_->GetMoves(players_[0]);
    std::cout << "You can move: ";
    for(int i=0;i<legalMoves.size();i++){
        std::cout << legalMoves[i]<< "  ";
    }
    std::cout << std::endl;
    bool successfulMoveP = false;
    while(successfulMoveP==false){
        std::cout << "Choose where you want to move (N,S,E,W) or Q to Quit" << std::endl;
        std::cin >> c;
        switch (c)
        {
        case 'n':
            /* code */
            successfulMoveP = TakeTurn(1, players_[0],enemylist_);
            break;
        case 's':
            successfulMoveP = TakeTurn(2, players_[0],enemylist_);
            break;
        case 'e':
            successfulMoveP = TakeTurn(3, players_[0],enemylist_);
            break;
        case 'w':
            successfulMoveP = TakeTurn(4, players_[0],enemylist_);
            break;
        case 'q':
            successfulMoveP = TakeTurn(5, players_[0],enemylist_);
            break;
        default:
            successfulMoveP = false;
            break;
        }
    }


    if(players_[0]->isDead()==false){
        for(int z=1;z<players_.size();z++){
            TakeTurnEnemy(players_[z]);
        }
    }
    //check if enemy is now dead, if so remove it from players_ and then spawn another one

    std::cout << *board_;
}
