#ifndef __ESACPE__HPP__
#define __ESCAPE__HPP__
#endif

#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdio>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

const char* PASSWORD = "$shellscriptmaster$";

// ANSI escape codes for colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

class room {
public:
    room() {} //default
    room(char k1, char k2): key1(k1), key2(k2) {}
    virtual void play() {}
    void printRoomEntry(const string &filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        cout << BLUE;
        while (getline(file, line)) {
            cout << line << endl;
        }
        cout << RESET;
        file.close();
    }
}
protected:
    char key1, key2;
};

class room1 : public room {
public :
    room1() { room('h','e'); }
    virtual void play () override {
        printRoomEntry("../.room1_entry.txt");
        int num;
        cout << YELLOW << "How many dwarves are in this room?" << RESET << endl;
        cin >> num;
        if (num == 6) {
            cout << RED << "FAIL! Find ALL of them again." << RESET << endl;
            exit(1);
        }
        else if (num != 18) {
            cout << RED << "FAIL! Count them again." << RESET << endl;
            exit(1);
        }
        cout << GREEN << "CORRECT!" << RESET << endl;

        cout << BLUE << "Dwarf 17 has something to tell you..." << RESET << endl;
        exit(0);

    }
};

class room2 : public room {
public :
    room2() { room('$','s'); }
    virtual void play () override {
        printRoomEntry("../.room2_entry.txt");
        if (filesAreEqual()) cout << GREEN << "SUCCESS!" << RESET << endl;
        else {
            cout << RED << "Error! Nicky and clone are not identical" << RESET << endl;
            exit(1);
        }
    }
private:
    int filesAreEqual() {
        FILE *f1 = fopen("clone", "rb");
        FILE *f2 = fopen("Nicky", "rb");

        if (f1 == NULL) {
            cout << "Nicky's 'clone' doesn't exist :( " << endl;
            exit(1);
        }

        if (f2 == NULL){
            cout << "Nicky doesn't exist. You shouldn't delete Nicky" << endl;
            exit(1);
        }

        fseek(f1, 0, SEEK_END);
        fseek(f2, 0, SEEK_END);

        long size1 = ftell(f1);
        long size2 = ftell(f2);

        if (size2 == 0){
            cout << "Heyyy what did you do to Nicky?" << endl;
            fclose(f1);
            fclose(f2);
            exit(1);
        }

        if (size1 != size2) {
            fclose(f1);
            fclose(f2);
            return 0; 
        }

        fseek(f1, 0, SEEK_SET);
        fseek(f2, 0, SEEK_SET);

        unsigned char buffer1, buffer2;
        while (fread(&buffer1, 1, 1, f1) == 1 && fread(&buffer2, 1, 1, f2) == 1) {
            if (buffer1 != buffer2) {
                fclose(f1);
                fclose(f2);
                return 0; 
            }
        }

        fclose(f1);
        fclose(f2);

        return 1; 
    }
};

class room3 : public room {
public :
    room3() { room('s','c'); }
    virtual void play () override {
        printRoomEntry("../.room3_entry.txt");
        FILE *f = fopen("bomb", "r");
        if (f !=NULL && free_of_bombs()){
            // first try 
                cout << YELLOW << "The 'bomb' is still here. Run ./deactivate.sh to remove it" << RESET << endl;
                sleep(10);
                cout << RED << "Error. Time's up!" << RESET << endl;
                exit(1);
        }

        else if (f != NULL && !free_of_bombs()) {
            cout << "Try to remove bombs step by step by yourself starting from bomb" << endl;
            sleep(10);
            cout << RED << "Error. Time's up!" << RESET << endl;
            exit(1);
        }

        else if (f == NULL && !free_of_bombs()) {
            cout << GREEN << "Success some bombs were removed. Keep up" << RESET << endl;
            sleep(10);
            cout << RED << "Error. Time's up!" << RESET << endl;
            exit(1);
        }

        else if (f == NULL && free_of_bombs()) {
            cout << GREEN << "SUCCESS. All bombs were removed. You are a life saver :)" << RESET << endl;
            exit(0);
        }
    }
private :
    bool free_of_bombs(){
        struct dirent *entry;
        DIR *dp = opendir(".");

        if (dp == NULL) {
            perror("opendir");
            exit(1);
        }

        while ((entry = readdir(dp))) {
            if (strncmp(entry->d_name, "bombXL", 6) == 0) {
                struct stat statbuf;
                stat(entry->d_name, &statbuf);
                
                if (S_ISDIR(statbuf.st_mode)) {
                    closedir(dp);
                    return 0;
                }
            }
        }
        closedir(dp);
        return 1;
    }
};

class room10 : public room {
public :
    room10 () {}
    virtual void play () override {
        printRoomEntry("../.room10_entry.txt");
        vector<string> seq(10);
        char entr; 
        char* pass;

        seq[0] = "The king wakes up in the morning, goes from his bedroom to the bathroom to wash his teeth, ";
        seq[1] = "then to the garden to water his beautiful plants, ";
        seq[2] = "and finally to the kitchen to make a hot tea, ";
        seq[3] = "that he is goint to drink straight afterwards sitting in his balcony.";
        seq[4] = "When it's about 10 o'clock, his accountant sends one of his clerks to king's house to check his gold.";
        seq[5] = "The clerk knocks the door, and the king goes down to the living room to open.";
        seq[6] = "They walk together in a long corridor at the end of which there is a secret door leading to king's vault.";
        seq[7] = "The king asks for a password to validate clerk's identity.";
        seq[8] = "Can you pretend the clerk and steal king's gold?" ;
        seq[9] = "Write the password: ";

        cout << YELLOW << endl;
        for (int i = 0; i < 10; i++) {
            cout << seq[i] << endl;
            cin.get(); 
            if (i == 9) break;
        }
        cout << RESET;

        cin >> pass;
        if (strcmp(pass ,PASSWORD)) {
            cout << RED << "Error! Incorrect password" << RESET << endl;
            exit(1);
        }
        else {
            cout << GREEN << "SUCCESS!\n" << RESET << "You managed to reach the end of this game! \
            You are really a shell script master! If you liked this game, ECE is the right place for you\
            See you there!" << endl;
        }
    }
};

//TODO! 
class room4 : public room {};
class room5 : public room {};
class room6 : public room {};
class room7 : public room {};
class room8 : public room {};
class room9 : public room {};