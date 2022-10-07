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
        if(s[0]=='+')s.erase(s.begin());
        string y=anotherDec.s;
        if(anotherDec.s[0]=='+')y.erase(y.begin());
        int len = s.size() > y.size() ? (int) s.size() : (int) y.size();
        int n_zeros = abs((int) s.size() - (int) y.size());
        int carry = 0;
        string q;
        string zeros(n_zeros, '0');
        q += zeros;
        if (s.size() > y.size()) {
            q += y;
        } else {
            q += s;
        }
        deque<int> dq;
        for (int i = len - 1; i >= 0; i--) {
            int sum = (s[i] - '0') + (q[i] - '0') + carry;
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
        if (s_cpy.size() > y.size()) {
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
            //anotherS-y
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