#include "observer.h"

Cmd_Observer::Cmd_Observer(Packet *pack) {
    pack->subscribe(this);
}

void Cmd_Observer::update(const std::string &str_commands, const std::string &str_time) {
    UNUSED(str_time);
    std::cout << str_commands << std::endl;
}

File_Observer::File_Observer(Packet *pack) {
    pack->subscribe(this);
}

void File_Observer::update(const std::string &str_commands, const std::string &str_time) {
    std::ofstream filecommand;
    std::string namefile = "bulk" + str_time + ".log";
    filecommand.open(namefile, std::ios::app);
    if (filecommand.is_open())
        filecommand << str_commands <<std::endl;
    filecommand.close();
}



