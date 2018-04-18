#ifndef SQUARES_H
#define SQUARES_H

#include<iostream>

using namespace std ;

template <typename T>
class Squares
{
public :
    Squares() {}
    Squares(T content) : p_content(content) {}
    virtual ~Squares() {}
    T content() const
    {
        return p_content;
    }
    void setContent(T content)
    {
        p_content = content;
    }

    void draw()
    {
        cout << p_content << " ";
    }


protected :
    T p_content;
};

#endif
