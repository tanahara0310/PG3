#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void printMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << message << std::endl;
}

int main() {
    std::thread thread1(printMessage, "thread 1");
    thread1.join();

    std::thread thread2(printMessage, "thread 2");
    thread2.join();

    std::thread thread3(printMessage, "thread 3");
    thread3.join();

    return 0;
}