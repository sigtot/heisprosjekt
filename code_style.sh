#!/bin/bash
for file in $(find -path ./src/driver -prune -o \( -name '*.c' -o -name '*.h' \) -print);
do
clang-format -style="{BasedOnStyle: Chromium, IndentWidth: 4,TabWidth: 4}" -i ${file};
echo "Formatted ${file}";
done
