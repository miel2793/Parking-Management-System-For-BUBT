#include <iostream>
#include<windows.h>
#include <cstdlib>
#include <time.h>
#include<unistd.h>
#include <stdlib.h>
#include "sqlite3.h"

using namespace std;

///Database Files ///

sqlite3 *db_obj;
sqlite3_stmt *stmt;
int res;
/// Global Variables ////
long long ID;
string v_num;
long long otp_main;
int vh_count_total=0;

///Function Declaration ///

void Connection_check();
void Create_Table();
int Get_intput();
void Find_Vehicle();
void Entry();
void Exit();
///Main Function Starts Here.......///

int optn;
int main()
{
    Connection_check();
    while(1)
    {
        optn=Get_intput();
        if(optn==1)
        {
            Entry();
        }
        else if(optn==2)
        {
            Exit();
        }
        else if(optn==3)
        {
            Find_Vehicle();
        }
        else if(optn==4)
        {
            cout<<"Check Space Availability\n";
            break; /// apatoto break
        }
        else if(optn==5)
        {
            cout<<"github/////link pore diboni\n";
            break; /// apatoto break
        }
        else if(optn==6)
        {
            cout<<"Thanks for using Our Services\n";
            break; /// apatoto break
        }
        else
        {
            system("cls");
            cout<<"\t\tInvalid Input\n";
            Sleep(3000);
            system("cls");
        }
    }

    sqlite3_close(db_obj);
    return 0;
}
///Main Function Ends Here.......///

void Connection_check()
{
    if(sqlite3_open("entry.db",&db_obj)==SQLITE_OK)
    {
        //cout<<"DB Connected !!\n";
        Create_Table();
    }
    else
    {
        cout<<"An error Found !!\n";
    }
}
void Create_Table()
{
    res=sqlite3_prepare_v2(db_obj,"CREATE TABLE IF NOT EXISTS entry(name varchar(50),id INT ,token INT , email varchar(80));",-1,&stmt,NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if(res!=SQLITE_OK)
    {
        cout<<"Error !!"<<sqlite3_errmsg(db_obj);
    }
}

int Get_intput()
{
    system("cls");
    cout<<"\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout<<"\t\t\t\t\t   Parking Management System\n\n\n\n";
    cout<<"\t\t1.Vehicle Entry\n";
    cout<<"\t\t2.Vehicle Exit\n";
    cout<<"\t\t3.Search Vehicle\n";
    cout<<"\t\t4.Check Space Availability\n";
    cout<<"\t\t5.Visit Git-hub repository\n";
    cout<<"\t\t6.Exit\n";
    cout<<"\n\t\t>";
    int x;
    cin>>x;
    cin.ignore();
    return x;
}
void Find_Vehicle()
{
    string vh_num_check;
    long long st_id_check;
    cout<<"\t\tEnter Vehicle Number :";
    getline(cin,vh_num_check);
    cin.ignore();
    if(vh_num_check==v_num)
    {
        cout<<"\t\tEnter Student ID :";
        cin>>st_id_check;
        cin.ignore();
        if(st_id_check==ID)
        {
            cout<<"\t\tVehicle Found !";
        }
        else
        {
            cout<<"\t\tStudent ID Not Matched !";
        }
    }
    else
    {
        cout<<"\t\tVehicle Not Found";
    }
    Sleep(2000);

}
void Entry()
{
    system("cls");
    cout<<"\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout<<"\t\t\t\t\t   Parking Management System\n\n\n\n";

    cout<<"\t\tEnter Student ID:";
    cin>>ID;
    cin.ignore();
    cout<<"\t\tEnter Vehicle Number:";
    getline(cin,v_num);
    srand(time(0));
    otp_main=rand()+119;
    cout<<"\t\tYour OTP Is : "<<otp_main<<"\n";
    vh_count_total++;
    cout<<"\t\tYou Are Ready to Park Your Car.....";
    Sleep(5000);
}
void Exit()
{
    system("cls");
    cout<<"\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout<<"\t\t\t\t\t   Parking Management System\n\n\n\n";

    long long otp_to_out;
    cout<<"\t\tEnter Your OTP:";
    cin>>otp_to_out;
    cin.ignore();
    if(otp_to_out==otp_main)
    {
        cout<<"\t\tOTP Matched !";
        otp_main=-1;
        vh_count_total--;
    }
    else
    {
        cout<<"\t\tWrong OTP!";
    }
    Sleep(2000);

}
