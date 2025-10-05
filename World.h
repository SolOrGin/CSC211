
#ifndef look_for2_WORLD_H
#define look_for2_WORLD_H
#include "Point.h"
class Robot;
class NewCharUnlock;
// originally I was using #include "Point.h" and "NewCharUnlock.h"
// but i found out it was bad because it increases compile times and
// leads to circular dependency issues. What does that mean? not sure but 
// this way it's like saying hey you see that robotLocation and playerLocation?
// yeah those are classes and Im using references '&' to them here

// so basically a had a loop of header files, each header file kept leading
// to the other creating a infinite loop, but doing it this way its like
// telling someone your name so they know you but not all of you. (forward declarations)

class World {
public:
    void printC() const;
    void set(int i, int x, int y);
    Point getCoin(int i) const;
    int findCoinAt(const Point& robotLocation)const;
    int getCoinsFound()const;
    void initGrid();
    void updateGrid(int x, int y);
    void printGrid(const Point& robotLocation, const Point& playerLocation) const;


private:
    Point coins[3];
    char grid[10][10];

    bool coinsFoundAlert[3];
    int coinsFound;

};

#endif //look_for2_WORLD_H