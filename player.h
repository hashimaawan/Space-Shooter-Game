#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>
#include <time.h>
#include "Bullet.h"
// #include "Explosion.h"
using namespace std;
#include "AddOn.h"
using namespace sf;
class Player
{
public:
    Texture tex;
    Sprite sprite;
    float speed = 0.7;
    float timm = 17;
    float timmm = 0;
    static int score;
    float timmfr = 7;
    int x, y;
    Bullet *bullet;
    static int lives;
    Fire *fire;
    AddOn *addon;
    PowerUp *powerUp;
    Danger *danger;
    LivesOn *live;
    // Explosion *explosion;

    bool checkk;
    Player()
    {
        bullet = nullptr;

        powerUp = nullptr;
        fire = nullptr;
        danger = nullptr;
        live = nullptr;
        // explosion = nullptr;
    }
    Player(std::string png_path)
    {

        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        x = 340;
        y = 670;
        sprite.setPosition(x, y);
        sprite.setScale(0.15, 0.15);

        bullet = new Bullet("img/laserGreen12.png");
        this->live = new LivesOn("img/PNG/Power-ups/things_gold.png");
        this->danger = new Danger("img/meteorGrey_big1.png");
        this->fire = new Fire("img/PNG/Power-ups/powerupRed_bolt.png");
        this->powerUp = new PowerUp("img/PNG/Power-ups/bold_silver.png");
        // explosion = NULL;

        checkk = false;
    }

    void bulletr()
    {
        if (this->bullet != nullptr)
        {
            this->bullet->sprite.setPosition(this->bullet->sprite.getPosition().x,
                                             this->bullet->sprite.getPosition().y - this->bullet->speed);
            if (this->bullet->sprite.getPosition().y < 0)
            {
                delete this->bullet;
                this->bullet = nullptr;
                this->bullet = new Bullet("img/laserGreen12.png");
                this->bullet->sprite.setPosition(this->sprite.getPosition().x + 30,
                                                 this->sprite.getPosition().y);
            }
        }
    }

    bool duration(float time1)
    {
      
        time1 = 0;
        if (time1 > 5.f)
            return true;
        else
            return false;
    }
    void liveson(int &lives, float &timer, Music &health)
    {

        if (timer - this->timm > 15)
        {
            if (this->live != NULL)
            {
                this->live->sprite.setPosition(this->live->sprite.getPosition().x, this->live->sprite.getPosition().y + this->live->speed);

                // p->danger->sprite.move(0.025,0);
                if (this->sprite.getPosition().x >= this->live->sprite.getPosition().x - 60 && this->sprite.getPosition().x <= this->live->sprite.getPosition().x + 70 && this->sprite.getPosition().y >= this->live->sprite.getPosition().y - 70 && this->sprite.getPosition().y <= this->live->sprite.getPosition().y + 70)
                {
                    // checkk = true;
                    cout << "Lives";

                    delete this->live;
                    this->live = NULL;
                    this->live = new LivesOn("img/PNG/Power-ups/things_gold.png");
                    this->timm = timer;

                    this->lives++;
                    health.play();
                }
                else if (this->live->sprite.getPosition().y > 780)
                {
                    delete this->live;
                    this->live = NULL;
                    this->live = new LivesOn("img/PNG/Power-ups/things_gold.png");
                    this->timm = timer;
                }
                //------Doesn't effect dangerOn even if bullets will hit it
            }
        }
    }
    void FireOn(float timer)
    {
        if (timer - this->timmfr > 8)
        {

            if (this->fire != NULL)
            {

                this->fire->sprite.setPosition(100, this->fire->sprite.getPosition().y + this->fire->speed);
                if (this->sprite.getPosition().x >= this->fire->sprite.getPosition().x - 60 && this->sprite.getPosition().x <= this->fire->sprite.getPosition().x + 60 && this->sprite.getPosition().y >= this->fire->sprite.getPosition().y - 50 && this->sprite.getPosition().y <= this->fire->sprite.getPosition().y + 50)
                {

                    this->timmfr = timer;
                    checkk = true;


                    delete this->fire;
                    this->fire = NULL;
                    this->fire = new Fire("img/PNG/Power-ups/powerupRed_bolt.png");
                }
                else if (this->fire->sprite.getPosition().y > 780)
                {

                    this->timmfr = timer;
                    delete this->fire;
                    this->fire = NULL;
                    this->fire = new Fire("img/PNG/Power-ups/powerupRed_bolt.png");
                }
            }
        }
    }

    bool getCheck()
    {
        return checkk;
    }

    void move(std::string s)
    {
        float delta_x = 0, delta_y = 0;
        if (s == "l")
        {
            delta_x = -1; // move the player left
        }
        else if (s == "r")
        {
            delta_x = 1; // move the player right
        }
        if (s == "u")
        {
            delta_y = -1; // move the player up
        }
        else if (s == "d")
        {
            delta_y = 1; // move the player down
        }

        // up and right
        if (s == "p")
        {
            delta_y = -1;
            delta_x = 1;
        }

        delta_x *= speed;
        delta_y *= speed;

        // Getting the boundaries of the game window
        float windowWidth = 654;
        float windowHeight = 780;

        // Checking if the player sprite is within the boundaries of the game window

        // Getting the position of the player sprite using sprite.getPosition() and store it in a sf::Vector2f variable named position.
        float X_Po = sprite.getPosition().x;
        float Y_Po = sprite.getPosition().y;

        // Check if the player sprite has gone outside the left boundary of the game window by comparing its x-coordinate to 0 and the width of the sprite using sprite.getTextureRect().width.
        if (X_Po < 0)
        {
            X_Po = windowWidth;
        }

        // If the player sprite has gone outside the right side of boundary, wrap it around to the right side of the window by setting its x-coordinate to windowWidth, which is the width of the game window.
        if (X_Po > windowWidth)
        {
            X_Po = 0;
        }

        if (Y_Po < 0)
        {
            Y_Po = windowHeight;
        }

        // If the player sprite has gone outside the top boundary, wrap it around to the bottom side of the window by setting its y-coordinate to windowHeight, which is the height of the game window.
        if (Y_Po > windowHeight)
        {
            Y_Po = 0;
        }

        // Finally, update the player sprite's position by calling sprite.setPosition(position) with the updated position variable.
        sprite.setPosition(X_Po, Y_Po);
        sprite.move(delta_x, delta_y);
    }

    void draw(RenderWindow &window, float &timer)
    {
        window.draw(this->sprite);
        window.draw(bullet->sprite);
        if (this->danger != NULL)
        {
            if (timer > 10)

            {
                // p->danger->timefire = timer;
                window.draw(this->danger->sprite);
            }
        }
        if (this->live != NULL)
        {
            if (timer > 15)
            // if(p->addon->timeinterval =0)
            {
                // p->danger->timefire = timer;
                window.draw(this->live->sprite);
            }
        }
        if (this->fire != NULL)
        {
            if (timer > 7.f)
            // if(p->addon->timeinterval =0)
            {
                window.draw(this->fire->sprite);
            }
        }
        // window.draw(this->fire->sprite);
    }
    ~Player()
    {
        delete bullet;
        //  delete explosion;
        delete live;
        delete danger;
        delete fire;
    }
};

int Player::lives = 3;
int Player ::score = 0;