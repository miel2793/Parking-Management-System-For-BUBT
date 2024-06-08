#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <time.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include "sqlite3.h"

using namespace std;

/// Database Files ///


sqlite3 *db_obj;
sqlite3_stmt *stmt;
int res;
/// Global Variables ////
long long ID;
string v_num;
long long otp_main;
int vh_count_total = 0;


/// Function Declaration ///

void Connection_check();
void Create_Table();
void create_Table_2();
void create_lg();
int Get_intput();
void Find_Vehicle();
void Entry();
void Exit();
void Wrong_Number_as_Input();
void Get_data_intodb();
void Check_For_Vehicle(string vh_num_check, long long st_otp_check);
void Check_For_Cycle(long long st_otp_check);
void Forgot_Token();
void Find_token(string fg_vh_name, long long fg_id);
void Find_token_cycle(long long fg_id);
void check_vh_type();
void cycle_entry();
void Get_cycle_intodb();
int Check_DublicateID(long long id_chk);
int Check_DublicateID_cycle(long long id_chk);
int Check_Exit(long long otp_chk);
int Check_Exit_cycle(long long otp_chk);
void Exit_Confirm(long long token);
void Exit_Confirm_cycle(long long token);
void Auth();
int get_auth(string usr,string pw);
void user_side();
void user_side_show();
void proctor_side();
void wrong_auth();
void show_all();
void show_current();
/// Main Function Starts Here.......///

int optn;
int main()
{
    // system("COLOR ");
    Connection_check();
    while(1)
    {
        Auth();
    }
    sqlite3_close(db_obj);
    return 0;
}
/// Main Function Ends Here.......///

