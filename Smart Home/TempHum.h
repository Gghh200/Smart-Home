#pragma once
#include "LiveHistoric.h"
#include <array>
#include <iostream>
using namespace std;

class TempHum : public LiveHistoric<array<int, 2>>, public Device{
    public:
        TempHum(list<string> Data, int& temp, int& humidity);
        TempHum(int& temp, int& humidity);
        TempHum(string name, int HistoricMax, float sensitivity, int& temp, int& humidity);
        void DisplayFunctions() override;
        ostream& GetValuse(ostream& os) const override;
        
    private:
        void incrementLive() override;
        int& temp;
        int& humidity;
};

TempHum::TempHum(int& temp, int& humidity) : humidity(humidity), temp(temp), LiveHistoric(0, 0){};

TempHum::TempHum(string name, int HistoricMax, float sensitivity, int& temp, int& humidity) : humidity(humidity), temp(temp), 
                 LiveHistoric(HistoricMax, sensitivity){
    this->SetName(name);
    UpdateLive();
}


void TempHum::incrementLive(){
    array<int, 2> value = {temp, humidity};
    SetLive(value);
}

void TempHum::DisplayFunctions(){
    cout << "Name is " << GetName() << "\n"
         << "The current temp is: " << (GetLive()[0]) << "\n"
         << "The current Humidity is: " << GetLive()[1] << "\n";
}

ostream& TempHum::GetValuse(ostream& os) const{
    os << "TempHum," << GetName() << "," << GetHistoricMax() << ","<< GetSensitivity()<< ",";
    for(int i = GetHistoric().size(); i > 0; i--){
        array<int, 2> arr = GetHistoric().front();
        GetHistoric().pop();
        os << arr[0] << ",";
        os << arr[1] << ",";
    }
    os << "\n";
    return os;
}

TempHum::TempHum(list<string> Data, int& temp, int& humidity) : temp(temp), humidity(humidity), LiveHistoric(array<int, 2> {0,0}){
    SetName(Data.front());
    Data.pop_front();
    SetHistoricMax(stoi(Data.front()));
    Data.pop_front();
    SetSensitivity(stoi(Data.front()));
    Data.pop_front();
    while(Data.empty())
    {
        string hold1 = Data.front();
        Data.pop_front();
        string hold2 = Data.front();
        Data.pop_front();
        array<int, 2> value = {stoi(hold1), stoi(hold2)};
        AddToHistoric(value);
    }
    UpdateLive();
}