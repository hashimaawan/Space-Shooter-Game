#include "Enemy.h"

Enemy::Enemy()
{
}

int Invaderr::getScore()
{
    return score;
}

Alphaa::Alphaa(std::string png_p)
{
    tex.loadFromFile(png_p);
    sprite.setTexture(tex);

    sprite.setPosition(x, y);
    sprite.setScale(0.4, 0.4);
    explosion = NULL;
    b = nullptr;

    bmbtimer = 0;
    score = 10;
}

int Alphaa::getScore()
{
    return score;
}

Alphaa::~Alphaa()
{
     delete b;
}

Beta::Beta(std::string png_p)
{
    tex.loadFromFile(png_p);
    sprite.setTexture(tex);

    sprite.setPosition(x, y);
    sprite.setScale(0.4, 0.4);

    b = nullptr;
    explosion = NULL;
    bmbtimer = 0;
    score = 20;
}

int Beta::getScore()
{
    return score;
}

Beta::~Beta()
{
    delete explosion;
     delete b;
}

Gamma::Gamma(std::string png_p)
{
    tex.loadFromFile(png_p);
    sprite.setTexture(tex);

    sprite.setPosition(x, y);
    sprite.setScale(0.3, 0.4);

    bmbtimer = 0;
    explosion = NULL;
    score = 30;
    b = nullptr;
}

int Gamma::getScore()
{
    return score;
}

Gamma::~Gamma()
{
     delete b;
}

Dragon::Dragon(std::string png_path)
{
    score = 40;
    tex.loadFromFile(png_path);
    sprite.setTexture(tex);
    x = 190;
    y = 90;
    sprite.setPosition(x, y);
    sprite.setScale(0.5, 0.5);
    firdn[0] = new FireDrgn("img/fire0.png");
    firdn[1] = new FireDrgn("img/fire0.png");
    firdn[2] = new FireDrgn("img/fire0.png");
}

int Dragon::getScore()
{
    return score;
}

