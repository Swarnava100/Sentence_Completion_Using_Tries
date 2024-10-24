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
        return this.findWords(node).slice(0, 5); // Return first 5 suggestions
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

// Function to split text based on various punctuation marks and line breaks
function splitText(text) {
    return text.match(/[^.!?]*[.!?]/g) || [];
}

// Event listener for file input
document.getElementById('fileInput').addEventListener('change', (event) => {
    const file = event.target.files[0];
    if (file) {
        const reader = new FileReader();
        reader.onload = function (e) {
            const sentences = splitText(e.target.result); // Split text into sentences
            sentences.forEach(sentence => {
                if (sentence.trim()) {
                    trie.insert(sentence.trim());
                }
            });
        };
        reader.readAsText(file);
    }
});

// Prefix input with 1-second buffer for search
let timeoutId;
document.getElementById('prefixInput').addEventListener('input', () => {
    clearTimeout(timeoutId); // Clear previous timeout to prevent multiple triggers
    timeoutId = setTimeout(() => {
        const prefix = document.getElementById('prefixInput').value;
        const resultsDiv = document.getElementById('results');
        resultsDiv.innerHTML = ''; // Clear previous results

        if (prefix === '') {
            return; // Do nothing if the input is empty
        }

        const results = trie.autocomplete(prefix);
        if (results.length) {
            results.forEach(result => {
                const suggestionDiv = document.createElement('div');
                suggestionDiv.classList.add('suggestion-item');
                suggestionDiv.textContent = result;

                // Add copy button (small, fixed size)
                const copyButton = document.createElement('button');
                copyButton.textContent = 'Copy';
                copyButton.classList.add('copy-btn');
                copyButton.style.marginLeft = '10px';
                copyButton.style.fontSize = '12px';
                copyButton.style.padding = '4px 8px';
                copyButton.style.borderRadius = '5px';
                copyButton.style.cursor = 'pointer';

                suggestionDiv.appendChild(copyButton);

                // Add event listener to copy the suggestion to clipboard
                copyButton.addEventListener('click', (e) => {
                    e.stopPropagation();
                    navigator.clipboard.writeText(result);
                    copyButton.textContent = 'Copied!'; // Change button text after copying
                    setTimeout(() => {
                        copyButton.textContent = 'Copy'; // Revert button text after a short delay
                    }, 2000);
                });

                // Add event listener for suggestion selection
                suggestionDiv.addEventListener('click', () => {
                    document.getElementById('prefixInput').value = result;
                    resultsDiv.innerHTML = ''; // Clear suggestions after selection
                });

                resultsDiv.appendChild(suggestionDiv);
            });
        } else {
            resultsDiv.innerHTML = '<div>No suggestions found.</div>';
        }
    }, 1000); // Buffer time: 1 seconds
});
