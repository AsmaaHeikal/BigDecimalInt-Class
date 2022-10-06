#include "BigDecimalInt_functions.h"

bool valid (const string& str)
{
    regex valid("[+-]?[0-9]+");
    return regex_match(str, valid);
}

BigDecimalInt::BigDecimalInt (const string& decStr){
    if(valid(decStr)){
        s=decStr;
    }else{
        cout<<"Bad format!!\n";
        EXIT_FAILURE;
    }
}
BigDecimalInt ::BigDecimalInt(int decInt){
    s=to_string(decInt);
}
BigDecimalInt BigDecimalInt::operator+ (const BigDecimalInt& anotherDec){
    int len=s.size()>anotherDec.s.size()?(int)s.size():(int)anotherDec.s.size();
    int n_zeros=abs((int)s.size()-(int)anotherDec.s.size());
    int carry=0;
    string q;
    string zeros(n_zeros,'0');
    q+=zeros;
    if(s.size()>anotherDec.s.size()){
        q+=anotherDec.s;
    }
    else{
        q+=s;
    }
    deque<int>dq;
    for(int i=len-1;i>=0;i--){
        int sum=(s[i]-'0')+(q[i]-'0')+carry;
        if(sum>9){
            carry=1;
            dq.push_front(sum%10);
        }
        else{
            carry=0;
            dq.push_front(sum);
        }
    }
    if(carry)dq.push_front(carry);
    string str;
    for(int i:dq){
        str+=char((char)i+'0');
    }
    BigDecimalInt rtrn(str);
    return rtrn;
}
BigDecimalInt BigDecimalInt::operator- (const BigDecimalInt& anotherDec){

}
bool BigDecimalInt::operator< (const BigDecimalInt& anotherDec){

}
bool BigDecimalInt::operator> (const BigDecimalInt& anotherDec){

}
bool BigDecimalInt::operator==(const BigDecimalInt& anotherDec){

}
BigDecimalInt& BigDecimalInt:: operator= (const BigDecimalInt& anotherDec){

}
int BigDecimalInt::size(){

}
int BigDecimalInt::sign(){}

ostream &operator << (ostream& out, const BigDecimalInt& b){

}