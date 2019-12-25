#pragma once
#ifndef OBSERVER223224122019_H
#define OBSERVER223224122019_H

#include <iostream>
#include "packet.h"

#define UNUSED(expr) do { (void)(expr); } while (0)

class Packet;

class Observer
{
public:
    virtual void update(const std::string &str_commands, const std::string &str_time) = 0;
};

class Cmd_Observer : public Observer
{
public:
    Cmd_Observer(Packet *pack);
    void update(const std::string &str_commands, const std::string &str_time) override;
};

class File_Observer : public Observer
{
public:
    File_Observer(Packet *pack);
    void update(const std::string &str_commands, const std::string &str_time) override;
};

#endif //OBSERVER223224122019_H
