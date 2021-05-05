#include <iostream>
#include <string>

using namespace std;

#define alphaSize 26

struct trie {

    struct trie* next[alphaSize]; //for each letter we can go to each letter of the alphabet
                                  //this way next[0] = 'a' next[1] = 'b' and so on
    bool eow;   // eow = end of word

};

typedef struct trie* Trie_t;

Trie_t newNode() {

    Trie_t add = new trie;  //memory allocation

    for (int i = 0; i < alphaSize; i++) 
        add -> next[i] = NULL;  //we set the next letters to be null
    
    add -> eow = false; //we set the end of the word to be false

    return add;
}

void add (Trie_t root, string word) {

    Trie_t newWord = root;

    for (size_t i = 0; i < word.length(); i++) {
        
        int j = word[i] - 'a'; //since we deal with the alphabet, 'a' - 'a' = 0, 'b' - 'a' = 1 and so on

        if (newWord -> next[j] == NULL) // if there doesn't exist a key
            newWord -> next[j] = newNode(); // add a key

        newWord = newWord -> next[j]; //we go to the next letter we just added

    }
    
    newWord -> eow = true;  //after we added word.length letters we mark the end of the world as true
}

void printAllWords (Trie_t root, string word) {

    if (root -> eow)
        cout << word << endl;   // if we found an end of word we print it
    
    for (int i = 0; i < alphaSize; i++) 
        if (root -> next[i]) {  //if there is a path from the current letter we follow it

            word += (i + 'a');  //we add the letter we found to a string
            printAllWords(root -> next[i], word);   //recursivly we go from the letter we found to all the other letters available
            word.pop_back();    //we delete the letter and go back
        
        }
}

int main () {

    Trie_t root = newNode();

    string words[] = {"bitcoin", "internat", "insigna", "pisicute", "intern", "zoo", "ornitorinc", "zinc", "ornament", "ata", "fazan", "faza", "catelus", "dragut", "pisici", "mici", "incrementare"};
    int n = 17;

    for (int i = 0; i < n; i++)
        add(root, words[i]);
    
    printAllWords(root, "");

    return 0;
}