void Connection_check()
{
    if (sqlite3_open("data.db", &db_obj) == SQLITE_OK)
    {
        // cout<<"DB Connected !!\n";
        Create_Table();
        create_Table_2();
        create_lg();
    }
    else
    {
        cout << "An error Found !!\n";
    }
}
void Create_Table()
{
    res = sqlite3_prepare_v2(db_obj, "CREATE TABLE IF NOT EXISTS car(car_num VARCHAR(100),id INT ,token INT);", -1, &stmt, NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (res != SQLITE_OK)
    {
        cout << "Error !!" << sqlite3_errmsg(db_obj);
    }
    res = sqlite3_prepare_v2(db_obj, "CREATE TABLE IF NOT EXISTS montr_car(car_num VARCHAR(100),id INT ,token INT);", -1, &stmt, NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (res != SQLITE_OK)
    {
        cout << "Error !!" << sqlite3_errmsg(db_obj);
    }
}
int Get_intput()
{
    system("cls");
    cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
    cout << "\t\t1.Vehicle Entry\n";
    cout << "\t\t2.Vehicle Exit\n";
    cout << "\t\t3.Search Vehicle\n";
    cout << "\t\t4.Forgot Token Number ?\n";
    cout << "\t\t5.Visit Git-hub repository\n";
    cout << "\t\t6.Exit\n";
    cout << "\n\t\t>";
    int x;
    cin >> x;
    cin.ignore();
    return x;
}
void Find_Vehicle()
{
    system("cls");
    cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
    cout << "\t\tEnter your Vehicle Type\n\n\n";
    cout << "\t\t1. Bike/Car\n";
    cout << "\t\t2. Bi-Cycle\n";
    cout << "\t\t>";
    int ch_otpn;
    cin >> ch_otpn;
    if (ch_otpn == 1)
    {
        system("cls");
        cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
        cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
        string vh_num_check;
        long long st_otp_check;
        cout << "\t\tEnter Token Number :";
        cin >> st_otp_check;
        cin.ignore();
        cout << "\t\tEnter Vehicle Number :";
        getline(cin, vh_num_check);
        Check_For_Vehicle(vh_num_check, st_otp_check);
    }
    else if (ch_otpn == 2)
    {
        long long st_otp_check;
        cout << "\t\tEnter Token Number :";
        cin >> st_otp_check;
        cin.ignore();
        Check_For_Cycle(st_otp_check);
    }
    else
    {
        cout << "\t\tInvalid Selection !!!";
        // Sleep(2000);
    }
    Sleep(5000);
}
void Entry()
{
    system("cls");
    cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";

    cout << "\t\tEnter Student ID:";
    cin >> ID;
    cin.ignore();
    // cout<<"\t\t"<<Check_DublicateID(ID)<<endl;
    if (Check_DublicateID(ID) == 0)
    {
        cout << "\t\tEnter Vehicle Number:";
        getline(cin, v_num);
        srand(time(0));
        otp_main = rand() + 119 + rand();
        cout << "\t\tYour OTP Is : " << otp_main << "\n";
        vh_count_total++;
        cout << "\t\tYou Are Ready to Park Your Car.....";
        Get_data_intodb();
        Sleep(5000);
    }
    else
    {
        system("cls");
        cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
        cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
        cout << "\t\tYou Have Already Parked Your Car !!";
        Sleep(2000);
    }

}
void Exit()
{
    system("cls");
    cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
    cout << "\t\tEnter your Vehicle Type\n\n\n";
    cout << "\t\t1. Bike/Car\n";
    cout << "\t\t2. Bi-Cycle\n";
    cout << "\t\t>";
    int ch_otpn;
    cin >> ch_otpn;
    if (ch_otpn == 1)
    {
        system("cls");
        cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
        cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";

        long long otp_to_out;
        cout << "\t\tEnter Your OTP:";
        cin >> otp_to_out;
        if (Check_Exit(otp_to_out))
        {
            Exit_Confirm(otp_to_out);
            cout << "\t\tThanks For Using Our Service";
        }
        else
        {
            cout << "\t\tVehicle Not Found !!!";
        }
    }
    else if (ch_otpn == 2)
    {
        system("cls");
        cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
        cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";

        long long otp_to_out;
        cout << "\t\tEnter Your OTP:";
        cin >> otp_to_out;
        if (Check_Exit_cycle(otp_to_out))
        {
            Exit_Confirm_cycle(otp_to_out);
            cout << "\t\tThanks For Using Our Service";
        }
        else
        {
            cout << "\t\tVehicle Not Found !!!";
        };
    }
    else
    {
        cout << "\t\tInvalid Selection !!!";
        //Sleep(2000);
    }
    Sleep(3000);

}
void Wrong_Number_as_Input()
{
    system("cls");
    cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
    cout << "\t\tInvalid Input\n";
    cout << "\t\tPlease Enter a Number Between [ 1 - 6 ] !!!";
    Sleep(2000);
    system("cls");
}
void Get_data_intodb()
{
    /// -------------------------------------------------------

    res = sqlite3_prepare_v2(db_obj, "INSERT INTO car(car_num,id,token) VALUES(?,?,?);", -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, v_num.c_str(), v_num.length(), SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 2, ID);
    sqlite3_bind_int(stmt, 3, otp_main);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (res != SQLITE_OK)
    {
        cout << "Error !!" << sqlite3_errmsg(db_obj);
    }
    res = sqlite3_prepare_v2(db_obj, "INSERT INTO montr_car(car_num,id,token) VALUES(?,?,?);", -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, v_num.c_str(), v_num.length(), SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 2, ID);
    sqlite3_bind_int(stmt, 3, otp_main);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (res != SQLITE_OK)
    {
        cout << "Error !!" << sqlite3_errmsg(db_obj);
    }
    otp_main = -1;
    ID = -1;
    v_num = " ";

    ///--------------------------------------------------------
}
void Check_For_Vehicle(string vh_num_check, long long st_otp_check)
{
    const char *sql = "SELECT car_num , id FROM car WHERE car_num = ? AND token = ?";
    res = sqlite3_prepare_v2(db_obj, sql, -1, &stmt, NULL);
    if (res != SQLITE_OK)
    {
        cout << "Error !! " << sqlite3_errmsg(db_obj);
    }
    else
    {
        sqlite3_bind_text(stmt, 1, vh_num_check.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int64(stmt, 2, st_otp_check);
        res = sqlite3_step(stmt);
        if (res == SQLITE_ROW)
        {
            cout << "\n\t\t Your Vehicle Number :" << sqlite3_column_text(stmt, 0) << "\n\t\t Your Student ID :" << sqlite3_column_int64(stmt, 1);
            cout << "\n\t\t Your Vehicle Exists In Parking";
        }
        else
        {
            cout << "\n\t\t Your Vehicle Is Not Exist In Parking";
        }

        sqlite3_finalize(stmt);
    }
}
void Check_For_Cycle(long long st_otp_check)
{
    const char *sql = "SELECT id,token FROM cycle WHERE token = ?";
    res = sqlite3_prepare_v2(db_obj, sql, -1, &stmt, NULL);
    if (res != SQLITE_OK)
    {
        cout << "Error !! " << sqlite3_errmsg(db_obj);
    }
    else
    {
        sqlite3_bind_int64(stmt, 1, st_otp_check);
        res = sqlite3_step(stmt);
        if (res == SQLITE_ROW)
        {
            cout << "\n\t\t Your Student ID :" << sqlite3_column_int64(stmt, 0);
            cout << "\n\t\t Your Vehicle Exists In Parking";
        }
        else
        {
            cout << "\n\t\t Your Vehicle Is Not Exist In Parking";
        }

        sqlite3_finalize(stmt);
    }
}
void Forgot_Token()
{
    system("cls");
    cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
    cout << "\t\tEnter your Vehicle Type\n\n\n";
    cout << "\t\t1. Bike/Car\n";
    cout << "\t\t2. Bi-Cycle\n";
    cout << "\t\t>";
    int ch_otpn;
    cin >> ch_otpn;
    if (ch_otpn == 1)
    {
        system("cls");
        cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
        cout << "\t\t\t\t\t    Parking Management System\n\n\n\n";
        string fg_vh_name;
        long long fg_id;
        cout << "\t\tEnter Student ID :";
        cin >> fg_id;
        cin.ignore();
        cout << "\t\tEnter Vehicle Number :";
        getline(cin, fg_vh_name);
        Find_token(fg_vh_name, fg_id);
    }
    else if (ch_otpn == 2)
    {
        system("cls");
        cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
        cout << "\t\t\t\t\t    Parking Management System\n\n\n\n";
        long long fg_id;
        cout << "\t\tEnter Student ID :";
        cin >> fg_id;
        Find_token_cycle(fg_id);
    }
    else
    {
        cout << "\t\tInvalid Selection !!!";
        Sleep(2000);
    }
}
void Find_token(string fg_vh_name, long long fg_id)
{
    const char *sql = "SELECT car_num , token FROM car WHERE car_num = ? AND id = ?";
    res = sqlite3_prepare_v2(db_obj, sql, -1, &stmt, NULL);
    if (res != SQLITE_OK)
    {
        cout << "Error !! " << sqlite3_errmsg(db_obj);
    }
    else
    {
        sqlite3_bind_text(stmt, 1, fg_vh_name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int64(stmt, 2, fg_id);
        res = sqlite3_step(stmt);
        if (res == SQLITE_ROW)
        {
            cout << "\n\t\t Your Vehicle Number :" << sqlite3_column_text(stmt, 0) << "\n\t\t Your Token Number :" << sqlite3_column_int64(stmt, 1);
            cout << "\n\t\t NOTE YOUR TOKEN NUMBER WELL !!!";
        }
        else
        {
            cout << "\n\t\t Your Did not Parked !!";
        }

        sqlite3_finalize(stmt);
    }
}
void Find_token_cycle(long long fg_id)
{
    const char *sql = "SELECT id , token FROM cycle WHERE id = ?";
    res = sqlite3_prepare_v2(db_obj, sql, -1, &stmt, NULL);
    if (res != SQLITE_OK)
    {
        cout << "Error !! " << sqlite3_errmsg(db_obj);
    }
    else
    {
        sqlite3_bind_int64(stmt, 1, fg_id);
        res = sqlite3_step(stmt);
        if (res == SQLITE_ROW)
        {
            cout << "\n\t\t Your Student ID :" << sqlite3_column_text(stmt, 0) << "\n\t\t Your Token Number :" << sqlite3_column_int64(stmt, 1);
            cout << "\n\t\t NOTE YOUR TOKEN NUMBER WELL !!!";
        }
        else
        {
            cout << "\n\t\t Your Did not Parked !!";
        }

        sqlite3_finalize(stmt);
    }
}
void check_vh_type()
{
    system("cls");
    cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
    cout << "\t\tEnter your Vehicle Type\n\n\n";
    cout << "\t\t1. Bike/Car\n";
    cout << "\t\t2. Bi-Cycle\n";
    cout << "\t\t>";
    int ch_otpn;
    cin >> ch_otpn;
    if (ch_otpn == 1)
    {
        Entry();
    }
    else if (ch_otpn == 2)
    {
        cycle_entry();
    }
    else
    {
        cout << "\t\tInvalid Selection !!!";
        Sleep(2000);
    }
}
void cycle_entry()
{
    system("cls");
    cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";

    cout << "\t\tEnter Student ID:";
    cin >> ID;
    cin.ignore();
    if (!Check_DublicateID_cycle(ID))
    {
        srand(time(0));
        otp_main = rand() + 12 + rand();
        cout << "\t\tYour OTP Is : " << otp_main << "\n";
        vh_count_total++;
        cout << "\t\tYou Are Ready to Park Your Cycle.....";
        Get_cycle_intodb();
        Sleep(5000);
    }
    else
    {
        system("cls");
        cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
        cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
        cout << "\t\tYou Have Already Parked Your Cycle !!";
        Sleep(2000);
    }
}
void Get_cycle_intodb()
{
    res = sqlite3_prepare_v2(db_obj, "INSERT INTO cycle(id,token) VALUES(?,?);", -1, &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, ID);
    sqlite3_bind_int(stmt, 2, otp_main);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (res != SQLITE_OK)
    {
        cout << "Error !!" << sqlite3_errmsg(db_obj);
    }
    res = sqlite3_prepare_v2(db_obj, "INSERT INTO montr_cyc(id,token) VALUES(?,?);", -1, &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, ID);
    sqlite3_bind_int(stmt, 2, otp_main);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (res != SQLITE_OK)
    {
        cout << "Error !!" << sqlite3_errmsg(db_obj);
    }
    otp_main = -1;
    ID = -1;
}
void create_Table_2()
{
    res = sqlite3_prepare_v2(db_obj, "CREATE TABLE IF NOT EXISTS cycle(id INT ,token INT);", -1, &stmt, NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (res != SQLITE_OK)
    {
        cout << "Error !!" << sqlite3_errmsg(db_obj);
    }
    res = sqlite3_prepare_v2(db_obj, "CREATE TABLE IF NOT EXISTS montr_cyc(car_num VARCHAR(100),id INT ,token INT);", -1, &stmt, NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (res != SQLITE_OK)
    {
        cout << "Error !!" << sqlite3_errmsg(db_obj);
    }
}
void create_lg()
{
    res = sqlite3_prepare_v2(db_obj, "CREATE TABLE IF NOT EXISTS ad_lg(usr_name VARCHAR(32) ,pw VARCHAR(32));", -1, &stmt, NULL);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (res != SQLITE_OK)
    {
        cout << "Error !!" << sqlite3_errmsg(db_obj);
    }
}
int Check_DublicateID(long long id_chk)
{
    const char *sql = "SELECT id FROM car WHERE id = ?";
    res = sqlite3_prepare_v2(db_obj, sql, -1, &stmt, NULL);
    if (res != SQLITE_OK)
    {
        cout << "Error !! " << sqlite3_errmsg(db_obj);
    }
    else
    {
        sqlite3_bind_int64(stmt, 1, id_chk);
        res = sqlite3_step(stmt);
        if (res == SQLITE_ROW)
        {
            sqlite3_finalize(stmt);
            return 1;
        }
        else
        {
            sqlite3_finalize(stmt);
            return 0;
        }
    }
}
int Check_DublicateID_cycle(long long id_chk)
{
    const char *sql = "SELECT id FROM cycle WHERE id = ?";
    res = sqlite3_prepare_v2(db_obj, sql, -1, &stmt, NULL);
    if (res != SQLITE_OK)
    {
        cout << "Error !! " << sqlite3_errmsg(db_obj);
    }
    else
    {
        sqlite3_bind_int64(stmt, 1, id_chk);
        res = sqlite3_step(stmt);
        if (res == SQLITE_ROW)
        {
            sqlite3_finalize(stmt);
            return 1;
        }
        else
        {
            sqlite3_finalize(stmt);
            return 0;
        }
    }
}
int Check_Exit(long long otp_chk)
{
    const char *sql = "SELECT id FROM car WHERE token = ?";
    res = sqlite3_prepare_v2(db_obj, sql, -1, &stmt, NULL);
    if (res != SQLITE_OK)
    {
        cout << "Error !! " << sqlite3_errmsg(db_obj);
    }
    else
    {
        sqlite3_bind_int64(stmt, 1, otp_chk);
        res = sqlite3_step(stmt);
        if (res == SQLITE_ROW)
        {
            sqlite3_finalize(stmt);
            return 1;
        }
        else
        {
            sqlite3_finalize(stmt);
            return 0;
        }
    }
}
int Check_Exit_cycle(long long otp_chk)
{
    const char *sql = "SELECT id FROM cycle WHERE token = ?";
    res = sqlite3_prepare_v2(db_obj, sql, -1, &stmt, NULL);
    if (res != SQLITE_OK)
    {
        cout << "Error !! " << sqlite3_errmsg(db_obj);
    }
    else
    {
        sqlite3_bind_int64(stmt, 1, otp_chk);
        res = sqlite3_step(stmt);
        if (res == SQLITE_ROW)
        {
            sqlite3_finalize(stmt);
            return 1;
        }
        else
        {
            sqlite3_finalize(stmt);
            return 0;
        }
    }
}
void Exit_Confirm(long long token)
{
    const char *sql = "DELETE FROM car WHERE token = ?";
    res = sqlite3_prepare_v2(db_obj, sql, -1, &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, token);
    res = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (res == SQLITE_OK)
    {
        system("cls");
        cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
        cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
        cout << "\t\tError !! " << sqlite3_errmsg(db_obj);
    }
    else
    {
        system("cls");
        cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
        cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
        cout<<"\t\tYou Are Ready to Exit !!\n";
    }
}
void Exit_Confirm_cycle(long long token)
{
    const char *sql = "DELETE FROM cycle WHERE token = ?";
    res = sqlite3_prepare_v2(db_obj, sql, -1, &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, token);
    res = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (res == SQLITE_OK)
    {

        system("cls");
        cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
        cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
        cout << "\t\tError !! " << sqlite3_errmsg(db_obj);
    }
    else
    {
        system("cls");
        cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
        cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
        cout<<"\t\tYou Are Ready to Exit !!\n";
    }
}
void Auth()
{
    system("cls");
    cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
    cout << "\t\t\t\t\t   Administration Dashboard\n\n\n\n";
    cout << "\t\t 1.Proctor Login\n";
    cout << "\t\t 2.User Login\n";
    cout << "\t\t 3.Exit\n\n\n";
    cout << "\t\t >";
    int lg;
    cin >> lg;
    cin.ignore();
    if (lg <= 0 || lg > 3)
    {
        cout << "\t\t Wrong Option !";
        Sleep(2000);
        system("cls");
        Auth();
    }
    else if (lg == 2)
    {
        user_side_show();
    }
    else if(lg==1)
    {
        system("cls");
        cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
        cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
        cout << "\t\t\t\t\t   Proctorial Dashboard\n\n\n\n";
        cout << "\t\t Enter Username:";
        string usrname;
        //getline(cin, usrname);
        cin>>usrname;
        string pw_str;
        cout << "\t\t Enter Password:";
        char ch;
        while ((ch = _getch()) != '\r')
        {
            cout << '*';
            pw_str += ch;
        }
        int cnt = get_auth(usrname, pw_str);
        if (cnt == 1)
        {
            proctor_side();
        }
        else if( cnt==-1)
        {
            cout<<"\t\t\t Database Error\n";
            Sleep(3000);
        }
        else
        {
            wrong_auth();
        }
    }
    else if(lg==3)
    {
        exit(0);
    }
}
int get_auth(string usr, string pw)
{
    string sql = "SELECT usr_name FROM ad_lg WHERE usr_name = ? AND pw = ?";
    res = sqlite3_prepare_v2(db_obj, sql.c_str(), -1, &stmt, NULL);

    if (res != SQLITE_OK)
    {
        cout << "Error preparing SQL statement: " << sqlite3_errmsg(db_obj) << endl;
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, usr.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, pw.c_str(), -1, SQLITE_TRANSIENT);

    res = sqlite3_step(stmt);
    if (res == SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        return 1;
    }
    else if (res == SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        return 0;
    }
    else
    {
        cout << "Error executing SQL statement: " << sqlite3_errmsg(db_obj) << endl;
        sqlite3_finalize(stmt);
        return -1;
    }
}
void user_side()
{
    while (1)
    {
        optn = Get_intput();
        if (optn == 1)
        {
            check_vh_type();
        }
        else if (optn == 2)
        {
            Exit();
        }
        else if (optn == 3)
        {
            Find_Vehicle();
        }
        else if (optn == 4)
        {
            Forgot_Token();
            Sleep(4000);
        }
        else if (optn == 5) /// Git-hub link Visit
        {
#ifdef _WIN32
            system("start https://github.com/anas20023/Parking-Management-System-For-BUBT");
#elif __linux__
            system("xdg-open https://github.com/anas20023/Parking-Management-System-For-BUBT");
#else
            cout << "Unsupported platform" << endl;
#endif
            system("cls");
        }
        else if (optn == 6)
        {
            system("cls");
            cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
            cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
            cout << "\t\tThanks for using Our Services";
            Sleep(5000);
            //sqlite3_close(db_obj);
            break;
        }
        else /// Wrong Input
        {
            Wrong_Number_as_Input();
        }
    }

}
void proctor_side()
{
    system("cls");
    cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
    cout << "\t\t\t\t\t   Proctorial Dashboard\n\n\n\n";
    cout << "\t\t 1. View Current Parking\n";
    cout << "\t\t 2. View Log\n";
    cout << "\t\t >";
    int tlt;
    cin>>tlt;
    cin.ignore();
    if(tlt==1)
    {
        show_current();
    }
    else if(tlt==2)
    {
        show_all();
    }
}
void wrong_auth()
{
    system("cls");
    cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
    cout << "\t\t\t\t\t   Administration Dashboard\n\n\n\n";
    cout << "\t\t Wrong Username or Password !!";
    Sleep(3000);
    Auth();
}
void user_side_show()
{
    system("cls");
    cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout << "\t\t\t\t\t   Parking Management System\n\n\n\n";
    cout << "\t\t\t\t\t   User Dashboard\n\n\n\n";
    cout << "\t\t Enter Username:";
    string usrname;
    //getline(cin, usrname);
    cin>>usrname;
    string pw_str;
    cout << "\t\t Enter Password:";
    char ch;
    while ((ch = _getch()) != '\r')
    {
        cout << '*';
        pw_str += ch;
    }
    int cnt = get_auth(usrname, pw_str);
    if (cnt == 1)
    {
        user_side();
    }
    else if( cnt==-1)
    {
        cout<<"\t\t\t Database Error\n";
        Sleep(3000);
    }
    else
    {
        wrong_auth();
    }
}
void show_all()
{
    system("cls");
    cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout << "\t\t\t\t\t   Parking Management System\n\n\n";
    cout << "\t\t\t\t\t\tAll Parking Log\n\n\n\n\n\n";
    cout << "\t\t\t\t\t\tCar/Bike\n\n\n\n";
    const char *sql111 = "SELECT * FROM montr_car";
    res = sqlite3_prepare_v2(db_obj, sql111, -1, &stmt, NULL);
    if (res != SQLITE_OK)
    {
        cout << "Error !! " << sqlite3_errmsg(db_obj);
    }
    else
    {
        cout << "\n\t\t| " << setw(15) << left << "Vehicle Number" << "  | " << setw(10) << left << "Student ID" << "   | " << setw(10) << left << "   OTP" << "|" << endl;
        cout << "\t\t| " << setfill('-') << setw(16) << "" << " | " << setw(11) << "" << " | " << setw(11) << "" << " |" << setfill(' ') << endl;

        while ((res = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            cout << "\t\t| " << setw(15) << left << sqlite3_column_text(stmt, 0) << " | " << setw(10) << left << sqlite3_column_int64(stmt, 1) << " | " << setw(10) << left << sqlite3_column_int64(stmt, 2) << " |" << endl;
        }

        if (res != SQLITE_DONE)
        {
            cout << "Error fetching data: " << sqlite3_errmsg(db_obj);
        }

        sqlite3_finalize(stmt);
    }
    cout << "\n\n\n\n\t\t\t\t\t\tCycle\n\n\n";
    const char *sql2 = "SELECT * FROM montr_cyc";
    res = sqlite3_prepare_v2(db_obj, sql2, -1, &stmt, NULL);
    if (res != SQLITE_OK)
    {
        cout << "Error !! " << sqlite3_errmsg(db_obj);
    }
    else
    {
        cout << "\n\t\t| " << setw(10) << left << "Student ID" << "   | " << setw(10) << left << "   OTP" << "|" << endl;
        cout << "\t\t| " << setfill('-') << setw(11) << "" << " | " << setw(11) << "" << " |" << setfill(' ') << endl;

        while ((res = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            cout << "\t\t| " << setw(10) << left << sqlite3_column_int64(stmt, 1) << " | " << setw(10) << left << sqlite3_column_int64(stmt, 2) << " |" << endl;
        }


        if (res != SQLITE_DONE)
        {
            cout << "Error fetching data: " << sqlite3_errmsg(db_obj);
        }

        sqlite3_finalize(stmt);
    }
    Sleep(10000);
}
void show_current()
{
    system("cls");
    cout << "\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout << "\t\t\t\t\t   Parking Management System\n\n\n";
    cout << "\t\t\t\t\t\tCurrent Parking Log\n\n\n\n\n\n";
    cout << "\t\t\t\t\t\tCar/Bike\n\n\n\n";
    const char *sql121 = "SELECT * FROM car";
    res = sqlite3_prepare_v2(db_obj, sql121, -1, &stmt, NULL);
    if (res != SQLITE_OK)
    {
        cout << "Error !! " << sqlite3_errmsg(db_obj);
    }
    else
    {
        cout << "\n\t\t| " << setw(15) << left << "Vehicle Number" << "  | " << setw(10) << left << "Student ID" << "   | " << setw(10) << left << "   OTP" << "|" << endl;
        cout << "\t\t| " << setfill('-') << setw(16) << "" << " | " << setw(11) << "" << " | " << setw(11) << "" << " |" << setfill(' ') << endl;

        while ((res = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            cout << "\t\t| " << setw(15) << left << sqlite3_column_text(stmt, 0) << " | " << setw(10) << left << sqlite3_column_int64(stmt, 1) << " | " << setw(10) << left << sqlite3_column_int64(stmt, 2) << " |" << endl;
        }

        if (res != SQLITE_DONE)
        {
            cout << "Error fetching data: " << sqlite3_errmsg(db_obj);
        }

        sqlite3_finalize(stmt);
    }
    cout << "\n\n\n\n\t\t\t\t\t\tCycle\n\n\n";
    const char *sql22 = "SELECT * FROM cyc";
    res = sqlite3_prepare_v2(db_obj, sql22, -1, &stmt, NULL);
    if (res != SQLITE_OK)
    {
        cout << "Error !! " << sqlite3_errmsg(db_obj);
    }
    else
    {
        cout << "\n\t\t| " << setw(10) << left << "Student ID" << "   | " << setw(10) << left << "   OTP" << "|" << endl;
        cout << "\t\t| " << setfill('-') << setw(11) << "" << " | " << setw(11) << "" << " |" << setfill(' ') << endl;

        while ((res = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            cout << "\t\t| " << setw(10) << left << sqlite3_column_int64(stmt, 1) << " | " << setw(10) << left << sqlite3_column_int64(stmt, 2) << " |" << endl;
        }


        if (res != SQLITE_DONE)
        {
            cout << "Error fetching data: " << sqlite3_errmsg(db_obj);
        }

        sqlite3_finalize(stmt);
    }
    Sleep(10000);
}