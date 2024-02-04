#include <iostream>
#include <stdlib.h>
#include "sqlite3.h"

using namespace std;

///Database Files ///

sqlite3 *db_obj;
sqlite3_stmt *stmt;
int res;

///Function Declaretion ///

void Connection_check();
void Create_Table();
int Get_intput();

///Main Function Starts Here.......///

int main()
{
    int optn;
    optn=Get_intput();
    system("cls");
    cout<<optn;
    Connection_check();
    sqlite3_close(db_obj);
    return 0;
}

void Connection_check()
{
    if(sqlite3_open("entry.db",&db_obj)==SQLITE_OK)
    {
        //  cout<<"DB Connected !!\n";
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
    cout<<"\n\t\t\t\tBangladesh University of Business and Technology\n";
    cout<<"\t\t\t\t\t   Parking Management System\n\n\n\n";
    cout<<"\t\t1.Vehicle Entry\n";
    cout<<"\t\t2.Vehicle Exit\n";
    cout<<"\t\t3.Search Vehicle\n";
    cout<<"\t\t4.Check Space Availablity\n";
    cout<<"\t\t5.Visit Github repository\n";
    cout<<"\t\t6.Exit\n";
    cout<<"\n\t\tChoose an Option:";
    int x;
    cin>>x;
    return x;
}
