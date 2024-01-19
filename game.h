
#include <iostream>
using namespace std;
#include "math.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "player.h"
#include "menu.h"
#include "Enemy.cpp"
#include "Enemy.h"
#include "LevelS.h"
#include "fstream"

const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:
    ScoreManager *high_Score = new ScoreManager("highscores.txt");
    bool check = false;
    bool is_pause = true;
    Sprite background, frame, frame2; // Game background sprite
    Texture bg_texture, frame1, frametex;

    int casse = 0;
    Texture t, ef;
    int counter = 0;

    float timedanger = 0.f;

    Player *p; // player
    Enemy *monstr;
    Enemy *dragon; // Dragon
    Menu *M;       // Menu

    int level = 1;

    Enemy *enemy[12];
    bool checkk = false;
    LeveLs *lev;
    Level2 *lev2;

    Game()
    {
        M = new Menu;
        p = new Player("img/playership.png"); //--------------Player
        for (int i = 0; i < 5; i++)
        {
            enemy[i] = new Gamma("img/enemy_3.png");
        }
        for (int i = 5; i < 9; i++)
        {
            enemy[i] = new Beta("img/enemy_2.png");
        }
        for (int i = 9; i < 12; i++)
        {
            enemy[i] = new Alphaa("img/enemy_1.png");
        }
        //------------ Dragon
        dragon = new Dragon("img/dragon2.png");
        monstr = new Monster("img/monster.png");

        lev2 = new Level2("img/levell2.png");
        lev = new LeveLs("img/levell1.png");
        // M->display_Menu();

        //   Gamma
        enemy[0]->sprite.setPosition(100, 50);
        enemy[1]->sprite.setPosition(200, 50);
        enemy[2]->sprite.setPosition(300, 50);
        enemy[3]->sprite.setPosition(400, 50);
        enemy[4]->sprite.setPosition(500, 50);

        // Beta
        enemy[5]->sprite.setPosition(150, 150);
        enemy[6]->sprite.setPosition(100, 50);
        enemy[7]->sprite.setPosition(450, 150);
        enemy[8]->sprite.setPosition(450, 150);

        // Alpha
        enemy[9]->sprite.setPosition(260, 270);
        enemy[10]->sprite.setPosition(360, 270);
        enemy[11]->sprite.setPosition(300, 370);

        for (int i = 0; i < 12; i++)
        {
            enemy[i]->b = new Bomb("img/laserRed08.png");
            enemy[i]->b->sprite.setPosition(enemy[i]->sprite.getPosition().x,
                                            enemy[i]->sprite.getPosition().y);
        }

        bg_texture.loadFromFile("img/backgroundn.jpg");
        frame1.loadFromFile("img/frame.png");
        frametex.loadFromFile("img/frame 1.png");

        background.setTexture(bg_texture);
        background.setScale(1.0, 1.2);

        frame.setTexture(frame1);
        frame.setScale(0.99, 0.5);
        frame.setPosition(695, -10);

        frame2.setTexture(frametex);
        frame2.setScale(0.99, 1.5);
        frame2.setPosition(695, 168);
        lev->sprite.setPosition(740, 270);
        lev2->sprite.setPosition(1000, 0);

        dragon->sprite.setPosition(200, 20);
    }
    ~Game()
    {
        if (p != NULL)
        {
            delete p;
            p = NULL;
        }
        if (M != NULL)
        {
            delete M;
            M = NULL;
        }
        for (int i = 0; i < 12; i++)
        {
            if (enemy[i] != NULL)
            {
                delete enemy[i];
                enemy[i] = NULL;
            }
        }
        if (high_Score != NULL)
        {
            delete high_Score;
            high_Score = NULL;
        }
        if (lev != NULL)
        {
            delete lev;
            lev = NULL;
        }
        if (lev2 != NULL)
        {
            delete lev2;
            lev2 = NULL;
        }
    }

    void start_game()
    {
        if (M->isGameStarted)
        {
            srand(time(0));
            RenderWindow window(VideoMode(924, 780), title);
            Clock clock, clock2;
            float timer = 0;
            float timer2 = 0;

            Music music1, music2, health, levelcom, gameover;
            Music music;
            music.openFromFile("MusiC/Space Shooter_Sounds_background.wav");
            music.play();

            music1.openFromFile("MusiC/rock-destroy-6409.wav");
            gameover.openFromFile("MusiC/gameover.ogg");
            health.openFromFile("MusiC/health-pickup-6860.ogg");
            levelcom.openFromFile("MusiC/game-level-complete-143022.ogg");

            Font font;
            font.loadFromFile("Roboto.ttf");
            Text startGameText("Start Game", font, 30);
            startGameText.setPosition(300, 200);

            window.setFramerateLimit(2000);
            while (window.isOpen())
            {
                float time = clock.getElapsedTime().asSeconds();
                float time2 = clock2.getElapsedTime().asSeconds();
                clock.restart();
                timer += time;
                Event e;

                Text Lives("Score: " + to_string(p->score), font, 20);
                Lives.setPosition(762, 85);
                Lives.setFillColor(Color::Green);
                Lives.setOutlineColor(Color::Red);

                Text Tiime(to_string((timer)), font, 30);
                Tiime.setPosition(740, 665);
                Tiime.setFillColor(Color::Green);
                Tiime.setOutlineColor(Color::Red);

                if (p->lives > 3)
                {
                    p->lives = 3;
                }
                Text Lives2("Lives: " + std::to_string(p->lives), font, 20);
                Lives2.setPosition(0, 0);
                Lives2.setFillColor(Color::Cyan);
                Lives2.setOutlineThickness(4);

                Text Lives1("Level:  " + std::to_string(level), font, 20);
                Lives1.setPosition(762, 50);
                Lives1.setFillColor(Color::Green);
                Lives1.setOutlineColor(Color::Red);

                while (window.pollEvent(e))
                {
                    if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    {
                        window.close(); // close the game
                        high_Score->SaveScore(p->score);
                    }
                }
                if (p != NULL)
                {
                    if (Keyboard::isKeyPressed(Keyboard::Left))                                              // If left key is pressed
                        p->move("l");                                                                        // Player will move to left
                    if (Keyboard::isKeyPressed(Keyboard::Right))                                             // If right key is pressed
                        p->move("r");                                                                        // player will move to right
                    if (Keyboard::isKeyPressed(Keyboard::Up))                                                // If up key is pressed
                        p->move("u");                                                                        // playet will move upwards
                    if (Keyboard::isKeyPressed(Keyboard::Down))                                              // If down key is pressed
                        p->move("d");                                                                        // player will move downwards
                    if ((Keyboard::isKeyPressed(Keyboard::Up)) && (Keyboard::isKeyPressed(Keyboard::Right))) // If down key is pressed
                        p->move("p");                                                                        // player will move downwards

                    if (Keyboard::isKeyPressed(Keyboard::Escape)) // if escape key pressesd then close window
                    {
                        window.close();
                        high_Score->SaveScore(p->score);
                    }

                    // If space key pressed then game will be paused
                    if (Keyboard::isKeyPressed(Keyboard::Space))
                    {
                        is_pause = false;
                        M->isGameStarted = false;
                        M->isResume = true;
                        music.pause();
                        M->Ismusic = false;
                        M->display_Menu();
                    }
                    if (Keyboard::isKeyPressed(Keyboard::C)) // If C pressed Game will continue
                    {
                        is_pause = true;
                        music.play();
                    }
                }
                ////////////////////////////////////////////////
                /////  Call your functions here            ////
                //////////////////////////////////////////////

                if (is_pause == true)
                {

                    ///////////////////////////////////////////
                    //// //----Bullet-------//
                    if (p->bullet != NULL)
                        p->bulletr();

                    /////////////////////////////////////////////////////
                    ////------- FIRE ON---------------------///////////
                    /////////////////////////////////////////////////////////

                    if (p->fire != NULL)
                        p->FireOn(timer); // Bullet will kill all enemies in it's way

                    /////////////////////////////////////////////////////////
                    /////-----------Lives On -------------------////////////
                    ///////////////////////////////////////////////////////
                    if (p->live != NULL)
                        p->liveson(p->lives, timer, health);

                    //////////////////////////////////////////////////////
                    ////////--------------------BOMB------///////////////
                    /////////////////////////////////////////////////////

                    if (level == 1)
                    {
                        for (int i = 0; i < 5; i++)
                        {

                            if (enemy[i] != NULL)
                            {
                                if (timer - enemy[i]->bmbtimer >= 2) // m[i]->randomInterval * 60000)
                                {

                                    enemy[i]->b->sprite.setPosition(enemy[i]->b->sprite.getPosition().x,
                                                                    enemy[i]->b->sprite.getPosition().y + enemy[i]->b->speed);

                                    if ((enemy[i]->b->sprite.getPosition().y > 780))
                                    {

                                        enemy[i]->bmbtimer = timer;
                                        delete enemy[i]->b;
                                        enemy[i]->b = nullptr;
                                        enemy[i]->b = new Bomb("img/laserRed08.png");
                                        enemy[i]->b->sprite.setPosition(enemy[i]->sprite.getPosition().x + 10,
                                                                        enemy[i]->sprite.getPosition().y + 12);
                                    }
                                }
                            }
                        }
                        for (int i = 5; i < 9; i++)
                        {
                            if (enemy[i] != NULL)
                            {
                                if (timer - enemy[i]->bmbtimer >= 3) // m[i]->randomInterval * 60000)
                                {

                                    enemy[i]->b->sprite.setPosition(enemy[i]->b->sprite.getPosition().x,
                                                                    enemy[i]->b->sprite.getPosition().y + enemy[i]->b->speed);

                                    if ((enemy[i]->b->sprite.getPosition().y > 780))
                                    {

                                        enemy[i]->bmbtimer = timer;
                                        delete enemy[i]->b;
                                        enemy[i]->b = nullptr;
                                        enemy[i]->b = new Bomb("img/laserRed08.png");
                                        enemy[i]->b->sprite.setPosition(enemy[i]->sprite.getPosition().x + 10,
                                                                        enemy[i]->sprite.getPosition().y + 12);
                                    }
                                }
                            }
                        }
                        for (int i = 9; i < 12; i++)
                        {

                            if (enemy[i] != NULL)
                            {
                                if (timer - enemy[i]->bmbtimer >= 5) // m[i]->randomInterval * 60000)
                                {

                                    enemy[i]->b->sprite.setPosition(enemy[i]->b->sprite.getPosition().x,
                                                                    enemy[i]->b->sprite.getPosition().y + enemy[i]->b->speed);

                                    if ((enemy[i]->b->sprite.getPosition().y > 780))
                                    {

                                        enemy[i]->bmbtimer = timer;
                                        delete enemy[i]->b;
                                        enemy[i]->b = nullptr;
                                        enemy[i]->b = new Bomb("img/laserRed08.png");
                                        enemy[i]->b->sprite.setPosition(enemy[i]->sprite.getPosition().x + 10,
                                                                        enemy[i]->sprite.getPosition().y + 12);
                                    }
                                }
                            }
                        }
                    }
                    if (level >= 2)
                    {
                        for (int i = 0; i < 5; i++)
                        {

                            if (enemy[i] != NULL)
                            {
                                if (timer - enemy[i]->bmbtimer >= 1) // m[i]->randomInterval * 60000)
                                {

                                    enemy[i]->b->sprite.setPosition(enemy[i]->b->sprite.getPosition().x,
                                                                    enemy[i]->b->sprite.getPosition().y + enemy[i]->b->speed);

                                    if ((enemy[i]->b->sprite.getPosition().y > 780))
                                    {

                                        enemy[i]->bmbtimer = timer;
                                        delete enemy[i]->b;
                                        enemy[i]->b = nullptr;
                                        enemy[i]->b = new Bomb("img/laserRed08.png");
                                        enemy[i]->b->sprite.setPosition(enemy[i]->sprite.getPosition().x + 10,
                                                                        enemy[i]->sprite.getPosition().y + 12);
                                    }
                                }
                            }
                        }
                        for (int i = 5; i < 9; i++)
                        {
                            if (enemy[i] != NULL)
                            {
                                if (timer - enemy[i]->bmbtimer >= 2) // m[i]->randomInterval * 60000)
                                {

                                    enemy[i]->b->sprite.setPosition(enemy[i]->b->sprite.getPosition().x,
                                                                    enemy[i]->b->sprite.getPosition().y + enemy[i]->b->speed);

                                    if ((enemy[i]->b->sprite.getPosition().y > 780))
                                    {

                                        enemy[i]->bmbtimer = timer;
                                        delete enemy[i]->b;
                                        enemy[i]->b = nullptr;
                                        enemy[i]->b = new Bomb("img/laserRed08.png");
                                        enemy[i]->b->sprite.setPosition(enemy[i]->sprite.getPosition().x + 10,
                                                                        enemy[i]->sprite.getPosition().y + 12);
                                    }
                                }
                            }
                        }
                        for (int i = 9; i < 12; i++)
                        {

                            if (enemy[i] != NULL)
                            {
                                if (timer - enemy[i]->bmbtimer >= 4) // m[i]->randomInterval * 60000)
                                {

                                    enemy[i]->b->sprite.setPosition(enemy[i]->b->sprite.getPosition().x,
                                                                    enemy[i]->b->sprite.getPosition().y + enemy[i]->b->speed);

                                    if ((enemy[i]->b->sprite.getPosition().y > 780))
                                    {

                                        enemy[i]->bmbtimer = timer;
                                        delete enemy[i]->b;
                                        enemy[i]->b = nullptr;
                                        enemy[i]->b = new Bomb("img/laserRed08.png");
                                        enemy[i]->b->sprite.setPosition(enemy[i]->sprite.getPosition().x + 10,
                                                                        enemy[i]->sprite.getPosition().y + 12);
                                    }
                                }
                            }
                        }
                    }
                    /////////////////////////////////////////////////////////////////
                    ///////-------------- DANGER ON -------------///////////////////
                    ////////////////////////////////////////////////////////////////
                    if (p->danger != NULL)
                    {

                        if (timer - timedanger >= 10.f)
                        {

                            p->danger->sprite.setPosition(p->danger->sprite.getPosition().x - 0.1, p->danger->sprite.getPosition().y + p->danger->speed);

                            if (p->sprite.getPosition().x >= p->danger->sprite.getPosition().x - 45 && p->sprite.getPosition().x <= p->danger->sprite.getPosition().x + 50 && p->sprite.getPosition().y >= p->danger->sprite.getPosition().y - 40 && p->sprite.getPosition().y <= p->danger->sprite.getPosition().y + 50)
                            {
                                timedanger = timer;
                                p->danger->isDodge = false;
                                delete p;
                                p = NULL;
                                p = new Player("img/playership.png");
                                p->lives--;

                                delete p->danger;
                                p->danger = NULL;
                                p->danger = new Danger("img/meteorGrey_big1.png");

                                
                            }
                            else
                            {
                                if (p->danger != NULL)
                                {
                                    if ((p->danger->sprite.getPosition().y > 780) && (p->danger->isDodge))
                                    {

                                        timedanger = timer;
                                        p->danger->isDodge = false;
                                        p->score += 5;
                                        delete p->danger;
                                        p->danger = NULL;
                                        p->danger = new Danger("img/meteorGrey_big1.png");
                                    }
                                }
                            }
                            //------Doesn't effect dangerOn even if bullets will hit it
                        }
                    }
                }
                ///////////////////////////////////////////////////////////////////////////
                ///--------       Monster -----------------------////////////
                ///////////////////////////////////////////////////////////////////////////
                if (monstr->isDodge)
                {
                    p->score += 40;
                    monstr->isDodge = false;
                }
                if (timer > 38 && monstr != NULL && timer < 45)
                {
                    monstr->move(timer, p->sprite.getPosition().x, p->sprite.getPosition().y);
                  
                }

                ///////////////////////////////////////////////////////////////////////////////////////
                ////--------------------------------  Destroying Enemies  ---------------------------//
                ///////////////////////////////////////////////////////////////////////////////////////
                if (p->getCheck() == false)
                {
                    for (int i = 0; i < 12; i++)
                    {
                        if (enemy[i] != NULL)
                        {

                            if (p->bullet->sprite.getPosition().x >= enemy[i]->sprite.getPosition().x - 30 && p->bullet->sprite.getPosition().x <= enemy[i]->sprite.getPosition().x + 60 && p->bullet->sprite.getPosition().y >= enemy[i]->sprite.getPosition().y - 30 && p->bullet->sprite.getPosition().y <= enemy[i]->sprite.getPosition().y + 30)
                            {
                                p->score += enemy[i]->getScore();
                                // cout << score << endl;
                                counter++;
                                enemy[i]->sprite.setPosition(1000, 0);
                                enemy[i]->b->sprite.setPosition(1000, 0);
                                if (casse == 8)
                                {
                                    delete enemy[i];
                                    enemy[i] = NULL;
                                }

                                music1.play();
                                delete p->bullet;
                                p->bullet = NULL;
                                p->bullet = new Bullet("img/laserGreen12.png");
                                p->bullet->sprite.setPosition(p->sprite.getPosition().x + 30,
                                                              p->sprite.getPosition().y);
                            }
                        }
                    }
                }
                else if (p->getCheck() == true)
                {

                    if (timer - p->timm > 8)
                    {
                        p->checkk = false;
                        p->timmm = timer;
                    }

                    for (int i = 0; i < 12; i++)
                    {
                        if (enemy[i] != NULL)
                        {

                            if (p->bullet->sprite.getPosition().x >= enemy[i]->sprite.getPosition().x - 30 && p->bullet->sprite.getPosition().x <= enemy[i]->sprite.getPosition().x + 40 && p->bullet->sprite.getPosition().y >= enemy[i]->sprite.getPosition().y - 30 && p->bullet->sprite.getPosition().y <= enemy[i]->sprite.getPosition().y + 30)
                            {
                                p->score += enemy[i]->getScore();
                                counter++;
                                music1.play();

                                enemy[i]->sprite.setPosition(1000, 0);
                                enemy[i]->b->sprite.setPosition(1000, 0);

                                if (casse == 8)
                                {
                                    delete enemy[i];
                                    enemy[i] = NULL;
                                }
                            }
                        }
                    }
                }
                //-------------------------------- Destrying Spaceship upon collision with enemies---------------------///
                for (int i = 0; i < 12; i++)
                {

                    if (p != NULL)
                    {
                        if (enemy[i] != NULL)
                        {
                            if (p->sprite.getPosition().x >= enemy[i]->sprite.getPosition().x - 100 && p->sprite.getPosition().x <= enemy[i]->sprite.getPosition().x + 10 && p->sprite.getPosition().y >= enemy[i]->sprite.getPosition().y - 50 && p->sprite.getPosition().y <= enemy[i]->sprite.getPosition().y + 50)
                            {

                                // if (p->explosion != NULL)
                                // {

                                delete p;
                                p = NULL;
                                p = new Player("img/playership.png");
                                p->lives--;
                            }
                        }
                    }
                }
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////---------------------------------Destriying spaceship upon collision with bombs-------------------------/////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                for (int i = 0; i < 12; i++)
                {

                    if (p != NULL)
                    {
                        if (enemy[i] != NULL)
                        {
                            if (p->sprite.getPosition().x >= enemy[i]->b->sprite.getPosition().x - 60 && p->sprite.getPosition().x <= enemy[i]->b->sprite.getPosition().x + 20 && p->sprite.getPosition().y >= enemy[i]->b->sprite.getPosition().y - 40 && p->sprite.getPosition().y <= enemy[i]->b->sprite.getPosition().y + 40)
                            {

                                delete p;
                                p = NULL;
                                p = new Player("img/playership.png");
                                p->lives--;
                                
                            }
                        }
                    }
                }

                if (counter == 12)
                {

                    casse += 1;

                    if (casse == 1)
                    {
                        p->sprite.setPosition(340, 670);
                        // cross
                        enemy[0]->sprite.setPosition(50, 50);
                        enemy[1]->sprite.setPosition(650, 50);
                        enemy[2]->sprite.setPosition(550, 100);
                        enemy[3]->sprite.setPosition(550, 100);
                        enemy[4]->sprite.setPosition(250, 200);

                        // Beta
                        enemy[5]->sprite.setPosition(450, 200);
                        enemy[6]->sprite.setPosition(350, 300);
                        enemy[7]->sprite.setPosition(250, 400);
                        enemy[8]->sprite.setPosition(450, 400);

                        // Alpha
                        enemy[9]->sprite.setPosition(150, 500);
                        enemy[10]->sprite.setPosition(550, 500);
                        enemy[11]->sprite.setPosition(50, 600);

                        counter = 0;
                    }

                    //  rectangle
                    if (casse == 2)
                    {
                        //  isGameStarted2 =true;
                        p->sprite.setPosition(340, 670);
                        // Gamma
                        enemy[0]->sprite.setPosition(100, 50);
                        enemy[1]->sprite.setPosition(200, 50);
                        enemy[2]->sprite.setPosition(300, 50);
                        enemy[3]->sprite.setPosition(400, 50);
                        enemy[4]->sprite.setPosition(400, 50);

                        // Beta
                        enemy[5]->sprite.setPosition(400, 150);
                        enemy[6]->sprite.setPosition(400, 280);
                        enemy[7]->sprite.setPosition(300, 280);
                        enemy[8]->sprite.setPosition(200, 280);

                        // Alpha
                        enemy[9]->sprite.setPosition(100, 300);
                        enemy[10]->sprite.setPosition(100, 200);
                        enemy[11]->sprite.setPosition(100, 200);
                        counter = 0;
                    }

                    // circle
                    if (casse == 3)
                    {

                        level = 2;

                        levelcom.play();
                        p->sprite.setPosition(340, 670);
                        enemy[0]->sprite.setPosition(250, 20);
                        enemy[1]->sprite.setPosition(150, 50);
                        enemy[2]->sprite.setPosition(340, 50);
                        enemy[3]->sprite.setPosition(100, 100);
                        enemy[4]->sprite.setPosition(390, 100);

                        // // Beta
                        enemy[5]->sprite.setPosition(130, 170);
                        enemy[6]->sprite.setPosition(380, 170);
                        enemy[7]->sprite.setPosition(150, 240);
                        enemy[8]->sprite.setPosition(350, 240);

                        // // Alpha
                        enemy[9]->sprite.setPosition(250, 300);
                        enemy[10]->sprite.setPosition(250, 300);
                        enemy[11]->sprite.setPosition(250, 300);
                        delete lev;
                        lev = NULL;
                        // lev->sprite.setPosition(1000, 0);

                        lev2->sprite.setPosition(740, 270);
                        counter = 0;
                    }
                    // Heart
                    if (casse == 4)
                    {
                        p->sprite.setPosition(600, 670);

                        enemy[0]->sprite.setPosition(300, 120);
                        enemy[1]->sprite.setPosition(190, 50);
                        enemy[2]->sprite.setPosition(400, 50);
                        enemy[3]->sprite.setPosition(150, 120);
                        enemy[4]->sprite.setPosition(440, 120);

                        // // Beta
                        enemy[5]->sprite.setPosition(180, 190);
                        enemy[6]->sprite.setPosition(430, 190);
                        enemy[7]->sprite.setPosition(200, 260);
                        enemy[8]->sprite.setPosition(400, 260);

                        // // Alpha
                        enemy[9]->sprite.setPosition(300, 340);
                        enemy[10]->sprite.setPosition(300, 340);
                        enemy[11]->sprite.setPosition(300, 340);

                        counter = 0;
                    }

                    // Diamond
                    if (casse == 5)
                    {

                        p->sprite.setPosition(550, 650);
                        enemy[0]->sprite.setPosition(320, 50);
                        enemy[1]->sprite.setPosition(220, 120);
                        enemy[2]->sprite.setPosition(410, 120);
                        enemy[3]->sprite.setPosition(135, 220);
                        enemy[4]->sprite.setPosition(490, 220);

                        // // // Beta
                        enemy[5]->sprite.setPosition(135, 320);
                        enemy[6]->sprite.setPosition(490, 320);
                        enemy[7]->sprite.setPosition(210, 400);
                        enemy[8]->sprite.setPosition(420, 400);

                        // // // Alpha
                        enemy[9]->sprite.setPosition(310, 470);
                        enemy[10]->sprite.setPosition(310, 470);
                        enemy[11]->sprite.setPosition(310, 470);

                        counter = 0;
                    }
                    if (casse == 6)
                    {
                        p->sprite.setPosition(600, 670);
                        level = 3;
                        // Triangle Filled
                        //   Gamma
                        enemy[0]->sprite.setPosition(100, 50);
                        enemy[1]->sprite.setPosition(200, 50);
                        enemy[2]->sprite.setPosition(300, 50);
                        enemy[3]->sprite.setPosition(400, 50);
                        enemy[4]->sprite.setPosition(500, 50);

                        // Beta
                        enemy[5]->sprite.setPosition(150, 150);
                        enemy[6]->sprite.setPosition(250, 150);
                        enemy[7]->sprite.setPosition(350, 150);
                        enemy[8]->sprite.setPosition(450, 150);

                        // Alpha
                        enemy[9]->sprite.setPosition(260, 270);
                        enemy[10]->sprite.setPosition(360, 270);
                        enemy[11]->sprite.setPosition(300, 370);
                        counter = 0;
                    }
                    if (casse == 7)
                    {
                        p->sprite.setPosition(600, 670);

                        // HEART Filled
                        enemy[0]->sprite.setPosition(300, 120);
                        enemy[1]->sprite.setPosition(190, 50);
                        enemy[2]->sprite.setPosition(400, 50);
                        enemy[3]->sprite.setPosition(150, 120);
                        enemy[4]->sprite.setPosition(440, 120);

                        // // Beta
                        enemy[5]->sprite.setPosition(180, 190);
                        enemy[6]->sprite.setPosition(430, 190);
                        enemy[7]->sprite.setPosition(200, 260);
                        enemy[8]->sprite.setPosition(400, 260);

                        // // Alpha
                        enemy[9]->sprite.setPosition(300, 340);
                        enemy[10]->sprite.setPosition(300, 190);
                        enemy[11]->sprite.setPosition(300, 275);

                        counter = 12;
                        casse = 8;
                    }
                }

                //---Draw
                window.clear(Color::Black); // clears the screen
                if (is_pause == true)
                {

                    window.draw(background); // setting background
                    window.draw(Lives);
                    window.draw(Lives1);
                    window.draw(Lives2);

                     if (timer > 40 && monstr != NULL && timer < 50)
                    {

                        window.draw(monstr->sprite);

                        if (p != NULL)
                            p->draw(window, timer);
                        if (lev2 != NULL)

                            window.draw(lev2->sprite);

                        if (lev != NULL)

                            window.draw(lev->sprite);
                        window.display();
                        if (p->lives == 0)
                        {

                            p->lives = 0;

                            window.close();
                            high_Score->SaveScore(p->score);
                            M->gameOver();

                        }
                    }

                    else
                    {
                    for (int i = 0; i < 12; i++)
                    {
                        if (enemy[i] != NULL)
                        {

                            window.draw(enemy[i]->sprite);
                            window.draw(enemy[i]->b->sprite);
                        }
                    }

                    //-- Displaying Player
                    if (p != NULL)
                        p->draw(window, timer);

                    window.draw(frame);
                    window.draw(frame2);

                    if (lev2 != NULL)

                        window.draw(lev2->sprite);

                    if (lev != NULL)

                        window.draw(lev->sprite);

                    if (p->lives == 0)
                    {
                        
                        gameover.play();

                        window.close();
                        M->gameOver();
                        high_Score->SaveScore(p->score);
                    }

                    window.display(); // Displying all the sprit
                }
            }
            }
        }
    }
};
