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
#include <vector>

using namespace std;

const char* PASSWORD = "$scriptmaster$";

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
    room1() { room('t','e'); }
    virtual void play () override {
        printRoomEntry("../icons/room1_entry.txt");
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
        cout << GREEN << "SUCCESS!\n Secret: (" << key1 << ", " << key2 << ")\n" << RESET << endl;

        exit(0);

    }
};

class room2 : public room {
public :
    room2() { room('$','s'); }
    virtual void play () override {
        printRoomEntry("../icons/room2_entry.txt");
        sleep(5);
        if (filesAreEqual()) cout << GREEN << "SUCCESS!\n Secret: (" 
                                  << key1 << ", " << key2 << ")\n" << RESET << endl;
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
            cout << RED << "Nicky's 'clone' doesn't exist :( " << RESET << endl;
            exit(1);
        }

        if (f2 == NULL){
            cout << RED << "Nicky doesn't exist. You shouldn't delete Nicky" << RESET << endl;
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
    room3() { room('c','r'); }
    virtual void play () override {
        printRoomEntry("../icons/room3_entry.txt");
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
            cout << GREEN << "SUCCESS. All bombs were removed.\n Secret: (" 
                 << key1 << ", " << key2 << ")\n" <<  RESET << endl;
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

class room4 : public room {
public : 
    room4 () { room('a','s'); } 
    virtual void play () override {
        printRoomEntry("../icons/room4_entry.txt");
        string ans;
        cout << "Enter your destination path: ";
        cin >> ans;

        if (ans.size() >= path.size() && ans.compare(ans.size() - path.size(), path.size(), path) == 0) {
            cout << GREEN << "SUCCESS! You found the right track!\n Secret: ( " 
                << key1 <<  ", " << key2 << ")\n" << RESET;
        } 
        else {
            cout << RED << "WRONG Path! Try again.\n" << RESET ;
            exit(0);
        }
    }
private:
    string path = "/ESCAPE/Australia/Egypt/Hawaii/Lanikai";
};

class room5 : public room {
public:
    room5() {room('t', 'm');}

    virtual void play () override {
        char symbol1, symbol2; 

        cout << "Enter first symbol: " << endl;
        cin >> symbol1;
        cout << "Enter second symbol: " << endl;
        cin >> symbol2;

        if (symbol1 == key1 && symbol2 == key2) {
            cout << GREEN << "SUCCESS!\n Secret: ( " << key1 <<  ", " << key2 << ")\n" << RESET;
        }
        else {
            cout << RED << "Wrong secret symbols. Try again.\n" << endl;
            exit(0);
        }
    }
};

class room6 : public room {
public : 
    room6() {room('r', '$'); }
    virtual void play () override {
        string size, date;
        cout << "a) Who's the biggest?" << endl;
        cin >> size; 
        if (size == biggest) {
            cout << "b) Who's the oldest?" << endl;
            cin >> date;
            if ( date == oldest) {
                cout << GREEN << "SUCCESS!\n Secret:(" << key1 << ", " << key2 << ")" << RESET << endl;
            }
            else {
                cout << RED << "Wrong age. Try again.\n" << RESET ;
                exit(0);
            }
        }
        else {
            cout << RED << "Wrong size. Try again.\n" << RESET ;
            exit(0);
        }
    }
private: 
    string biggest = "Paul";
    string oldest = "Sophia";
};

class room7 : public room {
public: 
    room7 () { room('i', 'p'); }
    virtual void play () override {
        struct stat fileStat;
        if (stat("lock", &fileStat) != 0) {
            perror("stat");
        }
        
        // Check if the file has no permissions (000)
        if ((fileStat.st_mode & S_IRWXU) == 0 &&   // U
            (fileStat.st_mode & S_IRWXG) == 0 &&   // G
            (fileStat.st_mode & S_IRWXO) == 0)    // O
                cout << GREEN << "SUCCESS!\n Secret:( " << key1 << ", " << key2 << ")\n" << RESET;
        else {
            cout << RED << "Error.Lock Properly!\n" << RESET; 
            exit(0);
        }   
    }

};

class room8 : public room {
public :
    room8 () {}
    virtual void play () override {
        printRoomEntry("../icons/room8_entry.txt");
        vector<string> seq(10);
        char entr; 
        char pass[50];

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
        if (strcmp(pass ,PASSWORD) != 0) {
            cout << RED << "Error! Incorrect password" << RESET << endl;
            exit(1);
        }
        else {
            cout << GREEN << "SUCCESS!\n" << RESET << "You managed to reach the end of this game! \n \
            You are really a shell script master! If you liked this game, ECE is the right place for you \n \
            See you there!" << endl;
        }
    }
};

// test from okeanos VM with public IP: 83.212.72.157
