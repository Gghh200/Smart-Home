#pragma once
#include "OneClick.h"
#include <iostream>
#include <string>
using namespace std;

class Thermostat : public OneClick::Schedule, public Device{
    public:
            Thermostat(list<string> Data);
            Thermostat(string name);
            void HeatingBoost();
            void DisplayFunctions() override;
            ostream& GetValuse(ostream& os) const override;
};

Thermostat::Thermostat(string name){
        this->SetName(name);
}

void Thermostat::HeatingBoost(){
    SetOnOff(true);
    this_thread::sleep_for(3600s);
    SetOnOff(false);
}

void Thermostat::DisplayFunctions(){
    bool Another();
    bool isNumber(const string input);
    string IsOnOff;
    string UserInput;
    bool end = true;
    if(GetOnOff()){
        IsOnOff = "ON";
    }else{
        IsOnOff = "OFF";
    }
    cout << "Name is " << GetName() << "\n"
         << "And is currently: " << IsOnOff << "\n";
         if(GetSchedule()){
            cout << "Is schedule starts at " << GetStart() << ":00 and last for " << GetLength() << " hours \n";
         }
    cout << "Its functions are: \n"
         << "1: Switch On or Off \n"
         << "2: Set/Replace a schedule \n"
         << "3: Delete Schedule if there is one \n"
         << "4: Exit Menu \n";

    while(end){
        cin >> UserInput;
        switch(UserInput[0]) {
            case '1':{
                ChangeOnOff();
                if(!Another()){
                    end = false;
                }
                break;
            }
            case '2':{
                int start;
                int length;
                string NewUserInput;
                while(true){
                    cout << "Enter start time eg (19): \n";
                    cin >> NewUserInput;
                    if(NewUserInput.length() == 2 && isNumber(NewUserInput)){
                        start = atoi((char*)NewUserInput.data());
                        break;
                    }
                }
                while(true){
                    cout << "Enter length in hours: \n";
                    cin >> NewUserInput;
                    if(isNumber(NewUserInput)){
                        length = atoi((char*)NewUserInput.data());
                        break;
                    }
                }
                StartSchedules(start, length);
            }
            case '3':{
                if(!GetSchedule()){
                    DeleteSchedule();
                }
            }
            case '4':{
                end = false;
            }
            default:{
                cout << "Enter 1,2,3,4: \n";
                cin >> UserInput;
            }
        }
    }
}

ostream& Thermostat::GetValuse(ostream& os) const{
    os << "Thermostat," << GetName() << "," << GetStart() << "," << GetLength() << "," << GetOnOff() << "," << "\n";
    return os;
}

Thermostat::Thermostat(list<string> Data){
    SetName(Data.front());
    Data.pop_front();
    string hold1 = Data.front();
    Data.pop_front();
    string hold2 = Data.front();
    Data.pop_front();
    StartSchedules(stoi(hold1), stoi(hold2));
    if(Data.front() == "1"){
        ChangeOnOff();
    }
    Data.pop_front();
}
