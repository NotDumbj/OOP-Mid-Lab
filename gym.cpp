#include<iostream>
#include<string>
#include<limits>
#include<vector>
#include<fstream> 
using namespace std;

// done some forward declarations 
class Gym;
class FitnessClass;

int loaddata(Gym& gym);
int savedata(Gym& gym);
void mainmenu();
void login(Gym& gym);
void admin_mainmenu(Gym& gym);
void user_mainmenu(Gym& gym);
void addFitnessClass(Gym& gym);
void removeFitnessClass(Gym& gym);
void bookFitnessClass(Gym& gym);
void cancelFitnessClass(Gym& gym);

class FitnessClass {
private:
    string className;
    int availableSlots;
    vector<string> bookings;

public:
    FitnessClass(string name, int slots) {
        className = name;
        availableSlots = slots;
    }

    string getClassName() {
        return className;
    }

    int getAvailableSlots() {
        return availableSlots;
    }

    bool bookSlot(string memberName) {
        if (availableSlots > 0) {
            bookings.push_back(memberName);
            availableSlots--;
            return true;
        }
        return false;
    }

    void displayBookings() {
        cout << "Bookings for " << className << ":" << endl;
        for (string booking : bookings) {
            cout << booking << endl;
        }
    }
};

class Gym {
private:
    vector<FitnessClass> fitnessClasses;

public:
    void addFitnessClass(FitnessClass fitnessClass) {
        fitnessClasses.push_back(fitnessClass);
    }

    void displayAvailableFitnessClasses() {
        cout << "Available Fitness Classes:" << endl;
        for (int i = 0; i < fitnessClasses.size(); i++) {
            cout << i + 1 << ". " << fitnessClasses[i].getClassName() << " (" << fitnessClasses[i].getAvailableSlots() << " slots available)" << endl;
        }
    }

    vector<FitnessClass>& getFitnessClasses() {
        return fitnessClasses;
    }

    FitnessClass* getFitnessClass(int classChoice) {
        if (classChoice >= 1 && classChoice <= fitnessClasses.size()) {
            return &fitnessClasses[classChoice - 1];
        }
        return nullptr;
    }
};


int main() {
    Gym gym;

    // Read fitness classes from file
    loaddata(gym);

    // Login
    login(gym);

    // Save fitness classes to file
    savedata(gym);

    return 0;
}

