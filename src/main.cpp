#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>

#define UNUSED(expr) do { (void)(expr); } while (0)

class Packet;

class Observer
{
public:
    virtual void update(std::string str_commands, std::string str_time) = 0;
};

class Packet
{
    std::vector<Observer *> subs;
    std::vector<std::string> commands;
    std::string str_time;
    int number_commnads = 2;
    int m_iter = 0;
    int m_bracket = 0;
    std::string m_res_str = "bulk: ";

    void set_time() {
        std::chrono::time_point<std::chrono::system_clock> start_time;
        start_time = std::chrono::system_clock::now();
        std::time_t time_t = std::chrono::system_clock::to_time_t(start_time);
        str_time = std::to_string(time_t);
    }

public:

    void set_number(int _number) {
        number_commnads = _number;
    }

    void setstring(std::string str) {

        if (str_time.size() == 0 && str != "{" && str != "}") {
            set_time();
        }

        if (str == "{") {
            m_bracket += 1;
            if (m_res_str.size() > 6 && m_bracket == 1)
                add_string();
        } else if (str == "}") {
            if (m_bracket > 0)
                m_bracket -= 1;
            if (m_bracket == 0 && m_res_str.size() > 6)
                add_string();
        } else {
            if (m_bracket == 0) {
                if (m_iter != (number_commnads - 1) ) {
                    if (m_res_str.size() == 6) {
                        m_res_str = m_res_str + str;
                        ++m_iter;
                    } else {
                        m_res_str = m_res_str + ", " + str;
                        ++m_iter;
                    }
                }
                else {
                    m_res_str = m_res_str + ", " + str;
                    add_string();
                }
            } else {
                if (m_res_str.size() == 6)
                    m_res_str = m_res_str + str;
                else
                    m_res_str = m_res_str + ", " + str;
            }
        }
    }

    void add_string() {
        commands.push_back(m_res_str);
        m_iter = 0;
        m_res_str = "bulk: ";
    }

    void modul() {
        if (m_res_str.size() > 6 && m_bracket == 0)
            add_string();
    }

    void subscribe(Observer *obs) {
        subs.push_back(obs);
    }

    void notify() {     
        for (auto s : subs) {
            for (auto str_commands: commands) {
//                std::string result;
//                for (int i = 0; i < number_commnads; ++i)
//                {
//                    result = "bulk: " + str_commands;
//                }


                s->update(str_commands, str_time);
            }
        }
    }


};

class Cmd_Observer : public Observer
{
public:
    Cmd_Observer(Packet *pack) {
        pack->subscribe(this);
    }

    void update(std::string str_commands, std::string str_time) override {
        UNUSED(str_time);
        std::cout << str_commands << std::endl;
    }
};

class File_Observer : public Observer
{
public:
    File_Observer(Packet *pack) {
        pack->subscribe(this);
    }

    void update(std::string str_commands, std::string str_time) override {
        UNUSED(str_commands);
        UNUSED(str_time);
 //       std::cout << "\n" << str_commands << ", " << str_time << std::endl;
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

        Packet pack;
        pack.set_number(atoi(argv[1]));
        Cmd_Observer cmdob(&pack);
        File_Observer fileobs(&pack);

        for(std::string line; std::getline(std::cin, line);)
        {
            pack.setstring(line);
        }
        pack.modul();
        pack.notify();



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




