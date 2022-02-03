#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>

class DirStat
{
    public:
        DirStat(std::filesystem::path DIR = ".") : dir(DIR) {};  // default c-tor
        virtual ~DirStat();

        void statShow();

    private:
        size_t filesNo{0}, linesNo{0}, emptyLNo{0}, charNo{0}, letterNo{0}, digitNo{0};
        std::filesystem::path dir;

        char entryType(std::filesystem::file_status);
        void dirStat(std::filesystem::path&);
};

