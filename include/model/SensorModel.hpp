#pragma once

class SensorModel{
private:
    bool soundOn;
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
    void setSoundOn(bool soundOn){
        this->soundOn = soundOn;
    }
    bool isSoundOn(){
        return this->soundOn;
    }
};
