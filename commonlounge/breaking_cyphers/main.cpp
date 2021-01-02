//  Cipher solver for Caesar Cipher, Shift Cipher and Vigenère Cipher

//  Input is restricted to all CAPS input file

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
#include <ctime>
#include <tuple>
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
double calcIC(string text, int strLength, map<char, float> letterFreq);
string solveRawText(string rawText, string decipheredText, int strLength);
bool sortbysec(const tuple<int,float,string> &a, const tuple<int,float,string> &b);
bool sortbysecstring(const pair<string,double> &a, const pair<string,double> &b);

string caesarCipher(string message, int shift);
void vigenereCipher(string textFileName, string keysFileName, string letterFreqFileName);
void vigenereCipherNoKeysBrute(string textFileName, string letterFreqFileName);
void vigenereCipherNoKeysEfficient(string textFileName, string letterFreqFileName);

int main() {
    
    // ------ Question 1 - Caesar Cipher --------
    //caesarCipher("WROLYHLVWKHUDUHVWWKLQJLQWKHZRUOGPRVWSHRSOHMXVWHALVW", 3);
    
    // ------ Question 2 - Shift Cipher --------
    /*for (int i{0}; i<26; i++){
        caesarCipher("DCANIWDHTLWDPIITBEIIWTPQHJGSRPCPRWXTKTIWTXBEDHHXQAT", i);
    }*/
    
    // ------ Question 3 - Vigenère Cipher ------ (using a list of keys)
    //vigenereCipher("encrypted.txt", "keys2.txt", "letterFreq.txt");
    
    // ------ Question 3a - Vigenère Cipher ----- (no keys, search by frequency analysis)
    //srand(static_cast<unsigned int>(time(0)));
    //vigenereCipherNoKeysBrute("encrypted.txt", "letterFreq.txt");
    
    // ------ Question 3b - Vigenère Cipher ----- (no keys, improved algorithm)
    vigenereCipherNoKeysEfficient("encrypted.txt", "letterFreq.txt");
    
    return 0;
}

string caesarCipher(string message, int shift){
    for (int s{0}; s<message.length(); s++){
        message[s] = (message[s] - 13 - shift) % 26 + 65;
    }
    return message;
}

void vigenereCipherNoKeysEfficient(string textFileName, string letterFreqFileName){
    string encryptedTextRaw {readText(textFileName)};
    string encryptedText {removePunctuation(encryptedTextRaw)};
    int strLen {static_cast<int>(encryptedText.length())};
    map<char, float> freqs{letterFreq(letterFreqFileName)};
    
    for (int keyLen {2}; keyLen<20; keyLen++){
        string key {""};
        string decipheredText;
        int reducedStrLen {0};
        
        for (int i{0}; i<keyLen; i++){
            // Generate reduced text for shift cipher at each key character
            string reducedEncryptedText {""};
            for (int c{0}; c<strLen; c++){
                if (c % keyLen == i){
                    reducedEncryptedText += encryptedText[c];
                }
            }
            reducedStrLen = static_cast<int>(reducedEncryptedText.length());
            // Check frequency at each shift
            double bestScore {999};
            char bestKey = '\0';
            for (int shift{0}; shift < 26; shift++){
                decipheredText = caesarCipher(reducedEncryptedText, shift);
                double score {matchScore(decipheredText, reducedStrLen, freqs)};
                if (score < bestScore){
                    bestScore = score;
                    bestKey = 65 + shift;
                }
            }
            key += bestKey;
        }
        // Check probability of identical adjacent characters (Friedman Test)
        double indexCoincidence {calcIC(decipheredText, reducedStrLen, freqs)};
        cout << keyLen << " " << key << " " << indexCoincidence << endl;
    }
    
}

