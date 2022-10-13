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
    //false -
    //true  +
    bool n1_sign=false;
    bool n2_sign=false;
    if(isdigit(s[0])||s[0]=='+'){
        n1_sign=true;
    }else n1_sign=false;
    if(isdigit(anotherDec.s[0])||anotherDec.s[0]=='+'){
        n2_sign=true;
    }else n2_sign=false;
    if(n2_sign&&n1_sign) {
        string cpyS=s;
        if(cpyS[0]=='+')cpyS.erase(cpyS.begin());
        string y=anotherDec.s;
        if(anotherDec.s[0]=='+')y.erase(y.begin());
        int len = cpyS.size() > y.size() ? (int) cpyS.size() : (int) y.size();
        int n_zeros = abs((int) cpyS.size() - (int) y.size());
        int carry = 0;
        string q;
        string zeros(n_zeros, '0');
        q += zeros;
        if (cpyS.size() >= y.size()) {
            q += y;
        } else {
            q += cpyS;
        }
        deque<int> dq;
        for (int i = len - 1; i >= 0; i--) {
            int sum = (int)(cpyS[i] - '0') + (int)(q[i] - '0') + carry;
            if (sum > 9) {
                carry = 1;
                dq.push_front(sum % 10);
            } else {
                carry = 0;
                dq.push_front(sum);
            }
        }
        if (carry)dq.push_front(carry);
        string str;
        for (int i: dq) {
            str += char((char) i + '0');
        }
        BigDecimalInt rtrn(str);
        return rtrn;
    }
        //Next statement will print 236913578023691357802369135780
    else if(!n2_sign&&!n1_sign){
        string s_cpy=s;
        s_cpy.erase(s_cpy.begin());
        string y=anotherDec.s;
        y.erase(y.begin());
        int len = s_cpy.size() > y.size() ? (int) s_cpy.size() : (int) y.size();
        int n_zeros = abs((int) s_cpy.size() - (int) y.size());
        int carry = 0;
        string q;
        string zeros(n_zeros, '0');
        q += zeros;
        if (s_cpy.size() >= y.size()) {
            q += y;
        } else {
            q += s_cpy;
        }
        deque<int> dq;
        for (int i = len - 1; i >= 0; i--) {
            int sum = (s_cpy[i] - '0') + (q[i] - '0') + carry;
            if (sum > 9) {
                carry = 1;
                dq.push_front(sum % 10);
            } else {
                carry = 0;
                dq.push_front(sum);
            }
        }
        if (carry)dq.push_front(carry);
        string str="-";
        for (int i: dq) {
            str += char((char) i + '0');
        }
        BigDecimalInt rtrn(str);
        return rtrn;
    }

    else if(n1_sign && !n2_sign){
        string y=anotherDec.s;
        y.erase(y.begin());
        if(s[0]=='+')s.erase(s.begin());
        int sign=false;

        int n_zeros = abs((int) s.size() - (int) y.size());
        string q;
        string zeros(n_zeros, '0');
        q += zeros;

        if(s>y){
            sign=true;
        }else sign=false;

        if (s.size() > y.size()) {
            q += y;
        } else if(s.size()==y.size()){
            if(sign)q=y;
            else q=s;
        }
        else {
            q += s;
        }

        if(sign){
            //s-y
            //y=q
            vector<int>v((int)s.size(),0);
            for(int i=(int)s.size()-1;i>=0;i--){
                if(s[i]+v[i]>=q[i]){
                    v[i]+=(s[i]-'0')-(q[i]-'0');
                }
                else{
                    v[i]+=(s[i]-'0')+10-(q[i]-'0');
                    v[i-1]--;
                }
            }
            string str;
            for (int i: v) {
                str += char((char) i + '0');
            }
            BigDecimalInt rtrn(str);
            return rtrn;
        }
        else{
            //y-s
            //s=q
            vector<int>v((int)s.size(),0);
            for(int i=(int)s.size()-1;i>=0;i--){
                if(y[i]+v[i]>=q[i]){
                    v[i]+=(y[i]-'0')-(q[i]-'0');
                }
                else{
                    v[i]+=(y[i]-'0')+10-(q[i]-'0');
                    v[i-1]--;
                }
            }
            string str="-";
            for (int i: v) {
                str += char((char) i + '0');
            }
            BigDecimalInt rtrn(str);
            return rtrn;
        }
    }
    else if(!n1_sign && n2_sign){
        string y=s;
        y.erase(y.begin());

        string anotherS=anotherDec.s;
        if(anotherS[0]=='+')anotherS.erase(anotherS.begin());
        int sign=false;

        int n_zeros = abs((int) s.size() - (int) y.size());
        string q;
        string zeros(n_zeros, '0');
        q += zeros;

        if(anotherS>y){
            sign=true;
        }else sign=false;

        if (anotherS.size() > y.size()) {
            q += y;
        } else if(anotherS.size()==y.size()){
            if(sign)q=y;
            else q=anotherS;
        }
        else {
            q += s;
        }

        if(sign){
            //  anotherS-y
            //q=y
            vector<int>v((int)y.size(),0);
            for(int i=(int)y.size()-1;i>=0;i--){
                if(anotherS[i]+v[i]>=q[i]){
                    v[i]+=(anotherS[i]-'0')-(q[i]-'0');
                }
                else{
                    v[i]+=(anotherS[i]-'0')+10-(q[i]-'0');
                    v[i-1]--;
                }
            }
            string str;
            for (int i: v) {
                str += char((char) i + '0');
            }
            BigDecimalInt rtrn(str);
            return rtrn;
        }
        else{
            //y-anotherS
            //q=anotherS
            vector<int>v((int)y.size(),0);
            for(int i=(int)y.size()-1;i>=0;i--){
                if(y[i]+v[i]>=q[i]){
                    v[i]+=(y[i]-'0')-(q[i]-'0');
                }
                else{
                    v[i]+=(y[i]-'0')+10-(q[i]-'0');
                    v[i-1]--;
                }
            }
            string str="-";
            for (int i: v) {
                str += char((char) i + '0');
            }
            BigDecimalInt rtrn(str);
            return rtrn;
        }
    }
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


