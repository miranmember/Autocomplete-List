//
//  application.cpp
//  Miran Member
/* for creative compotant it prints as you type the word you are most likely to type in. for it to work you type your word and press enter. */
//
#include "AutocompleteList.h"
#include <iostream>

int main() {
	string FileName, UserInput, Search;
	cout << "Enter filename: ";
	cin >> FileName;
	AutocompleteList List(FileName);
	cout << "Enter s-search or c-creative search: ";
	cin >> Search;
	cin.ignore();
	if (Search == "s") {
		cout << "Welcome!" << endl;
		cout
		<< "Type your search below, press enter for autocomplete (# to stop)."
		<< endl;
		while (true) {
			cout << "Search: ";
			getline(cin, UserInput);
			if (UserInput == "#") {
				break;
			}
			AutocompleteList MatchList = List.allMatches(UserInput);
			MatchList.print();
		}
	} else if (Search == "c") { // creative compotant //
		cout << "Welcome!" << endl;
		cout
		<< "Type your search below, press enter to find a specific word.(# to stop)."
		<< endl;
		while (true) {
			getline(cin, UserInput);
			if (UserInput == "#") {
				break;
			}
			AutocompleteList MatchList = List.allMatchesWord(UserInput);
			MatchList.print();
		}
	}
    return 0;
}
