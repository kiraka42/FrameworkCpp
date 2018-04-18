#ifndef TWOTHOUSANDANDFORTYHEIGHTGAMEVARIANT3_H
#define TWOTHOUSANDANDFORTYHEIGHTGAMEVARIANT3_H

#include "TwoThousandAndFortyEightGame.h"

/*
    VARIANT 3 : x2 /2
*/

using namespace std ;

class TwoThousandAndFortyEightGameVariant3 : public TwoThousandAndFortyEightGame
{
public :
    TwoThousandAndFortyEightGameVariant3(int size) : TwoThousandAndFortyEightGame(size) {}
    TwoThousandAndFortyEightGameVariant3(int a , int b) : TwoThousandAndFortyEightGame(a,b) {}

protected :
    string timesValue = "x2";
    string divValue = "/2";
    sf::Color timesColor = sf::Color(20,200,20);
    sf::Color divColor = sf::Color(200,20,20);

    virtual void initializeGrid()
    {
        // Adding times and div + setting probabilities
        elements.push_back(timesValue);
        elements.push_back(divValue);
        elementsProba = vector<int>({80,10,5,5});

        TwoThousandAndFortyEightGame::initializeGrid();
    }

    virtual string tryFusion(Position& p1, Position& p2)
    {
        string value1 = grid->getValue(p1).text(), value2 = grid->getValue(p2).text();

        // Equals can't fusion
        if ((value1 == timesValue && value2 == timesValue) || (value1 == divValue && value2 == divValue))
        {
            return "-1";
        }
        else
        {
            if (value1 == timesValue && isInteger(value2) && value2 != emptyValue)
            {
                return times(StringToInt(value2), p1, p2);
            }
            else if (value2 == timesValue && isInteger(value1) && value1 != emptyValue)
            {
                return times(StringToInt(value1), p1, p2);
            }
            if (value1 == divValue && isInteger(value2) && value2 != emptyValue)
            {
                return div(StringToInt(value2), p1, p2);
            }
            else if (value2 == divValue && isInteger(value1) && value1 != emptyValue)
            {
                return div(StringToInt(value1), p1, p2);
            }
        }

        return TwoThousandAndFortyEightGame::tryFusion(p1,p2);
    }

    string times(int v, Position& p1, Position& p2)
    {
        return coeff(v * 2, p1, p2);
    }

    string div(int v, Position& p1, Position& p2)
    {
        return coeff(v / 2, p1, p2);
    }

    string coeff(int v, Position& p1, Position& p2)
    {
        string res = intToString(v);
        fusion(p1, p2, res);
        return res;
    }

    virtual void fillRectangle(Position& pos, sf::RectangleShape& rectangle)
    {
        if(grid->getValue(pos).text() == timesValue)
            rectangle.setFillColor(timesColor);
        else if (grid->getValue(pos).text() == divValue)
            rectangle.setFillColor(divColor);
        else
            TwoThousandAndFortyEightGame::fillRectangle(pos, rectangle);
    }
};


#endif
