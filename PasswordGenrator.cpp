#include <iostream>
#include <cmath>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> results;

int reduceToSingleDigit(int num) {
    while (num > 9) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        num = sum;
    }
    return num;
}

string generatePassword(string numberStr, string name) {
    double number;
       
       if (any_of(numberStr.begin(), numberStr.end(), [](char c) { return !isdigit(c) && c != '.' && c != 'e' && c != '-'; })) {
           results.push_back("Invalid");
           return "Invalid";
       }
       
       try {
           number = stod(numberStr);
       } catch (const std::invalid_argument &) {
           results.push_back("Invalid");
           return "Invalid";
       }

       if (number <= 0 || name.empty() || name.find_first_not_of("abcdefghijklmnopqrstuvwxyz") != string::npos) {
           results.push_back("Invalid");
           return "Invalid";
       }
    
    string sign = "";
    bool dotfound = false;
    string beforedes = "0";
    string afterdes = "0";

    for (size_t i = 0; i < numberStr.size(); i++) {
        if (dotfound == false) {
            if (numberStr[i] == '.') {
                dotfound = true;
                continue;
            } else {
                beforedes = beforedes + numberStr[i];
            }
        } else {
            afterdes = afterdes + numberStr[i];
        }
    }

    double begin = stod(beforedes);
    double end = stod(afterdes);

    string s = "";
    string e = "";
    string ending = to_string(end);
    string begining = to_string(begin);
    int ex =0;

    if (begin == 0) {
        ex++;
        sign = "-";
        s = ending[0];
        size_t n = ending.size();
        ending = ending.substr(1, n - 1);
        end = stod(ending);
        int x = reduceToSingleDigit(static_cast<int>(end));
        e = to_string(x);
    } else if (end == 0) {
        sign = "+";
        if(afterdes =="0"){
            sign = "";
        }
        s = begining[0];
        size_t n = begining.size();
        ending = begining.substr(1, n - 1);
        end = stod(ending);
        int x = reduceToSingleDigit(static_cast<int>(end));
        e = to_string(x);
    } else {
        sign = "+";
        if(afterdes == "0"){
            sign = "";
        }
        int y = reduceToSingleDigit(static_cast<int>(begin));
        s = to_string(y);
        int x = reduceToSingleDigit(static_cast<int>(end));
        e = to_string(x);
    }




    int exponent = static_cast<int>(log10(fabs(number)));
    int simplifiedExponent = reduceToSingleDigit(exponent);
    simplifiedExponent = abs(simplifiedExponent) + ex;

    unordered_map<string, string> digitMap = {
        {"0", "zer"},
        {"1", "one"},
        {"2", "two"},
        {"3", "thr"},
        {"4", "for"},
        {"5", "fiv"},
        {"6", "six"},
        {"7", "sev"},
        {"8", "eig"},
        {"9", "nin"}};

    string exp = to_string(abs(simplifiedExponent));

    string s1 = digitMap[s] + "." + digitMap[e] + "e" + sign + digitMap[exp];

    string s2;
    if (simplifiedExponent % 2 == 1) {
        for (size_t i = 0; i < name.length(); i += 2) {
            s2 += name[i];
        }
    } else {
        for (size_t i = 1; i < name.length(); i += 2) {
            s2 += name[i];
        }
    }

    string result = s1 + "@" + s2;
    results.push_back(result);
    return result;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        string numberStr, name;
        cin >> numberStr >> name;

        generatePassword(numberStr, name);
    }

    for (const string &result : results) {
        cout << result << endl;
    }

    return 0;
}

