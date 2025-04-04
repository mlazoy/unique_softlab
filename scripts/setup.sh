#!/bin/bash

# arguement is number of users 
if [ -z "$1" ]; then
    echo "Usage: $0 <number>"
    exit 1
fi

for i in $(seq 1 $1); do
    cd /home/user${i} || { echo "Directory /home/user${i} not found"; continue; }
    sudo rm -rf unique_softlab
    git clone https://github.com/mlazoy/unique_softlab.git && cd unique_softlab
    ./init.sh
done
