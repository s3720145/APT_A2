#include "PlayerTests.h"
#include "../../Player.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>

using std::cout;
using std::endl;

Player* testPlayer = new Player("test", 1);

PlayerTests::PlayerTests() {
    cout << "TESTING PLAYER ..." << endl;
    mosaicTest();
    storageTest();
}

PlayerTests::~PlayerTests() {

}

void PlayerTests::mosaicTest() {
    cout << "TESTING PLAYER MOSAIC ..." << endl;

    // NOTE: Look at differences between ofstreams and ifstreams
    std::ifstream inputFile("src/tests/input/mosaic-input.txt");
    std::ofstream outputFile("src/tests/output/mosaic-output.txt");
    string mosaicInput;
    string mosaicOutput;


    if (!inputFile) {
        std::cout << "Somthing failed while opening the file\n";
    }

    // deletes content once closed
    //outputFile.open("../output/mosaic-output.txt", std::fstream::out | std::fstream::trunc);

    inputFile.clear();
    while(std::getline(inputFile, mosaicInput)) {
        // the read worked and the line is valid
    }

    testPlayer->setMosaic(mosaicInput);

    for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
            outputFile << *testPlayer->getMosaicTile(row_num,col_num);
        }
    }

    testPlayer->printPlayerBoard();

    inputFile.close();
    outputFile.close();
}

void PlayerTests::storageTest() {
    cout << "TESTING PLAYER STORAGE ..." << endl;

    std::ifstream inputFile("src/tests/input/storage-input.txt");
    std::ofstream outputFile("src/tests/output/storage-output.txt");
    string storageInput;
    string combinedInput;
    string storageOutput;

    if (!inputFile) {
        std::cout << "Something failed while opening the file \n";
    }

    inputFile.clear();
    while(std::getline(inputFile, storageInput, '\r')) {
        // the read worked and the line is valid
        cout << storageInput;
        storageInput.pop_back();
        //combinedInput += storageInput;
        combinedInput.append(storageInput);
    }

    //combinedInput.replace("\n", "");
    //combinedInput.erase(std::remove(combinedInput.begin(), combinedInput.end(), '\n'), combinedInput.end());

    cout << combinedInput << endl;

    testPlayer->setStorage(combinedInput);

    for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        for(int col_num = 0; col_num <= row_num; ++col_num) {
            outputFile << getTileColourAsString(*testPlayer->getStorageTile(row_num, col_num));
        }
        outputFile << '\n';
    }

    testPlayer->printPlayerBoard();

    inputFile.close();
    outputFile.close();
}