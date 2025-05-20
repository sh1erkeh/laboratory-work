#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

bool is_capital_latin(char c) {
    return 'A' <= c && c <= 'Z';
}

bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

std::vector<std::pair<size_t, std::string>> task1(const std::vector<std::string>& strings) {
    std::vector<std::pair<size_t, std::string>> substrings;

    for (size_t index = 0; index < strings.size(); index++) {
        for (size_t i = 0; i < strings[index].size(); i++) {
            std::string temp;
            for (size_t j = i + 1; j < strings[index].size(); j++) {
                if (is_capital_latin(strings[index][i]) 
                    && is_capital_latin(strings[index][j]) && i + 1 != j) {
                    substrings.emplace_back(index, temp);
                }
                temp += strings[index][j];
            }
            temp += strings[index][i];
        }
    }

    if (substrings.empty()) {
        throw std::runtime_error("No viable substrings");
    } else {
        return substrings;
    }
}

size_t task2(const std::vector<std::pair<size_t, std::string>>& substrings) noexcept {
    size_t min = 0;
    for (size_t i = 0; i < substrings.size(); i++) {
        if (substrings[i].second.size() < substrings[min].second.size()) {
            min = i;
        }
    }
    std::cout << substrings[min].second << '\n';
    return substrings[min].first;
}

void task3(size_t index, std::vector<std::string>& strings) {
    std::string new_string = "";
    bool digit_found = false;

    for (size_t i = 0; i < strings[index].size(); i++) {
        new_string += strings[index][i];
        if (is_digit(strings[index][i]) && !digit_found) {
            new_string += "***";
            digit_found = true;
        }
    }

    if (!digit_found) {
        throw std::runtime_error("No digits found");
    } else {
        strings[index] = std::move(new_string);
    }
}

int main() {
    size_t n;
    std::cin >> n;

    std::vector<std::string> strings;
    strings.assign(n, "");

    for (size_t i = 0; i < n; i++) {
        std::cin >> strings[i];
    }
    
    std::cout << "Executing Task1...\n";
    std::vector<std::pair<size_t, std::string>> substrings;
    try {
        substrings = task1(strings);
        std::cout << "Results:\n";
        for (size_t i = 0; i < substrings.size(); i++) {
            std::cout << substrings[i].second << '\n';
        }
    } catch (const std::runtime_error& error) {
        std::cout << error.what() << '\n';  
        return 1;
    }

    std::cout << "Executing Task2...\n";
    std::cout << "Results:\n";
    size_t min = task2(substrings);

    std::cout << "Executing Task3...\n";
    try {
        task3(min, strings);
        std::cout << "Results:\n";
        std::cout << strings[min] << '\n';
    } catch (const std::runtime_error& error) {
        std::cout << error.what() << '\n';
        return 3;
    }

    return 0;
}
