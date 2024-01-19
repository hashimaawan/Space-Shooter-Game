#ifndef BOMB_H
#define BOMB_H
#include <SFML/Graphics.hpp>
using namespace sf;
class Bomb
{
public:
    Texture tex;
    Sprite sprite;
    float speed = 0.5;
    int x, y;
      
   
  Bomb(){}
    Bomb(std::string png_path)
    {
          
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);      
        sprite.setScale(0.40, 0.40);
    }


};
#endif

