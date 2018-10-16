#pragma once
#include <string>
#include <vector>

class MessageQueue{
public:
    virtual void push(const std::string& message, const std::string& userName){
        queue.push_back(message);
        std::cout << "message \"" + message + "\" was pushed by " + userName + "\n";
    }
private:
    std::vector<std::string> queue;
};
