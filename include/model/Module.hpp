#include <string>

class Module {
private:
    std::string name;
    int pin;
    int mode;
public:
    Module(std::string name, int pin, int mode){
        this->name = name;
        this->pin = pin;
        this->mode = mode;
    }

    std::string getName(){
        return this->name;
    }

    int getPin(){
        return this->pin;
    }

    int getMode(){
        return this->mode;
    }
};