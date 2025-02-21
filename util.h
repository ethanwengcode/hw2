#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> result;
    
    const std::set<T> *smaller; //declaring a pointer to the smaller set 
    const std::set<T> *larger; //declarin a pointer to the larger set

    if (s1.size() < s2.size()) {
        smaller = &s1; //if s1 is smaller, point smaller to s1
        larger = &s2; // point larger to s2
    } else {
        smaller = &s2; //otherwise point smaller to s2 
        larger = &s1; //ppoint larger to s1
    }

    // Iterate through the smaller set and check existence in the larger set
    typename std::set<T>::iterator it;
    for (it = smaller->begin(); it != smaller->end(); ++it)
    {
        if (larger->find(*it) != larger->end())
        {
            result.insert(*it); // if the current element found in both sets , add to the result set
        }
    }
    
    return result;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> result = s1; //copy all the elements from s1
    result.insert(s2.begin(), s2.end()); // since dups are ignored, insert all elements fro
    // m s2
    return result;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
