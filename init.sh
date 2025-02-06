#!/bin/bash

NUM_ROOMS=(1 2 3 10)  # Corrected array syntax
ESCAPE_PATH="./ESCAPE"

rm -rf "$ESCAPE_PATH"
mkdir -p "$ESCAPE_PATH"

shopt -s dotglob  
cp *.txt "$ESCAPE_PATH"
shopt -u dotglob

for room_id in "${NUM_ROOMS[@]}"; do  
    VERSION="ROOM${room_id}"  
    mkdir -p "$ESCAPE_PATH/$VERSION"
    cp -r "./room${room_id}/." "$ESCAPE_PATH/$VERSION"
    echo "Compiling for $VERSION..."
    g++ -std=c++17 -D$VERSION escape.cpp -o "$ESCAPE_PATH/$VERSION/play"
done
