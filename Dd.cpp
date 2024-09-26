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

    TrieNode() {
        isEndOfWord = false;
    }
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

    // Level-order (BFS) print function for the Trie
    void printTrieLevelOrder() {
        if (!root) return;

        queue<pair<TrieNode*, string>> q;
        q.push({root, ""});

        while (!q.empty()) {
            auto current = q.front();
            TrieNode* node = current.first;
            string prefix = current.second;
            q.pop();

            for (const auto& child : node->children) {
                string word = prefix + (prefix.empty() ? "" : " ") + child.first;
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
    trie.insert("this is a test");
    trie.insert("this is another test");
    trie.insert("trie stores words");

    cout << "Printing Trie structure (Level Order):" << endl;
    trie.printTrieLevelOrder();

    return 0;
}

