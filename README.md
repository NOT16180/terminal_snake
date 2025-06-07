# 🐍 terminal_snake

**terminal_snake** is a terminal-based implementation of the classic Snake game written in C. This project explores dynamic data structures, game logic, and terminal I/O to build an interactive experience in the terminal.

---

## 🎮 Features

- Playable in the terminal
- Multiple game modes:
  - **Mode 1 – Classic Snake**: single-player, arrow-controlled
  - **Mode 2 – Versus Mode**: 1v1 mode where two players compete
  - **Mode 3 – AI Solver**: Snake is automatically solved using a pathfinding algorithm
- Real-time score tracking
- Speed adjustable via command-line arguments
- Grid size customizable

---

## 🛠️ Technologies Used

- **C** programming language
- Compilation via **Makefile**
- Terminal input/output handling
- Dynamic memory and linked lists

---

## 🚀 Installation & Running the Game

### ✅ Prerequisites

Ensure `gcc` and `make` are installed on your system.

```bash
# On Debian/Ubuntu:
sudo apt install build-essential

# On Arch Linux:
sudo pacman -S base-devel
```

### 🔧 Build Instructions

Clone the repository and compile the project:

```bash
git clone https://github.com/NOT16180/terminal_snake.git
cd terminal_snake
make
```

### ▶️ Running the Game

Run the program with the following format:

```bash
./main <n> <m> <mode> <speed>
```

- `<n>` = number of rows  
- `<m>` = number of columns (must be equal to `n`, square grid required)  
- `<mode>` = game mode:
  - `1` = Classic single-player snake
  - `2` = 1v1 mode (two players take turns)
  - `3` = Auto-solver (AI finds path to complete the game)
- `<speed>` = game speed (lower is faster)

**Example**:  
```bash
./main 20 20 1 100
```

> In mode `2`, you will be asked to enter the names of both players before the game starts.

---

## 📁 Project Structure

- `main.c` – Entry point and mode selection logic  
- `fonction_jeu.c/h`, `fonction_jeu_2.c/h` – Game logic for all modes  
- `grille.c/h` – Grid generation and display  
- `serpent.c/h` – Snake representation and movement  
- `liste_mouvement.c/h` – Queue management of directions  
- `matrice.c/h` – Matrix/grid abstraction  
- `Makefile` – Compilation automation

---

## 📌 Notes

- Designed for Unix/Linux terminals.  
- This project was developed as a school project for educational purposes.  
- Uses only standard C libraries.

---

## 📄 License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for more details.
