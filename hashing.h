#pragma once
#pragma warning( disable : 4244 ) 
#include<iostream>
#include <list>
#include<ctime>
using namespace std;
unsigned long long int primes[4] = { 5151723272933455759,351115273341475357,1132125314569758191, 51723394547697577 };
unsigned long long int w = pow(2, 64) - 1; 
void generateRandomKeys(unsigned long long int randomKeys[], int n)
{
	//generate Random integers in range 1-2^64
	for (int i = 0; i < n; i++)
	{
		randomKeys[i] = rand() % (w)+1;
		for (int j = 0; j < i; j++)
			if (randomKeys[i] == randomKeys[j])
			{
				i--;
				break;
			}
	}
}
void displayRandomKeys(unsigned long long int  randomKeys[], int n)
{
	for (int i = 0; i < n; i++)
		cout << randomKeys[i] << endl;
}
class hashing {
private:
	int collisions;
	int count; //keeps the count of total entries in hash table
	long long int m; //size of hash table
	list<unsigned long long int>* hashInd; // array of lists
	long long int a;
	long long int b;
	unsigned long long int prime;
	int hashKey(int); //returns key for mapping value in hash table
	void doubling(); //if count is equal to table size table will be doubled
	void halving(); // if count is less the 1/4th of table size it'll be halved
	void countCollisions(); //displays no of values hased to same index
public:
	hashing(); //initalizes required values
	void insert(int);
	bool deleteVal(int);
	void displayHash(); 
	int search(int value);
	long long int getPrime();
	int getSize();
	int getCollisions();
	list<unsigned long long int>* getList();
	void rehash()
	{
		hashing hashTemp;
		/*long long int tempP = primes[rand()%4];
		long long int tempa = (rand() % (tempP - 1)) + 1;
		long long int tempb = (rand() % (tempP - 1));
		list<unsigned long long int>* temp;
		temp = new list<unsigned long long int>[m];*/
		for (int i = 0; i < m; i++)
		{
			list <unsigned long long int> ::iterator j;
			for (j = hashInd[i].begin(); j != hashInd[i].end(); j++)
				hashTemp.insert(*j);
		}
		/*a = tempa;
		b = tempb;
		prime = tempP;*/
		cout << "Rehashing : " << a << " " << b << " " << prime << endl;
		*this = hashTemp;
		/*hashInd = new list<unsigned long long int>[m];
		for (int i = 0; i < m; i++)
		{
			list <unsigned long long int> ::iterator j;
			for (j = temp[i].begin(); j != temp[i].end(); j++)
				hashInd[i].push_front(*j);
		}*/
	}

};
hashing::hashing()
{
	//srand(time(NULL));
	prime = 18361375334787046697; //initializing with one of largest prime under 2^64
	count = 0; //initially table is empty
	m = 1; // and table size is 1
	//prime = primeInRange(m, w);
	hashInd = new list<unsigned long long int>[m]; //allocating list memory for table indexces
	a = (rand() % (prime - 1)) + 1;
	b = (rand() % (prime - 1));
	collisions = 0;
}
int hashing::hashKey(int value)
{
	return (((a * value) + b) % prime) % m;
}
void hashing::insert(int value)
{
	int index = hashKey(value);
	hashInd[index].push_front(value);
	count++;

	if (count == m)
		doubling();
}
bool hashing::deleteVal(int value)
{
	int index = hashKey(value);
	bool delFlag = false;
	for (int i = 0; i < m; i++)
	{
		list <unsigned long long int> ::iterator j;
		for (j = hashInd[i].begin(); j != hashInd[i].end(); j++)
			if (*j == value)
			{
				hashInd[index].erase(j);
				delFlag = true;
				break;
			}
		if (delFlag)
			break;
	}
	if (delFlag)
	{
		count--;
		if (count <= m / 4)
		{
			cout << "Size : " << m << " Values : " << count << " Half\n";
			halving();
		}
		return true;
	}
	return false;
}
void hashing::doubling()
{
	long long int tempP = prime;
	int tempa = (rand() % (tempP - 1)) + 1;
	int tempb = (rand() % (tempP - 1));
	list<unsigned long long int>* temp;
	temp = new list<unsigned long long int>[m * 2];
	for (int i = 0; i < m; i++)
	{
		list <unsigned long long int> ::iterator j;
		for (j = hashInd[i].begin(); j != hashInd[i].end(); j++)
		{
			int value = *j;
			temp[(((tempa * value) + tempb) % tempP) % (m * 2)].push_front(value);
		}
	}
	hashInd->clear();
	a = tempa;
	b = tempb;
	m = m * 2;
	prime = tempP;
	hashInd = new list<unsigned long long int>[m];
	for (int i = 0; i < m; i++)
		if (temp[i].size() != 0)
		{
			list <unsigned long long int> ::iterator j;
			for (j = temp[i].begin(); j != temp[i].end(); j++)
				hashInd[i].push_front(*j);
		}
}
void hashing::halving()
{
	long long int tempP = prime;
	int tempa = (rand() % (tempP - 1)) + 1;
	int tempb = (rand() % (tempP - 1));
	list<unsigned long long int>* temp;
	temp = new list<unsigned long long int>[m / 2];
	for (int i = 0; i < m; i++)
	{
		list <unsigned long long int> ::iterator j;
		for (j = hashInd[i].begin(); j != hashInd[i].end(); j++)
		{
			int value = *j;
			temp[(((tempa * value) + tempb) % tempP) % (m / 2)].push_front(value);
		}
	}
	hashInd->clear();
	a = tempa;
	b = tempb;
	m = m / 2;
	prime = tempP;
	hashInd = new list<unsigned long long int>[m];
	for (int i = 0; i < m; i++)
	{
		list <unsigned long long int> ::iterator j;
		for (j = temp[i].begin(); j != temp[i].end(); j++)
			hashInd[i].push_front(*j);
	}

}
void hashing::displayHash()
{
	for (int i = 0; i < m; i++)
	{
		cout << i << " | ";
		list <unsigned long long int> ::iterator j;
		for (j = hashInd[i].begin(); j != hashInd[i].end(); j++)
		{
			int value = *j;
			cout << value << " ";
		}
		cout << endl;
	}
}
void hashing::countCollisions()
{
	for (int i = 0; i < m; i++)
		cout << "Values Hased at index " << i << " are : " << hashInd[i].size() << endl;
}
int hashing::search(int value)
{
	int srch=hashKey(value);
	list <unsigned long long int> ::iterator j;
	for (j = hashInd[srch].begin(); j != hashInd[srch].end(); j++)
		if (*j == value)
			return srch;
	return -1;
}
long long int hashing::getPrime()
{
	return prime;
}
int hashing::getSize()
{
	return count;
}
int hashing::getCollisions()
{
	collisions = 0;
	for (int i = 0; i < m; i++)
		if (hashInd[i].size() > 1)
			collisions += (hashInd[i].size() - 1);
	return collisions;
}
list<unsigned long long int>* hashing::getList()
{
	return hashInd;
}