#pragma once
#include <iostream>
#include <string>
#include <functional>
using namespace std;

class Device{
        public:
                inline string GetName() const {return name;};
                virtual void DisplayFunctions() = 0;
                friend ostream& operator<<(ostream& os, const Device& data);
                virtual ostream& GetValuse(ostream& os) const = 0;

        protected:
                inline Device() : name("NULL"){};
                inline void SetName(string name){this->name = name;};

        private:
                string name;
};

ostream& operator<<(ostream& os, const Device& data){
        return data.GetValuse(os);
}