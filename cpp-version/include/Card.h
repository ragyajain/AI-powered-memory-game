#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
private:
    char symbol;
    bool isRevealed;
    bool isMatched;
    int row, col;

public:
    Card();
    Card(char sym, int r, int c);
    
    char getSymbol() const { return symbol; }
    bool getIsRevealed() const { return isRevealed; }
    bool getIsMatched() const { return isMatched; }
    int getRow() const { return row; }
    int getCol() const { return col; }
    
    void setRevealed(bool revealed) { isRevealed = revealed; }
    void setMatched(bool matched) { isMatched = matched; }
    
    std::string display() const;
};

#endif

