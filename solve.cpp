#include"solve.h"
using namespace std;
HugeInt::HugeInt(){
	size = 0;
	ptr = new int[size];
}
HugeInt::HugeInt(int value){
	int hold = value;
	int lengthCount = 0;
	if( value > 0 ) sign_ = '+';
	else sign_ = '-';
	for(; value != 0; value /= 10, lengthCount++);
	size = lengthCount;
	ptr = new int[size];
	for( int k = 0; k < size; ++k ){
		ptr[size-k-1] = hold % 10;
		hold = hold/10;
	}
}
HugeInt::HugeInt(string input){
	content = input;
	int counter = 0;
	for( int i = 0; i < content.size(); ++i ){
		if((content.at(i)-48 >= 0)  && (content.at(i)-57 <= 0))
			counter++;
		if(content.at(i) == 45 )
			sign_ = '-';
	}
	size = counter;
	ptr = new int[size];
	int j = 0;
	for( int k = 0; k < input.size(); ++k )
		if((content.at(k)-48 >= 0)  && (content.at(k)-57 <= 0)){
			ptr[j] = (content.at(k)-48);
			++j;
		}
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
		 if(&right != this){
			 if(size != right.size){
				 delete [] ptr;
				 	size = right.size;
					ptr = new int[size];
			 }
			 for(int i=0;i<size;++i)
			 		ptr[i] = right.ptr[i];
			 sign_ = right.sign_;
			 return *this;
		}
}
istream& operator>>(istream& in, HugeInt& a){
	string temp_use;
	in >> temp_use;
	HugeInt temp(temp_use);
	a = temp;
	return in;
}
ostream& operator<<(ostream& out, const HugeInt& a){
	if( a.sign_ == '-') cout <<'-';
  int start = 0;
	for( int i = 0; i < a.size; ++i ){
		if( a.ptr[i] == 0 ) continue;
		else if ( a.ptr[i] != 0){
			start = i;
			break;
		}
	}
	for( int i = start; i < a.size; ++i )
		out << a.ptr[i];
	return out;
}
HugeInt HugeInt::operator+(const HugeInt& right){
	HugeInt carry;
	HugeInt temp;
	HugeInt elementOne;
	HugeInt elementTwo;
	if( size >= right.size )
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
	/*for( int p = 0; p < temp.size; ++p )
		cout << temp.ptr[p];
	cout << endl;*/
	return temp;
}
HugeInt HugeInt::operator-(const HugeInt& right){
	HugeInt carry;
	HugeInt temp;
	HugeInt elementOne;
	HugeInt elementTwo;
	bool checker = false;
	if( size < right.size ){
		temp.sign_ = '-';
		carry.size= temp.size= elementOne.size= elementTwo.size = right.size;
	}
	else if( size == right.size ){
		for( int k = 0; k < size ;++k )
			if( ptr[k] < right.ptr[k] ){
				temp.sign_ = '-';
				carry.size= temp.size= elementOne.size= elementTwo.size = size;
				checker = true;
				break;
			}
	}
	else if ( size > right.size )
		carry.size= temp.size= elementOne.size= elementTwo.size = size;
	carry.ptr = new int[carry.size];
	temp.ptr = new int[temp.size];
	elementOne.ptr = new int[elementOne.size];
	elementTwo.ptr = new int[elementTwo.size];
	for( int k = 0; k < carry.size; ++k )
		carry.ptr[k] = temp.ptr[k] = elementOne.ptr[k] = elementTwo.ptr[k] = 0;
	if( size > right.size ){
		for( int p = 0; p < size ; ++p )
			elementOne.ptr[p+(elementOne.size - this->size)] = this->ptr[p];
		for( int l = 0; l < right.size; ++l )
		 	elementTwo.ptr[l+(elementTwo.size - right.size)] = right.ptr[l];
	}
	else if( size <= right.size ){
		if( checker == false ){
			for( int p = 0; p < size ; ++p )
				elementOne.ptr[p+(elementOne.size - this->size)] = right.ptr[p];
			for( int l = 0; l < right.size; ++l )
		 		elementTwo.ptr[l+(elementTwo.size - right.size)] = this->ptr[l];
		}
		else {
			for( int p = 0; p < size ; ++p )
				elementOne.ptr[p+(elementOne.size - this->size)] = this->ptr[p];
			for( int l = 0; l < right.size; ++l )
			 	elementTwo.ptr[l+(elementTwo.size - right.size)] = right.ptr[l];
		}
	}
	for( int k = elementOne.size-1 ; k >= 0; --k ){
		temp.ptr[k] = carry.ptr[k] + elementOne.ptr[k] - elementTwo.ptr[k];
		if( temp.ptr[k] < 0 ){
			temp.ptr[k] += 10;
			carry.ptr[k-1] -= 1;
		}
	}
	return temp;

}
