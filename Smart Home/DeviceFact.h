#include "Light.h"
#include "Plug.h"
#include "Radiator.h"
#include "Speaker.h"
#include "TempHum.h"
#include "Thermostat.h"

class DeviceFact{
	public:
		 static Device* createDevice(int type, const string& name, bool& end, int& temp, int& humidity);
};

Device* DeviceFact::createDevice(int type, const string& name, bool& end, int& temp, int& humidity) {
	 switch (type) {
		 case 1: 
			{ 
			 return new Light(name);
			 break;
			}
		 case 2:
		 {
            int HistoricMax;
            float sensitivity;
            int power;
            cout << "Enter maximum amount of readings stored \n";
            cin >> HistoricMax;
            cout << "Enter how often are reading taken in seconds \n";
            cin >> sensitivity;
            cout << "Enter power consumption of the plug \n";
            cin >> power;
			return new Plug(name, HistoricMax, sensitivity, power);
			break;
		 }
        case 3: 
        { 
            return new Radiator(name);
            break;
        }
        case 4:
        {
            int MaxVolume;
            cout << "Enter maximum volume of the speaker \n";
            cin >> MaxVolume;
            return new Speaker(name, MaxVolume);
            break;
        }
        case 5:
        
		 {
            int HistoricMax;
            float sensitivity;
            int power;
            cout << "Enter maximum amount of readings stored \n";
            cin >> HistoricMax;
            cout << "Enter how often are reading taken in seconds \n";
            cin >> sensitivity;
			return new TempHum(name, HistoricMax, sensitivity, temp, humidity);
			break;
		 }
        case 6: 
        { 
            return new Thermostat(name);
            break;
        }
        default:
            return nullptr;
            break;
	}
}