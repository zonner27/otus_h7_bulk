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

    void set_time() {
        std::chrono::time_point<std::chrono::system_clock> start_time;
        start_time = std::chrono::system_clock::now();
        std::time_t time_t = std::chrono::system_clock::to_time_t(start_time);
        m_str_time = std::to_string(time_t);
    }

    void add_string() {
        commands.push_back(m_res_str);
        m_iter = 0;
        m_res_str = "bulk: ";
    }

    void set_string(const std::string &str) {
        if (m_res_str.size() == 6) {
            m_res_str = m_res_str + str;
            ++m_iter;
        } else {
            m_res_str = m_res_str + ", " + str;
            ++m_iter;
        }
    }

public:

    void set_number(int _number) {
        m_number_commnads = _number;
    }

    void setstring(const std::string &str) {

        if (m_str_time.size() == 0 && str != "{" && str != "}")
            set_time();

        if (str == "{") {
            ++m_bracket;
            if (m_bracket == 1 && m_res_str.size() > 6)
                add_string();
        } else if (str == "}") {
            if (m_bracket > 0)
                --m_bracket;
            if (m_bracket == 0 && m_res_str.size() > 6)
                add_string();
        } else {
            if (m_bracket == 0) {
                if (m_iter != (m_number_commnads - 1) ) {
                    set_string(str);
                } else {
                    set_string(str);
                    add_string();
                }
            } else
                set_string(str);
        }
    }

    void modul() {
        if (m_res_str.size() > 6 && m_bracket == 0)
            add_string();
    }

    void subscribe(Observer *obs);
    void notify();
};



#endif //PACKET223224122019_H
