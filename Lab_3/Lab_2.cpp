#include "stdafx.h"
using namespace std;


struct Comand {
	int score;
	string comand;
};

int len(string n);
string * split(string input, char s, int n);

int main() {
	setlocale(LC_ALL, "rus");
	ifstream league;
	ofstream results("results.txt");
	league.open("premier_league.csv");
	string tempo;
	getline(league, tempo);
	int n = atoi(tempo.c_str());
	Comand * res = new Comand[n];
	int c = floor(n / 2 + 1);
	if (league.is_open()) {
		string line;
		int i = 0;
		while (league.good()) {
			Comand cmd;
			getline(league, line);
			string * temp = new string[c];
			temp = split(line, ',', n);
			int score = 0;
			cmd.comand = temp[0];
			for (int i = 1; i < c; i++) {
				
				if (i == 1) continue;
				if (temp[i][0] == '-') {
					score += 1;
					continue;
				} 	
				if (temp[i][0] == '-') {
					score += 1;
					continue;
				}
				if (temp[i][0] > temp[i][2]) score += 3;
				else if (temp[i][0] == temp[i][2]) score += 1;
			}
			cmd.score = score;
			res[i] = cmd;
			i++;
			delete[] temp;
		}
	}
	else {
		cout << "Файл не открыт\n\n";
		return -1;
	}
	for (int i = 1; i < n; i++) {
		Comand t = res[i];
		int j = i - 1;
		while (j >= 0 && res[j].score < t.score) {
				res[j + 1] = res[j];
				j--;
		}	
		res[j + 1] = t;
	}
	for (int i = 0; i < n; i++) {
		if (i < 3) results << i + 1 << "-th place with a score   " << res[i].score << ": \t" << res[i].comand << endl;
		else results << "  LOOSER!  With a score   "<< res[i].score << ": \t" << res[i].comand << endl;
	}
	results.close();
	league.close();
	return 0;
}

string * split(string input, char s, int n) {
	string * arr = new string[n/2 + 1];
	string temp = "";
	int j = 0;
	for (int i = 0; input[i]; i++) {
		if (input[i] == s) {
			arr[j] = temp;
			temp = "";
			j++;
		}
		else temp += input[i];
	}
	if (temp != "") arr[j] = temp;
	return arr;
}
