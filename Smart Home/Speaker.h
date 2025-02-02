#pragma once
#include "OneClick.h"

class Speaker : public OneClick, public Device{
        public:
                Speaker(list<string> Data);
                inline Speaker() : volume(0), MaxVolume(10){};
                inline Speaker(string name, int MaxVolume);
                inline void Setvolume(int volume){this->volume = volume;};
                inline void volumeUp(){if(volume != MaxVolume) volume++;};
                inline void volumeDown(){if(volume != 0) volume--;};
                void DisplayFunctions() override;
                ostream& GetValuse(ostream& os) const override;

        private:
                int volume;
                int MaxVolume;
};

Speaker::Speaker(string name, int MaxVolume) : volume(0), MaxVolume(MaxVolume){
    this->SetName(name);
}

void Speaker::DisplayFunctions(){
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
         << "Its volume is : " << volume << "\n"
         << "And it's currently: " << IsOnOff << "\n"
         << "Its functions are: \n"
         << "1: volume Up \n"
         << "2: volume Down \n"
         << "3: Switch On or Off \n"
         << "4: Exit Menu \n";

    while(end){
        cin >> UserInput;
        switch(UserInput[0]) {
            case '1':{
                volumeUp();
            }
            case '2':{   
                volumeDown();
            }
            case '3':{
                ChangeOnOff();
                if(!Another()){
                    end = false;
                }
                break;
            }
            case '4':{
                end = false;
            }
            default:{
                cout << "Enter 1,2,3: \n";
                cin >> UserInput;
            }
        }
    }
}

ostream& Speaker::GetValuse(ostream& os) const{
    os << "Speaker," << GetName() << "," << volume << "," << MaxVolume << "," << GetOnOff() << "\n";
    return os;
}

Speaker::Speaker(list<string> Data){
    SetName(Data.front());
    Data.pop_front();
    volume = stoi(Data.front());
    Data.pop_front();
    MaxVolume = stoi(Data.front());
    Data.pop_front();
    if(Data.front() == "1"){
        ChangeOnOff();
    }
    Data.pop_front();
}
