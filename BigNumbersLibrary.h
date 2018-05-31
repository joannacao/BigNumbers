#pragma once
#include <vector>
#include <string> 

using namespace std; 

namespace bn {
	class BigNumbers {
	private:
		int SIZE;
		vector<int> num;
	public:

		BigNumbers(const string&); 
		BigNumbers(); 

		void setNum(const string&); 

		int getSize(); 
		vector<int> getNum(); 

		BigNumbers operator+(BigNumbers &right);
		BigNumbers operator-(BigNumbers &right);
		BigNumbers operator*(BigNumbers &right);
		BigNumbers operator/(BigNumbers &right);
		BigNumbers operator%(BigNumbers &right);

		class DivideByZero
		{}; 

	};
}
