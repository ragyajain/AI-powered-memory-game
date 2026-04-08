# AI Memory Game (C++ + Web)

## Overview

AI-based memory matching game implemented using **Data Structures & Algorithms** concepts.
Includes both:

* C++ version (console-based)
* Web version (interactive UI)

---

## Features

### AI Player

* Uses memory to track previously seen cards
* Makes intelligent moves using stored data

### Data Structures Used

* **Stack** → Undo functionality
* **HashMap** → AI memory tracking
* **Binary Tree** → Difficulty selection
* **2D Grid** → Game board

---

## C++ Version

### Structure

```
cpp-version/
├── include/
├── src/
├── Makefile
```

### How to Run

```bash
cd cpp-version
g++ src/*.cpp -I include -o game
./game
```

---

## Web Version

### Structure

```
web-version/
├── index.html
├── style.css
├── script.js
```

### Run

Just open `index.html` in browser

---

## Screenshots

### Home Screen
![Home](assets/home.png)

### Game Screen
![Game](assets/game.png)

### Difficulty Selection
![Difficulty](assets/difficultyLevel.png)

### Result Screen
![Result](assets/result.png)

---

## Key Highlights

* AI-based decision making
* Modular OOP design
* Interactive UI with animations
* Real-world DS usage

---

## Future Improvements

* Smarter AI (probability-based)
* Multiplayer mode
* Database-based leaderboard

---

## Author

Ragya Jain
