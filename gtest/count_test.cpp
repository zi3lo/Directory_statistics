#include <iostream>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <gtest/gtest.h>

class DirStat{
    public:

        size_t linesNo{0}, emptyLNo{0}, charNo{0}, letterNo{0}, digitNo{0}, wordNo{0};

        void dirStat(std::filesystem::path file) {

                bool emptyLine, word=false;
                std::ifstream file_(file);
                std::istreambuf_iterator<char> ch{file_}, eos; // iterator char by char

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
            }
};

TEST(FactorialTest, Positive){\
    DirStat *cl = new DirStat;
    cl->dirStat("new_line_first_6_wrods.txt");
    EXPECT_EQ(7, cl->linesNo);
    EXPECT_EQ(3, cl->emptyLNo);
    EXPECT_EQ(41, cl->charNo);
    EXPECT_EQ(24, cl->letterNo);
    EXPECT_EQ(6, cl->digitNo);
    EXPECT_EQ(6, cl->wordNo);
    delete cl;
    cl =  new DirStat;
    cl->dirStat("spaces_first_5_wrods.txt");
    EXPECT_EQ(7, cl->linesNo);
    EXPECT_EQ(3, cl->emptyLNo);
    EXPECT_EQ(81, cl->charNo);
    EXPECT_EQ(20, cl->letterNo);
    EXPECT_EQ(5, cl->digitNo);
    EXPECT_EQ(5, cl->wordNo);\
    delete cl;
    cl = NULL;
}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

