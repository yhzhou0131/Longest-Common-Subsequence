#include<iostream>
#include<string>
#include <map>
#define MAXLEN 101

using namespace std;

int lcsLength = 0, m, n;
string A, B;
int matrix[MAXLEN][MAXLEN] = { 0 };
map<string, int> dict;
void traceBack(string, int, int, int);

void buildMatrix(string A, string B) {
	for (auto i = 0; i <= m; i++) {
		for (auto j = 0; j <= n; j++) {
			if (i == 0 || j == 0)
				matrix[i][j] = 0;
			else if (A[i - 1] == B[j - 1]) {
				matrix[i][j] = matrix[i - 1][j - 1] + 1;
			}
			else if (matrix[i - 1][j] < matrix[i][j - 1]) {
				matrix[i][j] = matrix[i][j - 1];
			}
			else if (matrix[i - 1][j] > matrix[i][j - 1]) {
				matrix[i][j] = matrix[i - 1][j];
			}
			else {
				matrix[i][j] = matrix[i][j - 1];
			}
		}
	}
	lcsLength = matrix[m][n];
	traceBack("", lcsLength, m, n);
}
void traceBack(string s, int len, int mm, int nn) {
	if (len == 0)
	{
		if (dict.count(s) == 0)
			dict[s] = 1;
		else
			dict[s] ++;
		return;
	}
	else {
		for (auto i = 1; i <= mm; i++) {
			for (auto j = 1; j <= nn; j++) {
				if (matrix[i][j] == matrix[mm][nn] && A[i - 1] == B[j - 1]) {
					traceBack(A[i - 1] + s, len - 1, i - 1, j - 1);
				}
			}
		}
	}
}
int main() {
	cin >> A >> B;
	m = A.length();
	n = B.length();

	buildMatrix(A, B);
	int size = 0;
	for (auto it : dict) {
		size += it.second;
	}
	// cout << matrix[m][n] << " " << size << "\n";
	printf("%d %d\n", matrix[m][n], size);
		
	for (auto it : dict) {
		for (int i = 0; i < it.second; ++i) {
			// cout << it.first << "\n";
			printf("%s\n", it.first.c_str());
		}
	}
	
	return 0;
}	