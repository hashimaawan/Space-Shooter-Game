
// #include "game.h"
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "highScore.cpp"
#include "iostream"

using namespace std;
using namespace sf;
const char titlee[] = "OOP-Project, Spring-2023";
class Menu
{
public:
    sf::RenderWindow window;
    sf::Font font;
    bool isGameStarted;
    bool isGameStarted2;
    bool isResume,Ismusic;
    ScoreManager *high_Score;
    Sprite background, frame, frame2, MENN, Instruct, hisc,onebadge,secbadge,thibadge; // Game background sprite
    Texture bg_texture, frame1, frametex, MENtex, intrttex, hisctex,obadgetex,sbadgetex,tbadgetex;
    // add menu attributes here

    Menu()
    {
        font.loadFromFile("Roboto.ttf");
        isGameStarted = false;
        isGameStarted2 = false;
        isResume = false;
        Ismusic = true;
        high_Score = new ScoreManager("highscores.txt");
        intrttex.loadFromFile("img/instructions.jpg");
        Instruct.setTexture(intrttex);
        Instruct.setScale(0.7, 0.82);

        hisctex.loadFromFile("img/highscore.jpg");
        hisc.setTexture(hisctex);
        hisc.setScale(1, 1.74);

        MENtex.loadFromFile("img/Image1.jpg");
        MENN.setTexture(MENtex);
        MENN.setScale(0.7, 0.82);

        obadgetex.loadFromFile("img/first.png");
        onebadge.setTexture(obadgetex);
        onebadge.setScale(0.007,0.007);

        sbadgetex.loadFromFile("img/second.png");
        secbadge.setTexture(sbadgetex);
        secbadge.setScale(0.12,0.12);

        tbadgetex.loadFromFile("img/third.png");
        thibadge.setTexture(tbadgetex);
        thibadge.setScale(0.05,0.045);
    }

    ~Menu()
    {
        delete high_Score;
    }

