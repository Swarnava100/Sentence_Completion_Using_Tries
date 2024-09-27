#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <queue>

using namespace std;

// Node structure for the Trie
struct TrieNode {
    unordered_map<string, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

// Trie class
class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    // Function to insert a sentence (split by words) into the Trie
    void insert(const string& sentence) {
        vector<string> words = splitSentence(sentence);
        TrieNode* node = root;

        for (const string& word : words) {
            if (node->children.find(word) == node->children.end()) {
                node->children[word] = new TrieNode();
            }
            node = node->children[word];
        }
        node->isEndOfWord = true;
    }

    // Function to search for a word in the Trie
    TrieNode* search(const string& word) {
        TrieNode* node = root;
        vector<string> words = splitSentence(word);

        for (const string& w : words) {
            if (node->children.find(w) == node->children.end()) {
                return nullptr; // Word not found
            }
            node = node->children[w];
        }
        return node; // Return the node where the word ends
    }

    // Level-order (BFS) print function for the Trie
    void printTrieLevelOrder(TrieNode* node, const string& prefix) {
        if (!node) return;

        queue<pair<TrieNode*, string>> q;
        q.push({node, prefix});

        while (!q.empty()) {
            auto current = q.front();
            TrieNode* currNode = current.first;
            string currentPrefix = current.second;
            q.pop();

            for (const auto& child : currNode->children) {
                string word = currentPrefix + (currentPrefix.empty() ? "" : " ") + child.first;
                cout << word << endl;
                q.push({child.second, word});
            }
        }
    }

private:
    // Helper function to split a sentence into words
    vector<string> splitSentence(const string& sentence) {
        vector<string> words;
        stringstream ss(sentence);
        string word;

        while (ss >> word) {
            words.push_back(word);
        }
        return words;
    }
};

int main() {
    Trie trie;
    string input;

    cout << "Enter strings to insert into the trie (type 'exit' to finish):" << std::endl;
    while (true) {
        getline(cin, input);
        if (input == "exit") {
            break;
        }
        trie.insert(input);
    }
    /*trie.insert("my name is tanisha");
    trie.insert("my name is mahi");
    trie.insert("my pet is a cat");
    trie.insert("my pet is nice");
    trie.insert("cats are fun");
    trie.insert("cats and dogs are animals");
    trie.insert("this is a trial test");*/

    string inputWord;
    cout << "Enter a word to search for its subtree: ";
    getline(cin, inputWord);

    TrieNode* searchNode = trie.search(inputWord);
    if (searchNode) {
        cout << "Subtree for the word '" << inputWord << "':" << endl;
        trie.printTrieLevelOrder(searchNode, inputWord);
    } else {
        cout << "Word '" << inputWord << "' not found" << endl;
    }

    return 0;
}
