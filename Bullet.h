#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
using namespace sf;
class Bullet
{
public:
    Texture tex;
    Sprite sprite;
    float speed = 3;
    int x, y;
   
  
    Bullet(std::string png_path)
    {
          
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);      
        sprite.setScale(1.2, 1.2);
    }
   
    void move()
{

}


};

#endif