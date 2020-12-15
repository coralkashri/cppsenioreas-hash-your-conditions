/**
 * All examples are taken from C++ Senioreas blog
 * https://cppsenioreas.wordpress.com/
 *
 * Examples from:
 * cpp_senioreas::hash_your_conditions_cpp
 * https://cppsenioreas.wordpress.com/SOON
 */

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <functional>

#define PART 2

#if PART == 1

struct interface {};
struct impl1 : interface {};
struct impl2 : interface {};
struct impl3 : interface {};
struct impl4 : interface {};
struct impl5 : interface {};
struct impl6 : interface {};
struct impl7 : interface {};

class type_hash {
public:
    type_hash() {
        // Prepare hash table
        hash = {
                {"1", [] { return std::make_shared<impl1>(); }},
                {"2", [] { return std::make_shared<impl2>(); }},
                {"3", [] { return std::make_shared<impl3>(); }},
                {"4", [] { return std::make_shared<impl4>(); }},
                {"5", [] { return std::make_shared<impl5>(); }},
                {"6", [] { return std::make_shared<impl6>(); }},
                {"7", [] { return std::make_shared<impl7>(); }}
        };
    }

    std::shared_ptr<interface> deduce_type(std::string &&type) {
        // Access in O(1), and throw an error if the type can't be deduced.
        return hash.at(type)(); // Call the function which exists in <type> place.
    }

private:
    std::unordered_map<std::string, std::function<std::shared_ptr<interface>()>> hash;
};

std::shared_ptr<interface> core_function(std::string &&type, type_hash &deducer) {
    std::shared_ptr<interface> res;
    res = deducer.deduce_type(std::move(type));
    return res;
}

#endif

#if PART == 2

class functions_collection {
public:
    void func1() { num = 1; print_number(); }
    void func2() { num = 2; print_number(); }
    void func3() { num = 3; print_number(); }
    void func4() { num = 4; print_number(); }
    void func5() { num = 5; print_number(); }
    void func6() { num = 6; print_number(); }
    void func7() { num = 7; print_number(); }

private:
    int num = 0;

    void print_number() {
        std::cout << num << "\n";
    }
};

class type_hash {
private:
    using functions_collection_t = void (functions_collection::*)();

public:
    type_hash() {
        hash = {
                {"1", &functions_collection::func1},
                {"2", &functions_collection::func2},
                {"3", &functions_collection::func3},
                {"4", &functions_collection::func4},
                {"5", &functions_collection::func5},
                {"6", &functions_collection::func6},
                {"7", &functions_collection::func7},
        };
    }

    functions_collection_t deduce_type(std::string &&type) {
        return hash.at(type);
    }

private:
    std::unordered_map<std::string, void (functions_collection::*)()> hash;
};

void core_function(std::string &&type, type_hash &deducer) {
    // ...
    functions_collection fc;
    auto desired_func = deducer.deduce_type(std::move(type));
    (fc.*desired_func)();
    // ...
}

#endif

int main() {
    type_hash hasher;
    core_function("5", hasher);
    return 0;
}