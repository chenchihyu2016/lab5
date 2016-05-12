#include"solve.h"
using namespace std;
HugeInt::HugeInt(){
	size = 0;
	ptr = new int[size];
}
HugeInt::HugeInt(int value){
	int hold = value;
	int lengthCount = 0;
	for(; value != 0; value /= 10, lengthCount++);
	size = lengthCount;
	ptr = new int[size];
	for( int k = 0; k < size; k++ ){
		ptr[k] = hold % 10;
		hold = hold/10;
	}
}
HugeInt::HugeInt(string input){
	content = input;
	int counter = 0;
	for( int i = 0; i < content.size(); ++i )
		if((content.at(i)-48 >= 0)  && (content.at(i)-57 <= 0))
			counter++;
	size = counter;
	ptr = new int[size];
	for( int j = 0; j < counter ; ++j )
		if((content.at(j)-48 >= 0)  && (content.at(j)-57 <= 0))
			ptr[j] = (content.at(j)-48);
}
HugeInt::HugeInt(const HugeInt& right){
	size = right.size;
	ptr = new int[size];
	for( int i = 0; i < size; ++i )
		ptr[i] = right.ptr[i];
}
HugeInt::~HugeInt(){
	delete []ptr;
}
HugeInt& HugeInt::operator=(const HugeInt& right){
	HugeInt temp(right);
	swap(*this,temp);
	return *this;
}
istream& operator>>(istream& in, HugeInt& a){
	string temp_use;
	in >> temp_use;
	HugeInt temp(temp_use);
	a = temp;
	return in;
}
ostream& operator<<(ostream& out, const HugeInt& a){
	for( int i = 0; i < a.size; ++i )
		out << a.ptr[i];
	out << endl;
	return out;
}
HugeInt HugeInt::operator+(const HugeInt& right){
	HugeInt carry;
	HugeInt temp;
	HugeInt elementOne;
	HugeInt elementTwo;
	if( size > right.size )
		carry.size= temp.size= elementOne.size= elementTwo.size = size+1;
	else
		carry.size= temp.size= elementOne.size= elementTwo.size = right.size+1;
	++carry.size;
	carry.ptr = new int[carry.size];
	temp.ptr = new int[temp.size];
	elementOne.ptr = new int[elementOne.size];
	elementTwo.ptr = new int[elementTwo.size];
	for( int k = 0; k < carry.size; ++k )
		carry.ptr[k] = temp.ptr[k] = elementOne.ptr[k] = elementTwo.ptr[k] = 0;
	for( int p = 0; p < size ; ++p )
		elementOne.ptr[p+(elementOne.size - this->size)] = this->ptr[p];
	for( int l = 0; l < right.size; ++l )
	 	elementTwo.ptr[l+(elementTwo.size - right.size)] = right.ptr[l];
	for( int pos = elementOne.size; pos >= 0; --pos ){
		temp.ptr[pos] = elementOne.ptr[pos] + elementTwo.ptr[pos] + carry.ptr[pos];
		if( temp.ptr[pos] > 9 ){
			temp.ptr[pos] -= 10;
			carry.ptr[pos-1] = 1;
		}
	}
	if( temp.ptr[0] != 0 ) return temp;
	else if( temp.ptr[0] == 0 ){
		HugeInt temper;
		temper.size = --temp.size;
		temper.ptr = new int[temper.size];
		for( int k = 0 ; k < temper.size ; ++k )
			temper.ptr[k] = temp.ptr[k+1];
		return temper;
	}
}
HugeInt HugeInt::operator-(const HugeInt&){
}
