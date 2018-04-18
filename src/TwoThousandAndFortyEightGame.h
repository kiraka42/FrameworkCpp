#ifndef TWOTHOUSANDANDFORTYHEIGHTGAME_H
#define TWOTHOUSANDANDFORTYHEIGHTGAME_H

#include "AbstractGame.h"
#include "TwoThousandAndFortyEightElement.h"

#include<string>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include<sstream>
#include<time.h>
#include<random>

using namespace std ;

class TwoThousandAndFortyEightGame : public AbstractGame <TwoThousandAndFortyEightElement>
{
public :
    TwoThousandAndFortyEightGame(int size) : AbstractGame(size) {}
    TwoThousandAndFortyEightGame(int a , int b) : AbstractGame(a,b) {}
    virtual ~TwoThousandAndFortyEightGame() {}

protected :
    bool testingGameOver = false;
    vector<string> elements = vector<string>({"2","4"});
    vector<int> elementsProba = vector<int>({90,10}); // coefficients probability of apparition
    sf::Color blankColor = sf::Color(200,200,200);
    std::string emptyValue = "0";


    virtual void initializeGrid()
    {
        for(int i(0) ; i < grid->width() ; i++)
        {
            for(int j(0) ; j < grid->height() ; j++)
            {
                grid->setValue(Position(i,j), TwoThousandAndFortyEightElement(emptyValue));
            }
        }
        startTurn();
    }

