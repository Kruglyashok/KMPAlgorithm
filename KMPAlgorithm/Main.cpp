#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <vector>
#include <ctime>

using namespace std;

int menu() {
	int key = -1;
	cout << "Type 0 to exit" << endl;
	cout << "Type 1 to choose nunm of letters in alphabet" << endl;
	cout << "Type 2 to type the needle to find" << endl;
	cout << "Type 3 to generate the needle automatically" << endl;
	cout << "Type 4 to choose text doc to search in, default is 'Text.txt' " << endl;
	cout << "Type 5 to perform SFT_TRIVIAL and SFT_KMP in text, default text is 'Text.txt'" << endl;
	cout << "Type 6 to show work time of algorithms" << endl;
	cout << "Type 7 to show the result of alghs work" << endl;
	cin >> key;
	system("cls");
	return key;
}

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
void SFT_Trivial(string needle, string haystack, list< pair<int, int> > &list, int m) {
	for (int j = 0; j < haystack.length() - needle.length() + 1; j++)
		if (haystack.substr(j, needle.length()) == needle)  list.push_back(make_pair(m, j));

}

//function for printing the elements in a list
void showlist(list <pair <int, int> > _list) {
	list < pair <int, int> > ::iterator it;
	for (it = _list.begin(); it != _list.end(); ++it)
		cout << '\t' << "string : " << (*it).first << " pos : " << (*it).second << endl;
	cout << endl;
}

//prefix function
vector<int> kmp(string needle) {
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
void SFT_KMP(string needle, string haystack, list < pair<int, int> > &list, int m) {
	unsigned int stime = clock();
	vector<int> pi(needle.length());
	int k = 0;
	pi = kmp(needle);
	for (int i = 0; i < haystack.length(); ++i)
	{
		while ((k > 0) && (needle[k] != haystack[i]))
			k = pi[k - 1];

		if (needle[k] == haystack[i])
			k++;

		if (k == needle.length())
			list.push_back(make_pair(m, i - needle.length() + 1));
	}
}

int main(int argc, char **argv) {

	list< pair<int, int> > naive, kmp;
	string haystack, needle; //haystack - source text, needle - string to find
	string filename = "Text.txt";
	
	int counter = 0;
	ifstream fin(filename, ios_base::in);
	int alph = 255;
	int k = -1;
	int len = 0;
	double T1, tmp, T2;
	srand(time(0));
	while (k != 0) {
		k = menu();
		switch (k) {
		case 1: 
			cout << "Type the number of letters in alphabet" << endl;
			cin >> alph;
			break;
		case 2:
			cout << "Type needle to find" << endl;
			cin >> needle;
			break;
		case 3:
			cout << "Type needle length" << endl;
			cin >> len;
			for (int i = 0; i < len; i++) needle += (char)(rand() % 255);
			cout << "Needle: " << needle << endl;;
			break;
		case 4: 
			cout << "Type filename" << endl;
			cin >> filename;
			break;
		case 5:
			//naive.clear();
			tmp = clock();
			//performing trivial
			while (getline(fin, haystack)) {
				SFT_Trivial(needle, haystack, naive, counter);
				counter++;
			}
			T1 = clock() - tmp;

			//performing KMP
			fin.clear(); //clears the bits with errors 
			fin.seekg(0); //returns pointer back to the beginning of the file
			
			counter = 0;
			kmp.clear();
			tmp = clock();
			while (getline(fin, haystack)) {
				SFT_KMP(needle, haystack, kmp, counter);
				counter++;
			}
			T2 = clock() - tmp;
			break;
		case 6:
			cout << "SFT_TRIVIAL worktime: " << T1 / 1000.0 << endl;
			cout << "SFT_KMP worktime: " << T2 / 1000.0 << endl;
			break;
		case 7:
			cout << "SFT_TRIVIAL result:" << endl;
			showlist(naive);
			cout << "SFT_KMP result:" << endl;
			showlist(kmp);
			break;
		case 0: break;
		default: break;
		}
	}
	return 0;
}