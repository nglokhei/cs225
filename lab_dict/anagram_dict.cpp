/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordFile(filename);
    string word;
    if (wordFile.is_open()){
	while(getline(wordFile, word)){
	    std::vector<char> chs;
    	    for (size_t i = 0; i < word.length(); i++)
		chs.push_back(word.at(i));
    	    std::sort(chs.begin(), chs.end());
	    dict[word] = chs;
	}
    }	      
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (auto & word : words){
	auto lookup = dict.find(word);
	if (lookup == dict.end()){
	    std::vector<char> chs;
    	    for (size_t i = 0; i < word.length(); i++)
		chs.push_back(word.at(i));
    	    std::sort(chs.begin(),chs.end());
	    dict[word] = chs;
	}
    }	    
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    vector<string> v;
    v.clear();

    std::vector<char> chs;
    for (size_t i = 0; i < word.length(); i++)
	chs.push_back(word.at(i));
    std::sort(chs.begin(),chs.end());

    for (auto & wordPair : dict){
	if (wordPair.second == chs){
	    v.push_back(wordPair.first);
	}
    }

    if (v.size() < 2)
	v.clear();
    return v;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> v;
    for (auto & wordPair : dict){
	string word= wordPair.first;

	// check if it is processed
	bool repeated = false;
	for (auto & words : v){
	    for (auto & tmpWord : words){
		if (word == tmpWord)
		    repeated = true;
	    }
	}

	//if not processed, find its anagrams
	if (!repeated){
	    vector<string> anagrams = get_anagrams(wordPair.first);
	    if (!anagrams.empty())
	        v.push_back(anagrams);
	}
    }

    return v;
}
    
