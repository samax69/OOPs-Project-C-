#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <utility>
#include<filesystem>
using namespace std;

// Abstract Class
class Device
{
protected:
    string name;
    bool status;

public:
    Device(string Name)
    {
        name = Name;
        status = false;
    }

    virtual void showStatus() = 0;
    virtual void turnoff() = 0;
    virtual void turnon() = 0;
    ~Device() {}
};


class Light : public Device
{
public:
    Light(string name) : Device(name) {}

    void turnon(){
        status = true;
        cout << "You turned on " << name << "Light!" << endl;
    }

    void turnoff(){
        status = false;
        cout << "You turned off " << name << "Light!" << endl;
    }

    void showStatus(){
        if(status){
            cout << name << "Light is Turned On!" << endl;
        }

        else{
            cout << name << "Light is Turned Off!" << endl;
        }
    }
};

class Fan : public Device
{
private:
    int speed;

public:
    Fan(string name) : Device(name) {}

    void turnon(){
        status = true;
        cout << "You turned on " << name << "Fan!" << endl;
    }

    void turnoff(){
        status = false;
        cout << "You turned off " << name << "Fan!" << endl;
    }

    void showStatus(){
        if(status){
            cout << name << "Fan is Turned On!" << endl;
        }

        else{
            cout << name << "Fan is Turned Off!" << endl;
        }
    }
};

class AC : public Device
{
public:
    AC(string name) : Device(name) {}

    void turnon(){
        status = true;
        cout << "You turned on " << name << "AC!" << endl;
    }

    void turnoff(){
        status = false;
        cout << "You turned off " << name << "AC!" << endl;
    }

    void showStatus(){
        if(status){
            cout << name << "AC is Turned On!" << endl;
        }

        else{
            cout << name << "AC is Turned Off!" << endl;
        }
    }
};

class Room
{
    string Room_name;
    vector<Device *> devices;
    friend class SHMS;

public:
    Room(string name)
    {
        Room_name = name;
    }

    void add_device(Device *device)
    {
        devices.push_back(device);
    }

    void show_Room_status()
    {
        cout << endl
             << "Status of " << Room_name << ":" << endl;

        for (auto &device : devices)
        {
            device->showStatus();
        }
    }

    void list_devices()
    {
        for (int i = 0; i < devices.size(); i++)
        {
            cout << i << ". ";
            devices[i]->showStatus();
        }
    }

    void ControlDevice(int idx, bool on)
    {

        if (on)
        {
            devices[idx]->turnon();
        }
        else
        {
            devices[idx]->turnoff();
        }
    }

    string get_room_name()
    {
        return Room_name;
    }

    int device_count()
    {
        return devices.size();
    }
};

enum User_Type
{
    OWNER,
    RESIDENT,
    GUEST
};

// User is Abstract Class
class User
{
    protected:
    User_Type usertype; 
    string name;

    public:
    User(string Name , User_Type type)
    {
        name = Name;
        usertype = type;
    }

    virtual bool canControl(Device* device) = 0; // Abstract method to check if user can control devices
    string getName(){
        return name;
    }

    User_Type getUserType(){
        return usertype;
    }

    virtual ~User() {} // Virtual destructor for proper cleanup
};



class Owner : public User
{
    public:
    Owner(string Name) : User(Name, OWNER) {}

    bool canControl(Device* device){
        return true; // Owner can control all devices
    }
};

class Resident : public User
{
    public:
    Resident(string Name) : User(Name, RESIDENT) {}
    bool canControl(Device* device){
        // Residents can control only lights and fans
        return dynamic_cast<Light*>(device) != nullptr || dynamic_cast<Fan*>(device) != nullptr;
    }
};

class Guest : public User
{
    public:
    Guest(string Name) : User(Name, GUEST) {}
    bool canControl(Device* device){
        // Guests can't control any devices
        return false;
    }
};

class SHMS
{
private:
    vector<Room *> rooms;
    User* currentUser = NULL;

public:
    void setCurrentUser(User* user)
    {
        currentUser = user;
    }

    void add_rooms(Room *room)
    {
        rooms.push_back(room);
    }

   // get a list of all rooms so that user can select a room
    vector<string> getRoomNames(){
        vector<string> roomNames;
        for (auto &room : rooms)
        {
            roomNames.push_back(room->get_room_name());
        }
        return roomNames;
    }

    // get device names for a room index
    vector<string> getDeviceNames(int roomIndex)
    {
        vector<string> deviceNames;
        if (roomIndex >= 0 && roomIndex < rooms.size())
        {
            Room* room = rooms[roomIndex];
            for (int i = 0; i < room->device_count(); i++)
            {
                deviceNames.push_back(room->devices[i]->name);
            }
        }
        return deviceNames;
    }

    // check if the current user can control a device
    bool canCurrentUserControl(int roomIndex, int deviceIndex)
    {
        if (currentUser == NULL || roomIndex < 0 || roomIndex >= rooms.size())
        {
            return false;
        }
        Room* room = rooms[roomIndex];
        if (deviceIndex < 0 || deviceIndex >= room->device_count())
        {
            return false; // Invalid device index
        }
        Device* device = room->devices[deviceIndex];
        return currentUser->canControl(device);
    }
    

    // control a device in a room
    string controlDevice(int roomIndex, int deviceIndex, bool turnOn){
        if (!canCurrentUserControl(roomIndex, deviceIndex)) {
            return "You don't have permission to control this device!";
        }

        rooms[roomIndex]->ControlDevice(deviceIndex, turnOn);
        return "Device control successful!";
    }

    void showAll()
    {
        for (auto room : rooms)
        {
            room->show_Room_status();
        }
    }

    ~SHMS()
    {
        for (auto room : rooms)
        {
            delete room;
        }
    }
};

int main()
{
    // here We can use username and password for login
    // to implement this we can use a map to store username and password
    unordered_map<string , pair<string , User*>> users; // username -> (password, User*)>
    users["owner123"] = make_pair("owner#123" , new Owner("Vaibhav"));
    users["resident123"] = make_pair("resident#123" , new Resident("Muskan"));
    users["guest123"] = make_pair("guest#123" , new Guest("Vicky"));

    string user_name;
    string password;
    cout << "Enter Username: ";
    cin >> user_name;
    cout << "Enter Password: ";
    cin >> password;

   // Check if user exists
    if (users.find(user_name) == users.end() || users[user_name].first != password)
    {
        cout << "Invalid Username or Password!" << endl;
        return 0;
    }

    User* currentUser = users[user_name].second;

    // Create SHMS instance and set current user
    SHMS home;
    home.setCurrentUser(currentUser);

    // adding rooms and devices
    Room *livingRoom = new Room("Living Room");
    livingRoom->add_device(new Light("Living Room "));
    livingRoom->add_device(new Fan("Living Room "));
    livingRoom->add_device(new AC("Living Room "));
    home.add_rooms(livingRoom);

    Room *bedRoom = new Room("Bed Room");
    bedRoom->add_device(new Light("Bed Room "));
    bedRoom->add_device(new Fan("Bed Room "));
    bedRoom->add_device(new AC("Bed Room "));
    home.add_rooms(bedRoom);

    Room *kitchen = new Room("Kitchen");
    kitchen->add_device(new Light("Kitchen "));
    home.add_rooms(kitchen);

    Room *GuestRoom = new Room("Guest Room");
    GuestRoom->add_device(new Light("Guest Room ")); 
    GuestRoom->add_device(new Fan("Guest Room "));
    GuestRoom->add_device(new AC("Guest Room "));
    home.add_rooms(GuestRoom);
    
    return 0;
    
}
