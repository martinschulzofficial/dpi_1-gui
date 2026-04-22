#include "zaprethandler.h"

// #include <chrono>
// #include <thread>
#include <QTimer>
#include <QProcess>
#include <iostream>
#include <stdexcept>

#include <string>
#include <fstream>
#include <sstream>

const std::string kIpsetDir = "/opt/zapret/ipset";

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

void exec_sudo(const char* cmd) {
    QProcess::startDetached("sudo", QStringList() << "-A" << cmd);
}


ZapretHandler::ZapretHandler() {
    QTimer* timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, [=](){
        checkStatus();
    });
    timer->start();

    status = false;
    checkStatus();
}

bool ZapretHandler::isActive() {
    return status;
}

void ZapretHandler::start() {
    // runAppleScript("/opt/zapret/init.d/macos/zapret start");
    exec_sudo("ls -la /");
    status = true;
    std::cout << "Start called" << std::endl;
    emit statusChanged(status);
}

void ZapretHandler::stop() {
    // runAppleScript("/opt/zapret/init.d/macos/zapret stop");
    exec_sudo("ls -la /");
    status = false;
    std::cout << "Stop called" << std::endl;
    emit statusChanged(status);
}

void ZapretHandler::toggle() {
    if (status) {
        stop();
    } else {
        start();
    }
}


std::string ZapretHandler::getDomains() {
    const auto kUserDomainsFilePath = kIpsetDir + "/zapret-hosts-user.txt";
    std::ifstream t(kUserDomainsFilePath);
    std::stringstream buffer;
    buffer << t.rdbuf();

    std::cout << "domains" << buffer.str() << std::endl;
    return buffer.str();
}

std::string ZapretHandler::getIps(){
    const auto kUserIpsFilePath = kIpsetDir + "/zapret-ip-user.txt";
    std::ifstream t(kUserIpsFilePath);
    std::stringstream buffer;
    buffer << t.rdbuf();

    std::cout << "ips" << buffer.str() << std::endl;
    return buffer.str();
}

void ZapretHandler::updateDomains(std::string newDomains) {

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