void login(Gym& gym)
{
    const string username = "Admin";
    const string password = "gymowner";

    bool end = false;
    while(true)
    {
        cout << "============" << endl;
        cout << " GYM SYSTEM" << endl;
        cout << "============" << endl;
        cout << "   Login" << endl;
        cout << "------------" << endl;
        cout << "  1. Admin" << endl;
        cout << "  2. User" << endl;
        cout << "  3. Exit" << endl;
        cout << "____________" << endl;
        cout << "> ";
        int choice;
        while (true)
        {
            if (cin >> choice)
            {
                string inputUsername;
                string inputPassword;
                if (choice == 1) {
                    cout << "Username: ";
                    cin >> inputUsername;
                    cout << "Password: ";
                    cin >> inputPassword;
                    if (inputUsername == username && inputPassword == password) {
                        admin_mainmenu(gym);
                    } else {
                        cout << "Invalid username or password!" << endl;
                    }
                    break;
                } else if (choice == 2) {
                    user_mainmenu(gym);
                    break;
                } else if (choice == 3) {
                    end = true;
                    break;
                } else {
                    cout << "Invalid choice!" << endl;
                    cout << "> ";
                }
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        if(end == true)
        {
            break;
        }

    }
}

void admin_mainmenu(Gym& gym)
{
    bool end = false;
    while(true)
    {
        cout << "===========================" << endl;
        cout << "        GYM SYSTEM" << endl;
        cout << "===========================" << endl;
        cout << "          Admin" << endl;
        cout << "---------------------------" << endl;
        cout << "  1. Add a Fitness Class" << endl;
        cout << "  2. Remove a Fitness Class" << endl; //if time will add a remove member feature
        cout << "  3. Exit" << endl;
        cout << "___________________________" << endl;
        cout << "> ";
        int choice;
        while (true)
        {
            if (cin >> choice)
            {
                if (choice == 1) {
                    addFitnessClass(gym);
                    break;
                } else if (choice == 2) {
                    removeFitnessClass(gym);
                    break;
                } else if (choice == 3) {
                    end = true;
                    break;
                } else {
                    cout << "Invalid choice!" << endl;
                    cout << "> ";
                }
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        if (end == true)
        {
            break;
        }
    }
    
}

void addFitnessClass(Gym& gym)
{
    cout << "Enter the name of the fitness class: ";
    string className;
    cin >> className;
    cout << "Enter the number of available slots: ";
    int availableSlots;
    while (true) {
        if (cin >> availableSlots) {
            FitnessClass fitnessClass(className, availableSlots);
            gym.addFitnessClass(fitnessClass);
            cout << "Fitness class added successfully!" << endl;
            break;
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void removeFitnessClass(Gym& gym)
{
    cout << "Enter the number of the fitness class you want to remove: ";
    int classChoice;
    while (true) {
        if (cin >> classChoice) {
            if (classChoice >= 1 && classChoice <= gym.getFitnessClasses().size()) {
                gym.getFitnessClasses().erase(gym.getFitnessClasses().begin() + classChoice - 1);
                cout << "Fitness class removed successfully!" << endl;
                break;
            }
            else {
                cout << "Invalid class choice!" << endl;
            }
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void user_mainmenu(Gym& gym)
{
    bool end = false;
    while(true)
    {
        cout << "===========================================" << endl;
        cout << "                GYM SYSTEM" << endl;
        cout << "===========================================" << endl;
        cout << "                   User" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "            Welcome to the Gym!" << endl;
        cout << "   1. Display available fitness classes" << endl;
        cout << "   2. Book a fitness class" << endl;
        cout << "   3. Cancel a fitness class" << endl;
        cout << "   4. Exit" << endl;
        cout << "_________________________________________" << endl;
        cout << "> ";
        int choice;
        while (true)
        {
            if (cin >> choice)
            {
                if (choice == 1) {
                    gym.displayAvailableFitnessClasses();
                    break;
                } else if (choice == 2) {
                    bookFitnessClass(gym);
                    break;
                } else if (choice == 3) {
                    cancelFitnessClass(gym);
                    break;
                } else if (choice == 4) {
                    end = true;
                    break;
                } else {
                    cout << "Invalid choice!" << endl;
                    cout << "> ";
                }
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        if (end == true)
        {
            break;
        }
    }
}

void bookFitnessClass(Gym& gym)
{
    cout << "Enter your name: ";
    string memberName;
    cin.ignore();
    getline(cin, memberName);
    cout << "Enter the number of the fitness class you want to book: ";
    int classChoice;
    while (true) {
        if (cin >> classChoice) {
            if (classChoice >= 1 && classChoice <= gym.getFitnessClasses().size()) {
                FitnessClass* selectedClass = gym.getFitnessClass(classChoice);
                if (selectedClass->bookSlot(memberName)) {
                    cout << "Booking successful!" << endl;
                }
                else {
                    cout << "No available slots for the selected class." << endl;
                }
                break;
            }
            else {
                cout << "Invalid class choice!" << endl;
            }
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void cancelFitnessClass(Gym& gym)
{
    cout << "Enter the number of the fitness class you want to cancel: ";
    int classChoice;
    while (true) {
        if (cin >> classChoice) {
            if (classChoice >= 1 && classChoice <= gym.getFitnessClasses().size()) {
                gym.getFitnessClasses().erase(gym.getFitnessClasses().begin() + classChoice - 1);
                cout << "Class cancelled successfully!" << endl;
                break;
            }
            else {
                cout << "Invalid class choice!" << endl;
            }
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int loaddata(Gym& gym)
{
    ifstream file("fitness_classes.txt");
    if (file.is_open()) {
        string className;
        int availableSlots;
        while (file >> className >> availableSlots) {
            FitnessClass fitnessClass(className, availableSlots);
            gym.addFitnessClass(fitnessClass);
        }
        file.close();
        return 0;
    }
    else {
        cout << "Failed to open file." << endl;
        return 1;
    }
}

int savedata(Gym& gym)
{
    ofstream file("fitness_classes.txt");
    if (file.is_open()) {
        for (FitnessClass fitnessClass : gym.getFitnessClasses()) {
            file << fitnessClass.getClassName() << " " << fitnessClass.getAvailableSlots() << endl;
        }
        file.close();
        return 0;
    }
    else {
        cout << "Failed to open file." << endl;
        return 1;
    }
}
