#include <array>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>

class Grade {
    unsigned int value : 4;
    friend std::istream& operator>>(std::istream&, Grade&);

public:
    template <typename T = unsigned int>
    requires std::is_integral_v<T>
    explicit Grade(T v = 0) : value(static_cast<unsigned int>(v)) {
        if (v < 0 || v > 10) {
            throw std::out_of_range("Value must be between 0 and 10");
        }
    }

    template <typename T>
    requires std::is_integral_v<T>
    Grade& operator=(T other) {
        if (other < 0 || other > 10) {
            throw std::out_of_range("Value must be between 0 and 10");
        }
        this->value = other;
        return *this;
    }

    unsigned int get_value() const noexcept {
        return value;
    };

    bool operator<(Grade other) const noexcept {
        return value < other.value;
    }
};

std::istream& operator>>(std::istream& is, Grade& g) {
    int temp;
    is >> temp;

    if (temp >= 0 && temp <= 10) {
        g.value = static_cast<unsigned int>(temp);
    } else {
        throw std::out_of_range("Grade is out of range");
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, Grade g) {
    os << g.get_value();
    return os;
}

class Student {
    struct _full_name {
        std::string first_name;
        std::string last_name;
        std::string patronimyc;
    };

    struct _performance {
        double gpa = 0;
        std::array<Grade, 4> exam_results;
    };

public:
    _full_name full_name;
    std::string group;
    _performance performance;
};

std::istream& operator>>(std::istream& is, Student& s) {
    is >> s.full_name.first_name;
    is >> s.full_name.last_name;
    is >> s.full_name.patronimyc;
    is >> s.group;
    for (int i = 0; i < 4; i++) {
        is >> s.performance.exam_results[i];
        s.performance.gpa += s.performance.exam_results[i].get_value();
    }
    s.performance.gpa /= 4.0;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << s.full_name.first_name << '\n';
    os << s.full_name.last_name << '\n';
    os << s.full_name.patronimyc << '\n';
    os << s.group << '\n';
    for (int i = 0; i < 4; i++) {
        os << s.performance.exam_results[i] << ' ';
    }
    os << '\n';
    os << s.performance.gpa;
    return os;
}

template <typename T>
class Queue {
protected:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        explicit Node(const T& data, Node* prev = nullptr,
                      Node* next = nullptr) noexcept
            : data(data), prev(prev), next(next) {}
    };

    Node* head = nullptr;
    size_t size = 0;

public:
    Queue() = default;

    ~Queue() { clear(); }

    T& front() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head->prev->data;
    }

    bool empty() const noexcept { 
        return size == 0;
    }

    void push(const T& data) {
        if (empty()) {
            head = new Node(data);
            head->prev = head;
            head->next = head;
        } else {
            Node* newNode = new Node(data, head->prev, head);
            head->prev->next = newNode;
            head->prev = newNode;
        }
        size++;
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }

        if (size == 1) {
            delete head;
            head = nullptr;
        } else {
            Node* temp = head;
            head->prev->next = head->next;
            head->next->prev = head->prev;
            head = head->next;
            delete temp;
        }
        size--;
    }

    void clear() {
        while (!empty()) {
            pop();
        }
    }

    size_t Size() const noexcept {
        return size;
    }
};

int main() {
    std::string input;
    std::cin >> input;

    std::fstream is(input);

    Queue<Student> students;
    
    size_t t;
    is >> t;

    double min_gpa = 10;
    while (t--) {
        Student s;
        is >> s;
        min_gpa = std::min(min_gpa, s.performance.gpa);
        students.push(s);
    }

    size_t sz = students.Size();
    for (size_t i = 0; i < sz; i++) {
        Student current = students.front();
        students.pop();
        if (current.performance.gpa != min_gpa) {
            students.push(current);
        }
    }

    if (students.empty()) {
        std::cout << "Resulting queue is empty\n";
        return 0;
    }

    while (!students.empty()) {
        std::cout << students.front() << "\n";
        students.pop();
    }

    is.close();
    return 0;
}
