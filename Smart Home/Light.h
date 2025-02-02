#pragma once
#include "OneClick.h"
#include <iostream>
#include <string>
using namespace std;

class Light : public OneClick::SleepTimer, public Device{
        public:
            Light(list<string> Data);
            inline ~Light(){delete this;};
            inline Light(string name) : brightness(0){this->SetName(name);};
            inline void setBrightness(int brightness){this->brightness = brightness;};
            void DisplayFunctions() override;
            ostream& GetValuse(ostream& os) const override;

        private:
            int brightness;
};

void Light::DisplayFunctions(){
    bool Another();
    string IsOnOff;
    string UserInput;
    bool end = true;
    if(GetOnOff()){
        IsOnOff = "ON";
    }else{
        IsOnOff = "OFF";
    }
    cout << "Name is " << GetName() << "\n"
         << "Its brightness is : " << brightness << "\n"
         << "And is currently: " << IsOnOff << "\n"
         << "Its functions are: \n"
         << "1: Change brightness \n"
         << "2: Switch On or Off \n"
         << "3: Exit Menu \n";

    while(end){
        cin >> UserInput;
        switch(UserInput[0]) {
            case '1':{
                int NewBrightness;
                cout << "Enter new brightness: \n";
                cin >> NewBrightness;
                if(!Another()){
                    end = false;
                }
                break;
            }
            case '2':{
                ChangeOnOff();
                if(!Another()){
                    end = false;
                }
                break;
            }
            case '3':{
                end = false;
            }
            default:{
                cout << "Enter 1,2,3: \n";
                cin >> UserInput;
            }
        }
    }
}

bool Another(){
    string UserInput;
    cout << "Would you like another option (Y/N): \n";
    cin >> UserInput;
    while(true){
            if((char)toupper(UserInput[0]) == 'Y'){
                return true;
            }else if((char)toupper(UserInput[0]) == 'N'){
                return false;
            }else{
                cout << "Enter Y/N \n";
                cin >> UserInput;
            }
    }
}

ostream& Light::GetValuse(ostream& os) const{
    os << "Light," << GetName() << "," << brightness << "," << GetOnOff() << "\n";
    return os;
}

Light::Light(list<string> Data){
    SetName(Data.front());
    Data.pop_front();
    brightness = stoi(Data.front());
    Data.pop_front();
    if(Data.front() == "1"){
        ChangeOnOff();
    }
    Data.pop_front();
}
