#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <set>
#include <algorithm>

class ExpressionParser {
public:
    std::set<char> variables;

    void init(std::string &infix_expression) {
        std::string clean_str = delete_spaces(infix_expression);
        postfix_expr = to_postfix(clean_str);
    }

    bool calculate(int values) {
        std::stack<bool> locals;

        for (size_t i = 0; i < postfix_expr.size(); i++) {
            char c = postfix_expr[i];

            if (is_variable(c)) {
                locals.push(determine_value(values, c));
            } else if (operation_priority[c]) {
                if (c == '!') {
                    bool top_variable = locals.top();
                    locals.pop();
                    locals.push(!top_variable);
                } else {
                    bool first_variable = locals.top();
                    locals.pop();
                    bool second_variable = locals.top();
                    locals.pop();
                    locals.push(execute(c, first_variable, second_variable));
                }
            }
        }

        return locals.top();
    }
private:
    std::vector<char> postfix_expr;
    std::map<char, int> operation_priority { {'+', 1}, {'^', 2}, {'*', 3}, {'!', 4} };

    std::string delete_spaces(std::string &str) {
        std::string clean_str = "";
        for (char &c : str) {
            if (c != ' ') {
                clean_str += c;
            }
        }
        return clean_str;
    }

    bool is_variable(char c) {
        return 'a' <= c && c <= 'z';
    }

    std::vector<char> to_postfix(std::string &infix_expression) {
        std::vector<char> postfix_expression;
        std::stack<char> stack;

        for (size_t i = 0; i < infix_expression.length(); i++) {
            char c = infix_expression[i];

            if (is_variable(c)) {
                variables.insert(c);
                postfix_expression.push_back(c);
            } else if (c == '(') {
                stack.push(c);
            } else if (c == ')') {
                while (!stack.empty() && stack.top() != '(') {
                    postfix_expression.push_back(stack.top());
                    stack.pop();
                }
                stack.pop();
            } else if (operation_priority[c]) {
                while (!stack.empty() && operation_priority[stack.top()] >= operation_priority[c]) {
                    postfix_expression.push_back(stack.top());
                    stack.pop();
                }
                stack.push(c);
            }
        }

        while (!stack.empty()) {
            postfix_expression.push_back(stack.top());
            stack.pop();
        }

        return postfix_expression;
    }

    bool determine_value(int values, char variable) {
        int index = distance(variables.begin(), variables.lower_bound(variable));
        return (values >> index) & 1;
    }

    bool execute(char operation, char value1, char value2) {
        switch (operation) {
            case '+':
                return value1 | value2;
            case '*':
                return value1 & value2;
            case '^':
                return value1 ^ value2;
            default:
                return 0;
        }
    }
};

class Simplifyer {
public:
    void init(std::string &expression) {
        parser.init(expression);
        number_of_variables = parser.variables.size();
    }

    void simplify() {
        std::vector<unit> maxterms = find_maxterms();
    }
private:
    struct unit {
        int counter;
        std::vector<char> value;
    };
    ExpressionParser parser;

    size_t number_of_variables;
    std::set<std::vector<char>> ans;

    std::vector<unit> find_maxterms() {
        std::vector<unit> maxterms;
        for (int value = 0; value < (1 << number_of_variables); value++) {
            if (parser.calculate(value)) {
                int counter = 0;
                std::vector<char> maxterm(number_of_variables);

                for (size_t i = 0; i < number_of_variables; i++) {
                    if (((value >> i) & 1)) {
                        maxterm[i] = 1;
                        counter++;
                    } else {
                        maxterm[i] = 0;
                    }
                }
                maxterms.push_back({counter, maxterm});
            }
        }
        sort(maxterms.begin(), maxterms.end(), comparator);
        return maxterms;
    }

    bool comparator(unit &first, unit &second) {
        return first.counter < second.counter;
    }

    bool minimize() {

    }
};  

int main() {
    ExpressionParser parser;
    std::string expression = "!a*b*c+a*!b*!c+a*b";
    parser.init(expression);
}
