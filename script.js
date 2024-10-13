class TrieNode {
    constructor() {
        this.children = {};
        this.isEndOfWord = false;
        this.fullSentence = "";
    }
}

class Trie {
    constructor() {
        this.root = new TrieNode();
    }

    insert(sentence) {
        let node = this.root;
        for (const char of sentence) {
            if (char === ' ') continue;
            if (!node.children[char]) {
                node.children[char] = new TrieNode();
            }
            node = node.children[char];
        }
        node.isEndOfWord = true;
        node.fullSentence = sentence;
    }

    autocomplete(prefix) {
        let node = this.root;
        for (const char of prefix) {
            if (char === ' ') continue;
            if (!node.children[char]) {
                return []; // No suggestions
            }
            node = node.children[char];
        }
        return this.findWords(node);
    }

    findWords(node) {
        const results = [];
        if (node.isEndOfWord) {
            results.push(node.fullSentence);
        }
        for (const child in node.children) {
            results.push(...this.findWords(node.children[child]));
        }
        return results;
    }
}

let trie = new Trie();

document.getElementById('fileInput').addEventListener('change', (event) => {
    const file = event.target.files[0];
    if (file) {
        const reader = new FileReader();
        reader.onload = function(e) {
            const lines = e.target.result.split('\n');
            lines.forEach(line => {
                trie.insert(line.trim());
            });
        };
        reader.readAsText(file);
    }
});

document.getElementById('searchButton').addEventListener('click', () => {
    const prefix = document.getElementById('prefixInput').value;
    const results = trie.autocomplete(prefix);
    const resultsDiv = document.getElementById('results');
    resultsDiv.innerHTML = results.length ? results.map(res => `<div>${res}</div>`).join('') : '<div>No suggestions found.</div>';
});
