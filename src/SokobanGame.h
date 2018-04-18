#ifndef SOKOBANGAME_H
#define SOKOBANGAME_H

#include "SokobanElement.h"
#include "AbstractGame.h"
#include "SokobanElement.h"
#include <cstdlib>
#include <ctime>
#include<vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<iostream>
#include <sstream>
#include <time.h>
#include <random>


using namespace std ;


class SokobanGame : public AbstractGame <SokobanElement>
{
public :
    SokobanGame(int size) : AbstractGame(size) {}
    SokobanGame(int a , int b): AbstractGame(a,b) {}
    virtual ~SokobanGame() {}

protected:
    Position positionCharacter;
    vector<Position> positionGoals;
    Position bric;
    sf::Color characterColor = sf::Color(9, 106, 9);
    sf::Color boxColor = sf::Color(88, 41, 0);
    sf::Color wallColor = sf::Color(12, 20, 220);
    sf::Color emptyColor = sf::Color(0, 0, 0);
    sf::Color goalColor = sf::Color(240, 195, 0);

    void initializeGrid()
    {
        generateRandomMap();
    }

    void generateRandomMap()
    {
        vector<Position> free;
        random_device rd;
        mt19937 gen(rd());
        int delimitation = 0 ;
        bool posStart=true;
        for(int i=0 ; i < grid->width() ; i++)
        {
            for(int j=0 ; j< grid->height() ; j++)
            {
                uniform_int_distribution<> dis(0, 2);
                Position pos(i,j);
                if(dis(gen) == 0)
                {
                    grid->setValue(pos , Box);
                    bric=pos ;
                    free.push_back(pos);
                    delimitation++ ;
                }
                else if(dis(gen) == 1)
                {
                    grid->setValue(pos , Wall);
                }
                else
                {
                    if(posStart)
                    {
                        Position xp (i,j);
                        positionCharacter = xp ;
                        posStart=false;
                    }
                    grid->setValue(pos , Empty);
                    free.push_back(pos);
                }
            }
        }

        for(int i=0 ; i < delimitation ; i++)
        {
            uniform_int_distribution<> dis2(0, free.size()-1);
            int ran = dis2(gen);
            positionGoals.push_back(free.at(ran));
            free.erase(free.begin()+ran);
        }
    }

    virtual void startTurn() {}

    virtual bool moving(Direction d)
    {
        Position p(positionCharacter);
        Position p2(p);
        switch (d)
        {
        case Direction::Up:
            p.y--;
            p2.y-=2;
            break;
        case Direction::Down:
            p.y++;
            p2.y+=2;

            break;
        case Direction::Left:
            p.x--;
            p2.x-=2;

            break;
        case Direction::Right:
            p.x++;
            p2.x+=2;
            break;
        }

        if(grid->isInGrid(p)  && (grid->getValue(p) == Box  || grid->getValue(p) == Empty))
        {
            if(grid->getValue(p) == Box)
            {
                if(grid->isInGrid(p2) && grid->getValue(p2)!= Wall && grid->getValue(p2)!= Box)
                {
                    bric = p2 ;
                }
                else return false;
            }

            return movingSquare(d,p);
        }

        return false;
    }

    virtual bool movingSquare(Direction d, Position p )
    {
        positionCharacter = p;
        grid->setValue(p , Empty);
        grid->setValue(bric ,Box);
        return true;
    }

    bool endGame()
    {
        for(unsigned int i=0 ; i < positionGoals.size() ; i++)
        {
            if(grid->getValue(positionGoals.at(i)) != Box) return false;
        }
        return true ;
    }

    void drawWindow()
    {
        sf::Vector2i rectangleSize = sf::Vector2i(window.getSize().x / grid->width(),
                                     window.getSize().y / grid->height());

        // Draw goals
        for(unsigned int i=0; i < positionGoals.size(); i++)
        {
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(rectangleSize.x - 1, rectangleSize.y - 1));
            rectangle.move(positionGoals.at(i).x * rectangleSize.x, positionGoals.at(i).y * rectangleSize.y);
            rectangle.setFillColor(goalColor);
            window.draw(rectangle);
        }

        // Draw walls and boxes
        for(int i(0); i < grid->width(); i++)
        {
            for(int j(0); j< grid->height(); j++)
            {
                Position pos(i,j);
                if (grid->getValue(pos) != Empty){
                    sf::RectangleShape rectangle;
                    sf::Text text;

                    // Draw rectangle
                    rectangle.setSize(sf::Vector2f(rectangleSize.x - 1, rectangleSize.y - 1));
                    rectangle.move(i * rectangleSize.x, j * rectangleSize.y);

                    if(grid->getValue(pos) == Wall)
                        rectangle.setFillColor(wallColor);
                    else if(grid->getValue(pos) == Box)
                        rectangle.setFillColor( boxColor);

                    window.draw(rectangle);
                }
            }
        }

        // Draw character
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(rectangleSize.x - 1, rectangleSize.y - 1));
        rectangle.move(positionCharacter.x * rectangleSize.x, positionCharacter.y * rectangleSize.y);
        rectangle.setFillColor(characterColor);
        window.draw(rectangle);
    }
};

#endif
