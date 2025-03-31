#!/bin/bash

NUM_ROOMS=(1 2 3 4 5 6 7 8)  
ESCAPE_PATH="./escape"

sudo rm -rf "$ESCAPE_PATH"
mkdir -p "$ESCAPE_PATH"

cp -r src/icons $ESCAPE_PATH 

for room_id in "${NUM_ROOMS[@]}"; do  
    VERSION="ROOM${room_id}"  
    dirname="room${room_id}"
    mkdir -p "$ESCAPE_PATH/$dirname"
    cp -r "./src/room${room_id}/." "$ESCAPE_PATH/$dirname"
    echo "Compiling for $VERSION..."
    g++ -std=c++17 -D$VERSION ./src/escape.cpp -o "$ESCAPE_PATH/$dirname/play"
    if [[ "$dirname" == "room6" ]]; then
        touch -t 200703311430 Alex
        touch -t 200903311430 Paul
        touch -t 200403311430 Sophia
        touch -t 200503311430 Jenny
    fi
done

chmod 000 $ESCAPE_PATH"/room7/readme.txt"
mv $ESCAPE_PATH"/icons" $ESCAPE_PATH"/../icons"

# be careful with this 
rm -r src
