#include <iostream>
#include "Game.h"
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

int main(){
    Game g = Game();
    while(g.IsGameOver()==false){
        g.simulateGame();
    }
    std::cout << "Game Over" << std::endl;
    g.GenerateReport();
    return 0;
}