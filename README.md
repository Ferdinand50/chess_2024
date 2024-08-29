# Chess Engine with AI opponent
Side project by Ferdinand 

Version 1 released

Simple Chess engine with an AI oppent implemented in C++. The opponent uses the MinMax+Pruning algorithm for choosing the best move. Currently it can look up 4 steps in advance. In addition sounds effects are implemented. 

![simulation_image](https://github.com/Ferdinand50/chess_2024/blob/main/src/images/board.png)

## Tested Environment
- Windows 11 with vscode
- x86_64-w64-mingw32

## Requirements
- SDL2 (https://github.com/libsdl-org/SDL/releases)
- SDL2_Image (https://github.com/libsdl-org/SDL_image/releases)
- SDL2_ttf (https://github.com/libsdl-org/SDL_ttf/releases)
- SDL2_mixer (https://github.com/libsdl-org/SDL_mixer/releases)


## Installation

1. Install all requirements
simply follow this tutorial for each package (4x): https://www.youtube.com/watch?v=H08t6gD1Y1E&t=197s




2. Build the code

```shell
make
```


## Usage
### Run the executable

```shell
./main.exe
```

press r to reset the game

press z to undo a move


## TODO
- implement castling
- implement en passant moves
- improve efficiency
- fix bugs

## Known Bugs
- the search for the best AI moves does not consider the shortes path. A move which leads to checkmate in 5 steps has a similar score to a move that leads to checkmate in 1 step. This can lead to an endless game. Possible Fix: https://stackoverflow.com/questions/59128279/how-can-i-make-minimax-alpha-beta-pruning-prioritize-shorter-paths
- Randomly spawning of a king (rarely happens)






