#include <bits/stdc++.h>
using namespace std;

bool f_subsub(vector<int>::const_iterator iter, vector<int>::const_iterator end, int sum_left)
{
    if (sum_left == 0) return false;
    if (iter == end) return true;
    return f_subsub(iter+1, end, sum_left - *iter) && f_subsub(iter+1, end, sum_left);
}

bool f_sub(const vector<int>& vec, int num)
{
    bool result = f_subsub(vec.begin(), vec.end(), num);
    if (result) cout << num << endl;
    return result;
}

int main()
{
	//vector<int> A = {1, 2}; // Answer: 4
	//vector<int> A = {1, 2, 3, 4, 5}; // Answer: 16
	//vector<int> A = {5, 10, 20, 50, 100}; // Answer: 1
	vector<int> A = {1, 5, 10, 20, 50}; // Answer: 2


	//vector<int> A = {1, 10, 22, 30}; // Answer: 2
	//vector<int> A = {1, 2, 4}; // Answer: 8
    //vector<int> A = {5, 6, 13, 15, 20}; // Answer: 1

    int maxx = 0;

    if (A[0] > 1)
        cout << 1 << endl;
	else {
        for (int i = 0; i < A.size(); i++)
            maxx += A[i];
        maxx++;

        for (int j = 1; j <= maxx; j++){
            if (f_sub(A, j))
                break;
        }
	}

	return 0;
}