    virtual void startTurn()
    {
        // Small wait before showing
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        vector<Position> freeSquares;
        for(int i(0) ; i < grid->width() ; i++)
        {
            for(int j(0) ; j < grid->height() ; j++)
            {
                Position pos(i,j);
                if (grid->getValue(pos).text() == emptyValue) freeSquares.push_back(pos);
            }
        }

        if(freeSquares.size() != 0)
        {
            int  probaSum = 0;
            for (unsigned int i(0); i < elementsProba.size(); i++) probaSum += elementsProba[i];

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, freeSquares.size()-1);
            uniform_int_distribution<> disNum(1,probaSum);
            int num = disNum(gen);
            string element = elements[0];
            probaSum = 0;
            for (unsigned int i(0); i < elements.size(); i++)
            {
                probaSum += elementsProba[i];
                if (probaSum >= num)
                {
                    element = elements[i];
                    break;
                }
            }
            grid->setValue(freeSquares.at(dis(gen)), TwoThousandAndFortyEightElement(element));
        }
    }

    virtual bool moving(Direction d)
    {
        bool changing = false;
        switch (d)
        {
        case Direction::Up:
            for (int j(0); j < grid->height(); j++)
            {
                for (int i(0); i < grid->width(); i++)
                {
                    changing |= tryMovingSquare(d, Position(i,j));
                    if (testingGameOver && changing) return true;
                }
            }
            break;
        case Direction::Down:
            for (int j(grid->height()-1); j >= 0; j--)
            {
                for (int i(0); i < grid->width(); i++)
                {
                    changing |= tryMovingSquare(d, Position(i,j));
                    if (testingGameOver && changing) return true;
                }
            }
            break;
        case Direction::Left:
            for (int i(0); i < grid->width(); i++)
            {
                for (int j(0); j < grid->height(); j++)
                {
                    changing |= tryMovingSquare(d, Position(i,j));
                    if (testingGameOver && changing) return true;
                }
            }
            break;
        case Direction::Right:
            for (int i(grid->width()-1); i >= 0; i--)
            {
                for (int j(0); j < grid->height(); j++)
                {
                    changing |= tryMovingSquare(d, Position(i,j));
                    if (testingGameOver && changing) return true;
                }
            }
            break;
        }

        // Reseting fusionned to false
        if (!testingGameOver) resetFusion();

        return changing;
    }

    bool tryMovingSquare(Direction d, Position p)
    {
        if (grid->getValue(p).text() != emptyValue) return movingSquare(d, p);
        return false;
    }

    virtual bool movingSquare(Direction d, Position p)
    {
        Position newPos(p);
        switch (d)
        {
        case Direction::Up:
            newPos.y--;
            break;
        case Direction::Down:
            newPos.y++;
            break;
        case Direction::Left:
            newPos.x--;
            break;
        case Direction::Right:
            newPos.x++;
            break;
        }
        std::string res = "-1";
        if (grid->isInGrid(newPos) && !grid->getValue(newPos).isFusionned())
        {
            res = tryFusion(p, newPos);
            if (res == emptyValue)
            {
                movingSquare(d, newPos);
            }
        }

        return res != "-1";
    }

    virtual std::string tryFusion(Position& p1, Position& p2)  // p1 is the moved square
    {
        std::string value1 = grid->getValue(p1).text(), value2 = grid->getValue(p2).text();
        if (value2 == emptyValue)
        {
            invertSquares(p1, p2);
            return emptyValue;
        }
        else if (value1 == value2)
        {
            return power(StringToInt(value1), p1, p2);
        }

        return "-1";
    }

    void invertSquares(Position& p1, Position& p2)
    {
        if (!testingGameOver)
        {
            TwoThousandAndFortyEightElement tmp = grid->getValue(p1);
            grid->setValue(p1,grid->getValue(p2));
            grid->setValue(p2,tmp);
        }
    }

    virtual std::string power(int v, Position& p1, Position& p2)
    {
        // If multiple of 2
        if (v % 2 == 0)
        {
            std::string res = intToString(v*2);
            fusion(p1,p2,res);
            return res;
        }
        return "-1";
    }

    void fusion(Position& p1, Position& p2, std::string newValue)
    {
        if (!testingGameOver)
        {
            grid->setValue(p1, TwoThousandAndFortyEightElement(emptyValue));
            grid->setValue(p2, TwoThousandAndFortyEightElement(newValue, true));
        }
    }

    void resetFusion()
    {
        for (int i(0); i < grid->width(); i++)
        {
            for (int j(0); j < grid->height(); j++)
            {
                TwoThousandAndFortyEightElement e(grid->getValue(Position(i,j)).text(), false);
                grid->setValue(Position(i,j), e);
            }
        }
    }

    virtual bool endGame()
    {
        testingGameOver = true;

        // If any direction can't change the state of the game...
        bool test = false;
        test |= moving(Direction::Up);
        test |= moving(Direction::Down);
        test |= moving(Direction::Left);
        test |= moving(Direction::Right);

        testingGameOver = false;

        return !test;
    }

    virtual void drawWindow()
    {
        sf::Vector2i rectangleSize = sf::Vector2i(window.getSize().x / grid->width(),
                                     window.getSize().y / grid->height());
        int fontSize = (rectangleSize.x / 2) - 5;

        for(int i(0); i < grid->width(); i++)
        {
            for(int j(0); j< grid->height(); j++)
            {
                Position pos(i,j);
                sf::RectangleShape rectangle;
                sf::Text text;

                // Draw rectangle
                rectangle.setSize(sf::Vector2f(rectangleSize.x - 1, rectangleSize.y - 1));
                rectangle.move(i * rectangleSize.x, j * rectangleSize.y);
                fillRectangle(pos, rectangle);
                window.draw(rectangle);

                // Draw text
                if(grid->getValue(pos).text() != emptyValue)
                {
                    text.setFont(font);
                    text.setCharacterSize(fontSize);
                    text.setColor(sf::Color::White);
                    text.setString(grid->getValue(pos).text());
                    text.setPosition(rectangle.getPosition().x + (rectangle.getSize().x / 2) - (text.getGlobalBounds().width / 2),
                                     rectangle.getPosition().y + (rectangle.getSize().y / 2) - (fontSize / 2));
                    window.draw(text);
                }
            }
        }
    }

    virtual void fillRectangle(Position& pos, sf::RectangleShape& rectangle)
    {
        if(grid->getValue(pos).text() == emptyValue)
            rectangle.setFillColor(blankColor);
        else
        {
            int v = StringToInt(grid->getValue(pos).text()) / 2;
            rectangle.setFillColor(sf::Color(20*v % 255, 10*v % 255, 5*v % 255));
        }
    }
};


#endif
