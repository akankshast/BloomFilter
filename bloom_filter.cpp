#include <bits/stdc++.h>
using namespace std;


typedef function<unsigned int(string)> HashFunction;

class BloomFilter
{
    unsigned int bit_nums;
    bool *cell;
    vector<HashFunction> hashFunctions;

public:
    BloomFilter(unsigned int numbCells, std::vector<HashFunction> funcs)
    {
        this->bit_nums = numbCells;
        this->hashFunctions = funcs;
        cell = new bool[numbCells];
    }

    void addElement(string str)
    {
        for (auto iter = hashFunctions.begin(); iter != hashFunctions.end(); iter++)
            cell[(*iter)(str) % bit_nums] = true;
    }

    bool searchElement(std::string str)
    {
        bool strInSet = true;

        for (auto iter = hashFunctions.begin(); iter != hashFunctions.end(); iter++)
        {
            if (cell[(*iter)(str) % bit_nums] == false)
            {
                strInSet = false;
                break;
            }
        }

        return strInSet;
    }

    ~BloomFilter()
    {
        free(cell);
        cell = NULL;
    }
};

unsigned int djb2(string str)
{
    unsigned int hash = 5381;

    for (auto iter = str.begin(); iter != str.end(); iter++)
        hash = ((hash << 5) + hash) + *iter;

    return hash;
}

unsigned int sdbm(string str)
{
    unsigned int hash = 0;

    for (auto iter = str.begin(); iter != str.end(); iter++)
        hash = ((hash << 6) + (hash << 16) - hash) + *iter;

    return hash;
}

int main()
{

    vector<HashFunction> hashFunctions;
    hashFunctions.push_back(djb2);
    hashFunctions.push_back(sdbm);

    BloomFilter bf(1024, hashFunctions);

    vector<string> setOfStrings({"Hello World!", "sweet potato", "C++", "alpha", "beta", "gamma"});

    cout << "Bloom filter created." << endl;
    cout << "Bloom filter tests for the following set of strings:" << endl;

    for (auto iter = setOfStrings.begin(); iter != setOfStrings.end(); iter++)
    {
        bf.addElement(*iter);
        cout << "\t" + *iter << endl;
    }

    vector<string> testSetOfStrings({"Hello World!", "sweet potato", "C++", "alpha", "beta", "gamma", "delta", "where am i?", "foo", "bar"});

    cout << "Testing set inclusion for the following strings:" << endl;
    cout << boolalpha;

    for (auto iter = testSetOfStrings.begin(); iter != testSetOfStrings.end(); iter++)
        cout << "\t" + *iter + ": " << bf.searchElement(*iter) << endl;
}
