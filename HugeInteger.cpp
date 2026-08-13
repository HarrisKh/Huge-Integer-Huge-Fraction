#include "HugeInteger.h"
#include<string>
using namespace std;

void HugeInteger::trim()
{
    while (Ds.size() > 1 and Ds.back() == 0)
        Ds.pop_back();
    if (Ds.size() == 1 and Ds[0] == 0)
        isNeg = false;
}

HugeInteger::HugeInteger()
{
    Ds.push_back(0);
    isNeg = false;
}

HugeInteger::HugeInteger(int s)
{
    if (s <= 0) 
        s = 1;
    Ds.assign(s, 0);
    isNeg = false;
}

HugeInteger::HugeInteger(const HugeInteger& H)
{
    Ds = H.Ds;
    isNeg = H.isNeg;
}

HugeInteger::HugeInteger(ifstream& rdr) {
    string val;
    rdr >> val;
    initializeFromString(val);
}

const HugeInteger& HugeInteger::operator=(const HugeInteger& H) {
    if (this != &H) {
        Ds = H.Ds;
        isNeg = H.isNeg;
    }
    return *this;
}

void HugeInteger::initializeFromString(const string& val) 
{
    Ds.clear();
    isNeg = false;
    int start = 0;
    if (val.length() > 0 and val[0] == '-') {
        isNeg = true;
        start = 1;
    }
    else if (val.length() > 0 and val[0] == '+') {
        start = 1;
    }

    int end = start;
    while (end < val.length() and val[end] == '0') {
        end++;
    }

    string trimmedStr = val.substr(end);
    if (trimmedStr.empty()) {
        Ds.push_back(0);
        isNeg = false;
        return;
    }
    for (int i = trimmedStr.length() - 1; i >= 0; i--) {
        Ds.push_back(trimmedStr[i] - '0');
    }
}

int& HugeInteger::ithDigit(int i)
{
 
    return Ds[i];
}

int HugeInteger::ithDigit(int i)const
{
    if (i < Ds.size()) {
        return Ds[i];
    }
    return 0;
}

int& HugeInteger::operator[](int i)
{
    return Ds[i];
}

int HugeInteger::operator[](int i) const
{
    return Ds[i];
}

HugeInteger HugeInteger::ADDQuantityWise(const HugeInteger& H2) const
{
    int maxSize = max(Ds.size(), H2.Ds.size());
    HugeInteger res(maxSize);
    int carry = 0;

    for (int i = 0; i < maxSize; i++) {
        int sum = ithDigit(i) + H2.ithDigit(i) + carry;
        res.Ds[i] = sum % 10;
        carry = sum / 10;
    }
    if (carry > 0) {
        res.Ds.push_back(carry);
    }
    res.trim();
    return res;
}

HugeInteger HugeInteger::SUBQuantityWise(const HugeInteger& H2) const
{
    HugeInteger res(Ds.size());
    int borrow = 0;

    for (int i = 0; i < Ds.size(); i++) {
        int diff = ithDigit(i) - H2.ithDigit(i) - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        res.Ds[i] = diff;
    }
    res.trim();
    return res;
}
bool HugeInteger::EqualQuantityWise(const HugeInteger& H2) const
{
    if (Ds.size() != H2.Ds.size()) 
        return false;
    for (int i = 0; i < Ds.size(); i++) {
        if (Ds[i] != H2.Ds[i]) 
            return false;
    }
    return true;
}
HugeInteger& HugeInteger::operator++()
{
    HugeInteger a;
    a.initializeFromString("1");
    *this = *this + a;
    return *this;
}
HugeInteger HugeInteger::operator++(int)
{
    HugeInteger temp = *this;
    ++(*this);
    return temp;
}
HugeInteger& HugeInteger::operator--()
{
    HugeInteger one;
    one.initializeFromString("1");
    *this = *this - one;
    return *this;
}
HugeInteger HugeInteger::operator--(int) 
{
    HugeInteger temp = *this;
    --(*this);
    return temp;
}
bool HugeInteger::LessThanQuantityWise(const HugeInteger& H2) const
{
    if (Ds.size() < H2.Ds.size())
        return true;
    if (Ds.size() > H2.Ds.size())
        return false;
    for (int i = Ds.size() - 1; i >= 0; i--) {
        if (Ds[i] < H2.Ds[i])
            return true;
        if (Ds[i] > H2.Ds[i])
            return false;
    }
    return false;
}
bool HugeInteger::GreaterThanQuantityWise(const HugeInteger& H2) const 
{
    return !LessThanQuantityWise(H2) and !EqualQuantityWise(H2);
}
ostream& operator<<(ostream&os, const HugeInteger&H)
{
    if (H.isNeg) {
        os << '-';
    }
    for (int i = H.Ds.size() - 1; i >= 0; i--) {
        os << H.Ds[i];
    }
    return os;
}
istream& operator>>(istream& is, HugeInteger& H) {
    string val;
    is >> val;
    H.initializeFromString(val);
    return is;
}

