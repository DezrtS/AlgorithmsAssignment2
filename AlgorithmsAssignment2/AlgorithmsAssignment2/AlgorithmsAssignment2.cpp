// -------------------------------------------------------------------- //
// Title: Algorithms and Data Structures Assignment 2                   //
// Author: Denzil Walrond                                               //
// Due Date: 03/24/2024                                                 //
// -------------------------------------------------------------------- //

#include <iostream>
#include <string>
#include <vector>

#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

static void PrintArray(int array[], int arraySize) {
    std::cout << array[0];
    for (int i = 1; i < arraySize; i++) {
        std::cout << ", " << array[i];
    }
    std::cout << std::endl;
}

static void Merge(int array[], int rightArray[], int rightArraySize, int leftArray[], int leftArraySize) {
    int totalArraySize = leftArraySize + rightArraySize;
    int leftArrayIndex = 0;
    int rightArrayIndex = 0;

    for (int i = 0; i < totalArraySize; i++) {
        if (leftArray[leftArrayIndex] <= rightArray[rightArrayIndex]) {
            array[i] = leftArray[leftArrayIndex];
            leftArrayIndex++;
            if (leftArrayIndex >= leftArraySize) {
                while (rightArrayIndex < rightArraySize) {
                    i++;
                    array[i] = rightArray[rightArrayIndex];
                    rightArrayIndex++;
                }
                std::cout << std::endl;
                std::cout << "[Merged Array] : ";
                PrintArray(array, totalArraySize);
                std::cout << std::endl;
                PlaySound(TEXT("SwapSFX.wav"), NULL, SND_FILENAME | SND_SYNC);
                return;
            }
        }
        else {
            array[i] = rightArray[rightArrayIndex];
            rightArrayIndex++;
            if (rightArrayIndex >= rightArraySize) {
                while (leftArrayIndex < leftArraySize) {
                    i++;
                    array[i] = leftArray[leftArrayIndex];
                    leftArrayIndex++;
                }
                std::cout << std::endl;
                std::cout << "[Merged Array] : ";
                PrintArray(array, totalArraySize);
                std::cout << std::endl;
                PlaySound(TEXT("SwapSFX.wav"), NULL, SND_FILENAME | SND_SYNC);
                return;
            }
        }
    }
}

static int* MergeSort(int array[], int arraySize) {
    PrintArray(array, arraySize);
    int rightArraySize = arraySize / 2;
    int leftArraySize = arraySize - rightArraySize;

    if (rightArraySize == 0) {
        return array;
    }

    int* leftArray = new int[leftArraySize];
    int* rightArray = new int[rightArraySize];

    for (int i = 0; i < leftArraySize; i++) {
        leftArray[i] = array[i];
    }

    for (int i = 0; i < rightArraySize; i++) {
        rightArray[i] = array[leftArraySize + i];
    }

    Merge(array, MergeSort(rightArray, rightArraySize), rightArraySize, MergeSort(leftArray, leftArraySize), leftArraySize);

    delete[] leftArray;
    delete[] rightArray;

    return array;
}

static std::vector<std::string> SplitString(const std::string& str, const std::string& delimiter) {
    // Splits a string up into a vector of strings.
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }

    result.push_back(str.substr(start));
    return result;
}

int main()
{
    std::cout << "Enter a integer array where each value is seperated by a comma ( Ex: [5,10,92] )" << std::endl;
    std::string inputtedNumbers;
    std::cin >> inputtedNumbers;
    std::vector<std::string> splitNumbers = SplitString(inputtedNumbers, ",");
    int arraySize = splitNumbers.size();
    int* array = new int[arraySize];

    try {
        for (int i = 0; i < arraySize; i++) {
            array[i] = std::stoi(splitNumbers[i]);
        }
    }
    catch (...) {
        std::cout << "\n[An Error Occured While Reading Inputted Numbers]";
        delete[] array;
        return 0;
    }

    std::cout << "\n------------------------Starting Merge Sorting------------------------" << std::endl << std::endl;
    MergeSort(array, arraySize);
    std::cout << "\n-------------------------Ending Merge Sorting-------------------------" << std::endl;

    std::cout << "\nFinal Sorted Array," << std::endl;
    PrintArray(array, arraySize);

    delete[] array;
    PlaySound(TEXT("Victory.wav"), NULL, SND_FILENAME | SND_SYNC);

    return 0;
}