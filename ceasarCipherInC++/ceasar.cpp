#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <chrono>
#include <iomanip>
using namespace std;

// Function create a vector of words inside of the txt file
vector<string> loadDictionary(const string& dictionaryFileName) {
    ifstream inputFile(dictionaryFileName); // Replace "example.txt" with your file's name
    string line;
    vector<string> dictVector;
    while (getline(inputFile, line)) {
        if(line != "zyzzyvas"){
            dictVector.push_back(line.substr(0, line.length() - 1));
        }
        else{
            dictVector.push_back(line);
        }
    }
    inputFile.close();
    return dictVector;
}

vector<string> split(const string& line){
    vector<string> word_list;
    istringstream tokenStream(line);
    string token;
    while (getline(tokenStream, token, ' ')) {
        word_list.push_back(token);
    }
    return word_list;
}

// Function to lower case an entire string
string lowerCase(const string& word) {
    string new_word;
    for (int i = 0; i < word.length(); ++i) {
        new_word += tolower(word[i]);
    }
    return new_word;
}
// Function to encrypt a message using Caesar cipher
string encrypt(const string& message, int shift) {
    string encryptedMessage = "";
    for (int i = 0; i < message.length(); ++i) {
        char character = message[i];
        if (isalpha(character)) {
            char base = isupper(character) ? 'A' : 'a';
            encryptedMessage += static_cast<char>((character - base + shift) % 26 + base);
        } 
        else {
            encryptedMessage += character;
        }
    }
    return encryptedMessage;
}

// Function to decrypt a ceasar cipher message using a brute force approach
vector<string> decrypt(const string& decryptedMessage) {
    string decryption;
    int shift;
    vector<string> dictionary = loadDictionary("dictionary.txt");
    int max = 0;
    for(int i = 0; i < 50; i++){
        int count = 0;
        string text = encrypt(decryptedMessage, i - 25);
        string possibleDecryption = text;
        text = lowerCase(text);
        vector<string> wordVector = split(text);
        for (int j = 0; j < wordVector.size(); j++){
            for (int k = 0; k < dictionary.size(); k++){
                if (wordVector[j] == dictionary[k]){
                    count ++;
                }
            }
        }
        if (count > max){
            shift = 25-i;
            max = count;
            decryption = possibleDecryption;
        }
    }
    if (shift < 0){
        shift += 26;
    }
    vector<string> returnValues;
    returnValues.push_back(decryption);
    returnValues.push_back(to_string(shift));
    return returnValues;
}

int main() {
    int decision;
    string message;
    int shift;
    while(true){
        cout << "Enter 1 to encrypt and 2 to decrypt: ";
        cin >> decision;
        if(decision == 1 || decision == 2){
            break;
        }
        else {
            cout << "Invalid input. Please enter 1 or 2." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
        }
    cout << endl;
    }
    if (decision == 1){
        cout << "Enter the message to encrypt: ";
        cin.ignore();
        getline(cin, message);
        cout << endl;
        cout << "Enter the shift value: ";
        cin >> shift;
        cout << endl;
        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
        string encryptedMessage = encrypt(message, shift);
        chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "Encrypted message: " << encryptedMessage << endl;
        cout << "This took " << fixed << setprecision(4) << duration / 1000000.0 << " Seconds" << endl;
    }
    else{
        cout << "Enter the message to decrypt: ";
        cin.ignore();
        getline(cin, message);
        cout << endl;
        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
        vector<string> decryptedMessageAndShift = decrypt(message);
        chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "Decrypted message: " << decryptedMessageAndShift[0] << endl << "Shift: " << decryptedMessageAndShift[1] << endl;
        cout << "This took " << fixed << setprecision(4) << duration / 1000000.0 << " Seconds" << endl;
    }
    return 0;
}