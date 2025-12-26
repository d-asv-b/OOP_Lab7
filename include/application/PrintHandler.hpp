#pragma once

#include <mutex>
#include <iostream>
#include <ostream>
#include <sstream>

class PrintHandler {
private:
    std::mutex mtx{};
    PrintHandler() = default;

public:
    static void print(const std::string& msg) {
        static PrintHandler instance;
        std::lock_guard<std::mutex> lock(instance.mtx);

        std::cout << msg << std::flush;
    }

    static void print(std::stringstream& ss) {
        print(ss.str());
    }
};