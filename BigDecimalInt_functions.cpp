#include "BigDecimalInt_functions.h"

bool valid (const string& str)
{
    regex valid("[+-]?[0-9]+");
    return regex_match(str, valid);
}

//____________________________________________________________________________________________________
string BigDecimalInt:: getS(){
    return s;
}

//____________________________________________________________________________________________________
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
BigDecimalInt ::BigDecimalInt() {} //default empty constructor

//____________________________________________________________________________________________________
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

//____________________________________________________________________________________________________
BigDecimalInt BigDecimalInt::operator- (const BigDecimalInt& anotherDec){
    BigDecimalInt finalNum ;
    string num1 , num2;
    num1 = s;
    num2 = anotherDec.s;
    bool flag1 = 1, flag2 =1, sign = 1;

    if((num1[0] == '+') ||  (num1[0] == '-')){
        if(num1[0] == '-')
            flag1 = 0;
        num1.erase(num1.begin());
    }
    if((num2[0] == '+') || (num2[0] == '-')){
        if (num2[0] == '-')
            flag2 =0;
        num2.erase(num2.begin());

    }

    if(flag1 && flag2 && num2 > num1 ){
        swap(num2, num1);
        sign = 0;
    }
    else if(flag1 && ! flag2){

        BigDecimalInt x (num1);
        BigDecimalInt y (num2);

        if(y.s.size() < x.s.size() ) {
            finalNum.s = (x+y).s;
        }
        else{
            finalNum.s = (y+x).s;
        }
        return finalNum;
    }
    else if(!flag1 && flag2) {

        BigDecimalInt x (num1);
        BigDecimalInt y (num2);

        if(y.s.size() < x.s.size() ) {
            finalNum.s = (x+y).s;
        }
        else{
            finalNum.s = (y+x).s;
        }
        finalNum.s = '-' +finalNum.s ;
        return finalNum;
    }
    else if( !flag1 && !flag2){
       string temp = num1 ;
        num1 = num2 ;
        num2 = temp;
    }

    ll numOfZeroes = abs((int)s.size()- (int)anotherDec.s.size());
    string zeroes (numOfZeroes, '0');
    if( num1.size() < num2.size()){
        num1 = zeroes + num1;
    }
    else if( num1.size() > num2.size()){

        num2 = zeroes + num2 ;
    }

    deque <int> ans;
    int carry =0;
    for(int i = num1.size()-1 ; i>-1 ; i--){
        int x = num1[i]-'0';
        int y = num2[i]-'0';

        if(x>= y){

           ans.push_front((x- y+ carry)%10 );
            carry = (x-y+carry)/10;
        }
        else {

            for(int j = i-1 ; j > -1 ; j -- ){
                if(num1[j] != '0'){
                    x += 10;
                    int temp = num1[j] -'0' -1;
                    num1[j] =char (temp +'0' );
                }
                else{
                    num1[j] = '9';
                }

            }
            ans.push_front((x- y+ carry)%10 );
            carry = (x-y+carry)/10;
        }
    }

    for(int x : ans){
        finalNum.s += char(x+'0');
    }
    if(!sign){
        finalNum.s = '-' + finalNum.s ;
    }

    return finalNum;

}


//____________________________________________________________________________________________________


bool BigDecimalInt::operator< (const BigDecimalInt& anotherDec){
    if(s.size() > anotherDec.s.size()){
        return false;
    }
    else if( anotherDec.s.size() > s.size()){
        return true;
    }
    else{
        for(int i = 0 ; i < anotherDec.s.size() ; i++){
            if(anotherDec.s[i] > s[i]){
                return true;
            }
            else if(anotherDec.s[i] < s[i]){
                return false;
            }
        }
    }
    return false ;

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


