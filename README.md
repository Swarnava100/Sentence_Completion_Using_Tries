# Sentence Completion DSA Project

## Overview
This project implements an autocomplete and sentence completion system using a Trie data structure. It provides suggestions based on user input, improving typing efficiency and user experience. The backend is implemented in C++, while the frontend uses HTML, CSS, and JavaScript.

## Features
- Efficient word and sentence storage using a Trie.
- Fast retrieval of autocomplete suggestions.
- Handles case insensitivity and special characters.
- Allows users to upload custom text files for dynamic word addition.
- Interactive frontend with real-time suggestions.

## Technologies Used
- **C++ (Backend)**: Implements the Trie data structure for sentence storage and retrieval.
- **JavaScript (Frontend Logic)**: Manages user input, Trie insertion, and search operations.
- **HTML & CSS (User Interface)**: Provides a structured and styled interface.
- **Bootstrap**: Enhances UI styling and responsiveness.

## Project Structure
```
Sentence_Completion_DSA_Project/
│-- Dd.cpp         # C++ implementation of Trie-based sentence completion
│-- Dd.exe         # Compiled executable of the C++ program
│-- index.html     # Web interface for user input and displaying suggestions
│-- script.js      # JavaScript logic for handling autocomplete
│-- style.css      # Styles for the web interface
│-- README.md      # Project documentation
│-- test.cpp       # Additional test cases and implementation
│-- wikipedia.txt  # Sample text file for sentence storage (not included in upload)
```

## How It Works
### Backend (C++ Implementation)
1. **Trie Data Structure**:  
   - Stores words and sentences efficiently.  
   - Each node contains child references and a flag indicating the end of a sentence.  
2. **Sentence Insertion**:  
   - Sentences are read from a file (e.g., `wikipedia.txt`) and inserted into the Trie.  
3. **Autocomplete Search**:  
   - User input is processed to find matching prefixes in the Trie.  
   - If matches are found, corresponding sentences are returned.  

### Frontend (HTML, CSS, JavaScript)
1. **User Input Handling**:  
   - The user enters a prefix in a text box.  
   - JavaScript processes the input and interacts with the Trie.  
2. **Dynamic Sentence Storage**:  
   - Users can upload `.txt` files to add more sentences dynamically.  
3. **Displaying Suggestions**:  
   - Matching sentences are displayed in real-time.  

## Installation & Usage
### Running the C++ Backend
1. Compile the C++ program:
   ```sh
   g++ -o autocomplete Dd.cpp
   ```
2. Run the executable:
   ```sh
   ./autocomplete
   ```
3. Enter a prefix to get suggestions.

### Running the Web Interface
1. Open `index.html` in a web browser.
2. Type a prefix in the input box.
3. View autocomplete suggestions dynamically.

## Future Improvements
- Implement machine learning for more intelligent suggestions.
- Add a database to store frequently used words dynamically.
- Optimize Trie storage using compression techniques.

## Group Members
- Abhishek Garg
- Tanisha Sonkar
- Swarnava Mandal

## Project Type
This is a DSA group project.
