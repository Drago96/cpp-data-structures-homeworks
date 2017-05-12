
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <regex>

using namespace std;

void addWordsToSet(set<string>& wordsSet)
{
	ifstream file("input.txt", ios::in);
	string currentWord;
	regex letterCheck("[a-zA-Z]+");
	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, currentWord);
			// checks line for valid input and adds it to a set
			if (regex_match(currentWord, letterCheck))
			{
				transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);
				wordsSet.insert(currentWord);
			}
			else
			{
				throw string("Invalid input!");
			}
		}

	}
	else
	{
		throw string("File not found!");
	}
	file.close();
}

void mapAnagrams(map<map<char, unsigned long>, vector<string>>& mapAnagrams, set<string>& wordsSet)
{
	set<string>::iterator it;
	//maps strings according to number of occurence of characters
	for (it = wordsSet.begin(); it != wordsSet.end(); it++)
	{
		map<char, unsigned long> occurencesOfLetters;
		for (int i = 0; i < (*it).length(); i++)
		{
			if (occurencesOfLetters[(*it)[i]] != NULL)
			{
				occurencesOfLetters[(*it)[i]]++;
			}
			else
			{
				occurencesOfLetters[(*it)[i]] = 1;
			}
		}
		mapAnagrams[occurencesOfLetters].push_back(*it);
	}
}

unsigned long factorial(unsigned long n)
{
	unsigned long result = 1;
	for (unsigned long i = 2; i <= n; i++)
	{
		result *= i;
	}
	return result;
}

unsigned long getAnagramsCount(map<map<char, unsigned long>, vector<string>>& anagrams)
{
	unsigned long count = 0;
	//gets total anagram count using the combinations formula
	for (std::map<map<char, unsigned long>, vector<string>>::iterator it = anagrams.begin(); it != anagrams.end(); ++it)
	{
		if (it->second.size() > 1)
		{
			count += (factorial(it->second.size())) / (2 * factorial(it->second.size() - 2));
		}
	}
	return count;
}



int main()
{
	try
	{
		set<string> wordsSet;
		addWordsToSet(wordsSet);
		map<map<char, unsigned long>, vector<string>> anagrams;
		mapAnagrams(anagrams, wordsSet);
		unsigned long count = getAnagramsCount(anagrams);
		cout << count << endl;
	}
	catch(string& e)
	{
		cout << e<<endl;
	}
	return 0;
}

