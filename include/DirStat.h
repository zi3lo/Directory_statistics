#pragma once

#include <iostream>
#include <filesystem>   // filessystem operation
#include <fstream>      // reading from files
#include <chrono>       // benchmark: high_resolution_clock::now
#include <semaphore>    // counting_semaphore
#include <future>       // thread pool: async
#include <vector>

class DirStat
{
    public:

        DirStat(std::filesystem::path DIR = ".", int THNO = 1) : dir(DIR),threadsNo(THNO) {
            dirList.push_back(dir);
        };  // default c-tor
        virtual ~DirStat();

        void statShow();


    private:

        void dirPool(int); // thread pool of dirStat calls (number of threads)
        void dirStat(const std::filesystem::path); // directory statistics
        void makeDirList(const std::filesystem::path); // recursive directory check
        char entryType(std::filesystem::file_status); // directory or regular file check

        size_t filesNo{0}, linesNo{0}, emptyLNo{0}, charNo{0}, letterNo{0}, digitNo{0}, wordNo{0};
        std::filesystem::path dir;
        std::vector<std::filesystem::path>dirList;
        int threadsNo;

};

