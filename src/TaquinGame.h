#ifndef TAQUINGAME_H
#define TAQUINGAME_H

#include "AbstractGame.h"
#include <cstdlib>

#include <ctime>
#include<vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<iostream>
#include <sstream>
#include <time.h>
#include <random>


class TaquinGame : public AbstractGame <int>
{
public:
    TaquinGame(int size): AbstractGame(size) {}
    TaquinGame(int a , int b): AbstractGame(a,b) {}
    virtual ~TaquinGame() {}

protected:
    Position positionEmptySquare;
    sf::Color emptyColor = sf::Color(2, 0, 0);
    sf::Color fillColor = sf::Color(50, 40, 220);
    int emptyValue = 0;


    virtual void initializeGrid()
    {
        generateResolvableGrid();
    }

    void generateResolvableGrid(int degree = 5)
    {
        int initValue = 0;
        for(int j = 0 ; j < grid->height(); j++)
        {
            for(int i = 0 ; i < grid->width(); i++)
            {
                Position pos(i,j);
                grid->setValue(pos, initValue);
                initValue++;
            }
        }
        random_device rand;
        mt19937 gen(rand());
        uniform_int_distribution<> dis(0, 3);

        for(int i(0); i < degree; i++)
        {
            while (!moving(static_cast<Direction>(dis(gen)))) {}
        }
    }

    virtual void startTurn() {}

    virtual bool moving(Direction d)
    {
        Position p(positionEmptySquare);
        switch (d)
        {
        case Direction::Up:
            p.y++;
            break;
        case Direction::Down:
            p.y--;
            break;
        case Direction::Left:
            p.x++;
            break;
        case Direction::Right:
            p.x--;
            break;
        default:
            cout << "Error : wrong direction" << endl;
        }
        if(grid->isInGrid(p))
        {
            movingSquare(d,p);
            return true;
        }

        return false;
    }

    virtual bool movingSquare(Direction d, Position p)
    {
        grid->setValue(positionEmptySquare, grid->getValue(p));
        grid->setValue(p,emptyValue);
        positionEmptySquare = p;
        return true;
    }

    virtual bool endGame()
    {
        int index = 0;
        for(int j(0); j < grid->height(); j++)
        {
            for(int i(0); i < grid->width(); i++)
            {
                if(index != grid->getValue(Position(i,j))) return false;
                index++;
            }
        }
        return true;
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
                if(grid->getValue(pos) == emptyValue)
                    rectangle.setFillColor(emptyColor);
                else
                    rectangle.setFillColor(fillColor);
                window.draw(rectangle);

                // Draw text
                if(grid->getValue(pos) != emptyValue)
                {
                    text.setFont(font);
                    text.setCharacterSize(fontSize);
                    text.setColor(sf::Color::White);
                    text.setString(intToString(grid->getValue(pos)));
                    text.setPosition(rectangle.getPosition().x + (rectangle.getSize().x / 2) - (text.getGlobalBounds().width / 2),
                                     rectangle.getPosition().y + (rectangle.getSize().y / 2) - (fontSize / 2));
                    window.draw(text);
                }
            }
        }
    }
};

#endif
