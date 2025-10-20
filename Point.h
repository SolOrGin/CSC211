#ifndef look_for_POINT2_H
#define look_for_POINT2_H


class Point {
public:
    bool operator==(const Point& other) const;

    Point(const Point& other);

    void print() const;
    void set(int x, int y);
    int getX() const;
    int getY() const;
private:
    int x;
    int y;

};

#endif //look_for_POINT2_H
