#pragma once
#include <iostream>
#include <iostream>
#include "B.h"

template<int N>
class C{};

// Proxy
template<>
class C<1>: public MessageQueue {
public:
    C<1>(MessageQueue* realQueue): realQueue(realQueue) {}
    void push(const std::string& message, const std::string& userName) {
        realQueue->push(message, userName);
        std::cout << "proxy: " << userName << " pushed " << message.length() << " symbols\n";
    }
private:
    MessageQueue* realQueue;
};


template<>
class C<2>: public MessageQueue {
public:
    void push(const std::string& message, const std::string& userName){
        if (userName == "Jim") {
            queue1.push(message, userName);
            std::cout << "mediator: message was pushed to queue1\n";
        } else {
            queue2.push(message, userName);
            std::cout << "mediator: message was pushed to queue2\n";
        }
    }
private:
    MessageQueue queue1;
    MessageQueue queue2;
};

template<>
class C<3>: public MessageQueue {
public:
    void subscribe(User* user) {
        subscribers.push_back(user);
    }
    void push(const std::string& message, const std::string& userName){
        MessageQueue::push(message, userName);
        for (auto subscr: subscribers) {
            subscr->receive(message);
        }
    }
private:
    std::vector<User*> subscribers;
};
