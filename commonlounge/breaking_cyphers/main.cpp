//
//  main.cpp
//  breaking_cyphers
//
//  Created by Jon Pring on 30/12/2020.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

string readText (string textFileName);
string removePunctuation(string text);
vector<string> readKeys(string keysFileName);
map<char, float> letterFreq (string letterFreqFileName);
string numToText(vector<int> textNum);
vector<int> textToNum(string text);
string solveText(string encryptedText, string keyText, int strLength);
map<char, int> countLetters(string text, int strLength);
float matchScore(string text, int strLength, map<char, float> letterFreq);
string solveRawText(string rawText, string decipheredText, int strLength);

void caesarCipher(string message, int shift);
void vigenereCipher(string textFileName, string keysFileName);

int main() {
    
    // ------ Question 1 - Caesar Cipher --------
    //caesarCipher("WROLYHLVWKHUDUHVWWKLQJLQWKHZRUOGPRVWSHRSOHMXVWHALVW", 3);
    
    // ------ Question 2 - Shift Cipher --------
    /*for (int i{0}; i<26; i++){
        caesarCipher("DCANIWDHTLWDPIITBEIIWTPQHJGSRPCPRWXTKTIWTXBEDHHXQAT", i);
    }*/
    
    // ------ Question 3 - Vigenère Cipher ------
    vigenereCipher("encrypted.txt", "keys.txt");
    
    return 0;
}

void caesarCipher(string message, int shift){
    for (int s{0}; s<message.length(); s++){
        message[s] = (message[s] - 13 - shift) % 26 + 65;
    }
    cout << message << " " << shift << endl;
}

void vigenereCipher(string textFileName, string keysFileName){
    string encryptedTextRaw {readText(textFileName)};
    string encryptedText {removePunctuation(encryptedTextRaw)};
    vector<string> keys{readKeys(keysFileName)};
    map<char, float> freqs{letterFreq("letterFreq.txt")};
    
    string decipheredText;
    int strLength {static_cast<int>(encryptedText.size())};
    float score;
    pair<string, float> bestScore {"", 9999999};
    
    for (auto key:keys){
        decipheredText = solveText(encryptedText, key, strLength);
        score          = matchScore(decipheredText, strLength, freqs);
        if (score < bestScore.second){
            bestScore.first = key;
            bestScore.second = score;
            cout << key << " " << score << endl;
        }
    }
    decipheredText = solveText(encryptedText, bestScore.first, strLength);
    score          = matchScore(decipheredText, strLength, freqs);
    cout << solveRawText(encryptedTextRaw, decipheredText, strLength);
}

string solveText(string encryptedText, string key, int strLength){
    vector<int> encryptedTextNum {textToNum(encryptedText)};
    vector<int> keyNum {textToNum(key)};
    vector<int> decipheredTextNum;
    for (int i{0}; i<strLength; i++){
        decipheredTextNum.push_back((26 + encryptedTextNum[i] - keyNum[i % key.length()]) % 26);
    }
    return numToText(decipheredTextNum);
};

string solveRawText(string rawText, string decipheredText, int strLength){
    int counter{0};
    for (int i{0}; i<rawText.length(); i++){
        if (isalpha(rawText[i])){
            rawText[i] = decipheredText[counter++];
        }
    }
    return rawText;
}

map<char, int> countLetters(string text, int strLength){
    map<char, int> letterCount;
    for (int i{0}; i<26; i++){letterCount[i + 65] = 0;}
    for (auto s:text){letterCount[s]++;}
    return letterCount;
}

float matchScore(string text, int strLength, map<char, float> letterFreq){
    map<char, int> letterCount{countLetters(text, strLength)};
    float score {0};
    for (int i{0}; i<26; i++){
        score += abs(letterCount[i+65] * 100 / strLength - letterFreq[i+65]);
    }
    
    return score;
}

map<char, float> letterFreq (string letterFreqFileName){
    ifstream ifs;
    map<char, float> freqs;
    char letter;
    float freq;
    ifs.open(letterFreqFileName);
    while (!ifs.eof()){
        ifs >> letter >> freq;
        freqs[letter] = freq;
    }
    ifs.close();
    return freqs;
}

vector<string> readKeys(string keysFileName){
    ifstream keysFile;
    vector<string> keys;
    string key;
    keysFile.open(keysFileName);
    if (!keysFile){
        cerr << "Uh oh! Keys file could not be opened." << endl;
    }
    while (keysFile){
        keysFile >> key;
        keys.push_back(key);
    }
    keysFile.close();
    return keys;
}

string readText (string textFileName){
    ifstream textFile;
    textFile.open(textFileName);
    string text((istreambuf_iterator<char>(textFile)), istreambuf_iterator<char>());
    textFile.close();
    return text;
}

string removePunctuation(string text){
    string tempstr {text};
    for (int i{0}; i<tempstr.size(); i++){
        if (ispunct(tempstr[i]) || isdigit(tempstr[i]) || tempstr[i] == '\n' || tempstr[i] == '\r'){
            tempstr[i] = ' ';
        }
        if (tempstr[i] == ' '){
            tempstr.erase(i--, 1);
        }
    }
    return tempstr;
}

vector<int> textToNum(string text){
    vector<int> result;
    for (int i{0}; i<text.size(); i++){
        result.push_back(static_cast<int>(text[i]) - 65);
    }
    return result;
}

string numToText(vector<int> textNum){
    string result;
    for (auto n:textNum){
        result += static_cast<char>(n + 65);
    }
    return result;
}
