#pragma once
#include "OneClick.h"
#include "LiveHistoric.h"

class Plug : public OneClick::SleepTimer, public OneClick::Schedule, public LiveHistoric<int>, public Device{
    public:
        Plug(list<string> Data);
        Plug(string name, int HistoricMax, float sensitivity, int power);
        void DisplayFunctions() override;
        ostream& GetValuse(ostream& os) const;
        
    private:
        void incrementLive() override;
        int power;
};

Plug::Plug(string name, int HistoricMax, float sensitivity, int power) : power(power), LiveHistoric(HistoricMax, sensitivity){
    this->SetName(name);
    UpdateLive();
}

void Plug::incrementLive(){
    srand(time(0));
    if(this->OneClick::GetOnOff()){
        if(rand() % 2 == 0){
            int temp = (power + rand() % 3);
            this->SetLive(temp);
        }else{
            int temp = (power - rand() % 3);
            this->SetLive(temp);
        }
    }
}

void Plug::DisplayFunctions(){
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
         << "Its current power usage is : " << GetLive() << "\n"
         << "And is currently: " << IsOnOff << "\n";
         if(GetSchedule()){
            cout << "Is schedule starts at " << GetStart() << ":00 and last for " << GetLength() << " hours \n";
         }
    cout << "Its functions are: \n"
         << "1: Switch On or Off \n"
         << "2: Set/Replace a schedule \n"
         << "3: Delete Schedule if there is one \n"
         << "4: Sleep Timer \n"
         << "5: Exit Menu \n";

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
                cout << "Enter start hour eg (19): \n";
                cin >> NewUserInput;
                while(true){
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
                int length;
                string NewUserInput;
                while(true){
                    cout << "Enter how long the device should be on for in seconds: \n";
                    cin >> NewUserInput;
                    if(isNumber(NewUserInput)){
                        length = atoi((char*)NewUserInput.data());
                        break;
                    }
                }
                call(length);
            }
            case '5':{
                end = false;
            }
            default:{
                cout << "Enter 1,2,3,4: \n";
                cin >> UserInput;
            }
        }
    }
}

bool isNumber(const string input){
    for (char digit : input) {
        if (!isdigit(digit)) {
            return false;
        }
    }
    return true;
}

ostream& Plug::GetValuse(ostream& os) const{
    os << "Plug," << GetName() << "," << power << "," << GetHistoricMax() << ","<< GetSensitivity() << "," << GetStart() 
       << "," << GetLength() << "," << GetOnOff();
    for(int i = GetHistoric().size(); i > 0; i--){
        int arr = GetHistoric().front();
        GetHistoric().pop();
        os << arr << ",";
    }
    os << "\n";
    return os;
}

Plug::Plug(list<string> Data) : LiveHistoric(0){
    SetName(Data.front());
    Data.pop_front();
    power = stoi(Data.front());
    Data.pop_front();
    SetSensitivity(stoi(Data.front()));
    Data.pop_front();
    SetHistoricMax(stoi(Data.front()));
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
    for(string i : Data){
        AddToHistoric(stoi(i));
    }
    UpdateLive();
}
