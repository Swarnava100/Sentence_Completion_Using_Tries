#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>  

struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    std::vector<std::string> sentences;  
    bool isEndOfWord;  

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        deleteNode(root);
    }

    // Insert a sentence into the Trie
    void insert(const std::string& sentence) {
        TrieNode* node = root;
        for (char ch : sentence) {
            if (!node->children.count(ch)) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true;
        node->sentences.push_back(sentence);  
    }

    std::vector<std::string> search(const std::string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (!node->children.count(ch)) {
                return {};  // If prefix is not found, return empty
            }
            node = node->children[ch];
        }
        // At the node corresponding to the last character of prefix, return stored sentences
        return collectSentences(node);
    }

private:
    std::vector<std::string> collectSentences(TrieNode* node) {
        std::vector<std::string> result;

        if (node->isEndOfWord) {
            result.insert(result.end(), node->sentences.begin(), node->sentences.end());
        }

        for (auto& [key, child] : node->children) {
            std::vector<std::string> childSentences = collectSentences(child);
            result.insert(result.end(), childSentences.begin(), childSentences.end());
        }

        return result;
    }

    void deleteNode(TrieNode* node) {
        for (auto& [key, child] : node->children) {
            deleteNode(child);
        }
        delete node;
    }
};

std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::vector<std::string> loadFile(const std::string& filename) {
    std::vector<std::string> sentences;
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return sentences;
    }

    std::string line;
    while (getline(file, line)) {
        if (!line.empty()) {  // Ensure that empty lines are ignored
            sentences.push_back(toLower(line));  // Store sentences in lowercase
        }
    }

    file.close();
    return sentences;
}

int main() {
    Trie trie;

    std::vector<std::string> sentences = loadFile("wikipedia.txt");
    for (const std::string& sentence : sentences) {
        trie.insert(sentence);
    }

    std::string input;
    std::cout << "Enter a word or prefix: ";
    std::getline(std::cin, input);

    input = toLower(input);

    if (input.length() < 2) {
        std::cout << "Please enter at least 2 characters for the prefix." << std::endl;
    } else {
        std::vector<std::string> results = trie.search(input);
        if (results.empty()) {
            std::cout << "No matching sentences found." << std::endl;
        } else {
            std::cout << "Matching sentences:\n";
            for (const auto& sentence : results) {
                std::cout << sentence << std::endl;
            }
        }
    }

    return 0;
}
