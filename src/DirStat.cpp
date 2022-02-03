#include "DirStat.h"


DirStat::~DirStat() {

}

char DirStat::entryType(std::filesystem::file_status file) {
    if (std::filesystem::is_directory(file)) return 'd';
    else if (std::filesystem::is_regular_file(file)) return 'f';
}

void DirStat::dirStat(std::filesystem::path& dir) {
    for (auto const& dirEntry : std::filesystem::directory_iterator{dir}) {
        std::filesystem::path entry{dirEntry};
        char type {entryType(status(entry))};
        //std::cout << entry.filename().c_str() << " " << type << std::endl;
        if (type == 'd') {
            //std::cout << std::endl << entry.filename().c_str() << " directory contains: " << std::endl;
            dirStat(entry);
        }
        if (type == 'f') {

            bool emptyLine;
            std::ifstream file(entry);
            std::istreambuf_iterator<char> ch(file), eos;

            if (*ch == '\n')
                emptyLine = true;

            while (ch != eos) {

                if (*ch == '\n') {
                    if (emptyLine) emptyLNo++;
                    emptyLine = true;
                    linesNo++;
                } else emptyLine = false;

                if ((*ch >= 'A' && *ch <= 'Z') || (*ch >= 'a' && *ch <= 'z'))
                    letterNo++;

                if (*ch >= '0' && *ch <= '9')
                    digitNo++;

                ch++;
                charNo++;
            }

            filesNo++;
        }

    }
}

void DirStat::statShow() {
    auto t1 = std::chrono::high_resolution_clock::now();
    dirStat(dir);
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t1);

    std::cout << "Directory " << canonical(dir).c_str() << " contains: \n";
    std::cout << "\nFILES: " << filesNo << std::endl;
    std::cout << "LINES: " << linesNo << std::endl;
    std::cout << "EMPTY LINES: " << emptyLNo << std::endl;
    std::cout << "CHARS: " << charNo << std::endl;
    std::cout << "LETTERS: " << letterNo << std::endl;
    std::cout << "DIGITS: " << digitNo << std::endl;
    std::cout << "\nExecution time: " << dur.count() << "ms\n";

}

