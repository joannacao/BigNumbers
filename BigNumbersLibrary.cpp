// BigNumbersLibrary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BigNumbersLibrary.h"
#include <stdexcept>
#include <iostream>
#include <vector> 
#include <string> 
#include <cmath>

using namespace std; 

namespace bn {
	BigNumbers BigNumbers::operator+( BigNumbers &right)
	{
		BigNumbers temp; //creates temp object to return 
		vector<int> ans; //creates vector to store answer
		vector<int> rVec = right.num; //rVec is the right object's vector num
		vector<int> copyNum; 
		for (int i = 0; i < num.size(); i++) {
			copyNum.push_back(num[i]); 
		}
		int answer; //int answer for digit to store in ans
		int size = copyNum.size(); //int size for left object's vector size 
		//first, line up vectors so that they have the same digits in the same places
		if (size > rVec.size()) { //if left object is larger, insert zeros into right vector
			int extraDigits = size - rVec.size();
			for (int x = 0; x < extraDigits; x++) {
				rVec.insert(rVec.begin(), 0);
			}
		}
		else if (size < rVec.size()) { //if right is larger, insert zeros into left vec 
			//iter = num.begin(); 
			int extraDigits = rVec.size() - size;
			for (int x = 0; x < extraDigits; x++) {
				copyNum.insert(copyNum.begin(), 0);
			}
		}
		for (int i = size-1; i >= 0; i--) { //starts from back of vector (single digit) and goes in reverse
			answer = copyNum[i] + rVec[i]; //stores added digits in answer
			while (answer > 9 && i != 0) { //if answer isn't a single digit, carry over by 10s until it is
				answer -= 10; //subtract 10 to get single digit
				copyNum[i - 1] += 1; //increment one to digit on the left 
			}
			ans.insert(ans.begin(), answer); //stores into vector but in reverse direction, will reverse later
		}
		//if the first element is more than a single digit then we fix it
		if (ans[0] > 9) {
			if (ans[0] - 10 < 10) {
				ans.insert(ans.begin(), 1);
				answer = ans[1] - 10;
				ans[1] = answer;
			} else if (ans[0] - 20 < 10) {
				ans.insert(ans.begin(), 2);
				answer = ans[1] - 20;
				ans[1] = answer;
			} else if (ans[0] - 30 < 10) {
				ans.insert(ans.begin(), 3);
				answer = ans[1] - 30;
				ans[1] = answer;
			} else if (ans[0] - 40 < 10) {
				ans.insert(ans.begin(), 4);
				answer = ans[1] - 40;
				ans[1] = answer;
			} else if (ans[0] - 50 < 10) {
				ans.insert(ans.begin(), 5);
				answer = ans[1] - 50;
				ans[1] = answer;
			} else if (ans[0] - 60 < 10) {
				ans.insert(ans.begin(), 6);
				answer = ans[1] - 60;
				ans[1] = answer;
			} else if (ans[0] - 70 < 10) {
				ans.insert(ans.begin(), 7);
				answer = ans[1] - 70;
				ans[1] = answer;
			} else if (ans[0] -80 < 10) {
				ans.insert(ans.begin(), 8);
				answer = ans[1] - 80;
				ans[1] = answer;
			} else if (ans[0] - 90 < 10) {
				ans.insert(ans.begin(), 9);
				answer = ans[1] - 90;
				ans[1] = answer;
			}
		}
		temp.num = ans; 
		temp.SIZE = ans.size(); 
		return temp; 
	}

	BigNumbers BigNumbers::operator-(BigNumbers &right)
	{
		BigNumbers temp; //create temp object to return 
		vector<int> ans; //create ans vector to store answer
		vector<int> rVec = right.num; 
		vector<int> copyNum; 
		for (int i = 0; i < num.size(); i++) {
			copyNum.push_back(num[i]); 
		}
		int answer;
		int size = num.size();
		//first, line up vectors so that they have the same digits in the same places
		if (size > rVec.size()) {
			int extraDigits = size - rVec.size();
			for (int x = 0; x < extraDigits; x++) {
				rVec.insert(rVec.begin(), 0);
			}
		}
		else if (size < rVec.size()) {
			int extraDigits = rVec.size() - size;
			for (int x = 0; x < extraDigits; x++) {
				copyNum.insert(copyNum.begin(), 0);
			}
		}
		for (int i = (size - 1); i >= 0; i--) { //starts from end (single digit) 
			if (copyNum[i] < rVec[i]) { //if first operand's digit is smaller than second, carries over
				copyNum[i - 1] -= 1; //decrements left digit
				copyNum[i] += 10; //adds ten to current digit
			}
			answer = copyNum[i] - rVec[i]; //stores subtracted answer 
			ans.insert(ans.begin(), answer); 
		}
		temp.num = ans;
		temp.SIZE = ans.size();
		return temp;
	}

