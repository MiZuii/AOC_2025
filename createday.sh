#!/bin/bash

if [ $# == 1 ]; then
    day_dir="$1"
else
    day_dir="day$(date +%d)"
fi

if [ -d "$day_dir" ]; then
    echo "directory \"$day_dir\" exists"
    exit 1
fi

mkdir "$day_dir"
cat template.cpp >> "$day_dir"/puzzle1.cpp
cat template.cpp >> "$day_dir"/puzzle2.cpp
cd "$day_dir"
touch input.txt
cp ../template.mk Makefile
