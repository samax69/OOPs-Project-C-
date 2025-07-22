A console‑based Smart Home Management System built in **C++** using **Object‑Oriented Programming principles**: inheritance, polymorphism, encapsulation, and dynamic dispatch.  
Users can log in with different roles (Owner, Resident, Guest) and control devices based on their permissions.

**Features**
- **Multiple user types**:
  - **Owner**: Full control over all devices.
  - **Resident**: Control of **Lights** and **Fans** only.
  - **Guest**: No control permissions.
- **Device types**: Light, Fan, AC – each with `turnOn`, `turnOff`, and `showStatus`.
- **Room grouping**: Rooms (Living, Bedroom, Kitchen, Guest Room) each holding a set of devices.
- **Role-based access control**: Enforced via virtual methods and runtime type-checking.
- **Interactive login**: Username & password authentication using an in-memory user map.
