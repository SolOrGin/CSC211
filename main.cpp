#include <iostream>
#include <cstdlib>
#include <unistd.h> // needed for usleep 
#include "NewCharUnlock.h"
#include "Point.h"
#include "Robot.h"
#include "World.h"
#include <fstream>


// this only works if the robot is moving at zig zag but once i use the human vs robot then this will be a problem
// because if the human goes straight up then ismapunlocked will be true
// no wait this can work because it's only for the robot.

//bool isMappedUnlocked(const Robot& robot) {
    //return robot.getLocation().getX() == 0 && robot.getLocation().getY() == 9;
//}




int main(int argc, char* argv[]) {

    if (argc != 9){ //now we add 2 more arguements
        std::cerr << "Error: 8 integer arguments are needed for coin placement" << std::endl;
        std::cerr << "Usage: " << argv[0] << " <coin1-x> <coin1-y> <coin2-x> <coin2-y> <coin3-x> <coin3-y> <inputFile> <outputFile>"  << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[7]);
    std::ofstream outputFile(argv[8]);
    
    if(!inputFile.is_open() || !outputFile.is_open()){
        std::cerr << "** Error: No file open! **"  << std::endl;
        return 1;
    }



    World world;
    Robot robot;
    NewCharUnlock player;
    int r_moves = 0;
    int p_moves = 0;
    int r_score = 0;
    int p_score = 0;

    bool coinsFoundAlert[3] = {false, false, false};
   


    for (int i = 0; i < 3; i++) {
        int x = atoi(argv[2 * i + 1]);
        int y = atoi(argv[2 * i + 2]);

        if (x < 0 || x > 9 || y < 0 || y > 9) {
            std::cerr << "Error: All coordinates must be in the range [0,9]." << std::endl;
            return 1;
        }

        world.set(i, x, y);
    }

    robot.init();   
    player.init();
    world.initGrid();


    outputFile<< "* * ** Player Control ** * *" << std::endl;
    outputFile << "     North: n South: s" << std::endl;
    outputFile << "       East: e West: w" << std::endl;
    outputFile << "         Quit game: q" << std::endl;
    outputFile <<"* ** ** *** **** *** ** ** *" << std::endl;

    robot.print();
    player.print();
    world.printC();
    outputFile << std::endl;

    int coinsFound = 0;

    while (coinsFound < 3) {

        outputFile << "      Robot's Turn" << std::endl;
        int rx = robot.getLocation().getX();
        int ry = robot.getLocation().getY();

        world.updateGrid(rx, ry);
        usleep(50000);


        int coinIdx = world.findCoinAt(robot.getLocation());
        if (coinIdx != -1 && !coinsFoundAlert[coinIdx]){
            r_score++;
            coinsFound++;
            coinsFoundAlert[coinIdx] = true;
            outputFile << "Robot found coin! Robot score: " << r_score << std::endl;

        }
        if(robot.forward()){
            r_moves++;
        }
        else if(robot.eastEnd() || robot.westEnd()){
            if (robot.eastEnd()){
                robot.zag();
                r_moves += 2;
            }
            else{
                robot.zig();
                r_moves += 2;
            }

        }
        world.printGrid(robot.getLocation(), player.getLocation());
        outputFile << "- - - - - - - - - - - - - -" << std::endl;

        if (coinsFound >= 3){ //>= is better in case of a situattin where the coin found +2. (good habit, not needed here)
            break;
        }


        //cout << "DEBUG: Location: (";
        //robot.getLocation().print();
        //cout << "), Moves: " << moves << endl;
        
        //BUG: Player was running into wall and then robot would move
        bool p_moveCheck = false;
        bool quit = false;
        char move;

        while (!p_moveCheck){
            bool moved = false;

            if(!(inputFile >> move)){
                outputFile << "End of input. Bye!" << std::endl;
                move = 'q';
                break;
            }
            switch(move){
                case 'n':
                    moved = player.moveNorth();
                    break;
                case 's':
                    moved = player.moveSouth();
                    break;
                case 'e':
                    moved = player.moveEast();
                    break;
                case 'w':
                    moved = player.moveWest();
                    break;
                default:
                    outputFile << "Invalid move: Try again." << std::endl;
                    break;

            }

            if (moved){
                p_moves++;
                p_moveCheck = true;
            }
        }

        if(move == 'q'){
            break;
        }

        coinIdx = world.findCoinAt(player.getLocation());
        if (coinIdx != -1 && !coinsFoundAlert[coinIdx]){
            p_score++;
            coinsFound++;
            coinsFoundAlert[coinIdx] = true;
            outputFile << "Player found a coin! Player score: " << p_score << std::endl;

        }
        world.updateGrid(player.getLocation().getX(), player.getLocation().getY());
        world.printGrid(robot.getLocation(), player.getLocation());
        outputFile << "- - - - - - - - - - - - - - - - - -" << std::endl;
        
    }

    

    outputFile << std::endl;
    if (coinsFound >= 3){
        outputFile << "      All coins have been found!" << std::endl;
        if(r_score > p_score){
            outputFile << "** *** *** *  ROBOT WINS  * *** *** **" << std::endl;
        }
        else if (p_score > r_score){
            outputFile << "** *** *** *  PLAYER WINS  * *** *** **" << std::endl;
        }
        else{
            outputFile << "** *** *** *  TIE GAME  * *** *** **" << std::endl;
        }
    }

    outputFile << "Final Scores: Robot - " << r_score << " Vs Player - " << p_score << std::endl;
    outputFile << "Total Moves: Robot - "<< r_moves << " Vs Player - " << p_moves << std::endl;

    //Always remember to close
    inputFile.close();
    outputFile.close();
    

    return 0;
}