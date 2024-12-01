#include "iostream"
#include "fstream"
#include "bits/stdc++.h"
#include "doctor.cpp"
#include "appointment.cpp"
using namespace std;
class Menu{
public:
    Menu(){
        bool flag =true;
        while(flag)
        {
            this_thread::sleep_for(chrono::seconds(1));
            cout<<"Choose one of the following: "
            "1.Add New Doctor"
            "2.Add New Appointment"
            "3.Update Doctor Name"
            "4.Update Appointment Date"
            "5.Delete Appointment"
            "6.Delete Doctor"
            "7.Print Doctor Info"
            "8.Print Appointment Info"
            "9.Write Query"
            "0.Exit: ";
            int choice;
            cin>>choice;
            cases(flag,choice);
        }
        
    }
    
    void cases(bool&flag, int choice)
    {
        char doctor_id [15], appointment_id [15],
            doctor_name [30], address [30], appointment_date [30];
        string query;
        
        switch (choice) {
        case 1:
            cout<<"enter doctor's id: ";
            cin>> doctor_id;
            cout<<"enter doctor's name: ";
            cin>> doctor_name;
            cout<<"enter doctor's address: ";
            cin>> address;
            //Add New Doctor
            break;
        case 2:
            cout<<"enter doctor's id: ";
            cin>> doctor_id;
            cout<<"enter appointment's id: ";
            cin>> appointment_id;
            cout<<"enter appointment's date: ";
            cin>> appointment_date;
            //Add New Appointment
            break;
        case 3:
            cout<<"enter the updated doctor's id: ";
            cin>> doctor_id;
            cout<<"enter the new name: ";
            cin>> doctor_name;
            //Update Doctor Name (Doctor ID)
            break;
        case 4:
            cout<<"enter the updated appointment's id: ";
            cin>> appointment_id;
            cout<<"enter the new date: ";
            cin>> appointment_date;
            //Update Appointment Date (Appointment ID)
            break;
        case 5:
            cout<<"enter the appointment's id you want to delete: ";
            cin>> appointment_id;
            //Delete Appointment (Appointment ID)
            break;
        case 6:
            cout<<"enter the doctor's id you want to delete: ";
            cin>> doctor_id;
            //Delete Doctor (Doctor ID)
            break;
        case 7:
            cout<<"enter the doctor's id: ";
            cin>> doctor_id;
            //Print Doctor Info (Doctor ID)
            break;
        case 8:
            cout<<"enter the appointment's id: ";
            cin>> appointment_id;
            //Print Appointment Info (Appointment ID)
            break;
        case 9:
            cout<<"enter your query: ";
            cin>> query;
            //Write Query
            break;
        case 0:
            flag=false;
            break;
        default:
            cout<<"Invalid choice!! /n Please try again with a number in between 9-0\n";
            break;
        }
    }
    
};

