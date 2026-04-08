// ============================================================================
// FILE: AIPlayer.h
// Description: HashMap-based AI with memory
// ============================================================================
#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include <unordered_map>
#include <vector>
#include <utility>
#include "Card.h"

class AIPlayer {
private:
    std::unordered_map<char, std::vector<std::pair<int, int>>> memory;
    int memoryCapacity;
    
public:
    AIPlayer(int capacity = 100);
    
    void rememberCard(char symbol, int row, int col);
    void forgetCard(char symbol, int row, int col);
    void clearMemory();
    
    std::pair<int, int> makeMove(const std::vector<std::vector<Card>>& grid, std::pair<int, int> firstCard);
    
    int getMemorySize() const;
    void displayMemory() const;
};

#endif