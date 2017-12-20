#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cmath>
#include <iterator>
#include <vector>
#include <ctime>

using namespace std;

vector<char> A = { 'a', 'b' };
const string filename1 = "Text.txt";

int menu() {
	system("cls");
	int key = -1;
	cout << "Type 0 to exit" << endl;
	cout << "Type 1 to choose nunm of letters in alphabet" << endl;
	cout << "Type 2 to type the needle to find" << endl;
	cout << "Type 3 to generate the needle automatically" << endl;
	cout << "Type 4 to choose text doc to search in, default is 'TextGen.txt' " << endl;
	cout << "Type 5 to perform SFT_TRIVIAL and SFT_KMP in text, default text is 'TextGen.txt'" << endl;
	cout << "Type 6 to show work time of algorithms" << endl;
	cout << "Type 7 to show the result of alghs work" << endl;
	cout << "Type 8 to type the haystack" << endl;
	cout << "Type 9 to generate the haystack automatically" << endl;
	cout << "Type 10 to proceed tests" << endl;
	cin >> key;

	return key;
}
//numer of strings in the file
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
//gets symbol from alphabet
char getSymb(int ind) {
	return A[ind];
}
//tests
void tests() {
	string haystack = "";
	string needle = "";
	ofstream kmpfout, trivfout;
	double t1, t2, tmp;
	string kmpflname = "TestResKMP1.txt";
	string trivflname = "TestResTriv1.txt";
	list<pair<int, int>> kmpRes;
	list<pair<int, int>> trivRes;

	trivfout.open(trivflname, ios_base::out && ios_base::trunc);
	kmpfout.open(kmpflname, ios_base::out && ios_base::trunc);
	//1st test
	cout << "[[Performing test 1]]" << endl;
	for (int k = 1; k <= 1001; k += 10) {
		for (int i = 0; i <= k; i++) needle += "ab";
		for (int i = 0; i <= 1000 * k; i++) haystack += "ab";
		//trivial output
		tmp = clock();
		SFT_Trivial(needle, haystack, trivRes, 0);
		t1 = clock() - tmp;
		trivfout << k << " " << t1 << endl;
		//kmp output
		tmp = clock();
		SFT_KMP(needle, haystack, kmpRes, 0);
		t2 = clock() - tmp;
		kmpfout << k << " " << t2 << endl;
		//refreshing storage
		needle = "";
		haystack = "";
		trivRes.clear();
		kmpRes.clear();
	}
	//closing fstreams
	kmpfout.clear();
	kmpfout.close();

	trivfout.clear();
	trivfout.close();

	//2nd test
	kmpflname = "TestResKMP2.txt";
	trivflname = "TestResTriv2.txt";

	trivfout.open(trivflname, ios_base::out && ios_base::trunc);
	kmpfout.open(kmpflname, ios_base::out && ios_base::trunc);
	//fill haystack	
	cout << "[[Performing test 2]]" << endl;
	for (int i = 0; i <= pow(10, 6) + 1; i++) haystack += getSymb(rand() % 2);

	for (int m = 1; m <= pow(10, 6) + 1; m += pow(10, 4)) {
		for (int i = needle.length(); i <= m; i++)	needle += "a";
		//trivial output
		tmp = clock();
		SFT_Trivial(needle, haystack, trivRes, 0);
		t1 = clock() - tmp;
		trivfout << m << " " << t1 << endl;
		//kmp output
		tmp = clock();
		SFT_KMP(needle, haystack, kmpRes, 0);
		t2 = clock() - tmp;
		kmpfout << m << " " << t2 << endl;
		//refreshing storage
		trivRes.clear();
		kmpRes.clear();
	}
	//closing fstreams
	kmpfout.clear();
	kmpfout.close();

	trivfout.clear();
	trivfout.close();

	//3d test
	kmpflname = "TestResKMP3.txt";
	trivflname = "TestResTriv3.txt";

	trivfout.open(trivflname, ios_base::out && ios_base::trunc);
	kmpfout.open(kmpflname, ios_base::out && ios_base::trunc);
	needle = "aaaaa";
	haystack = "";
	cout << "[[Performing test 3]]" << endl;
	for (int h = 1; h <= pow(10, 6); h += pow(10, 4)) {
		for (int i = haystack.length(); i <= h; i++) haystack += "aaaaab";
		//trivial output
		tmp = clock();
		SFT_Trivial(needle, haystack, trivRes, 1);
		t1 = clock() - tmp;
		trivfout << h << " " << t1 << endl;
		//kmp output
		tmp = clock();
		SFT_KMP(needle, haystack, kmpRes, 1);
		t2 = clock() - tmp;
		kmpfout << h << " " << t2 << endl;
		//refreshing storage
		trivRes.clear();
		kmpRes.clear();
	}
	//closing fstreams
	kmpfout.clear();
	kmpfout.close();

	trivfout.clear();
	trivfout.close();
}

