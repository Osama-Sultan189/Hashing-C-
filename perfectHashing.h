#pragma once
#include"hashing.h"
using namespace std;
class PerfectHahing
{
private:
	hashing* hashTabs;
	int reHashCount;
	int collide;
	long int size;
	long long int tries;
	long long int a;
	long long int b;
	long long int prime;
	int hashKey(int value);
public:
	PerfectHahing(int m);
	void insert(int value);
	void displayHash();
	int search(long long int value);
	int getNoOfCollisions();
	long long int getTries();
};
PerfectHahing::PerfectHahing(int m)
{
	collide = 0;
	reHashCount = 0;
	size = m;
	tries = 0;
	hashTabs = new hashing[size];
	prime = hashTabs[0].getPrime();
	a = (rand() % (prime - 1)) + 1;
	b = (rand() % (prime - 1));
}
int PerfectHahing::hashKey(int value)
{
	return (((a * value) + b) % prime) % size;
}
void PerfectHahing::insert(int value)
{
	int index = hashKey(value);
	hashTabs[index].insert(value);
	if (hashTabs[index].getCollisions() != 0)
		while (hashTabs[index].getCollisions() != 0)
		{
			hashTabs[index].rehash();
			tries++;
			/*cout << "No of collisions at index : " << index << " are :" << hashTabs[index].getCollisions() << endl;
			hashTabs[index].displayHash();
			int a;
			cin >> a;*/
		}
}
void PerfectHahing::displayHash()
{
	for (int i = 0; i < size; i++)
	{
		hashTabs[i].displayHash();
		cout << "No of collions at index " << i << " are : " << hashTabs[i].getCollisions() << endl;
		cout << "\n-------------------\n";
	}
}
int PerfectHahing::search(long long int value)
{
	int srch = -1;
	for (int i = 0; i < size; i++)
	{
		srch = hashTabs[i].search(value);
		if (srch != -1)
			return i;
	}
}
int PerfectHahing::getNoOfCollisions()
{
	collide = 0;
	for (int i = 0; i < size; i++)
		if (hashTabs[i].getCollisions() >= 1)
			collide++;
	return collide;
}
long long int PerfectHahing::getTries() 
{
	return tries;
}