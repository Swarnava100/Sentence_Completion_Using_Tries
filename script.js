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

// Array to store the uploaded files
let uploadedFiles = [];

// Event listener for file input to handle multiple files
document.getElementById('fileInput').addEventListener('change', (event) => {
    const files = event.target.files; // Get all selected files
    const fileDropdown = document.getElementById('fileDropdown');

    if (files.length > 0) {
        // Add files to the uploaded files array
        uploadedFiles.push(...Array.from(files));

        // Reset dropdown and add default option
        fileDropdown.innerHTML = '<option>Select a file</option>'; 

        // Enable the dropdown
        fileDropdown.disabled = false;

        // Populate the dropdown with the names of all uploaded files
        uploadedFiles.forEach((file, index) => {
            const option = document.createElement('option');
            option.value = index;
            option.textContent = file.name;
            fileDropdown.appendChild(option);
        });

        // Read and insert sentences from each uploaded file
        Array.from(files).forEach(file => {
            const reader = new FileReader();
            reader.onload = function (e) {
                const sentences = splitText(e.target.result); // Split text into sentences
                sentences.forEach(sentence => {
                    if (sentence.trim()) {
                        trie.insert(sentence.trim()); // Insert sentences into trie
                    }
                });
            };
            reader.readAsText(file); // Read file as text
        });
    }
});

// Event listener for input change with time buffer for search
let timeoutId;
document.getElementById('prefixInput').addEventListener('input', () => {
    clearTimeout(timeoutId); // Clear previous timeout to prevent multiple triggers
    timeoutId = setTimeout(() => {
        const input = document.getElementById('prefixInput').value;
        const resultsDiv = document.getElementById('results');

        // Extract text after the last full stop
        const sentences = input.split('.');
        const lastSentence = sentences.pop().trim();

        if (lastSentence === '') {
            resultsDiv.innerHTML = '<h4>Suggestions</h4>'; // Clear results if no input but keep the heading
            return;
        }

        const results = trie.autocomplete(lastSentence);
        resultsDiv.innerHTML = '<h4>Suggestions</h4>' + (results.length
            ? results.map(res => `<div class="suggestion-item">${res}</div>`).join('')
            : '<div>No suggestions found.</div>');

        // Add click event listeners to suggestion elements
        const suggestions = resultsDiv.querySelectorAll('.suggestion-item');
        suggestions.forEach(suggestion => {
            suggestion.addEventListener('click', () => {
                // Replace the last part of the input with the selected suggestion
                const newInput = sentences.join('.').trim() + '. ' + suggestion.textContent;
                document.getElementById('prefixInput').value = newInput;
                resultsDiv.innerHTML = '<h4>Suggestions</h4>'; // Clear suggestions after selection
            });
            suggestion.style.cursor = 'pointer'; // Set cursor to pointer on hover
        });
    }, 1000);
});
