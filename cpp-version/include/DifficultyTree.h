#ifndef DIFFICULTY_TREE_H
#define DIFFICULTY_TREE_H

#include <string>

class DifficultyNode {
public:
    std::string levelName;
    int rows, cols;
    int timeLimit;
    int aiDelay; 
    DifficultyNode* easier;
    DifficultyNode* harder;
    
    DifficultyNode(std::string name, int r, int c, int time, int delay);
    ~DifficultyNode();
};

class DifficultyTree {
private:
    DifficultyNode* root;
    DifficultyNode* currentLevel;

public:
    DifficultyTree();
    ~DifficultyTree();
    
    DifficultyNode* getRoot() { return root; }
    DifficultyNode* getCurrentLevel() { return currentLevel; }
    
    void setDifficulty(const std::string& level);
    void increaseDifficulty();
    void decreaseDifficulty();
    
    void displayLevels() const;
};

#endif
