#include <bits/stdc++.h>
using namespace std;

ifstream documentFile, stopWordFile;
ofstream indexFile;

map<string, pair<int, vector<int>>> index;
set<string> stopWord;

//add word to index file
void addWordToIndex(string word, int line) {
    auto it = index.find(word);
    //if not found word in index then add new word
    if (it == index.end()) {
        vector<int> lineList(0);
        lineList.push_back(line);
        index.insert(make_pair(word, make_pair(1, lineList)));
    } else {
        it->second.first += 1;
        int lastLine = it->second.second.back();
        if (line != lastLine) it->second.second.push_back(line);
    }
}

//read stop word from file
void readStopWord() {
    string word;
    while (stopWordFile >> word)
        stopWord.insert(word);
}

//check a word is stop word or not
bool checkStopWord(string word) {
    return stopWord.find(word) != stopWord.end();
}

//check a word is special name or not using first character
bool checkSpecialName(string word) {
    char firstCharacter = word[0];
    return (firstCharacter >= 'A' && firstCharacter <= 'Z');
}

int main() {
    //open input file
    documentFile.open("vanban.txt");
    stopWordFile.open("stopw.txt");
    indexFile.open("index.txt");

    readStopWord();

    //read char to get word from text file
    int currentLine = 1;
    char currentChar;
    string currentWord = "";
    bool endOfSentence = true;
    while (documentFile.get(currentChar)) {
        //if not an alphabet character, mean that end of word
        if (!isalpha(currentChar)) {
            //if end of a sentence
            if (currentChar == '.') endOfSentence = true;
            //if this word is not a special name or stop word, then add it to index
            if (!checkSpecialName(currentWord) && !checkStopWord(currentWord) && (currentWord != "")) addWordToIndex(currentWord, currentLine);
            //if to new line
            if (currentChar == '\n') ++currentLine;
            currentWord = "";
            continue;
        }
        //if this char is the first char of the word after a . mark, then lowercase it
        if (endOfSentence) {
            if(currentChar >= 'A' && currentChar <='Z') currentChar -= ('A' - 'a');
            endOfSentence = false;
        }
        //append this char to get the word
        currentWord += currentChar;
    }

    //print index from data structure to local file
    for (auto & it : index) {
        indexFile << it.first << " " << it.second.first << " ";
        vector<int> lineList = it.second.second;
        for (int & it2 : lineList)
            indexFile << it2 << " ";
        indexFile << "\n";
    }

    //close file
    documentFile.close();
    stopWordFile.close();
    indexFile.close();
    return 0;
}
