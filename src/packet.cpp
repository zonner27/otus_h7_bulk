#include "packet.h"


void Packet::subscribe(Observer *obs) {
    subs.push_back(obs);
}

void Packet::notify() {
    for (auto s : subs)
        for (auto str_commands: commands)
            s->update(str_commands, m_str_time);
}
