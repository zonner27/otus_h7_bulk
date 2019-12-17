#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>

//class Command
//{
//    std::string cmd1;
//};
class Packet;

class Observer
{
public:
    virtual void update(std::string str) = 0;
};

class Packet
{
    std::vector<Observer *> subs;
    std::vector<std::string> commands;

public:
    void setstring(std::string str) {
        commands.push_back(str);
    }

    void subscribe(Observer *obs) {
        subs.push_back(obs);
    }

    void notify() {
        
        
        for (auto s : subs) {
            for (auto str: commands)
                s->update(str);
        }
    }
};

class Cmd_Observer : public Observer
{
public:
    Cmd_Observer(Packet *pack) {
        pack->subscribe(this);
    }

    void update(std::string str) override {
        std::cout << str;
//        for (auto var : pack->commands)
//        {
//            std::cout << var << ", ";
//        }
        std::cout << std::endl;
    }
};

class File_Observer : public Observer
{
public:
    File_Observer(Packet *pack) {
        pack->subscribe(this);
    }

    void update(std::string str) override {
        std::cout << str << ", ";
//        for (auto var : pack->commands)
//        {
//            std::cout << var << ", ";
//        }
    }
};

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2) {
            std::cout << "Wrong amount arguments" << std::endl;
            return 1;
        }
        std::cout << argv[1] << std::endl;

        Packet pack;
        Cmd_Observer cmdob(&pack);
        File_Observer fileobs(&pack);

        for(std::string line; std::getline(std::cin, line);)
        {
            pack.setstring(line);
            //str.push_back(line);
        }

        pack.notify();

//        std::chrono::system_clock::duration  m_time;
//        //m_time = std::chrono::system_clock::now();

//        std::cout << std::to_string(m_time.) << std::endl;


//        std::chrono::time_point<std::chrono::system_clock> now;
//        now = std::chrono::system_clock::now();
//        std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
//        std::cout << "One day ago, the time was "
//                  << std::put_time(std::localtime(&now_c), "%F %T") << '\n';
//        std::cout << std::to_string(now) << std::endl;

        //    report_observer rpt(&lang);
        //    ui_observer ui(&lang);

//        std::vector<std::string> str;

//        for(std::string line; std::getline(std::cin, line);)
//        {
//            str.push_back(line);
//        }


//        std::ofstream myfile;
//        myfile.open("bulk.log");
//        myfile << "__________" << std::endl;
//        for (auto var : str)
//        {
//            std::cout << var << std::endl;
//            myfile << var <<std::endl;
//        }
//        myfile.close();


    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }


    return 0;
}





//// Наблюдатель (Observer)

//#include <iostream>
//#include <vector>

//enum class Lang
//{
//    ru, en
//};

//class Observer {
//public:
//    virtual void update(Lang lang) = 0;
//};

//class Language {
//    Lang lang{Lang::ru};
//    std::vector<Observer *> subs;
//public:
//    void subscribe(Observer *obs) {
//        subs.push_back(obs);
//    }

//    void set_language(Lang lang_) {
//        lang = lang_;
//        notify();
//    }

//    void notify() {
//        for (auto s : subs) {
//            s->update(lang);
//        }
//    }
//};

//class report_observer : public Observer {
//public:
//    report_observer(Language *lang) {
//        lang->subscribe(this);
//    }

//    void update(Lang lang) override {
//        std::cout << "switch report template to lang " << int(lang) << std::endl;
//    }
//};

//class ui_observer : public Observer {
//public:
//    ui_observer(Language *lang) {
//        lang->subscribe(this);
//    }

//    void update(Lang lang) override {
//        std::cout << "refresh ui for lang " << int(lang) << std::endl;
//    }
//};

//int main(int, char *[]) {
//    Language lang;

//    report_observer rpt(&lang);
//    ui_observer ui(&lang);

//    lang.set_language(Lang::ru);

//    lang.set_language(Lang::en);

//    return 0;
//}




