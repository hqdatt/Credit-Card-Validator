#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>

using namespace std;

unordered_map<string, string> card_types = {
    {"^4[0-9]{12}(?:[0-9]{3})?$", "Visa"},
    {"^5[1-5][0-9]{14}$", "MasterCard"},
    {"^3[47][0-9]{13}$", "American Express"},
    {"^6(?:011|5[0-9]{2})[0-9]{12}$", "Discover"},
    {"^(?:2131|1800|35[0-9]{3})[0-9]{11}$", "JCB"},
    {"^(5018|5020|5038|6304|6759|6761|6762|6763)[0-9]{8,15}$", "Maestro"},
    {"^62[0-9]{14,17}$", "UnionPay"},
    {"^5067[0-9]{12,15}$", "Elo"},
};

int get_size(long number) {
    string num = to_string(number);
    return num.size();
}

int oddSum(long cardNumber) {
    int sum = 0;
    string num = to_string(cardNumber);
    for (int i = get_size(cardNumber) - 1; i >= 0; i -= 2) {
        sum += num[i] - '0';
    }
    return sum;
}

int evenSum(long cardNumber) {
    int sum = 0;
    string num = to_string(cardNumber);
    for (int i = get_size(cardNumber) - 2; i >= 0; i -= 2) {
        sum += get_digit((num[i] - '0') * 2);
    }
    return sum;
}

int get_digit(int number) {
    int sum = 0;
    int digit;
    while (number > 0) {
        digit = number % 10;
        sum += digit;
        number /= 10;
    }
    return sum;
}

bool isValid(long cardNumber) {
    return (13 <= get_size(cardNumber) && get_size(cardNumber) <= 16) &&
           ((oddSum(cardNumber) + evenSum(cardNumber)) % 10 == 0) &&
           getCardType(cardNumber) != "N/A";
}

string getCardType(long cardNumber) {
    string num = to_string(cardNumber);
    for (const auto& pair : card_types) {
        if (regex_match(num, regex(pair.first))) {
            return pair.second;
        }
    }
    return "N/A";
}

int main() {
    long cardNumber;
    cout << "Enter credit card number here: ";
    cin >> cardNumber;
    cout << cardNumber << " is " << (isValid(cardNumber) ? "Valid" : "Invalid");
    string cardType = getCardType(cardNumber);
    if (isValid(cardNumber) && cardType != "N/A") {
        cout << "\nThis is a " << cardType << " card";
    } else {
        cout << "\nThis is not a real card";
    }
    return 0;
}
