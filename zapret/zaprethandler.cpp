#include "zaprethandler.h"

// #include <chrono>
// #include <thread>
#include <QTimer>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


ZapretHandler::ZapretHandler() {
    QTimer* timer = new QTimer();
    timer->setInterval(1000); //Time in milliseconds
    //timer->setSingleShot(false); //Setting this to true makes the timer run only once
    connect(timer, &QTimer::timeout, this, [=](){
        checkStatus();
    });
    timer->start(); //Call start() AFTER connect

    status = false;
    // checkStatus();
}

bool ZapretHandler::isActive() {
    return status;
}

void ZapretHandler::start() {
    status = true;
    std::cout << "Start called" << std::endl;
    emit statusChanged(status);
}

void ZapretHandler::stop() {
    status = false;
    std::cout << "Stop called" << std::endl;
    emit statusChanged(status);
}

void ZapretHandler::checkStatus() {
    const std::string response = exec("ps aux | grep zapret");
    const bool new_status = response.find("daemon") != std::string::npos;

    // std::cout << response << status << new_status << std::endl;
    if (status != new_status) {
        if (new_status) {
            start();
        } else {
            stop();
        }
    }
}
