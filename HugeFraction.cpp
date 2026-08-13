#include "HugeFraction.h"

void HugeFraction::normalize()
{
	HugeInteger zero;
	zero.initializeFromString("0");
	if (denominator < zero){
		numerator = -numerator;
		denominator = -denominator;
	}
}
void HugeFraction::reduce()
{
	HugeInteger g = gcd(numerator, denominator);
	numerator /= g;
	denominator /= g;
}
HugeInteger HugeFraction::gcd(HugeInteger a, HugeInteger b) const
{
	HugeInteger zero;
	zero.initializeFromString("0");
	if (a < zero)
		a = -a;
	if (b < zero)
		b = -b;
	while (a != b) {
		if (a > b)
			a -= b;
		else
			b -= a;
	}
	return a;
}
HugeFraction::HugeFraction()
{
	numerator = HugeInteger();
	denominator = HugeInteger();
	denominator.initializeFromString("1");
}

HugeFraction::HugeFraction(const HugeInteger& n)
{
	numerator = n;
	denominator.initializeFromString("1");
}

HugeFraction::HugeFraction(const HugeInteger& n, const HugeInteger& d)
{
	numerator = n;
	denominator = d;
	normalize();
	reduce();
}

HugeFraction::HugeFraction(const HugeFraction& F)
{
	numerator = F.numerator;
	denominator = F.denominator;
}

const HugeFraction& HugeFraction::operator=(const HugeFraction& F)
{
	if (this != &F) {
		numerator = F.numerator;
		denominator= F.denominator;
	}
	return *this;
}

HugeFraction HugeFraction::operator+(const HugeFraction& F2) const
{
	HugeInteger n =this->numerator * F2.denominator +F2.numerator * this->denominator;
	HugeInteger d =this->denominator * F2.denominator;
	return HugeFraction(n, d);
}

HugeFraction HugeFraction::operator-(const HugeFraction& F2) const
{
	HugeInteger n = this->numerator * F2.denominator - F2.numerator * this->denominator;
	HugeInteger d = this->denominator * F2.denominator;
	return HugeFraction(n, d);
}
HugeFraction HugeFraction::operator*(const HugeFraction& F2) const
{
	HugeInteger n = numerator * F2.numerator;
	HugeInteger d = denominator * F2.denominator;
	return HugeFraction(n, d);
}

HugeFraction HugeFraction::operator/(const HugeFraction& F2) const
{
	HugeInteger n = numerator * F2.denominator;
	HugeInteger d = denominator * F2.numerator;
	return HugeFraction(n, d);
}

HugeFraction& HugeFraction::operator+=(const HugeFraction& F2)
{
	*this = *this + F2;
	return *this;
}

HugeFraction& HugeFraction::operator-=(const HugeFraction& F2)
{
	*this = *this - F2;
	return *this;
}

HugeFraction& HugeFraction::operator*=(const HugeFraction& F2)
{
	*this = *this * F2;
	return *this;
}

HugeFraction& HugeFraction::operator/=(const HugeFraction& F2)
{
	*this = *this /F2;
	return *this;
}
bool HugeFraction::operator==(const HugeFraction& F2) const
{
	return this->numerator * F2.denominator ==F2.numerator *this-> denominator;
}

bool HugeFraction::operator!=(const HugeFraction& F2) const
{
	return !(*this==F2);
}

bool HugeFraction::operator<(const HugeFraction& F2) const
{
	return this->numerator * F2.denominator < F2.numerator * this->denominator;
}
bool HugeFraction::operator<=(const HugeFraction& F2) const
{
	return (*this < F2) or (*this == F2);
}
bool HugeFraction::operator>(const HugeFraction& F2) const
{
	return !(*this <= F2);
}
bool HugeFraction::operator>=(const HugeFraction& F2) const
{
	return !(*this < F2);
}

HugeFraction HugeFraction::operator-() const
{
	return HugeFraction(-numerator, denominator);
}

void HugeFraction::fromDecimalString(const string& s)
{
	int pos = s.find('.');
	if (pos == -1){
		numerator.initializeFromString(s);
		denominator.initializeFromString("1");
		return;
	}
	string intPart = s.substr(0, pos);
	string fracPart = s.substr(pos + 1);
	string com = intPart + fracPart;
	numerator.initializeFromString(com);
	string d = "1";
	for (int i = 0; i < fracPart.length(); i++) {
		d += "0";
	}
	denominator.initializeFromString(d);
	
}

ostream& operator<<(ostream& os, const HugeFraction&F)
{
	os << F.numerator << "/" << F.denominator;
	return os;
}
istream& operator>>(istream& is, HugeFraction& F)
{
	string s;
	is >> s;
	F.fromDecimalString(s);
	return is;
}
