#ifndef HUGEINT_H
#define HUGEINT_H
#include<iostream>
using namespace std;

class HugeInt{
friend ostream& operator << (ostream&, const HugeInt& );
friend istream& operator >> (istream&, HugeInt&);
public:
	HugeInt();
	HugeInt(const HugeInt&);
	HugeInt(int value);
	HugeInt(string input);
	~HugeInt();
	HugeInt& operator=(const HugeInt&);
	HugeInt operator+(const HugeInt&);
	HugeInt operator-(const HugeInt&);
private:
	string content;
	int size;
	int* ptr;
};
#endif
