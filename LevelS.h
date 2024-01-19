#ifndef LevelS_H
#define LevelS_H
#include <SFML/Graphics.hpp>
using namespace sf;
class LeveLs
{
public:
    Texture tex;
    Sprite sprite;
    float speed = 1.8;
    int x, y;

    LeveLs() {}
    LeveLs(std::string png_path)
    {

        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        sprite.setScale(0.3, 0.3);
    }

    void move()
    {
    }
};

class Level2: public LeveLs
{
    public:
    Level2(std::string png_path)
    {

        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        sprite.setScale(0.3, 0.3);
    }


};

#endif