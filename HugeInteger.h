#pragma once
#include<fstream>
#include<vector>
using namespace std;
class HugeInteger
{
	vector<int> Ds;
	bool isNeg;
	void trim();
public:
	void initializeFromString(const std::string& val);
	HugeInteger();
	HugeInteger(int s);
	HugeInteger(const HugeInteger &);
	HugeInteger(ifstream &rdr);

	const HugeInteger& operator=(const HugeInteger&);
	int& ithDigit(int i);
	int ithDigit(int i)const;
	int& operator[](int i);
	int operator[](int i) const;

	HugeInteger ADDQuantityWise(const HugeInteger& H2) const;
	HugeInteger SUBQuantityWise(const HugeInteger& H2) const;
	bool LessThanQuantityWise(const HugeInteger& H2) const;
	bool GreaterThanQuantityWise(const HugeInteger& H2) const;
	bool EqualQuantityWise(const HugeInteger& H2) const;

	HugeInteger& operator++();  
	HugeInteger operator++(int);
	HugeInteger& operator--();  
	HugeInteger operator--(int);

	HugeInteger operator+(const HugeInteger& H2) const;
	HugeInteger& operator+=(const HugeInteger& H2);
	HugeInteger operator-(const HugeInteger& H2) const;
	HugeInteger& operator-=(const HugeInteger& H2);
	bool operator!=(const HugeInteger& H2) const;
	bool operator<(const HugeInteger& H2) const;
	bool operator<=(const HugeInteger& H2) const;
	bool operator>(const HugeInteger& H2) const;
	bool operator>=(const HugeInteger& H2) const;
	bool operator==(const HugeInteger& H2) const;
	HugeInteger operator*(const HugeInteger& H2) const;
	HugeInteger& operator*=(const HugeInteger& H2);
	HugeInteger operator/(const HugeInteger& H2) const;
	HugeInteger& operator/=(const HugeInteger& H2);
	HugeInteger operator%(const HugeInteger& H2) const;
	HugeInteger& operator%=(const HugeInteger& H2);
	HugeInteger operator-() const;
	friend ostream& operator<<(ostream&, const HugeInteger&);
	friend istream& operator>>(istream&, HugeInteger&);
};

