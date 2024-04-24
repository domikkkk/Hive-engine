# Needed
- Cmake installed with:
```bash
sudo apt update
sudo apt install cmake
```

# How to build?
Just run:
```bash
sh build.sh
```
or
```bash
./build.sh
```

# How to run?
to run program:
```bash
./hive_engine
```
to run test:
```bash
./tests
```

# File structure
```
<project root>
├── CMakeLists.txt
├── README.md
├── build.sh
├── include
│   ├── Hive
│   ├── engine
│   │   └── alfabeta.hpp
│   └── hive
│       ├── board.hpp
│       └── pieces.hpp
├── src
│   ├── hive
│   │   ├── CMakeLists.txt
│   │   ├── board.cpp
│   │   └── pieces.cpp
│   └── main.cpp
└── test
    └── test.cpp
```
