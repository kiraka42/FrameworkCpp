#ifndef ABSTRACTGAME_H
#define ABSTRACTGAME_H

#include<iostream>
#include <chrono>
#include <thread>
#include "Direction.h"
#include "Grid.h"

using namespace std ;

template <typename T>
class AbstractGame
{

public :
    AbstractGame(int s) : AbstractGame(s,s) {}

    AbstractGame(int a, int b, int wait = 200000) : frameWait(wait)
    {
        grid = new Grid<T>(a,b);
    }

    virtual ~AbstractGame()
    {
        delete grid ;
    }

    void play(bool ig, bool ia)
    {
        // Initialize
        if (ig)
        {
            window.create(sf::VideoMode(600, 600), "Game");
            window.setPosition(sf::Vector2i(220, 120));
            if (!font.loadFromFile("font/arial.ttf")) cout << "error in loading font file" << endl;
            window.clear(sf::Color::White);
            window.display();
        }
        initializeGrid();
        draw(ig);

        // Game loop
        while (!ig || window.isOpen())
        {
            startTurn();
            gameOver = endGame();
            if (gameOver) break;
            draw(ig);
            Direction d;
            do
            {
                d = ia ? robotAction() : humanAction(ig);
            }
            while(!moving(d));
            draw(ig);

            // If ia, wait before next action
            if (ia) wait(frameWait);
        }

        // End of the game
        if (gameOver)
        {
            if (ig)
            {
                sf::Event event;
                draw(ig);
                while (window.isOpen())
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed) window.close();
                    }
                }
            }
            else
            {
                cout << "End of the game !" << endl;
            }
        }
    }

protected :
    Grid<T>* grid ;
    sf::RenderWindow window;
    sf::Font font;
    int frameWait;
    bool gameOver = false;

    virtual void initializeGrid() = 0;
    virtual void startTurn() = 0;
    virtual bool moving(Direction d) = 0;
    virtual bool movingSquare(Direction d, Position p ) = 0;
    virtual bool endGame() = 0;
    virtual void drawWindow() = 0;

    Direction humanAction(bool ig)
    {
        if (ig)
        {
            sf::Event event;
            while (window.isOpen())
            {
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed) window.close();
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) return Direction::Up;
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) return Direction::Down;
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) return Direction::Left;
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) return Direction::Right;
                }
            }
        }
        else
        {
            while (true)
            {
                cout << "Your Move ?(\u21E7 =z ,\u21E6  =q , \u21E8 =d ,\u21E9 =s) : " << endl;
                string userEntry;
                cin >> userEntry;
                if (userEntry == "z") return Direction::Up;
                else if (userEntry == "s") return Direction::Down;
                else if (userEntry == "q") return Direction::Left;
                else if (userEntry == "d") return Direction::Right;
            }
        }

        return Direction::Up;
    }

    Direction robotAction()
    {
        int action = std::rand() % 4;
        return static_cast<Direction>(action);
    }

    void draw(bool ig)
    {
        if (ig)
        {
            window.clear(sf::Color::White);
            drawWindow();
            drawGameOver();
            window.display();
        }
        else
        {
            grid->draw();
        }
    }

    void virtual drawGameOver(){
        if (gameOver)
        {
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(window.getSize().x / 8);
            text.setColor(sf::Color::Red);
            text.setString("GAME OVER");
            text.setPosition((window.getSize().x / 2) - (text.getGlobalBounds().width / 2),
                             (window.getSize().y / 2) - (text.getGlobalBounds().height / 2));
            window.draw(text);
        }
    }

    void wait(int t)
    {
        sf::Event event;
        while (window.isOpen())
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) window.close();
            }
            t--;
            if (t==0) return;
        }
    }

    // Utils functions

    std::string intToString(int i) const
    {
        std::ostringstream oss;
        oss << i;
        return oss.str();
    }

    int StringToInt(std::string str) const
    {
        return atoi(str.c_str());
    }

    bool isInteger(const string & s)
    {
        if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

        char * p ;
        strtol(s.c_str(), &p, 10) ;

        return (*p == 0) ;
    }
};

#endif
