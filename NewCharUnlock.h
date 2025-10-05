#ifndef look_for_NEWCHARUNLOCK_H
#define look_for_NEWCHARUNLOCK_H

#include "Point.h"
class NewCharUnlock {
public:
    void init();
    void print() const;
    bool moveNorth();
    bool moveSouth();
    bool moveEast();
    bool moveWest();
    bool eastEnd()const;
    bool westEnd()const;
    bool northEnd()const;
    bool southEnd()const;
     
    Point getLocation() const;

private:
    Point location;
};


#endif //look_for_NEWCHARUNLOCK_H