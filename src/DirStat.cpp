#include "DirStat.h"


DirStat::~DirStat() {
}

char DirStat::entryType(std::filesystem::file_status file) { // directory or regular file check
    if (std::filesystem::is_directory(file)) return 'd';
    else if (std::filesystem::is_regular_file(file)) return 'f';
}

void DirStat::makeDirList(const std::filesystem::path dir_) {  // recursive directory check
    for (auto const& dirEntry : std::filesystem::directory_iterator{dir_}) {
        if ( entryType(status(dirEntry)) == 'd' ) {
            dirList.push_back(dirEntry); // list of directories to vec
            makeDirList(dirEntry);
        }
    }
}

void DirStat::dirStat(std::filesystem::path dir) {
    for (auto const& dirEntry : std::filesystem::directory_iterator{dir}) {

        if ( entryType(status(dirEntry)) == 'f' ) {

            bool emptyLine, word=false;
            std::ifstream file(std::filesystem::canonical(dirEntry));
            std::istreambuf_iterator<char> ch{file}, eos; // iterator char by char

            if (*ch == '\n')
                emptyLine = true;

            while (ch != eos) {
                if (*ch == '\n' || *ch == '\t' || *ch == ' '){ // words counter
                    if (word) wordNo++;
                    word = false;
                } else word = true;


                if (*ch == '\n') { // (empty)lines counter
                    if (emptyLine) emptyLNo++;
                    emptyLine = true;
                    linesNo++;
                } else emptyLine = false;

                if ((*ch >= 'A' && *ch <= 'Z') || (*ch >= 'a' && *ch <= 'z')) // letter counter
                    letterNo++;

                if (*ch >= '0' && *ch <= '9') // digit counter
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

    makeDirList(dir);
    dirPool(threadsNo);

    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t1); // some benchmark ;)
    double d = (double)dur.count()/1000; // let's make it human readable

    std::cout << "Directory " << canonical(dir).c_str() << " contains: \n";
    std::cout << "\nFILES: " << filesNo << std::endl;
    std::cout << "LINES: " << linesNo << std::endl;
    std::cout << "EMPTY LINES: " << emptyLNo << std::endl;
    std::cout << "WORDS: " << wordNo << std::endl;
    std::cout << "CHARS: " << charNo << std::endl;
    std::cout << "LETTERS: " << letterNo << std::endl;
    std::cout << "DIGITS: " << digitNo << std::endl;
    std::cout << "\nExecution time: " << d << "ms\n";
}

void DirStat::dirPool(int tn) { // thread pool of dirStat calls (number of threads)
    std::counting_semaphore tasks{tn}; // semaphores (since c++20)
    std::vector<std::future<void>>futures;
    int c = 0;

    for (auto d : dirList) {
        tasks.acquire(); // lock
        futures.push_back( std::async(std::launch::async, [this, &tasks, d] () {
            this->dirStat(d);
            tasks.release(); // release (in thread)
        } ) );
    }
}


