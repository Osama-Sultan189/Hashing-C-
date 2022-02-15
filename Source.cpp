#include"hashing.h"
#include"perfectHashing.h"
#include<conio.h>
int main()
{
	srand(time(NULL));
	int n = 0;
	cout << "Enter size of Network Stream : ";
	cin >> n;
	unsigned long long int* arr = new unsigned long long int[n];
	generateRandomKeys(arr, n);
	cout << "Enter 1 for single level hashing\nEnter 2 for perfect hashing :\n ";
	int choice;
	cin >> choice;
	if (choice == 2)
	{
		PerfectHahing hash(n);
		for (int i = 0; i < n; i++)
			hash.insert(arr[i]);
		cout << "\nNo. of tries are : " << hash.getTries();
		
	}
	else if (choice == 1)
	{
		hashing hashTab;
		hashTab.insert(arr[0]);
		srand(time(NULL));
		for (int i = 1; i < n; i++)
		{
			int choice = rand() % 3 + 1;
			switch (choice)
			{
			case 1:
			{
				hashTab.insert(arr[i]);
				cout << "Inserted " << arr[i] << endl;
				break;
			}
			case 2:
			{
				int del = rand() % i + 1;
				if (hashTab.deleteVal(arr[del]))
					cout << "Deleted " << arr[del] << endl;
				i--;
				break;
			}
			case 3:
			{
				int srch = rand() % i + 1;
				cout << arr[srch] << " is found at " << hashTab.search(arr[srch]) << endl;
				i--;
				break;
			}
			}
		}
		hashTab.displayHash();
		cout << "Hash tab collisions are : " << hashTab.getCollisions();
	}
}