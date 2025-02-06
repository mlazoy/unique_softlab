#include "escape.hpp"

int main() {
    room *curr_room;

    #ifdef ROOM1 
        curr_room = new room1();
        curr_room->play();
    #endif 

    #ifdef ROOM2 
        curr_room = new room2();
        curr_room->play();
    #endif 

    #ifdef ROOM3
        curr_room = new room3();
        curr_room->play();
    #endif 

    #ifdef ROOM4
        curr_room = new room4();
        curr_room->play();
    #endif 

    #ifdef ROOM5 
        curr_room = new room5();
        curr_room->play();
    #endif 

    #ifdef ROOM6
        curr_room = new room6();
        curr_room->play();
    #endif 

    #ifdef ROOM7 
        curr_room = new room7();
        curr_room->play();
    #endif 

    #ifdef ROOM8 
        curr_room = new room8();
        curr_room->play();
    #endif 

    #ifdef ROOM9
        curr_room = new room9();
        curr_room->play();
    #endif

    #ifdef ROOM10
        curr_room = new room10();
        curr_room->play();
    #endif  

}
