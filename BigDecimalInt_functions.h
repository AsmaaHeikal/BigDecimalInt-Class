#ifndef BIGDECIMALINT_CLASS_BIGDECIMALINT_FUNCTIONS_H
#define BIGDECIMALINT_CLASS_BIGDECIMALINT_FUNCTIONS_H

#include <bits/stdc++.h>
using namespace std;

class BigDecimalInt{
private:
    string s;
public:
    explicit  BigDecimalInt (const string& decStr);
    explicit BigDecimalInt (int decInt);
    BigDecimalInt operator+ (const BigDecimalInt& anotherDec);
    BigDecimalInt operator- (const BigDecimalInt& anotherDec);
    bool operator< (const BigDecimalInt& anotherDec);
    bool operator> (const BigDecimalInt& anotherDec);
    bool operator==(const BigDecimalInt& anotherDec);
    BigDecimalInt& operator= (const BigDecimalInt& anotherDec);
    int size();
    int sign();
    friend ostream& operator << (ostream& out, const BigDecimalInt& b);
};

#endif //BIGDECIMALINT_CLASS_BIGDECIMALINT_FUNCTIONS_H
