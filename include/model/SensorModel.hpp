#pragma once

class SensorModel{
private:
    bool isAlarmOn;
public:
    bool getAlarmStatus() { 
        return isAlarmOn;
    }
    void setAlarmStatus(bool isAlarmOn) {
        this->isAlarmOn = isAlarmOn;
    }
};
