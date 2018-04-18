#ifndef TWOTHOUSANDANDFORTYHEIGHTGAMEVARIANT2_H
#define TWOTHOUSANDANDFORTYHEIGHTGAMEVARIANT2_H

#include "TwoThousandAndFortyEightGame.h"

/*
    VARIANT 2 : Destroy tile
*/

using namespace std ;

class TwoThousandAndFortyEightGameVariant2 : public TwoThousandAndFortyEightGame
{
public :
    TwoThousandAndFortyEightGameVariant2(int size) : TwoThousandAndFortyEightGame(size) {}
    TwoThousandAndFortyEightGameVariant2(int a , int b) : TwoThousandAndFortyEightGame(a,b) {}

protected :
    string destroyValue = "D";
    sf::Color destroyColor = sf::Color(10,10,10);

    virtual void initializeGrid()
    {
        // Adding destroy + setting probabilities
        elements.push_back(destroyValue);
        elementsProba = vector<int>({85,10,5});

        TwoThousandAndFortyEightGame::initializeGrid();
    }

    virtual string tryFusion(Position& p1, Position& p2)
    {
        string value1 = grid->getValue(p1).text(), value2 = grid->getValue(p2).text();
        if ((value1 == destroyValue || value2 == destroyValue)
                && value1 != emptyValue && value2 != emptyValue)
        {
            destroy(p1,p2);
            return destroyValue;
        }

        return TwoThousandAndFortyEightGame::tryFusion(p1,p2);
    }

    void destroy(Position& p1, Position& p2)
    {
        if (!testingGameOver)
        {
            grid->setValue(p1, TwoThousandAndFortyEightElement(emptyValue));
            grid->setValue(p2, TwoThousandAndFortyEightElement(emptyValue));
        }
    }

    virtual void fillRectangle(Position& pos, sf::RectangleShape& rectangle)
    {
        if(grid->getValue(pos).text() == destroyValue)
            rectangle.setFillColor(destroyColor);
        else
        {
            TwoThousandAndFortyEightGame::fillRectangle(pos, rectangle);
        }
    }
};


#endif
