#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

#define SUM 0

using namespace std;
using namespace std::chrono; 

//For the 50k numbers we have 62 million triplets and the best solution I could find works in o(n^2), I hope that's reasonable enough for the assignment

ifstream fin;
ofstream fout;

long get_triplets(vector<int> arr) 
{
	long unsigned i, j, k;
	int localsum;
	long count = 0;

	//For each element we go from the left and from the right. We check if the sum is right and if it isn't we modify the left and the right until they meet in the middle
	//Then it means we have no more triplets for the current element

	for (i = 0; i < arr.size() - 1; i++)
	{
		j = i + 1;
		k = arr.size() - 1;

		while (j < k)
		{
			localsum = arr[j] + arr[i] + arr[k];

			if (localsum == SUM)
			{
				// if (false)
				// 	fout << arr[j] << " " << arr[i] << " " << arr[k] << endl;

				count++;

				j++;
				k--;

			}
			else if (localsum < SUM) 
				j++;

			else 
				k--;
		}

	}

	return count;

}


int main (int argc, char **argv)
{
	if (argc <= 2)
	{
		printf("Please give the filename as command line argument\n Usage: %s file.in file.out\n", argv[0]);
		exit(1);
	}	

	fin.open(argv[1]);
	fout.open(argv[2]);

	vector<int> arr;
	int x;

	//We read the whole file

	while (fin >> x)
		arr.push_back(x);
	arr.erase(arr.begin(), arr.begin() + 1);	//We delete the first element with the number of elements (we have vect.size())

	auto start = high_resolution_clock::now();

	sort(arr.begin(), arr.end());	//We need the array sorted

	fout <<	get_triplets(arr) << endl;

	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start); 

	cout << duration.count() << " microseconds" << endl; 

	fin.close();
	fout.close();

	return 0;
}