#include "../include/GameBoard.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#define SLEEP_MS(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))
#endif

GameBoard::GameBoard(int r, int c) 
    : rows(r), cols(c), playerScore(0), aiScore(0), 
      matchedPairs(0), moveHistory(50) {
    totalPairs = (rows * cols) / 2;
    initializeGrid();
}

void GameBoard::initializeGrid() {
    std::vector<char> symbols;
    
    for (int i = 0; i < totalPairs; i++) {
        char sym = 'A' + i;
        symbols.push_back(sym);
        symbols.push_back(sym);
    }
    
    shuffleCards(symbols);
    
    grid.resize(rows, std::vector<Card>(cols));
    int idx = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = Card(symbols[idx++], i, j);
        }
    }
}

void GameBoard::shuffleCards(std::vector<char>& cards) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

void GameBoard::displayBoard(bool hideUnmatched) const {
    std::cout << "\n╔════════════════════════════════════╗\n";
    std::cout << "║      MEMORY GAME - GRID LAYOUT     ║\n";
    std::cout << "╚════════════════════════════════════╝\n\n";
    
    std::cout << "    ";
    for (int j = 0; j < cols; j++) {
        std::cout << std::setw(3) << j << " ";
    }
    std::cout << "\n   ┌";
    for (int j = 0; j < cols; j++) std::cout << "────";
    std::cout << "┐\n";
    
    for (int i = 0; i < rows; i++) {
        std::cout << std::setw(2) << i << " │";
        for (int j = 0; j < cols; j++) {
            if (grid[i][j].getIsMatched()) {
                std::cout << "  ✓ ";
            } else if (grid[i][j].getIsRevealed() && !hideUnmatched) {
                std::cout << "  " << grid[i][j].getSymbol() << " ";
            } else {
                std::cout << "  ? ";
            }
        }
        std::cout << "│\n";
    }
    
    std::cout << "   └";
    for (int j = 0; j < cols; j++) std::cout << "────";
    std::cout << "┘\n";
}

Card* GameBoard::flipCard(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return nullptr;
    }
    if (grid[row][col].getIsMatched() || grid[row][col].getIsRevealed()) {
        return nullptr;
    }
    
    grid[row][col].setRevealed(true);
    return &grid[row][col];
}

bool GameBoard::checkMatch(int r1, int c1, int r2, int c2, bool isPlayer) {
    if (grid[r1][c1].getSymbol() == grid[r2][c2].getSymbol()) {
        grid[r1][c1].setMatched(true);
        grid[r2][c2].setMatched(true);
        
        if (isPlayer) {
            playerScore++;
        } else {
            aiScore++;
            ai.forgetCard(grid[r1][c1].getSymbol(), r1, c1);
            ai.forgetCard(grid[r2][c2].getSymbol(), r2, c2);
        }
        
        matchedPairs++;
        
        moveHistory.push(Move({r1, c1}, {r2, c2}, isPlayer));
        return true;
    }
    return false;
}

void GameBoard::hideUnmatchedCards() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!grid[i][j].getIsMatched()) {
                grid[i][j].setRevealed(false);
            }
        }
    }
}

void GameBoard::undoMove() {
    if (moveHistory.isEmpty()) {
        std::cout << "❌ No moves to undo!\n";
        return;
    }
    
    Move lastMove = moveHistory.pop();
    
    if (!lastMove.isPlayerMove) {
        std::cout << "❌ Cannot undo AI moves!\n";
        moveHistory.push(lastMove); 
        return;
    }
    
    grid[lastMove.card1.first][lastMove.card1.second].setMatched(false);
    grid[lastMove.card2.first][lastMove.card2.second].setMatched(false);
    
    playerScore--;
    matchedPairs--;
    
    std::cout << "✅ Last move undone!\n";
}

std::pair<int, int> GameBoard::getAIMove(std::pair<int, int> firstCard) {
    return ai.makeMove(grid, firstCard);
}

void GameBoard::aiTurn() {
    std::cout << "\n═══════════════════════════════════\n";
    std::cout << "        🤖 AI'S TURN\n";
    std::cout << "═══════════════════════════════════\n";
    
    displayBoard(true);
    std::cout << "\n🤖 AI is thinking...\n";
    SLEEP_MS(1000);
    
    auto pos1 = getAIMove();
    if (pos1.first == -1) return;
    
    Card* card1 = flipCard(pos1.first, pos1.second);
    displayBoard(false);
    std::cout << "\n🎴 AI flipped: " << card1->getSymbol() 
              << " at (" << pos1.first << ", " << pos1.second << ")\n";
    
    SLEEP_MS(1000);
    
    auto pos2 = getAIMove(pos1);
    if (pos2.first == -1) {
        hideUnmatchedCards();
        return;
    }
    
    Card* card2 = flipCard(pos2.first, pos2.second);
    displayBoard(false);
    std::cout << "\n🎴 AI flipped: " << card2->getSymbol() 
              << " at (" << pos2.first << ", " << pos2.second << ")\n";
    
    SLEEP_MS(1000);
    
    if (checkMatch(pos1.first, pos1.second, pos2.first, pos2.second, false)) {
        std::cout << "\n🤖 AI found a match! AI scores! 🤖\n";
    } else {
        std::cout << "\n❌ AI didn't match. Cards hidden.\n";
        ai.rememberCard(card1->getSymbol(), pos1.first, pos1.second);
        ai.rememberCard(card2->getSymbol(), pos2.first, pos2.second);
    }
    
    SLEEP_MS(1500);
    hideUnmatchedCards();
}

bool GameBoard::isGameOver() const {
    return matchedPairs >= totalPairs;
}

void GameBoard::displayScore() const {
    std::cout << "\n┌─────────────────────────────────┐\n";
    std::cout << "│ 👤 Player Score: " << std::setw(2) << playerScore 
              << "            │\n";
    std::cout << "│ 🤖 AI Score:     " << std::setw(2) << aiScore 
              << "            │\n";
    std::cout << "│ Matched: " << matchedPairs << "/" << totalPairs 
              << "                   │\n";
    std::cout << "└─────────────────────────────────┘\n";
}

void GameBoard::resetGame() {
    playerScore = 0;
    aiScore = 0;
    matchedPairs = 0;
    moveHistory.clear();
    ai.clearMemory();
    initializeGrid();
}

void GameBoard::displayStatistics() const {
    std::cout << "\n╔════════════════════════════════════╗\n";
    std::cout << "║       GAME STATISTICS              ║\n";
    std::cout << "╠════════════════════════════════════╣\n";
    std::cout << "║ Total Moves (Stack): " << std::setw(2) 
              << moveHistory.size() << "          ║\n";
    std::cout << "║ AI Memory Size: " << std::setw(2) 
              << ai.getMemorySize() << "               ║\n";
    std::cout << "║ Grid Size: " << rows << "x" << cols 
              << "                   ║\n";
    std::cout << "╚════════════════════════════════════╝\n";
}
    
