#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class TrieNode {
public:
    TrieNode* children[26]; // Array for 26 lowercase letters
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr; // Initialize all children to nullptr
        }
    }
};

class Trie {
private:
    TrieNode* root;

    int charToIndex(char c) {
        return c - 'a'; // Convert character to array index (assuming lowercase letters)
    }

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a sentence into the trie
    void insert(const string& sentence) {
        TrieNode* node = root;
        for (char c : sentence) {
            if (c == ' ') continue; // Ignore spaces for indexing
            int index = charToIndex(c);
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true; // Mark the end of a word
    }

    // Recursive function to find words
    void findWords(TrieNode* node, const string& prefix, vector<string>& suggestions, const string& originalPrefix) {
        if (node->isEndOfWord) {
            suggestions.push_back(originalPrefix); // Use the original prefix to maintain correct format
        }
        for (int i = 0; i < 26; ++i) {
            if (node->children[i] != nullptr) {
                findWords(node->children[i], prefix + char(i + 'a'), suggestions, originalPrefix + char(i + 'a'));
            }
        }
    }

    vector<string> autocomplete(const string& prefix) {
        TrieNode* node = root;
        vector<string> suggestions;
        string cleanedPrefix;

        // Clean the prefix to ignore spaces
        for (char c : prefix) {
            if (c != ' ') {
                cleanedPrefix += c;
            }
        }

        for (char c : cleanedPrefix) {
            int index = charToIndex(c);
            if (node->children[index] == nullptr) {
                return suggestions; // No suggestions
            }
            node = node->children[index];
        }
        findWords(node, "", suggestions, cleanedPrefix); // Start with the cleaned prefix
        return suggestions;
    }
};

int main() {
    Trie trie; // Instantiate the Trie

    // Read sentences from a file
    ifstream file("sentences.txt");
    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        trie.insert(line); // Use the trie object to insert sentences
    }
    file.close();

    // Search for prefixes and get completions
    string input;
    while (true) {
        cout << "\nEnter a prefix to autocomplete (or type 'exit' to quit): ";
        getline(cin, input);

        if (input == "exit") {
            break; // Exit the loop if the user types 'exit'
        }

        auto results = trie.autocomplete(input);
        cout << "Autocomplete suggestions for '" << input << "':\n";
        if (results.empty()) {
            cout << " - No suggestions found.\n";
        } else {
            for (const string& suggestion : results) {
                cout << " - " << suggestion << "\n";
            }
        }
    }

    return 0;
}
