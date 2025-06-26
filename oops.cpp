#include <iostream>
#include <vector>
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

    void showStatus();
    void turnoff();
    void turnon();
    ~Device() {}
};

class Light : public Device
{
};

class Fan : public Device
{
private:
    int speed;
};

class AC : public Device
{
};


class Room
{
    string Room_name;
    vector<Device *> devices;

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
        if (idx < 0 || idx >= devices.size())
        {
            cout << "Invalid Device Index!" << endl;
            return;
        }

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

// User is Abstract Class
class User
{                  
    int User_type; // 1. Owner , 2. Residence , 3. Guest
    string name;
};

class Owner : public User
{
};

class Resident : public User
{
};

class Guest : public User
{
};

class SHMS
{
private:
    vector<Room *> rooms;

public:
    void add_rooms(Room *room)
    {
        rooms.push_back(room);
    }

    // here SHMS Control Pannel

    void control()
    {
        while (true)
        {
            cout << "Select The Room : " << endl;
            for (int i = 0; i < rooms.size(); i++)
            {
                cout << i << "." << rooms[i]->get_room_name() << endl;
            }

            cout << "For Exit Enter : " << rooms.size() << endl;

            int room_idx;
            cin >> room_idx;

            if (room_idx == rooms.size())
                break;

            if (room_idx < 0 && room_idx > rooms.size())
            {
                cout << "You Selected Invalid Room!" << endl;
                continue;
            }

            Room *room = rooms[room_idx];
            if (room->device_count() == 0)
            {
                cout << "This Room has no Devices!" << endl;
                continue;
            }

            // In this part we will select a device

            room->list_devices();

            cout << "Select Device Index : ";

            int deviceIdx;
            cin >> deviceIdx;

            cout << "1. Turn On" << endl
                 << "2. Turn Off" << endl;

            int cmd;
            cin >> cmd;

            room->ControlDevice(deviceIdx, cmd == 1);
        }
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
}