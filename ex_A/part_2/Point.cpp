/**
 *  File Name: Point.cpp
 *  Assignment: ENSF 694 Summer 2024 - Lab 4 Exercise A Part 2
 *  Created by: Yael Gonzalez
 *  Submission Date: July 26, 2024
 */

#include "Point.h"

Point::Point(int x, int y, const char *label) : x(x), y(y), label(new char[strlen(label + 1)])
{
    strcpy(this->label, label);
}

Point::~Point()
{
    delete[] label;
}

Point::Point(const Point &src) : x(src.x), y(src.y), label(new char[strlen(src.label + 1)])
{
    strcpy(label, src.label);
}

Point &Point::operator=(const Point &rhs)
{
    if (this != &rhs) // avoid self copy
    {
        x = rhs.x;
        y = rhs.y;
        delete[] label;
        label = new char[strlen(rhs.label + 1)];
        strcpy(label, rhs.label);
    }
    return *this;
}

int Point::getx() const
{
    return x;
}

int Point::gety() const
{
    return y;
}

char *Point::get_label() const
{
    return label;
}
