#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<iostream>
#include <sstream>
#include <time.h>
#include "Squares.h"
#include "Position.h"

using namespace std ;
template <typename T>
class Grid
{
public :
    Grid() {}
    Grid(int size) : Grid(size,size) {}
    Grid(int m, int n) : p_width(m), p_height(n)
    {
        p_squares = new Squares<T>*[m];
        for(int i(0); i < m; i++)
        {
            p_squares[i] = new Squares<T>[n] ;
        }
    }

    virtual ~Grid()
    {
        for(int i(0); i < width(); i++)
        {
            delete[] p_squares[i] ;
        }
        delete[] p_squares ;
    }

    int width() const { return p_width; }
    int height() const { return p_height; }
    Squares<T> ** squares() const { return p_squares; }

    bool isInGrid(Position p) const
    {
        return p.x < width() && p.x >= 0 && p.y >= 0 && p.y < height();
    }

    T getValue(Position p) const
    {
        return p_squares[p.x][p.y].content();
    }

    void setValue(Position p, T value)
    {
        return p_squares[p.x][p.y].setContent(value);
    }

    void draw() const
    {
        cout << "\n";
        for(int j(0); j < height(); j++)
        {
            for(int i(0); i < width(); i++)
            {
                p_squares[i][j].draw();
            }
            cout << "\n";
        }
    }

protected :
    Squares <T> ** p_squares;
    int p_width;
    int p_height;

};

#endif
