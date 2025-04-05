#!/bin/bash

mkdir bombXL

for j in {1..10}
do
  dirname="bombXL${j}.b"
  mkdir "$dirname"
  
  for i in {1..20}
  do
    filename="bomb$i"
    touch "$dirname/$filename"
  done
done


ORANGE='\e[38;5;214m'
RESET='\e[0m'
printf "${ORANGE}$(cat ../../icons/bomb_icon.txt | sed 's/%/%%/g')${RESET}\n"


