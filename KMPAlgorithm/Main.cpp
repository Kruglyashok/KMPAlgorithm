#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>

using namespace std;

const string filename = "Text.txt";

int strNum(string _filename) {
	int res = 0;
	string s;
	ifstream fin(_filename, ios_base::in);
	if (fin.is_open()) 	while (getline(fin, s)) res++;
	else return 0;
	fin.close();
	return res;
}

//naive text search 
void naiveSearch(string needle, string *haystack, int num, list< pair<int,int> > &list) {
	for (int i = 0; i < num; i++) 
		for (int j = 0; j < haystack[i].length() - needle.length() + 1 ; j++) if (haystack[i].substr(j, needle.length()) == needle)  list.push_back(make_pair(i, j));
}

//function for printing the elements in a list
void showlist(list <pair <int,int> > g) {
	list < pair <int,int> > ::iterator it;
	for (it = g.begin(); it != g.end(); ++it)
		cout << '\t' << "string : " << (*it).first << " pos : " << (*it).second << endl;
	cout << '\n';
}

void kmp(string needle, string *haystack, int num, list < pair<int,int> > &list) {

}

int main(int argc, char **argv) {
	list< pair<int, int> > naive;
	string *haystack, needle; //haystack - source text, needle - string to find
	ifstream fin(filename, ios_base::in);
	if (fin.is_open()) {
		cout << "Type needle to find." << endl;
		cin >> needle;
		int n = strNum(filename);
		haystack = new string[n];
		for (int i = 0; i < n; i++) getline(fin,haystack[i]);
		cout << "Text: " << endl;
		cout << endl;
		for (int i = 0; i < n; i++) cout << haystack[i] << "\n";
		cout << endl;
		naiveSearch(needle, haystack, n, naive);
		cout << "Needle " << needle << " was found here:" << endl;
		showlist(naive);
	}
	else{ 
		cout << "File can't be opened!" << endl;
	}
	system("pause");
	return 0;
}