#include "PlayerTests.h"
#include "../../Player.h"
#include <fstream>
#include <iostream>

Player* testPlayer = new Player("test", 1);

PlayerTests::PlayerTests() {
    std::cout << "TESTING PLAYER" << std::endl;
    mosaicTest();
}

PlayerTests::~PlayerTests() {

}

void PlayerTests::mosaicTest() {
    // NOTE: Look at differences between ofstreams and ifstreams
    std::fstream inputFile("../input/mosaic-input.txt");
    std::fstream outputFile("../output/mosaic-output.txt");
    string mosaicStrInput;
    string mosaicStrOutput;

    testPlayer->printPlayerBoard();

    // deletes content once closed
    //outputFile.open("../output/mosaic-output.txt", std::fstream::out | std::fstream::trunc);

    std::getline(inputFile, mosaicStrInput);
    mosaicStrInput = "byRullbyruULbyrrUlbyyrUlb";
    std::cout << mosaicStrInput << std::endl;

    testPlayer->setMosaic(mosaicStrInput);

    // Don't have to dereference. It is done implicitly
    std::array<std::array<char, 5>, 5>& mosaicRef = testPlayer->getMosaic();
    std::cout << mosaicRef[0][0] << std::endl;
    outputFile << mosaicRef[0][0];
    for(int row_num = 0; row_num < 5; ++row_num) {
        for(int col_num = 0; col_num < 5; ++col_num) {
            outputFile << mosaicRef[row_num][col_num];
        }
    }

    outputFile << 'I';
    std::getline(outputFile, mosaicStrOutput);
    std::cout << mosaicStrOutput << std::endl;

    if(mosaicStrInput == mosaicStrOutput) {
        std::cout << "TESTING MOSAIC ... PASSED" << std::endl;
    } else {
        std::cout << "TESTING MOSAIC ... FAILED" << std::endl;
    }

    inputFile.close();
    outputFile.close();
}