int main(int argc, char **argv) {

	list< pair<int, int> > naive, kmp;
	string haystack, needle; //haystack - source text, needle - string to find
	string filename = "TextGen.txt";

	int counter = 0;
	ifstream fin;
	ofstream fout;
	int alph = 26;
	int k = -1;
	int len = 0;
	int flg = 0;
	double T1, tmp, T2;
	srand(time(0));
	while (k != 0) {
		k = menu();
		switch (k) {
		case 1:
			cout << "Type the number of letters in alphabet" << endl;
			cin >> alph;
			system("pause");
			break;
		case 2:
			cout << "Type needle to find" << endl;
			cin >> needle;
			system("pause");
			break;
		case 3:
			cout << "Type needle length" << endl;
			cin >> len;
			needle = "";
			if (0 < alph < 27) 	for (int i = 0; i < len; i++) needle += (char)(rand() % alph + 97);
			else for (int i = 0; i < len; i++) needle += (char)(rand() % alph);
			cout << "Needle: " << needle << endl;
			system("pause");
			break;
		case 4:
			cout << "Type filename" << endl;
			cin >> filename;
			system("pause");
			break;
		case 5:
			fin.open(filename, ios_base::in);
			tmp = clock();
			//performing trivial
			counter = 0;
			naive.clear();
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
			fin.clear();
			fin.close();
			break;
		case 6:
			cout << "SFT_TRIVIAL worktime: " << T1 / 1000.0 << endl;
			cout << "SFT_KMP worktime: " << T2 / 1000.0 << endl;
			system("pause");
			break;
		case 7:
			cout << "SFT_TRIVIAL result:" << endl;
			showlist(naive);
			cout << "SFT_KMP result:" << endl;
			showlist(kmp);
			system("pause");
			break;
		case 8:
			cout << "Type haystack to find" << endl;
			cin >> haystack;
			fout.open(filename, ios_base::out & ios_base::trunc);
			fout << haystack;
			fout.clear();
			fout.close();
			system("pause");
			break;
		case 9:
			fout.open(filename, ios_base::out & ios_base::trunc);
			cout << "Type 1 to gen haystack with rand letters, 2 to build haystack, with needle base" << endl;
			cin >> flg;
			if (flg != 2) {
				cout << "Type length of haystack" << endl;
				int hlength;
				cin >> hlength;
				haystack = "";
				if (0 < alph < 27) 	for (int i = 0; i < hlength; i++) haystack += (char)(rand() % alph + 97);
				else for (int i = 0; i < hlength; i++) haystack += (char)(rand() % alph);
			}
			else {
				cout << "Type k to build hay" << endl;
				int k;
				cin >> k;
				for (int i = 0; i < k; i++) {
					haystack += needle;
				}
			}
			fout << haystack;
			fout.clear();
			fout.close();
			system("pause");
			break;
		case 10:
			tests();
			break;
		case 0: break;
		default: break;
		}
	}
	return 0;
}