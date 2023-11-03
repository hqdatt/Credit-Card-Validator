#include<iostream>

using namespace std;

int get_size(long number);
int oddSum(long cardNumber);
int evenSum(long cardNumber);
int get_digit(int number);
bool matchedPrefix(long cardNumber, int k);
bool isValid(long  cardNumber);
string bankCard(long cardNumber);

int main()
{
    long cardNumber;
    cout<<"Enter credit card number here: "; cin>>cardNumber;
    cout<<cardNumber<<" is "<< (isValid(cardNumber) ? "Valid" : "Invalid");
    if(isValid(cardNumber) && bankCard(cardNumber)!="N/A"){
        cout<<"\nThis is a "<<bankCard(cardNumber)<<" card";
    }
    else {
        cout<<"\nThis is not a real card";
    }
    return 0;
}
int get_size(long number){
    string num = to_string(number);
    return num.size();
}
int oddSum(long cardNumber){
    int sum = 0;
    string num = to_string(cardNumber);
    for(int i=get_size(cardNumber)-1; i>=0; i-=2){
        sum += num[i]-'0';
    }
    return sum;
}
int evenSum(long cardNumber){
    int sum = 0;
    string num = to_string(cardNumber);
    for(int i=get_size(cardNumber)-2; i>=0; i-=2){
        sum += get_digit((num[i]-'0')*2);
    }
    return sum;
}
int get_digit(int number){
    int sum = 0;
    int digit;
    while(number>0){
        digit = number%10;
        sum += digit;
        number/=10; 
    }
    return sum;
}
bool matchedPrefix(long cardNumber, int k){
    string num = to_string(cardNumber);
    return stol(num.substr(0,get_size(k)))==k;
}
bool isValid(long cardNumber){
    return (13 <= get_size(cardNumber) && get_size(cardNumber) <= 16) && 
    ((oddSum(cardNumber) + evenSum(cardNumber))%10==0) &&
    (matchedPrefix(cardNumber, 3)|| matchedPrefix(cardNumber, 4)||
    matchedPrefix(cardNumber, 5) || matchedPrefix(cardNumber, 6));
}
string bankCard(long cardNumber){
    string num = to_string(cardNumber);
    int prefix1 = stol(num.substr(0,1));
    int prefix2 = stol(num.substr(0,2));
    int prefix4 = stol(num.substr(0,4));
    switch(prefix4){
        case 6011: return "Discover";
        case 5067: return "Elo";
    }
    switch(prefix2){
        case 34:
        case 37: return "American Express";
        case 36: return "Diners Club International";
        case 56: return "Maestro";
        case 62: return "UnionPay";
        case 65: return "Discover";
    }
    switch(prefix1){
        case 3: return "JCB";
        case 4: return "Visa";
        case 5: return "Master";
        default: return "N/A";
    }
    return 0;
}