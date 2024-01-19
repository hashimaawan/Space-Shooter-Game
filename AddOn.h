#include <SFML/Graphics.hpp>
#include <string.h>
using namespace sf;
class AddOn
{
public:
    Texture tex;
    Sprite sprite;
     float speed=0.3;
    int x, y;
    bool isDead;
    float time=0;
   AddOn(){
    isDead=false;
    time =0;

   };
    

};

class Danger : public AddOn
{
    public:
    
    bool isDodge;
    Danger()
    {

    }
    Danger (std::string png_path)
    {
        speed = 0.4;
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        x = 649;
        y = -55;
        sprite.setPosition(x, y);
        sprite.setScale(0.7, 0.7);
        isDodge=true;
    }
   
};

class PowerUp : public  AddOn{
public:
int timeinterval =0;
    PowerUp(){}
    PowerUp(std::string png_path)
    {
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        x = 190;
        y = 0;
        sprite.setPosition(x, y);
        sprite.setScale(0.50, 0.5);
    }
    ~PowerUp()
    {
         
        
    }

};
class Fire : public AddOn
{
public:
int timefire;
   
  
    Fire(std::string png_path)
    {
        timefire=0;
          
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        x = 190;
        y = -45;
        sprite.setPosition(x, y);
        sprite.setScale(1, 1);
    }
   
    void move()
{

}
~Fire(){}


};
class LivesOn : public AddOn
{
public:
    LivesOn(std::string png_path)
    {
          
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        x = 350;
        y = -45;
        sprite.setPosition(x, y);
        sprite.setScale(1.5, 1.5);
    }
    ~LivesOn(){}
   
};