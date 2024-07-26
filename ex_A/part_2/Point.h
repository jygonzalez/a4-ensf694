/**
 *  File Name: Point.h
 *  Assignment: ENSF 694 Summer 2024 - Lab 4 Exercise A Part 2
 *  Created by: Mahmood Moussavi on 2024-05-10.
 *  Completed by: Yael Gonzalez
 *  Submission Date: July 26, 2024
 */

#ifndef Point_h
#define Point_h
#include <string.h>
class Point
{
public:
    Point(int x, int y, const char *label);
    ~Point();
    Point(const Point &src);
    Point &operator=(const Point &rhs);
    int getx() const;
    int gety() const;
    char *get_label() const;

private:
    int x, y;    // x and y coordinates of a point on Cartesian plain
    char *label; // pointer to an array allocated on the heap to store the label for a point
};

#endif /* Point_h */
