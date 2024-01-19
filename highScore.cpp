#include "highScore.h"
using namespace std;
ScoreManager::ScoreManager(const string &highScoresFile) : ScoresFile(highScoresFile){}


void ScoreManager::SaveScore(int score)
{
    string playerName;
    cout << "\nEnter your name: ";
    getline(std::cin, playerName);

    ofstream file(ScoresFile, ios::app); // Open the file in append mode
    if (file.is_open())
    {
        file << playerName << ":" << score << std::endl;
        file.close();
    }
    else
    {
        cout << "Failed to open the high scores file for writing." << std::endl;
    }
}

void ScoreManager::getScores(Score highScores[], int &size)
{
    ifstream file(ScoresFile);
    if (file.is_open())
    {
        string line;  // to store each line read from file
        int index = 0;     // to score index for storing high scores
        string pname; // To extract the player Name
        int score = 0;     // To extract the score

        // Reading each line until the end of line
        while (std::getline(file, line) && index < size) // index < size number of scores available
        {
            int pos = line.find(':'); // finding the position of :using find function of string library

            if (pos != line.length()) // checking whether the position of : was found or not
            {
                pname = "";
                score = 0;

                for (int i = 0; i < pos; i++)
                {
                    pname += line[i];
                }

                for (int i = pos + 1; i < line.length(); i++) // starting from pos+1 ....+1 because one is space
                {
                    int digit = (line[i] - '0'); // converting the ASCII code
                    score = score * 10 + digit;  // Multiplying by 10 to shift it to left
                }

                // Store the player name and score in the highScores array
                highScores[index].name = pname;
                highScores[index].score = score;
                index++;
            }
        }

        size = index; // Update the size to reflect the actual number of scores read

        file.close();

        // Bubble sort to update in descending order
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (highScores[j].score > highScores[i].score)
                {
                    Score temp = highScores[i];
                    highScores[i] = highScores[j];
                    highScores[j] = temp;
                }
            }
        }
    }
}
