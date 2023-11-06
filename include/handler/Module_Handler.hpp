#include <list>
#include "model/Module.hpp"

class Module_Handler{
private:
    static Module_Handler *instance;
    Module_Handler();
    std::list<Module> modules;
public:
    static Module_Handler *getInstance(){
        if(instance = nullptr){
            return new Module_Handler();
        } else {
            return instance;
        }
    }

    void addModule(Module module){
        
    }
};

