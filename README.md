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
├── build.sh
├── include
│   ├── Hive
│   ├── HiveEngine
│   ├── engine
│   │   └── alfabeta.hpp
│   └── hive
│       ├── board.hpp
│       └── pieces.hpp
├── src
│   ├── engine
│   │   ├── CMakeLists.txt
│   │   └── alfabeta.cpp
│   ├── hive
│   │   ├── CMakeLists.txt
│   │   ├── board.cpp
│   │   └── pieces.cpp
│   └── main.cpp
└── test
    └── test.cpp
```
