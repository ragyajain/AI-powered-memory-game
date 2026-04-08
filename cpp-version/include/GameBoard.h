#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "Card.h"
#include "Stack.h"
#include "AIPlayer.h"
#include <vector>
#include <utility>

struct Move {
    std::pair<int, int> card1;
    std::pair<int, int> card2;
    bool isPlayerMove;
    
    Move(std::pair<int, int> c1, std::pair<int, int> c2, bool player)
        : card1(c1), card2(c2), isPlayerMove(player) {}
};

class GameBoard {
private:
    int rows, cols;
    std::vector<std::vector<Card>> grid;  
    Stack<Move> moveHistory;              
    AIPlayer ai;                           
    
    int playerScore;
    int aiScore;
    int totalPairs;
    int matchedPairs;
    
    void initializeGrid();
    void shuffleCards(std::vector<char>& cards);

public:
    GameBoard(int r, int c);
    
    void displayBoard(bool hideUnmatched = true) const;
    Card* flipCard(int row, int col);
    bool checkMatch(int r1, int c1, int r2, int c2, bool isPlayer);
    void hideUnmatchedCards();
    
    void undoMove();
    bool canUndo() const { return !moveHistory.isEmpty(); }
    
    void aiTurn();
    std::pair<int, int> getAIMove(std::pair<int, int> firstCard = {-1, -1});
    
    bool isGameOver() const;
    void displayScore() const;
    void resetGame();
    
    int getPlayerScore() const { return playerScore; }
    int getAIScore() const { return aiScore; }
    int getMatchedPairs() const { return matchedPairs; }
    const std::vector<std::vector<Card>>& getGrid() const { return grid; }
    
    void displayStatistics() const;
};

#endif