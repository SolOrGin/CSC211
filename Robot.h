
#ifndef look_for_ROBOT2_H
#define look_for_ROBOT2_H
#include "Point.h"

class Robot {
public:
    enum orientation_type {NORTH, SOUTH, EAST, WEST};

    void init();
    void print() const;
    void setOrientation(orientation_type orientation);
    bool forward();
    void turnCW();
    void turnAntiCW();
    bool eastEnd()const;
    bool westEnd()const;
    bool northEnd()const;
    bool southEnd()const;
    bool zag();
    bool zig();
    Point getLocation() const;
    
    bool operator++();
    bool operator--();
    float operator-(const Robot& other) const;
    bool opperator==(const Robot& other) const;
    bool reverse();

private:
    Point location;
    orientation_type orientation;

};


#endif //look_for_ROBOT2_H
