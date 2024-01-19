#ifndef EXPLOSION_H
#define EXPLOSION_H
#include <SFML/Graphics.hpp>
using namespace sf;
class Explosion
{
public:
    Texture tex;
    Sprite sprite;
    float speed = 0.2;
    int x, y;
      
   
  Explosion(){}
Explosion(std::string png_path)
    {
          
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);      
        sprite.setScale(0.40, 0.40);
    }


};
#endif

