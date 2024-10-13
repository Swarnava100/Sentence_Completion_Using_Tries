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
            if (char === ' ') continue; // Ignore spaces
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
            if (char === ' ') continue; // Ignore spaces
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

// Event listener for file input
document.getElementById('fileInput').addEventListener('change', (event) => {
    const file = event.target.files[0];
    if (file) {
        const reader = new FileReader();
        reader.onload = function(e) {
            const lines = e.target.result.split('\n');
            lines.forEach(line => {
                if (line.trim()) { // Only insert non-empty lines
                    trie.insert(line.trim());
                }
            });
        };
        reader.readAsText(file);
    }
});

// Event listener for input change to provide instant suggestions
document.getElementById('prefixInput').addEventListener('input', () => {
    const prefix = document.getElementById('prefixInput').value;
    const resultsDiv = document.getElementById('results');

    if (prefix === '') {
        resultsDiv.innerHTML = ''; // Clear results if no input
        return;
    }

    const results = trie.autocomplete(prefix);
    resultsDiv.innerHTML = results.length
        ? results.map(res => `<div class="suggestion">${res}</div>`).join('')
        : '<div>No suggestions found.</div>';

    // Add click event listeners to suggestion elements
    const suggestions = resultsDiv.querySelectorAll('.suggestion');
    suggestions.forEach(suggestion => {
        suggestion.addEventListener('click', () => {
            document.getElementById('prefixInput').value = suggestion.textContent; // Populate the input with the clicked suggestion
            resultsDiv.innerHTML = ''; // Clear suggestions after selection
        });
    });
});
