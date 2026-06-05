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
├── build.sh
├── CMakeLists.txt
├── hive_engine
├── include
│   ├── decorators.hpp
│   ├── engine
│   │   ├── alfabeta.hpp
│   │   ├── bestmove.hpp
│   │   ├── evaluations.hpp
│   │   └── transpositionTable.hpp
│   ├── exceptions.hpp
│   ├── hive
│   │   ├── board.hpp
│   │   ├── coordinates.hpp
│   │   ├── game.hpp
│   │   ├── gamecontroller.hpp
│   │   ├── moves.hpp
│   │   ├── namespaces.hpp
│   │   ├── protocol.hpp
│   │   └── zobrist.hpp
│   ├── Hive.h
│   ├── HiveAI
│   ├── nnue
│   │   ├── accumulator.hpp
│   │   ├── activations.hpp
│   │   ├── FullyConnected.hpp
│   │   ├── layer.hpp
│   │   ├── loss.hpp
│   │   ├── ndarray.hpp
│   │   └── sequential.hpp
│   ├── nnue.h
│   └── version.h
├── README.md
├── src
│   ├── engine
│   │   ├── alfabeta.cpp
│   │   ├── CMakeLists.txt
│   │   ├── evaluations.cpp
│   │   └── transpositionTable.cpp
│   ├── hive
│   │   ├── board.cpp
│   │   ├── CMakeLists.txt
│   │   ├── coordinates.cpp
│   │   ├── game.cpp
│   │   ├── gamecontroller.cpp
│   │   ├── moves.cpp
│   │   ├── protocol.cpp
│   │   └── zobrist.cpp
│   ├── main.cpp
│   ├── nnue.cpp
│   └── trained_nnue.cpp
├── test
│   └── test.cpp
└── Trainer.py
```