void vigenereCipherNoKeysBrute(string textFileName, string letterFreqFileName){
    string encryptedTextRaw {readText(textFileName)};
    string encryptedText {removePunctuation(encryptedTextRaw)};
    map<char, float> freqs{letterFreq(letterFreqFileName)};
    
    string decipheredText;
    int strLength {static_cast<int>(encryptedText.size())};
    float score {0};
    vector<tuple<int, float, string>> keyLenScores {};
    int nRandKeys {50};
    int maxKeyLen {20};
    int nToAverage {5};
    string keys[nRandKeys];
    
    // Find best key lengths using frequency analysis of randomly generated keys
    for (int i{0}; i<maxKeyLen; i++){
        vector<pair<string, float>> scores;
        double bestAverageScore{0};
        for (auto key:keys){
            for (int c{0}; c<i+1; c++){
                key += static_cast<char>(65 + rand() % 26);
            }
            decipheredText = solveText(encryptedText, key, strLength);
            scores.push_back(make_pair(key, matchScore(decipheredText, strLength, freqs)));
        }
        sort(scores.begin(), scores.end(), sortbysecstring);
        for (int i{0}; i<nToAverage; i++){bestAverageScore += scores[i].second;}
        keyLenScores.push_back(make_tuple(i+1, bestAverageScore / nToAverage, scores[0].first));
        cout << get<2>(keyLenScores[i]) << " " << get<0>(keyLenScores[i]) << " " << get<1>(keyLenScores[i]) << endl;
        score = 0;
    }
    sort(keyLenScores.begin() + 3, keyLenScores.end(), sortbysec);
    for (int i{0}; i<5; i++){
        cout << get<0>(keyLenScores[i]) << " " << get<1>(keyLenScores[i]) << endl;
    }
    
    // Try changing one letter at a time from the best key
    string bestKey {get<2>(keyLenScores[3])};
    double bestScore {get<1>(keyLenScores[3])};
    int counter{0};
    while (true){
        double newBestScore {bestScore};
        for (int i{0}; i<bestKey.length(); i++){
            string tempkey {bestKey};
            for (char c{'A'}; c <= 'Z'; c++){
                if (counter > 1 && i < bestKey.length() - 1){
                    for (int j{i+1}; j<bestKey.length(); j++){
                        tempkey = bestKey;
                        tempkey[i] = c;
                        for (char d{'A'}; d <= 'Z'; d++){
                            tempkey[j] = d;
                            decipheredText = solveText(encryptedText, tempkey, strLength);
                            score = matchScore(decipheredText, strLength, freqs);
                            if (score < newBestScore){
                                newBestScore = score;
                                bestKey[i] = tempkey[i];
                                bestKey[j] = tempkey[j];
                            }
                            cout << tempkey << " " << score << c << d << endl;
                        }
                    }
                }
                else {
                    tempkey[i] = c;
                    decipheredText = solveText(encryptedText, tempkey, strLength);
                    score = matchScore(decipheredText, strLength, freqs);
                    if (score < newBestScore){
                        newBestScore = score;
                        bestKey[i] = tempkey[i];
                    }
                }
                cout << tempkey << " " << score << endl;
            }
            cout << bestKey << " " << newBestScore << endl;
        }
        if (newBestScore < bestScore){
            cout << "Improved" << endl;
            bestScore = newBestScore;
            counter = 0;
        }
        else if (bestKey.length() < maxKeyLen / 2){
            bestKey += bestKey;
            counter = 0;
        }
        else if (counter < 2){
            cout << "Not improved" << endl;
            counter++;
        }
        else {
            break;
        }
    }
    cout << "decipher complete" << endl;
}

void vigenereCipher(string textFileName, string keysFileName, string letterFreqFileName){
    string encryptedTextRaw {readText(textFileName)};
    string encryptedText {removePunctuation(encryptedTextRaw)};
    vector<string> keys{readKeys(keysFileName)};
    map<char, float> freqs{letterFreq(letterFreqFileName)};
    
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

bool sortbysecstring(const pair<string,double> &a, const pair<string,double> &b){
    return (a.second < b.second);
}

bool sortbysec(const tuple<int,float,string> &a, const tuple<int,float,string> &b){
    return (get<1>(a) < get<1>(b));
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

double calcIC(string text, int strLength, map<char, float> letterFreq){
    double count{0};
    for (int i{0}; i<strLength-1; i++){
        if (text[i+1] == text[i]){count++;}
    }
    return count / strLength;
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
