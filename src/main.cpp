#include<iostream>
#include<string>

#include "TaquinGame.h"
#include "SokobanGame.h"
#include "Direction.h"
#include "SokobanElement.h"
#include "TwoThousandAndFortyEightGameVariant1.h"
#include "TwoThousandAndFortyEightGameVariant2.h"
#include "TwoThousandAndFortyEightGameVariant3.h"

using namespace std ;
bool DEBUG_MODE = true;

int main()
{
    int mode, xSize, ySize;
    bool ig, ia;

    if (DEBUG_MODE)
    {
        mode = 3;
        xSize = 10;
        ySize = 10;
        ig = true;
        ia = false;
    }
    else
    {
        cout << "Type : 1) Taquin 2) 2048 3)Sokoban" << endl;
        cin >> mode ;
        cout << "What size do you want ?" << endl;
        cout << "X = ?";
        cin >> xSize ;
        cout << "\nY = ?";
        cin >> ySize;
        string valid;
        cout << "Do you want an IG ?(y/n)" << endl;
        cin >> valid ;
        ig = valid == "y";
        cout << "Do you want an IA ?(y/n)" << endl;
        cin >> valid ;
        ia = valid == "y";
    }

    switch(mode)
    {
    case 1:
    {
        TaquinGame t(xSize,ySize);
        t.play(ig, ia);
        break;
    }
    case 2:
    {
        TwoThousandAndFortyEightGame* t2 = nullptr;
        int varmode;
        cout << "type (0)classic (1)with3,5  (2)with Destroy Tile  (3)with X2,/2" << endl ;
        cin >> varmode;
        switch(varmode)
        {
        case 0:
        {
            t2 = new TwoThousandAndFortyEightGame(xSize,ySize);
            break;
        }
        case 1:
        {
            t2 = new TwoThousandAndFortyEightGameVariant1(xSize,ySize);
            break;
        }
        case 2:
        {
            t2 = new TwoThousandAndFortyEightGameVariant2(xSize,ySize);
            break;
        }
        case 3:
        {
            t2 = new TwoThousandAndFortyEightGameVariant3(xSize,ySize);
            break;
        }
        }
        t2->play(ig, ia);
        delete t2;
        break;
    }
    case 3:
    {
        SokobanGame t3(xSize,ySize);
        t3.play(ig, ia);
        break;
    }
    }
}
