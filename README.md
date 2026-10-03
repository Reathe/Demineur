# Démineur: Terminal Minesweeper in C

> A full Minesweeper game for the Linux terminal, written in C99 from scratch. It has keyboard navigation,
> three difficulty levels plus custom boards, and a persistent leaderboard for each board size.

![C](https://img.shields.io/badge/C99-00599C?logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-terminal-FCC624?logo=linux&logoColor=black)
![Make](https://img.shields.io/badge/build-make-427819)

A student project by **Rafael Bachourian** and **Boucksom**. The game UI is in French.

## Features

- **Real-time keyboard controls.** The terminal is switched to non-canonical mode, so keys act immediately
  without pressing *Enter*.
- **Safe first move.** Mines are placed *after* your first reveal, never on that cell or its 8 neighbours.
- **Flood-fill reveal.** Opening an empty cell recursively uncovers the whole empty region around it.
- **Chording.** Pressing `g` on an already revealed number whose flags are all placed opens its remaining
  neighbours.
- **Difficulty levels** (columns × rows):

  | Level | Board | Mines |
  | --- | --- | --- |
  | Easy (`f`) | 10 × 10 | 12 |
  | Medium (`m`) | 50 × 30 | 170 |
  | Hard (`d`) | 90 × 50 | 600 |
  | Custom (`p`) | up to 256 × 256 | your choice |

- **Leaderboard.** Your completion time is saved with your name in a separate ranking for each board
  configuration (`save/<rows>_<columns>_<mines>.txt`).
- **Unicode rendering** with mines `☢`, flags `⚑`, and hidden/open cells `◼`/`□`.

## Getting started

### Requirements

- Linux or macOS terminal (uses `clear` and `stty`)
- `gcc` and `make`

### Build and run

```bash
git clone https://github.com/Reathe/Demineur
cd Demineur
make run        # builds the `Demineur` binary and starts the game
```

Other targets: `make` (build only) and `make clean`.

## How to play

From the main menu you can **(1)** play, **(2)** view the leaderboard, **(3)** read the rules, or **(4)** quit.

| Key | Action |
| --- | --- |
| Arrow keys or `z` `q` `s` `d` | Move the cursor |
| `g` | Reveal the cell |
| `f` | Place or remove a flag |
| `p` | Quit the current game |

Reveal every cell that doesn't hide a mine to win. The faster you finish, the better your rank.

## Project structure

```
.
├── main.c               # Main menu loop
├── Demineur.c/.h        # Game loop, input handling, reveal / flood-fill / flag logic
├── structure.c/.h       # Board abstract data type (grid, cursor, mine placement, rendering)
├── saisie.c/.h          # User input, difficulty selection, score saving & leaderboard display
├── GestionProfiles/
│   ├── tadpro.c/.h      # "Profile" ADT (player name + score)
│   ├── tadlst.c/.h      # Sorted linked list of profiles
│   └── io.c/.h          # Reading / writing leaderboards to disk
├── save/                # Leaderboard files, one per board configuration
└── makefile
```

## What this project shows

- Modular C design built on **abstract data types** (board, cursor, profile, linked list), each with its own
  constructor, accessors and destructor
- Manual memory management with `calloc`/`free`
- Recursive algorithms (flood-fill on empty cells)
- File persistence with a sorted insert into the leaderboard
- Low-level terminal control (`stty -icanon`)
