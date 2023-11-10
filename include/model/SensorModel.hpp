#pragma once

class SensorModel{
private:
    bool isAlarmOn;
    bool limiter;
public:
    bool isAlarmStatus() { 
        return isAlarmOn;
    }
    void setAlarmStatus(bool isAlarmOn) {
        this->isAlarmOn = isAlarmOn;
    }
    void setLimiter(bool limiter){
        this->limiter = limiter;
    }
    bool isLimiter(){
        return this->limiter;
    }
};
