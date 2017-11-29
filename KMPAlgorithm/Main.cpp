#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <vector>

using namespace std;

const string filename = "Text.txt";

int strNum(string _filename) {
	int res = 0;
	string s;
	ifstream fin(_filename, ios_base::in);
	if (fin.is_open()) while (getline(fin, s)) res++;
	else return 0;
	fin.close();
	return res;
}

//naive text search 
void naiveSearch(string needle, string *haystack, int num, list< pair<int,int> > &list) {
	for (int i = 0; i < num; i++) 
		for (int j = 0; j < haystack[i].length() - needle.length() + 1 ; j++) 
			if (haystack[i].substr(j, needle.length()) == needle)  list.push_back(make_pair(i, j));
}

//function for printing the elements in a list
void showlist(list <pair <int,int> > l) {
	list < pair <int,int> > ::iterator it;
	for (it = l.begin(); it != l.end(); ++it)
		cout << '\t' << "string : " << (*it).first << " pos : " << (*it).second << endl;
	cout << '\n';
}

//prefix function
vector<int> prefix(string needle) {
	vector<int> v(needle.length());
	v[0] = 0;
	int j;
	for (int i = 1; i < needle.length(); i++) {
		j = v[i - 1];
		while ((j > 0) && (needle[i] != needle[j]))	j = v[j - 1];         
		if (needle[i] == needle[j]) j++;
		v[i] = j;
	}
	return v;
}
//kmp search alg
void kmpSearch(string needle, string *haystack, int num, list < pair<int,int> > &list) {
	vector<int> pi(needle.length());
	int k = 0;
	pi = prefix(needle);
	for (int m = 0; m < num; m++) {
		for (int  i = 0; i < haystack[m].length(); ++i)
		{
			while ((k > 0) && (needle[k] != haystack[m][i]))
				k = pi[k - 1];

			if (needle[k] == haystack[m][i])
				k++;

			if (k == needle.length())
			list.push_back(make_pair(m, i - needle.length() + 1));
		}
	}
}

int main(int argc, char **argv) {
	list< pair<int, int> > naive, kmp;
	string *haystack, needle; //haystack - source text, needle - string to find
	ifstream fin(filename, ios_base::in);
	if (fin.is_open()) {
		cout << "Type needle to find." << endl;
		cin >> needle;
		int n = strNum(filename);
		haystack = new string[n];
		for (int i = 0; i < n; i++) getline(fin, haystack[i]);
		cout << "Text: " << endl;
		cout << endl;
		for (int i = 0; i < n; i++) cout << haystack[i] << "\n";
		cout << endl;
		naiveSearch(needle, haystack, n, naive);
		kmpSearch(needle, haystack, n, kmp);
		cout << "Needle '" << needle << "' was found here with NAIVE search:" << endl;
		showlist(naive);
		cout << "Needle '" << needle << "' was found here with KMP search:" << endl;
		showlist(kmp);
		cout << endl;
		if (naive == kmp) cout << "Eq" << endl;
		else cout << "NotEq" << endl;
		fin.close();
	}
	else{ 
		cout << "File can't be opened!" << endl;
	}
	system("pause");
	return 0;
}