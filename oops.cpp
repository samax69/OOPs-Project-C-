#include<iostream>
#include<vector>
using namespace std;

class Device{
    protected:
    string name;
    bool status;

    public:
    void showStatus();
    


};

void Device :: showStatus(){
    if(status == 1) {
        cout << "Device is On" << endl;
    }

    else{
        cout << "Device is Off" << endl;
    }
}

class Light : public Device{

};

class Fan : public Device{
    private:
    int speed;

    
};

class AC : public Device{

};

class Room{
    string Room_name;
    vector <Device*> devices;

};

class User{   // this should be my Abstract Class
    int User_type;  // 1. Owner , 2. Residence , 3. Guest
    string name;
};

class Owner : public User{

};

class Resident: public User{

};

class Guest: public User{

};

class SHMS{
    vector<Room*> rooms;
};


int main(){

}