# <centre>Plagiarism Detector</centre>

A straightforward plagiarism detector written in C, designed to identify content similarity efficiently. This tool uses text analysis to detect plagiarism.

![Plagiarism detector running](https://github.com/TasfiqulTapu/plagiarism/blob/master/builds/run.png?raw=true)

## How It Works
This project uses a Bag of Words (BoW) approach for [content similarity detection](https://en.wikipedia.org/wiki/Content_similarity_detection#Bag_of_words) .

### Bag of Words Model
The core idea is to treat each document as a "bag" of words, ignoring word order and grammar. The focus is on the frequency of words. For plagiarism detection, the [BoW model](https://en.wikipedia.org/wiki/Bag-of-words_model) helps identify common vocabulary between two documents.

### Processing Steps
The detector processes text through these stages:

Reading Files: The program reads the content of the text files provided for comparison.

Normalizing Text: Text is cleaned by converting all characters to lowercase and removing punctuation. This ensures words like "Word" and "word." are treated as the same.

Tokenizer: The cleaned text is broken down into individual words, or "tokens."

Stopword Remover: Common words like "the," "is," and "and" (stopwords) are removed because they don't significantly contribute to content meaning.

Cosine Similarity: Once words are vectorized, cosine similarity measures the angle between two vectors. A value closer to 1 means higher similarity, while a value closer to 0 indicates less similarity. This metric quantifies the degree of plagiarism.

Final detection: If cosine similarity exceeds a certain threshold, content is marked as plagiarised.

### Pros & Cons
Every tool has its advantages and limitations.

Pros:
    Semantic Understanding: The detector goes beyond simple string matching and looks at the content in its entirity.

    Efficiency: Using data structures like HashMaps/Dictionaries for word counting and vector storage makes the process efficient, even for large texts.

Cons:

    Contextual Limitation: The BoW model's nature means some nuances of sentence structure and precise word order can be lost.

    Potential Evasion: Very subtle rephrasing or clever word substitutions might still challenge detection if the semantic similarity isn't strong enough.

## Getting Started

To compile and run the plagiarism detector, follow these instructions:
### Using make
If you have make installed, run:
```bash
make
./plagiarism_detector <file1.txt> <file2.txt>
```
This compiles the source code and creates an executable named plagiarism_detector.

### Manual Compilation with gcc
Alternatively, you can compile main.c directly:
```bash
gcc main.c -o plagiarism_detector -lm
./plagiarism_detector <file1.txt> <file2.txt>
```
The -lm flag is needed to link the math library for functions used in cosine similarity calculations.