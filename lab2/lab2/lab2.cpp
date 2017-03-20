#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

using namespace std;

// Function Merge Sorting
pair<int*, int> MergeAndCountSplitInv(int* Lb, int Lsize, int* Rb, int Rsize)
{
	int* L = new int[Lsize + 1]; // Local copy of Left Array
	int* R = new int[Rsize + 1]; // Local copy of Right Array

	memcpy(L, Lb, Lsize * sizeof(int));
	memcpy(R, Rb, Rsize * sizeof(int));

	L[Lsize] = INT_MAX;
	R[Rsize] = INT_MAX;

	int counter = 0; // counter of inversions
	int i = 0, j = 0;

	int* A = new int[Lsize + Rsize]; // Merged Array

	for (int k = 0; k < Lsize + Rsize; k++)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
			counter += (Lsize - i);
		}
	}

	delete[] L;
	delete[] R;

	return make_pair(A, counter);
}

// Sorting and find counter of Inversions
pair <int*, int> SortAndCountInv(int* begin, int* end)
{
	int counter = 0; // counter of inversions
	int size = end - begin; // size of array

	if (size == 1)
	{
		int* A = new int[1];
		memcpy(A, begin, sizeof(int));

		return make_pair(A,0);
	}

	else
	{
		int size1 = (size / 2) + (size % 2); // size of Left Array
		int size2 = (size / 2); // size of Right Array

		int* Lb = new int[size1]; // Left Array
		int* Rb = new int[size2]; // Right Array

		memcpy(Lb, begin, size1 * sizeof(int));
		memcpy(Rb, begin + (size / 2) + (size % 2), size2 * sizeof(int));

		pair <int*, int> L; // Sorted Left Array and counter of inversions
		pair <int*, int> R; // Sorted Right Array and counter of inversions
		pair <int*, int> A; // Sorted Array and counter of inversions

		L = SortAndCountInv(Lb, Lb + size1); // Sorting of Left Array
		R = SortAndCountInv(Rb, Rb + size2); // Sorting of Right Array

		delete[] Lb;
		delete[] Rb;

		A = MergeAndCountSplitInv(L.first, size1, R.first, size2); // Merging of Left and Right Array
		A.second += L.second + R.second;

		delete[] L.first;
		delete[] R.first;

		return A;
	}
}

// Searching index of x in matrix
int search(int** matrix, int u, int x) {
	for (int i = 0; i < u; i++) {
		if (matrix[i][0] == x)  return i;
	}
	return -1;
}

// Making Index-Line
void makeIndex(int** matrix, int* dest, int m, int index, int src) {
	for (int i = 1; i <= m; i++) {
		dest[matrix[index][i]] = matrix[src][i];
	}
}

// Find Answer of the Task
void Answer(vector< pair<int, int> >& ans, int** matrix, int u, int m, int x) {
	int* tmp = new int[m + 1];

	for (int i = 0; i < u; i++) {
		if (i == x) continue;

		makeIndex(matrix, tmp, m, x, i); // making Index-Line
		pair<int*, int> B = SortAndCountInv(tmp + 1, tmp + m + 1); 
		// find counter of inversions for each user

		ans.push_back(std::make_pair(B.second, matrix[i][0]));
	}

	delete[] tmp;
}

// Outputting data
void output(vector< pair<int, int> >& ans, int x) {
	std::sort(ans.begin(), ans.end());

	printf("%d\n", x);

	for (int i = 0; i < ans.size(); i++)
		printf("%d %d\n", ans[i].second, ans[i].first);
}


int main(int argc, char* argv[]) {
	if (argc != 2) exit(-1);
	int x = atoi(argv[1]); // inputing x from command line

	// inputing from file
	int u, m;
	scanf("%d%d", &u, &m);

	int** matrix = new int*[u];

	for (int i = 0; i < u; i++) {
		matrix[i] = new int[m + 1];
	}

	for (int i = 0; i < u; i++) {
		for (int j = 0; j <= m; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}

	// search index of X in matrix
	x = search(matrix, u, x);
	if (x == -1) exit(-2);

	// finding answer to the Task
	vector< pair<int, int> > ans;
	Answer(ans, matrix, u, m, x);

	// outputing answer to file
	output(ans, matrix[x][0]);

	for (int i = 0; i < u; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}