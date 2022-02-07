#include <iostream>
#include <filesystem>
#include <stdlib.h>     // atoi
#include "DirStat.h"

using namespace std;
using namespace std::filesystem;

static int maxThreadNo = std::thread::hardware_concurrency(); // threads avaliable


int main(int argc, char *argv[]) {

    const path prgName = argv[0];
    int threadNo = maxThreadNo;
    path dir = ".";

    if (argc > 3 ){
        cout << "Syntax error. " << prgName.filename().c_str() << " -h for help." << endl;
        return 1;
    }
    else if (argc > 1){
        if (argc == 1 && string(argv[1]) == "-h") {
            cout << "Syntax: " << prgName.filename().c_str() << " [directory] [thread number] \ndefaults:\n\tdir: '.',\n\tthread number: current machine max  note: if you want to use this, directory is mandatory\n\n";
            return 0;
        }
        else{
            dir = argv[1];
            if (argc == 3){
                threadNo = min(atoi(argv[2]), maxThreadNo);
            }
        }
    }

    if (!exists(".")) {
        cout << endl << "The specified path does not exist! ( " << dir <<  " )" << endl;
        return 1;
    }

    DirStat dirObj(dir,threadNo);
    dirObj.statShow();
    return 0;
}
