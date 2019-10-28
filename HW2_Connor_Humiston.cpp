// Connor Humiston
// Christopher Godley 310
// Data Structures 
// Homework 2

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <iomanip>
#include <cmath>
using namespace std;

int arraySize;

struct wordItem 
{
    string word;
    int count; 
};

// Purpose: read stop word list from file and store into an array
// @param ignoreWordFile — filename (the file storing ignore words)
// @param ignoreWords — store ignore words from the file (pass by reference) 
// @return — none
// Note: The number of words is fixed to 50
void getStopWords(string ignoreWordFileName, string ignoreWords[])
{
    //Reading the File:
    ifstream in(ignoreWordFileName);
    if (!in)
    {
        cout << "File can't be opened! " << endl;
        exit(1);
    }

    string currentWord;
    for(int i = 0; i < 50; i++)
    {
        in >> currentWord;
        ignoreWords[i] = currentWord;
    }
}

// Purpose: to see if a word is a stop word (ignore word)
// @param word — a word (which you want to check if it is a stop word)
// @param ignoreWords — the array of strings storing ignore/stop words
// @return — true (if word is a stop word), or false (otherwise) 
bool isStopWord(string word, string ignoreWords[])
{
    for(int i = 0; i < 50; i++)
    {
        if(word.compare(ignoreWords[i]) == 0) //if the word is in array, true is returned
            return true;
    }
    return false;
}

// Purpose: sort an array of wordItems, increasing, by their count fields
// @param list — an array of wordItems to be sorted
// @param length — the length of the words array
void arraySort(wordItem list[], int length)
{
    //using a bubble sort
    for(int i = 0; i < length-1; i++)
    {
        for(int j = 0; j < length-i-1; j++)
        {
            if((list[j].count > list[j+1].count) && (list[j].count != 0)) //if element greater than next & it is not zero (prefilled in double array)
            {
                wordItem swap = list[j];
                list[j] = list[j+1];
                list[j+1] = swap;
            }
        }
    }
}

// Purpose: compute the total number of words saved in the words array
// (including repeated words)
// @param list — an array of wordItems containing non—stopwords
// @param length — the length of the words array
// @return — the total number of words in the words array (including
// repeated words multiple times)
int getTotalNumberNonStopWords(wordItem list[], int length)
{
    int counter = 0;
    for(int i = 0; i < length; i++)
    {
        counter = counter + list[i].count;
    }
    return counter-1; //1 was subtracted here because 
}

// Purpose: to print the top N high frequency words
// @param list — a pointer to a *sorted* array of wordItems
// @param topN — the number of top frequency words to print
// @param totalWordCount — total number of words (used for percent)
// @param wordsInArray - the number of unique words in the array
// @return none
void printTopN(wordItem list[], int topN, int totalWordCount)
{
    if(topN > totalWordCount)
    {
        cout << "ERROR: the number of top-frequency words to print is greater than the number of words in the file!";
    }
    else
    {
        for(int i = arraySize-1; i >= (arraySize - topN); i--)
        {
            double percent = ((100*list[i].count)/(double)totalWordCount);
            cout << list[i].count << " - " << setprecision(2) << fixed << percent << "% - " << list[i].word << endl;
        }
    }
}


int main(int argc, char* argv[])
{
    //Reading file name from the terminal command line
    string nString = argv[1]; //the top n uncommon words to be displayed
    int n = stoi(nString);
    string fileName = argv[2];
    string ignoreWordFileName = argv[3];

    //Reading the File (Tom Sawyer):
    ifstream in(fileName);
    if (!in)
    {
    	cout << "File can't be opened! " << endl;
    	exit(1);
    }

    cout << "One moment please, " << fileName << " is being analyzed." << endl;

    //Fills the ignoreWords array with the ignore words from file
    string ignoreWords[50];
    getStopWords(ignoreWordFileName, ignoreWords);

    //The dynamic array of wordItem structs
    arraySize = 10;
    wordItem* words = new wordItem[arraySize];
    //initializing the counts to 0 for best practices
    for(int i = 0; i < arraySize; i++)
    {
        words[i].count = 0;
    }
    
    int uniqueWordCount = 0;    //this is the number of different words in the array (obvi excluding ignore words)
    int totalWordCount = 0;     //the total number of words in the file
    string currentWord;         //the word being read from the file
    int numDoublings = 0;       //how many times the array was doubled

    //The algorithm/filing the array
    while (!in.eof()) //while not at the end of file marker (this counts the last word twice and is dealt with l8r)
    {
        in >> currentWord;
        totalWordCount++;

        if(!isStopWord(currentWord, ignoreWords))
        {
            //array doubling
            if(uniqueWordCount >= arraySize)
            {
                wordItem *temp = new wordItem[arraySize*2]; //creating new bigger array on the heap w/ 2x size
                for(int i = 0; i < arraySize; i++)
                {
                    temp[i] = words[i];                     //copy values to new array up until current size
                }
                for(int j = arraySize; j < arraySize*2; j++) 
                {
                    temp[j].count = 0;                      //filling the rest of the array with zeros
                }
                words = temp;
                arraySize = arraySize * 2;
                delete [] temp;                             //freeing memory
                numDoublings++;
                //cout << "The array was just doubled and now has size " << arraySize << endl;

            }

            //We have two cases for the current word being read:
            for(int i = 0; i < arraySize; i++)
            {
                //The current word is a repeat (already in the array)
                if(currentWord.compare(words[i].word) == 0)
                {
                    words[i].count++;                       //increment the count of that word in the struct array
                    //totalWordCount++;
                    break;
                }
                //the current word is new (not already in array) and the preset empty section has been reached
                else if(words[i].count == 0)
                {
                    words[i].word = currentWord;            //add the word to the open spot
                    words[i].count = words[i].count + 1;    //add to count
                    //totalWordCount++;
                    uniqueWordCount++;
                    break;
                }
            }
        }
    }

    arraySort(words, arraySize);

    //Printing
    cout << "Here are the results for " << fileName << "\'s most common words:" << endl;
    int uncommonWordCount = getTotalNumberNonStopWords(words, arraySize);
    printTopN(words, n, totalWordCount);
    cout << "#" << endl;
    cout << "Array doublings: " << numDoublings << endl;
    cout << "#" << endl;
    cout << "Unique uncommon words in " << fileName << ": " << uniqueWordCount-1 << endl; //one less than unique word count because .eof loops an extra time
    cout << "#" << endl;
    cout << "Total uncommon words in " << fileName << ": " << uncommonWordCount << endl;

    //cout << totalWordCount;
}
