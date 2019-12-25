#pragma once
#ifndef PACKET223224122019_H
#define PACKET223224122019_H

#include <vector>
#include <fstream>
#include <chrono>
#include "observer.h"

class Observer;

class Packet
{
    std::vector<Observer *> subs;
    std::vector<std::string> commands;
    std::string m_str_time;
    int m_number_commnads = 2;
    int m_iter = 0;
    int m_bracket = 0;
    std::string m_res_str = "bulk: ";
    void set_time();
    void add_string();
    void set_string(const std::string &str);

public:
    void set_number(int _number);
    void setstring(const std::string &str);
    void modul();
    void subscribe(Observer *obs);
    void notify();
};

#endif //PACKET223224122019_H
