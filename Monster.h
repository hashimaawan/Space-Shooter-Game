#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "Enemy.h"

using namespace std;
using namespace sf;

// class Monster : public Enemy
// {
// public:
// Texture texture;
// Sprite sprite;
// Clock clock;
// float timer = 0.0f;
// bool is_attacking = false;
// Monster()
// {
//     texture.loadFromFile("img/monster.png");
//     sprite.setTexture(texture);
//     sprite.setScale(0.1f, 0.1f);
//     sprite.setPosition(350, 100);
//     score= 40;
// }
// Monster(string png_path)
// {
//     score = 40;
//     tex.loadFromFile(png_path);
//     sprite.setTexture(tex);
//     x = 190;
//     y = 90;
//     sprite.setPosition(x, y);
//     sprite.setScale(0.5, 0.5);
   
// }
// int getScore()
// {
//     return score;
// }

// void update(float dt, int& xpos, int& ypos)
// {
//     timer += dt;
//     if (timer > 2.0f)
//     {
//         timer = 0.0f;
//         is_attacking = true;
//     }

//     if (is_attacking)
//     {
      
//         float monster_x = sprite.getPosition().x;
//         float monster_y = sprite.getPosition().y;

//         if (xpos < ypos)
//         {
//             sprite.move(-0.2f, 0);
//         }
//         else if (xpos > ypos)
//         {
//             sprite.move(0.2f, 0);
//         }

       
//     }
// }

// void draw(RenderWindow& window)
// {
//     window.draw(sprite);
// }
// };