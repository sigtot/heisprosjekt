# Heisprosjekt
Heisprosjekt i tilpdat

TTK4235 Tilpassede Datasystemer

# Dependencies
* comedilib
* gcc

# Compilation
* `make` to compile
* `make clean` to remove all binaries and object files
* `make rebuild` to remove binaries and object files then recompile

# Usage
* `./bin/heis` to run
* Add the `-w` or `--web` flags to enable the web view (requires curl)

# Code style
* The project uses the [Chromium code style](https://chromium.googlesource.com/chromium/src/+/master/styleguide/c++/c++.md)
* `sh code_style.sh` to apply the styling to the codebase (requires clang-format)
