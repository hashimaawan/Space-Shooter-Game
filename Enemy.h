#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Bomb.h"
#include "Explosion.h"
#include "FireDrgn.h"

class Enemy
{
protected:
    int score;

public:
    sf::Texture tex;
    sf::Sprite sprite;
    FireDrgn *firdn[3];
    float speed = 0.5;
    int x, y;
    bool isDead = false;
    bool isAttack;
    bool isDodge;
    Bomb *b;
    Explosion *explosion;

    float bmbtimer;

    Enemy();
    virtual void move(float &time, int x, int y)
    {
    }
    virtual int getScore() = 0;
};

class Invaderr : public Enemy
{
public:
    float speed = 0.8;

    virtual int getScore();
};

class Alphaa : public Invaderr
{
public:
    Alphaa(std::string png_p);

    virtual int getScore();

    ~Alphaa();
};

class Beta : public Invaderr
{
public:
    Beta(std::string png_p);

    virtual int getScore();

    ~Beta();
};

class Gamma : public Invaderr
{
public:
    Gamma(std::string png_p);

    virtual int getScore();

    ~Gamma();
};

class Dragon : public Enemy
{
public:
    Dragon(std::string png_path);

    virtual int getScore();

    void move();
};

class Monster : public Enemy
{
public:
    float timer = 0.0f;
   
    Monster(std::string png_path)
    {
        score = 40;
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        x = 190;
        y = 90;
        sprite.setPosition(x, y);
        sprite.setScale(0.3, 0.3);
        isAttack = false;
         b = new Bomb("img/PNG/Lasers/laserGreen04.png");
        b->sprite.setPosition(this->sprite.getPosition().x + 60, this->sprite.getPosition().y);
        b->sprite.setScale(1, 1);
        isDodge =false;
    }
    int getScore()
    {
        return score;
    }
    void move(float &time, int x, int y)
    {
        timer += time;

        if (x < this->sprite.getPosition().x)
        {
            this->sprite.move(-0.2f, 0);
        }
        else if (x > this->sprite.getPosition().x)
        {
            isAttack =true;
            this->sprite.move(0.2f, 0);
            if (this->b != nullptr)
            {
                this->b->sprite.setPosition(this->b->sprite.getPosition().x,
                                            this->b->sprite.getPosition().y + this->b->speed);
                                            
                if (this->b->sprite.getPosition().y > 780)
                {
                    delete this->b;
                    this->b = nullptr;
                    this->b = new Bomb("img/PNG/Lasers/laserGreen04.png");
                    b->sprite.setScale(1, 1);
                    this->b->sprite.setPosition(this->sprite.getPosition().x + 60,
                                                this->sprite.getPosition().y);
                }
            }
        }
    }
   
};

#endif
