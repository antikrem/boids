# Compilation
## Default
Compilation with `make` for running tests in moss/goliath/getafix.

Two flags can be modified within `main.cpp`. Commenting `#define USE_OPENMP` will compile the program in its old serial form.

## View
Uncommenting `#define USE_GRAPHICS` will render a simple view with Simple2D, but this needs to have Simple2D library on path

# Usage
`boid [-counts count0 [count1...]] [-threads n] [-frames n] 
     [-size x y] [-scatterstart cycle] [-scatterduration cycle]
     [-save file] [-seed value]`

Any missing parameters will have reasonable defaults.
