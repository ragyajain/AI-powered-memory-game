#include "../include/Card.h"

Card::Card() : symbol('?'), isRevealed(false), isMatched(false), row(-1), col(-1) {}

Card::Card(char sym, int r, int c) 
    : symbol(sym), isRevealed(false), isMatched(false), row(r), col(c) {}

std::string Card::display() const {
    if (isMatched) return "✓";
    if (isRevealed) return std::string(1, symbol);
    return "?";
}