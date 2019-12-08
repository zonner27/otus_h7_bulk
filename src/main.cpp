#include <iostream>
#include <vector>
#include <fstream>

class Command
{
    std::string cmd1;
};
class Packet;

class Observer{
public:
    virtual void update() = 0;
    //virtual ~Observer() {}
};

class Packet {

    std::string str;
    std::vector<Observer *> subs;

public:
    void subscribe(Observer *obs) {
        subs.push_back(obs);
    }

    void notify() {
        for (auto s : subs) {
            s->update();
        }
    }
};

class Cmd_Observer : public Observer {
public:
    Cmd_Observer(Packet *pack) {
        pack->subscribe(this);
    }

    void update() override {
        std::cout << "CMD out "  << std::endl;
    }
};

class File_Observer : public Observer {
public:
    File_Observer(Packet *pack) {
        pack->subscribe(this);
    }

    void update() override {
        std::cout << "File out " << std::endl;
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

        pack.notify();
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




