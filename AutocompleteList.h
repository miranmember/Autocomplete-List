// AutocompleteList.h
//
// Miran Member 10/05/2020
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct Term {
    string query;
    long long int weight;
    // need this for autograding
    bool operator==(const Term& term) const {
        return (query == term.query && weight == term.weight);
    }
};

//
// AutocompleteList
//
class AutocompleteList {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, terms, to store a list of
    // Terms.  As a result, you must also keep track of the number of elements
    // stored (size).
    //
    Term* terms;  // pointer to a C-style array
    int size;  // number of elements in the array
    string sortType;  // records how list is sorted
    
    //
    // Private member function.
    // Returns the index of the first word in terms[] that contains the prefix,
    // or -1 if there are no words containing the prefix. This search should be
    // implemented using a variation of the binary search algorithm.
    // Performance requirement: O(logn), n is size.
    //
    
    // Finds the first index in the sorted array
    // at which the userinput matches using binary search.
    int firstIndexOf(string prefix) {
		int Result = -1;
		int Size, Begin = 0, End = size;
		while (true) {
			// loops until the word searched matches
			Size = End - Begin;
			if (Size == 0) {
				break;
			}

			int Mid = Begin + (End - Begin - 1) / 2;
			//updates maid each loop

			string Query = terms[Mid].query.substr(0, prefix.length());
			int CompareResult = Query.compare(prefix);
			// compares the word from binary search to
			// user input using string compare.
			if (CompareResult == 0) { 
				// if compare result is the same then update the Mid
				// and size is 1 word then break else update the End
				// and continue searching 
				Result = Mid;
				if (Size == 1) {
					break;
				} else {
					End = Mid;
				}
			} else if (CompareResult > 0) {
				//update the end of the array to mid because its binary serach.
				End = Mid;
			} else {
				Begin = Mid + 1;
			}
		}
		// return the index at which the result was found
		return Result;
    }
    
    //
    // Private member function.
    // Returns the index of the last word in terms[] that contains the prefix,
    // or -1 if there are no words containing the prefix. This search should be
    // implemented using a variation of the binary search algorithm.
    // Performance requirement: O(logn), n is size.
    //
    // its the same proccess to find the last index as the first the
    // the only diffrence is on line 111.
    int lastIndexOf(string prefix) {
		int Result = -1;
		int Size, Begin = 0, End = size;
		while (true) {
			Size = End - Begin;
			if (Size == 0) {
				break;
			}

			int Mid = Begin + (End - Begin - 1) / 2;
			
			string Query = terms[Mid].query.substr(0, prefix.length());
			int CompareResult = Query.compare(prefix);

			if (CompareResult == 0) {
				Result = Mid;
				if (Size == 1) {
					break;
				} else {
					// update the start of the list.
					Begin = Mid + 1;
				}
			} else if (CompareResult > 0) {
				End = Mid;
			} else {
				Begin = Mid + 1;
			}
		}
		return Result;
    }
    
    //
    // Private member function.
    // This function sorts the terms array by lexicographic order of the query
    // string.
    // Set sortType to "lex".
    // Performance requirement: O(nlogn), n is size.
    //
    void sortByLexOrder() {
        // TODO: Write this function (optional).
        sort(terms, terms + size, 
        [](Term &A, Term &B) {
        	return (A.query < B.query);
        });
        // using sort and using lambda
        sortType = "lex";
    }
    //
    // Private member function.
    // This function sorts the terms array by decreasing weight order.
    // Set the sortType to "weight".
    // Performance requirement: O(nlogn), n is size.
    //
    void sortByWeightOrder() {
        // TODO: Write this function
        sort(terms, terms + size,
        [](Term &A, Term &B) {
        	return (A.weight > B.weight);
        });// using sort and using lambda
        sortType = "weight";
    }
    
 public:
    //
    // default constructor:
    //
    // Called automatically by C++ to create a AutocompleteList.
    // When this is called, intialize terms to a nullptr and set size to 0.
    // Set sortType to "none".
    // Performance requirement: O(1)
    //
    // default constructor
    AutocompleteList() {
        // TODO: Write this constructor (required).
        terms = nullptr;
    	size = 0;
    	sortType = "none";
    }
    //
    // a second constructor:
    //
    // Parameter passed in determines size of terms.
    // When this is called, allocate memory for n Terms and
    // set size accordingly.
    // Set sortType to "none".
    // Performance requirement: O(1)
    //
    // constructor if a specifi size is defined
    AutocompleteList(int n) {
        // TODO: Write this constructor (required).
        if (n > 0) {
        	terms = new Term[n];
        } else {
        	terms = nullptr;
        }
    	size = n;
    	sortType = "none";
    }
    
    //
    // a third constructor:
    //
    // Parameter passed in is name of file to read in.
    // This constructor will build Autocomplete list from file.
    // Assume file format is:
    // line 1: "<size>"
    // lines 2 thru size+1: "weight query"
    // The list should be sorted lexicographic order by the query string.
    // Set sortType to "lex".
    // Performance requirement: O(nlogn), n is size.
    //
    // constructor for when a file is passed, whcih
    // it reads the file and then stores the values
    // accordingly. 
    AutocompleteList(string filename) {
        // TODO: Write this constructor (required).
        ifstream infile(filename);
        infile >> size;
        terms = new Term[size];
        string Temp, Line;
        getline(infile, Temp);
        for(int i = 0; i < size; i++) {
        	getline(infile, Line);
        	istringstream iss(Line);
        	iss >> terms[i].weight;
        	getline(iss, Temp, '\t');
        	getline(iss, terms[i].query);
        }
        sortByLexOrder();// call for sort by lex as default
    }
    