HugeInteger HugeInteger::operator+(const HugeInteger& H2) const
{
        HugeInteger res;
        if (isNeg == H2.isNeg) {
            res = ADDQuantityWise(H2);
            res.isNeg = isNeg;
        }
        else {
            if (GreaterThanQuantityWise(H2)) {
                res = SUBQuantityWise(H2);
                res.isNeg = isNeg;
            }
            else if (LessThanQuantityWise(H2)) {
                res = H2.SUBQuantityWise(*this);
                res.isNeg = H2.isNeg;
            }
            else {
                res = HugeInteger();
            }
        }
        if (res.Ds.size() == 1 and res.Ds[0] == 0)
            res.isNeg = false;
        return res;
    
}
HugeInteger& HugeInteger::operator+=(const HugeInteger& H2)
{
    *this = *this + H2;
    return *this;
}
HugeInteger HugeInteger::operator-(const HugeInteger& H2) const
{
    HugeInteger temp = H2;
    if (!(temp.Ds.size() == 1 and temp.Ds[0] == 0)) {
        temp.isNeg = !temp.isNeg;
    }
    return *this + temp;
}
HugeInteger& HugeInteger::operator-=(const HugeInteger& H2) 
{
    *this = *this - H2;
    return *this;
}

bool HugeInteger::operator!=(const HugeInteger& H2) const
{
    return !(*this == H2);
}

bool HugeInteger::operator<(const HugeInteger& H2) const
{
    if (isNeg and !H2.isNeg)
        return true;
    if (!isNeg and H2.isNeg)
        return false;
    if (isNeg) {
        return GreaterThanQuantityWise(H2);
    }
    else {
        return LessThanQuantityWise(H2);
    }
}
bool HugeInteger::operator<=(const HugeInteger& H2) const
{
    return (*this < H2) or (*this == H2);
}

bool HugeInteger::operator>(const HugeInteger& H2) const
{
    return !(*this <= H2);
}
bool HugeInteger::operator>=(const HugeInteger& H2) const
{
    return !(*this < H2);
}

bool HugeInteger::operator==(const HugeInteger& H2) const
{
    return isNeg == H2.isNeg and EqualQuantityWise(H2);
}

HugeInteger HugeInteger::operator*(const HugeInteger& H2) const
{
    HugeInteger a = *this;
    HugeInteger b = H2;
    HugeInteger res;

    HugeInteger zero;
    zero.initializeFromString("0");

    HugeInteger two;
    two.initializeFromString("2");
    while (b > zero){
        if (b.Ds[0] % 2 == 1){
            res += a;
        }
        a += a;
        b /= two;
    }

    res.isNeg = (isNeg != H2.isNeg);
    res.trim();
    return res;
}

HugeInteger& HugeInteger::operator*=(const HugeInteger& H2)
{
    *this = *this * H2;
    return *this;
}

HugeInteger HugeInteger::operator/(const HugeInteger& H2) const
{
    HugeInteger dividend = *this;
    HugeInteger divisor = H2;
    HugeInteger zero;
    zero.initializeFromString("0");
    HugeInteger one;
    one.initializeFromString("1");

    HugeInteger quotient;
    if (divisor == zero){
        throw runtime_error("Division by zero");
    }
    while (dividend >= divisor){
        dividend -= divisor;
        quotient += one;
    }
    quotient.isNeg = (isNeg != H2.isNeg);
    quotient.trim();

    return quotient;
}
HugeInteger& HugeInteger::operator/=(const HugeInteger& H2)
{
    *this = *this / H2;
    return *this;
}
HugeInteger HugeInteger::operator%(const HugeInteger& H2) const
{
    HugeInteger dividend = *this;
    HugeInteger divisor = H2;
    while (dividend >= divisor){
        dividend -= divisor;
    }

    dividend.trim();
    return dividend;
}
HugeInteger& HugeInteger::operator%=(const HugeInteger& H2)
{
    *this = *this % H2;
    return *this;
}
HugeInteger HugeInteger::operator-() const
{
    HugeInteger res = *this;
    if (!(res.Ds.size() == 1 and res.Ds[0] == 0)) {
        res.isNeg = res.isNeg*-1;
    }
    return res;
}

