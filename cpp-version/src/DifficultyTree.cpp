#include "../include/DifficultyTree.h"
#include <iostream>

DifficultyNode::DifficultyNode(std::string name, int r, int c, int time, int delay)
    : levelName(name), rows(r), cols(c), timeLimit(time), aiDelay(delay),
      easier(nullptr), harder(nullptr) {}

DifficultyNode::~DifficultyNode() {
}

DifficultyTree::DifficultyTree() {
    root = new DifficultyNode("Medium", 4, 4, 120, 1000);
    root->easier = new DifficultyNode("Easy", 3, 4, 180, 1500);
    root->harder = new DifficultyNode("Hard", 4, 6, 90, 800);
    
    root->easier->harder = root;
    root->harder->easier = root;
    
    currentLevel = root;
}

DifficultyTree::~DifficultyTree() {
    delete root->easier;
    delete root->harder;
    delete root;
}

void DifficultyTree::setDifficulty(const std::string& level) {
    if (level == "easy" || level == "Easy") {
        currentLevel = root->easier;
    } else if (level == "medium" || level == "Medium") {
        currentLevel = root;
    } else if (level == "hard" || level == "Hard") {
        currentLevel = root->harder;
    }
}

void DifficultyTree::increaseDifficulty() {
    if (currentLevel->harder != nullptr) {
        currentLevel = currentLevel->harder;
        std::cout << "Difficulty increased to: " << currentLevel->levelName << std::endl;
    }
}

void DifficultyTree::decreaseDifficulty() {
    if (currentLevel->easier != nullptr) {
        currentLevel = currentLevel->easier;
        std::cout << "Difficulty decreased to: " << currentLevel->levelName << std::endl;
    }
}

void DifficultyTree::displayLevels() const {
    std::cout << "\n╔════════════════════════════════════╗\n";
    std::cout << "║      DIFFICULTY LEVELS             ║\n";
    std::cout << "╠════════════════════════════════════╣\n";
    std::cout << "║  1. Easy   (3x4 - 6 pairs)         ║\n";
    std::cout << "║  2. Medium (4x4 - 8 pairs)         ║\n";
    std::cout << "║  3. Hard   (4x6 - 12 pairs)        ║\n";
    std::cout << "╚════════════════════════════════════╝\n";
}