	BigNumbers BigNumbers::operator*(BigNumbers& right)
	{
		BigNumbers temp; //temp object to return 
		vector<int> rVec = right.num; 
		vector<int> copyNum; 
		for (int i = 0; i < num.size(); i++) {
			copyNum.push_back(num[i]); //stores num values into copyNum 
		}
		int rightSize = rVec.size(); //size of right vector
		int size = num.size(); //size of left vector
		vector<int> ans;
		vector<int> row; //represents a row of multiplication (will be added together at the end for total answer)
		int moveDigit = 0; 
		for (int i = rightSize - 1; i >= 0; i--) { //i refers to index of rVec
			row.clear(); //resets row vector
			for (int j = size - 1; j >= 0; j--) { //j refers to index of copyNum 
				int answer = copyNum[j] * rVec[i];
				row.insert(row.begin(),answer); //multiplies the entire top num by the first digit of bottom, then stores in row vector
			}
			if (ans.size() < row.size()) { //lines up row with ans vector
				int extraDigit = row.size() - ans.size();
				for (int x = 0; x < extraDigit; x++) {
					ans.insert(ans.begin(), 0);
				}
			}
			else if (ans.size() > row.size()) {
				int extraDigit = ans.size() - row.size();
				for (int x = 0; x < extraDigit; x++) {
					row.insert(row.begin(), 0);
				}
			}
			if (moveDigit != 0) {
				for (int i = 1; i <= moveDigit; i++) {
					row.push_back(0); 
					ans.insert(ans.begin(), 0); 
				}
			}
			//int newSize = row.size(); //stores size of row into newSize
			int answer; 
			for (int k = row.size() - 1; k >= 0; k--) {
				answer = ans[k] + row[k];
				ans.at(k) = answer; //increments row values to ans vector, repeats with each row created
				while (ans[k] > 9) { //carries over as needed
					if (k != 0) {
						ans[k - 1] += 1; 
						ans[k] -= 10; 
					}
					else { //if the carry over is needed at index 0
						ans.insert(ans.begin(), 0); 
						while (ans[1] > 9) {
							ans[0] += 1; 
							ans[1] -= 10; 
						}
					}
				}
			}
			moveDigit++; 
			while (ans[0] == 0) {
				ans.erase(ans.begin()); 
			}
		}
		temp.num = ans;
		temp.SIZE = ans.size();
		return temp;
	}

