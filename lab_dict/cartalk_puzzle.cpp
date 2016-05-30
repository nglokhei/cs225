/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    /* Your code goes here! */
    vector<StringTriple> retVal;  
    vector<string> checkedWords;

    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()){
	while(getline(wordsFile,word)){
	    // check previous words
	    if (word.length() == 5){
		string test1 = word.substr(1);
		string test2 = word.substr(0,1).append(word.substr(2));
		if (d.homophones(test1, word) && d.homophones(test1, test2) && d.homophones(test2, word))
		    retVal.push_back(make_tuple(word, test1, test2));
	    }
	}
    }		
    return retVal;
}
