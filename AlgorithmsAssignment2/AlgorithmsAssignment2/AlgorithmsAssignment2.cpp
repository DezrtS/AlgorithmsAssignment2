// -------------------------------------------------------------------- //
// Title: Algorithms and Data Structures Assignment 2                   //
// Author: Denzil Walrond                                               //
// Due Date: 03/24/2024                                                 //
// -------------------------------------------------------------------- //

// #Include statements
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

/**
 * @brief Prints out an array.
 *
 * @param array The array to be printed out.
 * @param arraySize The size of the given array.
 */
static void PrintArray(int array[], int arraySize) {
    // Prints out the initial element.
    std::cout << array[0];
    // Cycles through the array and prints out each element seperated by a comma and space.
    for (int i = 1; i < arraySize; i++) {
        std::cout << ", " << array[i];
    }
    std::cout << std::endl;
}

/**
 * @brief Runs the Merge Sort Algorithm on an array.
 *
 * This static method takes a main array, a right sub array, a right 
 * sub array size, a left sub array, and a left sub array size. The
 * two sub arrays are merged sorted into the main array and then a
 * sound is played to indicate that a merge/swap has occured.
 *
 * @param array The main array to facilitate the merge.
 * @param rightArray The right sub array to be merged with.
 * @param rightArraySize The size of the right sub array.
 * @param leftArray The left sub array to be merged with.
 * @param leftArraySize The size of the left sub array.
 */
static void Merge(int array[], int rightArray[], int rightArraySize, int leftArray[], int leftArraySize) {
    // Calculates the total array size.
    int totalArraySize = leftArraySize + rightArraySize;
    int leftArrayIndex = 0;
    int rightArrayIndex = 0;

    // Cycles through the entire initial array.
    for (int i = 0; i < totalArraySize; i++) {
        // If the left array element is less than or equal to the right array element, 
        // set it current index element of the inital array equal to the left array element.
        // Or vise versa for the right array element if the opposite is true.
        if (leftArray[leftArrayIndex] <= rightArray[rightArrayIndex]) {
            array[i] = leftArray[leftArrayIndex];
            leftArrayIndex++;
            // If there are no more elements to compare from the left sub array, insert the remaining elements from the right sub array.
            if (leftArrayIndex >= leftArraySize) {
                // Cycle through the right sub array until there are no more values left to add.
                while (rightArrayIndex < rightArraySize) {
                    i++;
                    array[i] = rightArray[rightArrayIndex];
                    rightArrayIndex++;
                }
                std::cout << std::endl;
                // Print out the newly merged and sorted array.
                std::cout << "[Merged Array] : ";
                PrintArray(array, totalArraySize);
                std::cout << std::endl;
                // Play the swap SFX.
                PlaySound(TEXT("SwapSFX.wav"), NULL, SND_FILENAME | SND_SYNC);
                return;
            }
        }
        else {
            array[i] = rightArray[rightArrayIndex];
            rightArrayIndex++;
            // If there are no more elements to compare from the right sub array, insert the remaining elements from the left sub array.
            if (rightArrayIndex >= rightArraySize) {
                // Cycle through the left sub array until there are no more values left to add.
                while (leftArrayIndex < leftArraySize) {
                    i++;
                    array[i] = leftArray[leftArrayIndex];
                    leftArrayIndex++;
                }
                std::cout << std::endl;
                // Print out the newly merged and sorted array.
                std::cout << "[Merged Array] : ";
                PrintArray(array, totalArraySize);
                std::cout << std::endl;
                // Play the swap SFX.
                PlaySound(TEXT("SwapSFX.wav"), NULL, SND_FILENAME | SND_SYNC);
                return;
            }
        }
    }
}

/**
 * @brief Runs the Merge Sort Algorithm on an array.
 *
 * This static method takes a main array and array size and recursively 
 * splits it up into 2 sub arrays. It then merges and sorts the two sub 
 * arrays back into their main array before returning the sorted array.
 *
 * @param array The array to be sorted.
 * @param arraySize The size of the given array.
 *
 * @return The sorted array.
 */
static int* MergeSort(int array[], int arraySize) {
    // Prints out the initial array.
    PrintArray(array, arraySize);
    // Calculates the size of the left and right sub arrays.
    int rightArraySize = arraySize / 2;
    int leftArraySize = arraySize - rightArraySize;

    // If the right sub array has no elements, return the initial array.
    if (rightArraySize == 0) {
        return array;
    }

    // Creates the left and right sub arrays.
    int* leftArray = new int[leftArraySize];
    int* rightArray = new int[rightArraySize];

    // Copies the values from the initial array to the left sub array. 
    for (int i = 0; i < leftArraySize; i++) {
        leftArray[i] = array[i];
    }

    // Copies the values from the initial array to the right sub array. 
    for (int i = 0; i < rightArraySize; i++) {
        rightArray[i] = array[leftArraySize + i];
    }

    // Merges the result of the Merge Sort Algorithm on both the left and right sub arrays into the initial array. 
    Merge(array, MergeSort(rightArray, rightArraySize), rightArraySize, MergeSort(leftArray, leftArraySize), leftArraySize);

    // Deletes the left and right sub arrays.
    delete[] leftArray;
    delete[] rightArray;

    // Returns the final array.
    return array;
}

/**
 * @brief Splits a given string into substrings based on a specified delimiter.
 *
 * This static method takes a source string and a delimiter, and breaks the source
 * string into substrings wherever the delimiter occurs. The resulting substrings
 * are stored in a vector, which is then returned.
 *
 * @param str The source string to be split.
 * @param delimiter The string that acts as a delimiter for splitting the source string.
 *
 * @return A vector of strings containing the substrings obtained by splitting the source string.
 */
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

// --------------------------------------------------------------------------------------------------------- //
// Main Function                                                                                             //
// --------------------------------------------------------------------------------------------------------- //

/**
 * @brief Gets the user input and initiates the Merge Sort Algorithm.
 */
int main()
{
    // Gets the array the user wants to run the Merge Sort Algorithm on.
    std::cout << "Enter a integer array where each value is seperated by a comma ( Ex: [5,10,92] )" << std::endl;
    std::string inputtedNumbers;
    std::cin >> inputtedNumbers;
    // Splits up the inputted string of numbers.
    std::vector<std::string> splitNumbers = SplitString(inputtedNumbers, ",");
    int arraySize = splitNumbers.size();
    int* array = new int[arraySize];

    try {
        // Converts and copies the vector of strings into an integer array.
        for (int i = 0; i < arraySize; i++) {
            array[i] = std::stoi(splitNumbers[i]);
        }
    }
    catch (...) {
        // Catches any errors that occur while filling out the integer array. 
        std::cout << "\n[An Error Occured While Reading Inputted Numbers]";
        // Deletes the array.
        delete[] array;
        return 0;
    }

    std::cout << "\n------------------------Starting Merge Sorting------------------------" << std::endl << std::endl;
    // Runs the Merge Sort Algorithm.
    MergeSort(array, arraySize);
    std::cout << "\n-------------------------Ending Merge Sorting-------------------------" << std::endl;

    std::cout << "\nFinal Sorted Array," << std::endl;
    // Prints out the final sorted array.
    PrintArray(array, arraySize);

    // Deletes the array.
    delete[] array;
    // Plays the victory SFX.
    PlaySound(TEXT("Victory.wav"), NULL, SND_FILENAME | SND_SYNC);
    return 0;
}