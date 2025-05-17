# Plagiarism detector
A simple plagiarism detector written in C.


## Progress
- [x] Reading files
- [x] Normalizing text
- [x] Tokenizer
- [x] Stopword remover
- [ ] Word2Vec
- [ ] Cosine Similarity
- [ ] UI
- [ ] :tada:

## Details
This project uses [Bag of words](https://en.wikipedia.org/wiki/Content_similarity_detection#Bag_of_words) approach for content similarity detection. 

Content Similarity detection: https://en.wikipedia.org/wiki/Content_similarity_detection#Bag_of_words

Bag of words model: https://en.wikipedia.org/wiki/Bag-of-words_model

Pros: 
- Looks beyond just simple text comparison
- Much more efficient since we can use HashMap/Dictionary 

Cons: 
- Meaning is lost during compute. 
- Words can be replaced to circumnavigate