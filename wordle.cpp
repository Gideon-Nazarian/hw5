// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <string>
#include <vector>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void wordGen(std::string in, std::string floating, const std::set<std::string>& dict, std::set<std::string>& solutions);

std::vector<int> Loc( char c, std::string& in); // used to find loc of char in string


//helper 
std::vector<int> Loc(char c, std::string& in)
{
    std::vector<int> cLocs; 
    for(int i = 0; i < (int)in.size(); ++i){
        if (in[i] == c){
            cLocs.push_back(i);
        }
    }
    return cLocs;
}


//helper
void wordGen(std::string in, std::string floating, const std::set<std::string>& dict, std::set<std::string>& solutions)
{
    if(in.find('-') == std::string::npos){ // checks if word has no remaining -'s
        if (dict.find(in) != dict.end()){ // if word is in dictionary
            solutions.insert(in);   // insert it 
        }
    }

   // must start generating, but start by ising yellow chars as they must appear in the word
    
    else if (!(floating.size() == 0)) // checks if more yellow chars are needed to use
    {
        std::vector<int> locs = Loc('-', in); // holds all of the locations of -'s in the remaining word
        
        std::vector<int>::iterator it; // 

        for (it = locs.begin(); it != locs.end(); ++it) //itterates through respective Loc and start to try letters
        {
            std::string tempWord = in; // tempWord to hold input 
            tempWord[*it] = floating[0]; // utilize the yellow char

            wordGen(tempWord, floating.substr(1,std::string::npos), dict, solutions); // call w/ yellow char used so yelow char list is smaller
        }
    }
    else
    {
        int place = (int)in.find("-"); 

        for(int i = 97; i <= 122; ++i){ // generate alphebet letters and start filling in slots
            
            std::string tempWord2 = in; //similar to tempWord
            tempWord2[place] = (char)i; // use yellow chars
      
            wordGen(tempWord2, floating, dict, solutions); // call w/ added letter
        }
    }
}

//Base Wordle

std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{

    std::set<std::string> solutions;
    wordGen(in, floating, dict, solutions);
    return solutions;

}
