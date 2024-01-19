#ifndef FIREDRGN_H
#define FIREDRGN_H
#include <SFML/Graphics.hpp>
using namespace sf;
class FireDrgn
{
public:
    Texture tex;
    Sprite sprite;
    float speed = 1;
    int x, y;
   
  
    FireDrgn(std::string png_path)
    {
          
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);      
        sprite.setScale(1.2, 1.2);
    }
   

};

#endif