    void display_Menu()
    {
        srand(time(0));
        RenderWindow window(VideoMode(880, 880), titlee);
        Font font;
        font.loadFromFile("Roboto.ttf");

        Music music;
        music.openFromFile("MusiC/Space Shooter_Sounds_background.wav");
        
        if(Ismusic== false)
        {
            music.pause();
        }
        else if(Ismusic==true)
        {
            music.play();
        }

        Text strt("Press S to start Game\nE to Exit the Game\nI to view instructions\nPress H to view High Scores", font, 20);
        strt.setPosition(300, 50);
        strt.setFillColor(Color::Cyan);
        strt.setOutlineThickness(3);

        strt.setPosition(0, 30);

        Text startGameText("Start Game", font, 32);
        startGameText.setPosition(330, 230);
        startGameText.setFillColor(Color::Magenta);
        ;
        startGameText.setOutlineThickness(3);

        Text exitText("Exit", font, 32);
        exitText.setPosition(330, 280);
        exitText.setFillColor(Color::Magenta);
        exitText.setOutlineThickness(3);

        Text instructionsText("Instructions", font, 32);
        instructionsText.setPosition(330, 330);
        instructionsText.setFillColor(Color::Magenta);

        instructionsText.setOutlineThickness(2);

        // levels
        Text slevels("Levels", font, 32);
        slevels.setPosition(330, 380);
        slevels.setFillColor(Color::Magenta);

        slevels.setOutlineThickness(3);

        // level 1
        Text levell1("Level 1\nLevel 2", font, 32);
        levell1.setPosition(330, 200);
        levell1.setFillColor(Color::Green);
        levell1.setOutlineColor(Color::Red);
        levell1.setOutlineThickness(3);

        Text instructions("How to play:\n\nUse the arrow keys to move your spaceship.\nPress the spacebar to Pause the game.\nCollect power-ups to upgrade your weapons.\n\nGood luck, pilot!", font, 20);
        instructions.setPosition(100, 250);
        instructions.setFillColor(Color::Cyan);
        instructions.setOutlineThickness(3);
        Text inst2("Press Esc to go back to menu", font, 14);
        inst2.setPosition(0, 10);
        inst2.setFillColor(Color::Cyan);
        inst2.setOutlineThickness(3);

        int numHighScores = 10;
        ScoreManager::Score highScores[numHighScores]; // Object score array to store scores in descending order--- struct object array
        high_Score->getScores(highScores, numHighScores);

        Text highScoreTitle("High Scores", font, 32);
        highScoreTitle.setPosition(330, 430);
        highScoreTitle.setFillColor(Color::Magenta);
        highScoreTitle.setOutlineThickness(3);

        Text Resume("Resume Game", font, 32);
        Resume.setPosition(330, 180);
        Resume.setFillColor(Color::Magenta);
        Resume.setOutlineThickness(3);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                if (Keyboard::isKeyPressed(Keyboard::S))
                    isGameStarted = true;
                if (Keyboard::isKeyPressed(Keyboard::C))
                    {
                        isGameStarted = true;
                        window.close();
                        Ismusic = true;
                    }
                if (Keyboard::isKeyPressed(Keyboard::E))
                {
                    isGameStarted = false;
                  
                    window.close();
                }
                if (Keyboard::isKeyPressed(Keyboard::I))
                {
                    window.clear();
                    window.draw(Instruct);
                    window.draw(instructions);
                    window.draw(inst2);
                    window.display();
                    while (true)
                    {
                        sf::Event event;
                        while (window.pollEvent(event))
                        {
                            if (Keyboard::isKeyPressed(Keyboard::Escape))
                            {
                                break;
                            }
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Escape))
                        {
                            break;
                        }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::H))
                {

                    window.clear();

                    // Display the high scores
                    int yPos = 360;

                    window.draw(hisc);
                    for (int i = 0; i < numHighScores; i++)
                    {
                        Text scoreText(highScores[i].name + ": " + to_string(highScores[i].score), font, 20);
                        scoreText.setPosition(200, yPos);
                        scoreText.setFillColor(Color::Green);
                        scoreText.setOutlineThickness(1);
                        yPos += 30;
                        window.draw(scoreText);
                    }
                    onebadge.setPosition(165,355);
                    secbadge.setPosition(165,385);
                    thibadge.setPosition(171,417);
                    window.draw(onebadge);
                    window.draw(secbadge);
                    window.draw(thibadge);
                    window.display();
                    while (true)
                    {
                        sf::Event event;
                        while (window.pollEvent(event))
                        {
                            if (Keyboard::isKeyPressed(Keyboard::Escape))
                            {
                                break;
                            }
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Escape))
                        {
                            break;
                        }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::L))
                {
                    window.clear();

                    window.draw(levell1);

                    window.display();
                    while (true)
                    {
                        sf::Event event;
                        while (window.pollEvent(event))
                        {
                            if (event.type == sf::Event::Closed)
                            {
                                window.close();
                            }
                            if (Keyboard::isKeyPressed(Keyboard::M))
                            {
                                isGameStarted = true;
                                break;
                            }
                            else if (Keyboard::isKeyPressed(Keyboard::N))
                            {
                                isGameStarted2 = true;
                                break;
                            }
                            else if (Keyboard::isKeyPressed(Keyboard::Escape))
                            {
                                break;
                            }
                        }
                        if (isGameStarted || isGameStarted2)
                        {
                            break;
                        }
                    }
                }
            }

            window.clear();

            window.draw(MENN);
                if(isResume==true)
                {
                    window.draw(Resume);

                }

            window.draw(startGameText);
            window.draw(exitText);
            window.draw(instructionsText);
            window.draw(slevels);
            window.draw(strt);

            //  window.draw(highScoreText);
            window.draw(highScoreTitle);

            // window.draw(eff);

            if (isGameStarted)
            {
                window.close();
                //   start_game();
            }
            // else if (isGameStarted2)
            // {
            //     window.close();
            //     //   start_game2();
            // }

            window.display();
        }
    }

    void gameOver()
    {
        srand(time(0));
        RenderWindow window(VideoMode(500, 500), titlee);
        Font font;
        font.loadFromFile("Roboto.ttf");

        Text startGameTex("GAME OVER!", font, 50);
        startGameTex.setPosition(130, 170);
        startGameTex.setFillColor(Color::Green);
        startGameTex.setOutlineColor(Color::Red);
        startGameTex.setOutlineThickness(3);

        Text exitText("Exit", font, 45);
        exitText.setPosition(130, 300);
        exitText.setFillColor(Color::Green);
        exitText.setOutlineColor(Color::Red);
        exitText.setOutlineThickness(3);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                if (Keyboard::isKeyPressed(Keyboard::R))
                {
                    // p->lives =3;
                    isGameStarted = true;
                }
                if (Keyboard::isKeyPressed(Keyboard::E))
                {
                    isGameStarted = false;
                    window.close();
                }
            }

            window.clear();

            window.draw(startGameTex);

            window.display();
        }
    }
};
