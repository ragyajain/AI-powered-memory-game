#include "../include/AIPlayer.h"
#include <algorithm>
#include <random>
#include <iostream>

AIPlayer::AIPlayer(int capacity) : memoryCapacity(capacity) {}

void AIPlayer::rememberCard(char symbol, int row, int col) {
    if (memory[symbol].size() < memoryCapacity) {
        memory[symbol].push_back({row, col});
    }
}

void AIPlayer::forgetCard(char symbol, int row, int col) {
    if (memory.find(symbol) != memory.end()) {
        auto& positions = memory[symbol];
        positions.erase(
            std::remove(positions.begin(), positions.end(), std::make_pair(row, col)),
            positions.end()
        );
        
        if (positions.empty()) {
            memory.erase(symbol);
        }
    }
}

void AIPlayer::clearMemory() {
    memory.clear();
}

std::pair<int, int> AIPlayer::makeMove(const std::vector<std::vector<Card>>& grid, std::pair<int, int> firstCard) {
    int rows = grid.size();
    int cols = grid[0].size();
    
    if (firstCard.first != -1) {
        char targetSymbol = grid[firstCard.first][firstCard.second].getSymbol();
        
        if (memory.find(targetSymbol) != memory.end()) {
            for (const auto& pos : memory[targetSymbol]) {
                if ((pos.first != firstCard.first || pos.second != firstCard.second) &&
                    !grid[pos.first][pos.second].getIsMatched() &&
                    !grid[pos.first][pos.second].getIsRevealed()) {
                    return pos;
                }
            }
        }
    }
    
    std::vector<std::pair<int, int>> available;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!grid[i][j].getIsMatched() && !grid[i][j].getIsRevealed()) {
                available.push_back({i, j});
            }
        }
    }
    
    if (available.empty()) {
        return {-1, -1};
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, available.size() - 1);
    
    return available[dis(gen)];
}

int AIPlayer::getMemorySize() const {
    int total = 0;
    for (const auto& pair : memory) {
        total += pair.second.size();
    }
    return total;
}

void AIPlayer::displayMemory() const {
    std::cout << "\n🧠 AI Memory Contents:\n";
    for (const auto& pair : memory) {
        std::cout << "  Symbol '" << pair.first << "': ";
        for (const auto& pos : pair.second) {
            std::cout << "(" << pos.first << "," << pos.second << ") ";
        }
        std::cout << std::endl;
    }
}
