#include "A.h"
#include "B.h"
#include "C.h"
#include <iostream>

//----------
int main(int argc, const char * argv[]) {
    User user1("Jim");
    User user2("Mike");
    User user3("Michael");
    MessageQueue queue1;
    MessageQueue queue2;
    
    // Proxy
    std::cout << "PROXY--------------------------\n";
    C<1> proxy = C<1>(&queue1);
    user1.send("hello", proxy);
    std::cout << "===============================\n";
    
    // Mediator
    std::cout << "MEDIATOR=======================\n";
    C<2> mediator;
    user1.send("hi", mediator);
    user2.send("greeting", mediator);
    user3.send("good morning", mediator);
    std::cout << "===============================\n";
    
    // Observer
    std::cout << "OBSERVER-----------------------\n";
    C<3> queue;
    queue.subscribe(&user1);
    queue.subscribe(&user2);
    user3.send("Yo", queue);
    std::cout << "===============================\n";
    return 0;
}
