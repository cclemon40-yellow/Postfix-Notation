#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>

// 檢查運算式的括號是否對稱
bool areParenthesesBalanced(const std::string& expr) {
    std::stack<char> s;
    for (char ch : expr) {
        if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            // 如果堆疊為空，表示沒有匹配的左括號，返回 false
            if (s.empty()) return false;
            //從堆疊 s 中移除頂部的元素
            s.pop();
        }
    }
    return s.empty();
}

// 獲取運算符的優先級
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 將中序運算式轉換為後序運算式
std::string infixToPostfix(const std::string& expr) {
    std::stack<char> s;
    std::string postfix;
    for (char ch : expr) {
        // 如果字元是數字，直接加入後序運算式
        if (isdigit(ch)) {
            postfix += ch;
        }
        else if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            while (!s.empty()/*檢查堆疊 s 是否不為空*/ && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
			s.pop(); // 移除左括號
        }
        // 如果字元是運算符
        else {
            // 將堆疊中優先級大於或等於當前運算符的運算符彈出並加入後序運算式
            while (!s.empty() && precedence(s.top()) >= precedence(ch)) {
                postfix += s.top();
                s.pop();
            }
            s.push(ch);
        }
    }
    // 將堆疊中剩餘的運算符全部彈出並加入後序運算式
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
    return postfix;
}

// 計算後序運算式的結果
int evaluatePostfix(const std::string& postfix) {
    std::stack<int> s;
    for (char ch : postfix) {
        if (isdigit(ch)) {
            s.push(ch - '0');
        }
        else {
            int val2 = s.top(); s.pop();
            int val1 = s.top(); s.pop();
            switch (ch) {
            case '+': s.push(val1 + val2); break;
            case '-': s.push(val1 - val2); break;
            case '*': s.push(val1 * val2); break;
            case '/': s.push(val1 / val2); break;
            }
        }
    }
    return s.top();
}

int main() {
    std::string expr;
    std::cout << "請輸入一個運算式: ";
    std::cin >> expr;

    // 檢查括號是否對稱
    if (!areParenthesesBalanced(expr)) {
        std::cout << "此運算式的括號不對稱，無法繼續運算" << std::endl;
        return 1;
    }

    // 將中序運算式轉換為後序運算式
    std::string postfix = infixToPostfix(expr);
    // 計算後序運算式的結果
    int result = evaluatePostfix(postfix);

    // 輸出結果
    std::cout << "A." << expr << " 運算式的左右括號對稱" << std::endl;
    std::cout << "B." << expr << " 運算式的後序表式法為： " << postfix << std::endl;
    std::cout << "C." << expr << " 運算式的運算結果為：" << result << std::endl;

    return 0;
}
