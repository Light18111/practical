/*
----------Assignment No - 9----------
Given sequence k = k1 <k2 < ... <kn of n sorted keys, with a search probability pi for each key ki . 
Build the Binary search tree that has the least search cost given the access probability for each key.
*/

#include <bits/stdc++.h>
using namespace std;

int sum(int freq[], int i, int j);

int optimalSearchTree(int keys[], int freq[], int n)
{
	int cost[n][n];

	for (int i = 0; i < n; i++)
		cost[i][i] = freq[i];

	for (int L = 2; L <= n; L++)
	{
		for (int i = 0; i <= n-L+1; i++)
		{
			// Get column number j from row number i and
			// chain length L
			int j = i+L-1;
			cost[i][j] = INT_MAX;

			// Try making all keys in interval keys[i..j] as root
			for (int r = i; r <= j; r++)
			{
			// c = cost when keys[r] becomes root of this subtree
			int c = ((r > i)? cost[i][r-1]:0) +
					((r < j)? cost[r+1][j]:0) +
					sum(freq, i, j);
			if (c < cost[i][j])
				cost[i][j] = c;
			}
		}
	}
	return cost[0][n-1];
}

int sum(int freq[], int i, int j)
{
	int s = 0;
	for (int k = i; k <= j; k++)
	s += freq[k];
	return s;
}

int main()
{
	int keys[] = {10, 20, 30, 40};
	int freq[] = {3, 3, 1, 1};
	int n = sizeof(keys)/sizeof(keys[0]);
	cout << "Cost of Optimal BST is " << optimalSearchTree(keys, freq, n);
	return 0;
}
