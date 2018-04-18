#ifndef TWOTHOUSANDANDFORTYHEIGHTGAMEVARIANT1_H
#define TWOTHOUSANDANDFORTYHEIGHTGAMEVARIANT1_H

#include "TwoThousandAndFortyEightGame.h"

/*
    VARIANT 1 : 3 & 5
*/

using namespace std ;

class TwoThousandAndFortyEightGameVariant1 : public TwoThousandAndFortyEightGame
{
public :
    TwoThousandAndFortyEightGameVariant1(int size) : TwoThousandAndFortyEightGame(size) {}
    TwoThousandAndFortyEightGameVariant1(int a , int b) : TwoThousandAndFortyEightGame(a,b) {}

protected :

    virtual void initializeGrid()
    {
        // Adding 3 and 5 + setting probabilities
        elements.push_back("3");
        elements.push_back("5");
        elementsProba = vector<int>({40,10,40,10});

        TwoThousandAndFortyEightGame::initializeGrid();
    }

    virtual std::string power(int v, Position& p1, Position& p2)
    {
        std::string parentRes = TwoThousandAndFortyEightGame::power(v,p1,p2);

        // If not a muktiple of 2, let's see if multiple of 3 or 5
        if (parentRes == "-1")
        {
            if (v % 3 == 0)
            {
                std::string res = intToString(v*3);
                fusion(p1,p2,res);
                return res;
            }
            else if (v % 5 == 0)
            {
                std::string res = intToString(v*5);
                fusion(p1,p2,res);
                return res;
            }
        }

        return parentRes;
    }
};


#endif
