/* program bierze pod uwagę katalogi i zwykłe pliki
omija symlinki i odnośniki do urządzeń
*/

/// TO DO : words, threads, Gtest, benchmark

#include <iostream>
#include <filesystem>
#include "DirStat.h"


using namespace std;
using namespace std::filesystem;

int main(int argc, char *argv[])
{
    const path prgName = argv[0];

    if (argc > 2) {
        cout << "Syntax error. " << prgName.filename().c_str() << " -h for help." << endl;

        return 1;
    }
    if (argc == 2 && string(argv[1]) == "-h"){
        cout << "Syntax: " << prgName.filename().c_str() << " [directory] \tdefault is local " << endl;
        return 0;
    }

    const path dir {argc == 2 ? argv[1] : "."}; // user defined directory or current


    if (!exists(dir)){
        cout << endl << "Podana ścieżka nie istnieje! ( " << dir <<  " )" << endl;
        return 1;
    }
    //cout << canonical(dir).c_str() << endl; //remove . .. and (c.str) remove "


    DirStat dirObj;
    dirObj.statShow();


    return 0;
}
