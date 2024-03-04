# Usage

Make sure you have cmake installed, you can download it from their [website here](https://cmake.org/download/).

To setup the project, run:

```cmake 
cmake -Bbuild -S.
``` 

You can specify a generator with the `-G` flag, for example, Ninja: `-GNinja`.

To compile / recompile the project, run:
```cmake
cmake --build build
```