    //
    // copy constructor:
    //
    // Called automatically by C++ to create an AutocompleteList that contains
    // a copy of an existing AutocompleteList.  Example: this occurs when
    // passing AutocompleteList as a parameter by value.
    // Performance requirement: O(n), n is size.
    //
    AutocompleteList(const AutocompleteList& other) {
        // TODO: Write this constructor (required).
        terms = nullptr; // set terms to nullptr as default
        size = other.size; // set size to match
        sortType = other.sortType;
        if (size > 0) {
        	// only update the array if size is more than 0.
			terms = new Term[size];
			for (int i = 0; i < size; i++) {
				terms[i] = other.terms[i];
			}
        }
    }
    
    //
    // copy operator=
    //
    // Called when you assign one AutocompleteList into another,
    // i.e. this = other;
    // Performance requirement: O(n), n is size.
    //
    // using the outvector.h 
    AutocompleteList& operator=(const AutocompleteList& other) {
        if (this == & other) {
               return *this;
        }

           delete[] terms;
           terms = nullptr;

        this->size = other.size;
        this->sortType = other.sortType;

        if (size > 0) {
            this->terms = new Term[size];
            for (int i = 0; i < size; i++) {
                this->terms[i] = other.terms[i];
            }
        }
        return *this;  // TODO: update
    }
    
    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the Term.
    //
    // deallocate memory
    virtual ~AutocompleteList() {
        if(terms) {
        	delete[] terms;
			terms = nullptr;
		}
    }
    
    //
    // Public member function.
    // Returns the size of the AutocompleteList.
    // Performance requirement: O(1).
    //
    int getSize() {
        return size;
    }
    
    //
    // Public member function.
    // Returns Term element in AutocompleteList.
    // This gives public access to Terms stored in the AutocompleteList.
    // If i is out of bounds, throw an out_of_range error message:
    // "AutocompleteList: i out of bounds"
    // Note:  This public function does not necessarily fit the design of this
    // abstraction but we are having you write it for testing purposes.
    // Performance requirement: O(1).
    //
    Term& operator[](int i) {
        if ( i < 0 || i >= size) {
        	throw out_of_range("AutocompleteList: " + to_string(i) +
        					  " out of bounds");
        }
        return terms[i];
    }
    // Public member function.
    // Returns an AutocompleteList which stores a list of all Terms that
    // start with the prefix.  The AutocompleteList returned should be sorted
    // in descending order by weight.  Set the returned AutocompleteList's
    // sortType to "weight".
    // If prefix is empty string, return an empty AutocompleteList;
    // If there are no words in the list the start with the prefix, return an
    // empty AutocompleteList.
    // If *this* AutocompleteList's sortType does not equal "lex", then return
    // an empty AutocompleteList.  In other words, allMatches should only be
    // called on an AutocompleteList that is sorted in lexicographic order by
    // the query string.
    // Performance requirement: O(mlogm+logn), n is size and
    // where m is the number of matching terms.
    //
    AutocompleteList allMatches(string prefix) {
        if (prefix.empty()) {
        	return AutocompleteList();
        }

        if (sortType != "lex") {
        	return AutocompleteList();
        }

		if (firstIndexOf(prefix) == -1 || lastIndexOf(prefix) == -1) {
			return AutocompleteList();
		}
		int FirstInd = firstIndexOf(prefix);
		int LastInd = lastIndexOf(prefix);
		int Matches = LastInd - FirstInd + 1;
		AutocompleteList R(Matches);

		for(int i = 0; i < Matches; i++) {
			R.terms[i] = terms[FirstInd + i];
		}
		R.sortByWeightOrder();
		return R;
    }
    
    
    AutocompleteList allMatchesWord(string prefix) {
    	if (prefix.empty()) {
        	return AutocompleteList();
        }
		if (firstIndexOf(prefix) == -1) {
			return AutocompleteList();
		}
		AutocompleteList R(1);
		R.terms[0] = terms[firstIndexOf(prefix)];
		return R;
    }
    // Public member function.
    // Returns the number of Terms that start with the given prefix.
    // If prefix is empty, return 0.
    // If *this* AutocompleteList's sortType does not equal "lex",
    // then return 0.
    // Performance requirement: O(logn), n is size.
    //
    int numberOfMatches(string prefix) {
        if (prefix.empty()) {
        	return 0;
        }
        if (sortType != "lex") {
        	return 0;
        }

        if (firstIndexOf(prefix) == -1) {
        	return 0;
        }

        int Matches = lastIndexOf(prefix) - firstIndexOf(prefix) + 1;

        return Matches;  // TODO: update
    }
    //
    // Public member function.
    // Prints the AutocompleteList.
    // Pad the front of the print with 8 spaces for nicely formatted search:
    // print: "        query, weight".
    // NOTE:  This is also useful for debugging purposes.
    // Performance requirement: O(n), n is size
    //
    // print all terms that are within the user input.
    void print() {
		for (int i = 0; i < size; i++) {
			cout << "        " << terms[i].query << ", " << terms[i].weight << endl;
		}
    }
};