	BigNumbers BigNumbers::operator/(BigNumbers &right) //like a typical int, it will cut off decimals
	{
		//we are treating this as if it's long division
		BigNumbers temp;
		vector<int> rVec = right.num; //number we're dividing by 
		vector<int> copyNum; //number we're dividing
		for (int i = 0; i < num.size(); i++) {
			copyNum.push_back(num[i]); 
		}
		vector<int> ans;
		vector<int> divVec; //vec to divide with numerator for each step
		vector<int> remainder; 
		vector<int> multiplied; 
		int size = copyNum.size(); 
		if (copyNum.size() < rVec.size() || copyNum[0] == 0) { //check if right side is larger, then just return zero
			ans.push_back(0);
		}
		else {
			while (copyNum.size() >= rVec.size()) { //will keep going as long as there's still something to divide
				if (copyNum.size() < rVec.size() || copyNum[0] == 0) { //check if right side is larger, then just return zero
					break;
				}
				for (int i = 0; i < rVec.size(); i++) {
					divVec.push_back(copyNum[i]); //uses the first few digits of right to store into divVec, so that it's the same size as num
				}
				if (copyNum.size() > divVec.size()) {
					for (int i = 0; i < rVec.size(); i++) {
						if (rVec[i] > divVec[i]) { //if value of divVec is smaller, then add an extra digit
							divVec.push_back(copyNum[divVec.size()]);
							break;
						}
					}
				}
				//multiply and store digit until multiplied value is larger than denominator- this is the digit
				int digit = 2;
				int val;
				while (digit < 10) {
					multiplied.clear(); 
					for (int i = rVec.size() - 1; i >= 0; i--) { //multiplies by digit, stores in multiplied
						val = rVec[i] * digit;
						multiplied.insert(multiplied.begin(), val); 
					}
					for (int i = multiplied.size() - 1; i >= 0; i--) { //carries over digits that are over 9
						while (multiplied[i] > 9) {
							if (i > 0) {
								multiplied[i - 1] += 1; 
								multiplied[i] -= 10; 
							}
							else if (i == 0) {
								multiplied.insert(multiplied.begin(), 0); 
								while (multiplied[i+1] > 9) {
									multiplied[i] += 1; 
									multiplied[i+1] -= 10; 
								}
							}
						}
					}
					while (multiplied.size() != divVec.size()) { //lines up multiplied and divVec
						if (multiplied.size() > divVec.size()) {
							int extraDigit = multiplied.size() - divVec.size();
							for (int x = 0; x < extraDigit; x++) {
								divVec.insert(divVec.begin(), 0);
							}
						}
						else if (multiplied.size() < divVec.size()) {
							int extraDigit = divVec.size() - multiplied.size();
							for (int x = 0; x < extraDigit; x++) {
								multiplied.insert(multiplied.begin(), 0);
							}
						}
					}
					int index = 0;
					int sameDigit = 0; 
					for (int i = 0; i < multiplied.size(); i++) { //checks if digit is larger than corresponding, moves on unless it finds one
						index = i; //if multiplied is ever larger than divVec, the index is recorded and checked outside the loop
						if (multiplied[i] > divVec[i]) {
							break;
						}
						else if (multiplied[i] == divVec[i]) {
							sameDigit++; 
						}
					}
					if (multiplied[index] > divVec[index]) {
						break;
					}
					else if (sameDigit == multiplied.size()) {
						digit++;
						break; 
					}
					else { //if it didn't break out of the loop because multiplied was larger, then digit is incremented and loop repeated
						digit++;
					}
				}
				digit--; 
				ans.push_back(digit);
				multiplied.clear();
				while (divVec[0] == 0) {
					divVec.erase(divVec.begin()); 
				}
				for (int i = 0; i < rVec.size(); i++) { //multiplies by digit, stores in multiplied
					val = rVec[i] * (digit);
					multiplied.push_back(val);
				}
				for (int i = multiplied.size() - 1; i >= 0; i--) { //carries over digits that are over 9
					while (multiplied[i] > 9) {
						if (i > 0) {
							multiplied[i - 1] += 1;
							multiplied[i] -= 10;
						}
						else if (i==0) {
							multiplied.insert(multiplied.begin(), 0);
							while (multiplied[i+1] > 9) {
								multiplied[i] += 1;
								multiplied[i+1] -= 10;
							}
						}
					}
				}
				while (multiplied.size() != divVec.size()) { //lines up multiplied and divVec
					if (multiplied.size() > divVec.size()) {
						int extraDigit = multiplied.size() - divVec.size();
						for (int x = 0; x < extraDigit; x++) {
							divVec.insert(divVec.begin(), 0);
						}
					}
					else if (multiplied.size() < divVec.size()) {
						int extraDigit = divVec.size() - multiplied.size();
						for (int x = 0; x < extraDigit; x++) {
							multiplied.insert(multiplied.begin(), 0);
						}
					}
				}
				//int divVecSize = divVec.size(); 
				for (int i = divVec.size() - 1; i >= 0; i--) { //determines remainder 
					if (multiplied[i] <= divVec[i]) { //if top is larger than bottom or equal
						int value = divVec[i] - multiplied[i];
						remainder.insert(remainder.begin(), value);
					}
					else {
						divVec[i - 1] -= 1;
						divVec[i] += 10;
						int value = divVec[i] - multiplied[i];
						remainder.insert(remainder.begin(), value);
					}
				}
				//remainder.insert(remainder.begin(), divVec[0] - multiplied[0]); 
				while (divVec[0] == 0) {
					divVec.erase(divVec.begin());
				}
				for (int i = 0; i < divVec.size(); i++) { //gets rid of used digits from num divided
					copyNum.erase(copyNum.begin());
				}
				if (remainder.size() > 0) {
					while (remainder[0] == 0) { //gets rid of extra zeros
						remainder.erase(remainder.begin());
						if (remainder.size() == 0) {
							break; 
						}
					}
				}
				if (remainder.size() > 0) {
					for (int i = remainder.size() - 1; i >= 0; i--) { //stores remainder into num to divide
						copyNum.insert(copyNum.begin(), remainder[i]);
					}
				}
				remainder.clear();
				divVec.clear(); 
				rVec = right.num; 
				size = copyNum.size(); 
				int small = 0; 
				if (copyNum.size() == rVec.size()) {
					for (int i = 0; i < copyNum.size(); i++) {
						if (copyNum[i] < rVec[i]) {
							small++; 
							break;
						}
					}
				}
				if (small > 0) {
					break; 
				}
			}
		}
		temp.num = ans;
		temp.SIZE = ans.size();
		return temp;
	}

