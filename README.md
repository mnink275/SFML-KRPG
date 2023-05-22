# Simple RPG game

- The [SFML](https://github.com/SFML) library is used for graphics.

- The initial sturcture is based on a game from the book ["SFML Game Development"](https://www.amazon.com/SFML-Game-Development-Artur-Moreira-ebook/dp/B00DL0CFHC), written by Arthur Moreira, Vogelius Henrik Hansson, and Jan Haller.

## Building
- Visual Studio 17 2022:
  ```shell
  git clone https://github.com/mnink275/SFML-KRPG
  cd SFML-KRPG
  cmake -S . -B build
  cmake --build build
  cmake --open build
  ```

- Linux:
  ```shell
  git clone https://github.com/mnink275/SFML-KRPG
  cd SFML-KRPG/
  make build-debug
  ./build/SFML-KRPG
  ```

## License
This software is available under 2 licenses -- choose whichever you prefer.

