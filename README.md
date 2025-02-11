# Needed

- Cmake installed with:

```bash
sudo apt update
sudo apt install cmake
```

## How to build?

Just run:

```bash
sh build.sh
```

or

```bash
./build.sh
```

## How to run?

to run program:

```bash
./hive_engine
```

to run test:

```bash
./tests
```

## File structure

```md
<project root>
├── CMakeLists.txt
├── README.md
├── Trainer.py
├── build.sh
├── include
│   ├── Hive
│   ├── HiveAI
│   ├── decorators.hpp
│   ├── engine
│   │   ├── alfabeta.hpp
│   │   ├── bestmove.hpp
│   │   ├── evaluations.hpp
│   │   └── transpositionTable.hpp
│   ├── hive
│   │   ├── board.hpp
│   │   ├── coordinates.hpp
│   │   ├── game.hpp
│   │   ├── gamecontroller.hpp
│   │   ├── moves.hpp
│   │   ├── namespaces.hpp
│   │   ├── protocol.hpp
│   │   └── zobrist.hpp
│   └── version.h
├── src
│   ├── engine
│   │   ├── CMakeLists.txt
│   │   ├── alfabeta.cpp
│   │   ├── evaluations.cpp
│   │   └── transpositionTable.cpp
│   ├── hive
│   │   ├── CMakeLists.txt
│   │   ├── board.cpp
│   │   ├── coordinates.cpp
│   │   ├── game.cpp
│   │   ├── gamecontroller.cpp
│   │   ├── moves.cpp
│   │   ├── protocol.cpp
│   │   └── zobrist.cpp
│   └── main.cpp
└── test
    └── test.cpp
```
