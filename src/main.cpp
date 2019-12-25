#include "packet.h"
#include "observer.h"

int main(int argc, char *argv[])
{
    try {
        if (argc != 2) {
            std::cout << "Wrong amount arguments" << std::endl;
            return 1;
        }

        Packet pack;
        pack.set_number(atoi(argv[1]));
        Cmd_Observer cmdob(&pack);
        File_Observer fileobs(&pack);

        for(std::string line; std::getline(std::cin, line);) {
            pack.setstring(line);
        }
        pack.modul();
        pack.notify();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}








