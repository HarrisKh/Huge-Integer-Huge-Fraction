#pragma once
#include "HugeInteger.h"
#include <iostream>
#include <string>
using namespace std;
class HugeFraction
{
	HugeInteger numerator;
	HugeInteger denominator;
	void normalize();
	void reduce();
	HugeInteger gcd(HugeInteger a, HugeInteger b) const;
public:
	HugeFraction();
	HugeFraction(const HugeInteger& n);
	HugeFraction(const HugeInteger& n, const HugeInteger& d);
	HugeFraction(const HugeFraction& F);
	const HugeFraction& operator=(const HugeFraction& F);  
	HugeFraction operator+(const HugeFraction& F2) const;
	HugeFraction operator-(const HugeFraction& F2) const;
	HugeFraction operator*(const HugeFraction& F2) const;
	HugeFraction operator/(const HugeFraction& F2) const;
	HugeFraction& operator+=(const HugeFraction& F2);
	HugeFraction& operator-=(const HugeFraction& F2);
	HugeFraction& operator*=(const HugeFraction& F2);
	HugeFraction& operator/=(const HugeFraction& F2);

	bool operator==(const HugeFraction& F2)const;
	bool operator!=(const HugeFraction& F2)const;
	bool operator<(const HugeFraction& F2)const;
	bool operator<=(const HugeFraction& F2)const;
	bool operator>(const HugeFraction& F2)const;
	bool operator>=(const HugeFraction& F2)const;
	HugeFraction operator-() const;
	void fromDecimalString(const string& s);
	friend ostream& operator<<(ostream&, const HugeFraction&);
	friend istream& operator>>(istream&, HugeFraction&);
};