	BigNumbers BigNumbers::operator%(BigNumbers &right)
	{
		BigNumbers temp;
		vector<int> rVec = right.num; //number we're dividing by 
		vector<int> copyNum; //number we're dividing
		vector<int> multiplied; 
		vector<int> remainder; 
		vector<int> divVec; 
		for (int i = 0; i < num.size(); i++) {
			copyNum.push_back(num[i]);
		}
		vector<int> ans;
		if (copyNum.size() < rVec.size()) { //check if right side is larger, then just return zero
			for (int i = 0; i < copyNum.size(); i++) {
				ans.push_back(copyNum[i]); 
			}
		}
		else if (copyNum[0] == 0) {
			ans.push_back(0); 
		}
		else {
			while (copyNum.size() >= rVec.size() && ans.size() == 0) {
				for (int i = 0; i < rVec.size(); i++) {
					divVec.push_back(copyNum[i]); //uses the first few digits of right to store into divVec, so that it's the same size as num
				}
				if (copyNum.size() > divVec.size()) {
					for (int i = 0; i < rVec.size(); i++) {
						if (rVec[i] > divVec[i]) { //if value of divVec is smaller, then add an extra digit
							divVec.push_back(copyNum[divVec.size()]);
							break;
						}
					}
				}
				int digit = 2;
				int val;
				while (digit < 10) {
					multiplied.clear();
					for (int i = rVec.size() - 1; i >= 0; i--) { //multiplies by digit, stores in multiplied
						val = rVec[i] * digit;
						multiplied.insert(multiplied.begin(), val);
					}
					for (int i = multiplied.size() - 1; i >= 0; i--) { //carries over digits that are over 9
						while (multiplied[i] > 9) {
							if (i > 0) {
								multiplied[i - 1] += 1;
								multiplied[i] -= 10;
							}
							else if (i == 0) {
								multiplied.insert(multiplied.begin(), 0);
								while (multiplied[i + 1] > 9) {
									multiplied[i] += 1;
									multiplied[i+1] -= 10;
								}
							}
						}
					}
					while (multiplied.size() != divVec.size()) { //lines up multiplied and divVec
						if (multiplied.size() > divVec.size()) {
							int extraDigit = multiplied.size() - divVec.size();
							for (int x = 0; x < extraDigit; x++) {
								divVec.insert(divVec.begin(), 0);
							}
						}
						else if (multiplied.size() < divVec.size()) {
							int extraDigit = divVec.size() - multiplied.size();
							for (int x = 0; x < extraDigit; x++) {
								multiplied.insert(multiplied.begin(), 0);
							}
						}
					}
					int index = 0;
					int sameDigit = 0;
					for (int i = 0; i < multiplied.size(); i++) { //checks if digit is larger than corresponding, moves on unless it finds one
						index = i; //if multiplied is ever larger than divVec, the index is recorded and checked outside the loop
						if (multiplied[i] > divVec[i]) {
							break;
						}
						else if (multiplied[i] == divVec[i]) {
							sameDigit++;
						}
					}
					if (multiplied[index] > divVec[index]) {
						break;
					}
					else if (sameDigit == multiplied.size()) {
						digit++;
						break;
					}
					else { //if it didn't break out of the loop because multiplied was larger, then digit is incremented and loop repeated
						digit++;
					}
				}
				digit--;
				multiplied.clear();
				for (int i = 0; i < rVec.size(); i++) { //multiplies by digit, stores in multiplied
					val = rVec[i] * (digit);
					multiplied.push_back(val);
				}
				for (int i = multiplied.size() - 1; i >= 0; i--) { //carries over digits that are over 9
					while (multiplied[i] > 9) {
						if (i > 0) {
							multiplied[i - 1] += 1;
							multiplied[i] -= 10;
						}
						else if (i == 0) {
							multiplied.insert(multiplied.begin(), 0);
							while (multiplied[i + 1] > 9) {
								multiplied[i] += 1;
								multiplied[i + 1] -= 10;
							}
						}
					}
				}
				while (multiplied.size() < divVec.size()) {
					multiplied.insert(multiplied.begin(), 0); 
				}
				int divVecSize = divVec.size();
				for (int i = divVecSize - 1; i > 0; i--) { //determines remainder 
					if (multiplied[i] <= divVec[i]) { //if top is larger than bottom or equal
						int value = divVec[i] - multiplied[i];
						remainder.insert(remainder.begin(), value);
					}
					else {
						divVec[i - 1] -= 1;
						divVec[i] += 10;
						int value = divVec[i] - multiplied[i];
						remainder.insert(remainder.begin(), value);
					}
				}
				remainder.insert(remainder.begin(), divVec[0] - multiplied[0]);
				while (divVec[0] == 0) {
					divVec.erase(divVec.begin()); 
				}
				for (int i = 0; i < divVec.size(); i++) { //gets rid of used digits from num divided
					copyNum.erase(copyNum.begin());
				}
				if (remainder.size() > 0) {
					while (remainder[0] == 0) { //gets rid of extra zeros
						remainder.erase(remainder.begin());
						if (remainder.size() == 0) {
							break;
						}
					}
				}
				if (remainder.size() > 0) {
					for (int i = remainder.size() - 1; i >= 0; i--) { //stores remainder into num to divide
						copyNum.insert(copyNum.begin(), remainder[i]);
					}
				}
				remainder.clear();
				divVec.clear();
				rVec = right.num;
				if (copyNum.size() < rVec.size()) { //check if right side is larger, then just return zero
					for (int i = 0; i < copyNum.size(); i++) {
						ans.push_back(copyNum[i]);
					}
					break;
				} //check if value itself is smaller
				else if (copyNum[0] == 0) {
					ans.push_back(0);
					break; 
				}
				else if (copyNum.size() == rVec.size()) {
					for (int i = 0; i < copyNum.size(); i++) {
						if (copyNum[i] < rVec[i]) {
							for (int j = 0; j < copyNum.size(); j++) {
								ans.push_back(copyNum[j]);
							}
							break;
						}
					}
				}
				if (ans.size() > 0) {
					break;
				}
			}
		}
		temp.num = ans; 
		temp.SIZE = ans.size(); 
		return temp; 
	}

	BigNumbers::BigNumbers(const string& s)
	{
		//string::iterator iter; 
		if (s.length() <= 10000) {
			for (unsigned int i = 0; i< s.length(); i++) {
				char c = s[i]; //this is your character
				int elem = c - '0'; 
				num.push_back(elem); 
			}
			SIZE = num.size();
		}
	}

	BigNumbers::BigNumbers()
	{
	}

	void BigNumbers::setNum(const string& s)
	{
		if (s.length() <= 10000) {
			for (unsigned int i = 0; i< s.length(); i++) {
				char c = s[i]; //this is your character
				int elem = c - '0'; 
				num.push_back(elem); 
			}
			SIZE = num.size();
		}
	}

	int BigNumbers::getSize()
	{
		return SIZE;
	}

	vector<int> BigNumbers::getNum()
	{
		return num;
	}
}
