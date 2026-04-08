#include "../include/GameBoard.h"
#include "../include/DifficultyTree.h"
#include <iostream>
#include <thread>
#include <chrono>
#include<iomanip>
// avoid `using namespace std;` to keep symbols explicit

// cross-platform sleep helper: use WinAPI Sleep on Windows (ms), otherwise std::this_thread
#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#define SLEEP_MS(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))
#endif

void displayTitle() {
    std::cout << "\n";
    std::cout << "███╗   ███╗███████╗███╗   ███╗ ██████╗ ██████╗ ██╗   ██╗\n";
    std::cout << "████╗ ████║██╔════╝████╗ ████║██╔═══██╗██╔══██╗╚██╗ ██╔╝\n";
    std::cout << "██╔████╔██║█████╗  ██╔████╔██║██║   ██║██████╔╝ ╚████╔╝ \n";
    std::cout << "██║╚██╔╝██║██╔══╝  ██║╚██╔╝██║██║   ██║██╔══██╗  ╚██╔╝  \n";
    std::cout << "██║ ╚═╝ ██║███████╗██║ ╚═╝ ██║╚██████╔╝██║  ██║   ██║   \n";
    std::cout << "╚═╝     ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝   \n";
    std::cout << "        🎮 AI POWERED CARD MATCHING GAME 🎮              \n";
    std::cout << "        DATA STRUCTURES PROJECT - 2024-25                \n\n";
}

void playerTurn(GameBoard& game) {
    std::cout << "\n═══════════════════════════════════\n";
    std::cout << "        👤 YOUR TURN\n";
    std::cout << "═══════════════════════════════════\n";
    
    game.displayBoard(true);
    game.displayScore();
    
    int r1, c1, r2, c2;
    std::cout << "\nEnter first card (row col): ";
    std::cin >> r1 >> c1;
    
    Card* card1 = game.flipCard(r1, c1);
    if (!card1) {
        std::cout << "❌ Invalid card! Try again.\n";
        SLEEP_MS(1000);
        return;
    }
    
    game.displayBoard(false);
        std::cout << "\n🎴 First card: " << card1->getSymbol() 
            << " at (" << r1 << ", " << c1 << ")\n";
    
    std::cout << "\nEnter second card (row col): ";
    std::cin >> r2 >> c2;
    
    if (r1 == r2 && c1 == c2) {
        std::cout << "❌ Cannot select the same card twice!\n";
        game.hideUnmatchedCards();
        SLEEP_MS(1000);
        return;
    }
    
    Card* card2 = game.flipCard(r2, c2);
    if (!card2) {
        std::cout << "❌ Invalid card! Try again.\n";
        game.hideUnmatchedCards();
        SLEEP_MS(1000);
        return;
    }
    
    game.displayBoard(false);
        std::cout << "\n🎴 Second card: " << card2->getSymbol() 
            << " at (" << r2 << ", " << c2 << ")\n";
    
    SLEEP_MS(1000);
    
    if (game.checkMatch(r1, c1, r2, c2, true)) {
        std::cout << "\n✨ MATCH! You got a point! ✨\n";
    } else {
        std::cout << "\n❌ No match. Cards will be hidden.\n";
    }
    
    SLEEP_MS(1000);
    game.hideUnmatchedCards();
}

void playGame(GameBoard& game) {
    std::cout << "\n╔════════════════════════════════════════════╗\n";
    std::cout << "║  🎮 GAME STARTED! 🎮                      ║\n";
    std::cout << "║  Find matching pairs to score points!     ║\n";
    std::cout << "╚════════════════════════════════════════════╝\n";
    
    while (!game.isGameOver()) {
        playerTurn(game);
        if (game.isGameOver()) break;
        
        game.aiTurn();
    }
    
    // Game Over
        std::cout << "\n\n╔════════════════════════════════════════════╗\n";
        std::cout << "║           🏆 GAME OVER! 🏆                ║\n";
        std::cout << "╠════════════════════════════════════════════╣\n";
        std::cout << "║  👤 Your Score:  " << std::setw(2) << game.getPlayerScore() 
            << "                        ║\n";
        std::cout << "║  🤖 AI Score:    " << std::setw(2) << game.getAIScore() 
            << "                        ║\n";
        std::cout << "╠════════════════════════════════════════════╣\n";
    
    if (game.getPlayerScore() > game.getAIScore()) {
        std::cout << "║       🎉 YOU WIN! CONGRATULATIONS! 🎉     ║\n";
    } else if (game.getAIScore() > game.getPlayerScore()) {
        std::cout << "║         🤖 AI WINS! BETTER LUCK! 🤖       ║\n";
    } else {
        std::cout << "║          🤝 IT'S A TIE! 🤝                ║\n";
    }
    
    std::cout << "╚════════════════════════════════════════════╝\n\n";
    
    game.displayStatistics();
}

int main() {
    displayTitle();
    
    DifficultyTree diffTree;
    diffTree.displayLevels();
    
    std::cout << "\nEnter choice (1-3): ";
    int choice;
    std::cin >> choice;
    
    DifficultyNode* level;
    switch (choice) {
        case 1: 
            diffTree.setDifficulty("easy");
            level = diffTree.getCurrentLevel();
            break;
        case 2: 
            diffTree.setDifficulty("medium");
            level = diffTree.getCurrentLevel();
            break;
        case 3: 
            diffTree.setDifficulty("hard");
            level = diffTree.getCurrentLevel();
            break;
        default:
            level = diffTree.getRoot();
    }
    
        std::cout << "\n✅ Starting " << level->levelName << " mode (" 
            << level->rows << "x" << level->cols << " grid)\n";
    
        SLEEP_MS(1000);
    
    GameBoard game(level->rows, level->cols);
    playGame(game);
    
    return 0;
}
