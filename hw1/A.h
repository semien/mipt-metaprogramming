#pragma once
#include <iostream>
#include <string>
#include "B.h"

class User {
public:
    User(const std::string& userName): name(userName) {}
    void send(const std::string& message, MessageQueue& queue) {
        queue.push(message, name);
    }
    
    void receive(const std::string& message) {
        std::cout << "I'm " << name << " and I receive: \"" << message << "\"\n";
    }
private:
    std::string name;
};
