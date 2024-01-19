#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class ScoreManager
{
public:
    ScoreManager(const string &highScoresFile);

    void SaveScore(int score);

    struct Score
    {
        int index;
        string name;
        int score;
    };

    void getScores(Score highScores[], int &size);

private:
    string ScoresFile;
};

#endif
