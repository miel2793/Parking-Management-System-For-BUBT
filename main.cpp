#include <iostream>
#include "sqlite3.h"

using namespace std;

int main()
{
    sqlite3 *db_obj;
    sqlite3_open("entry.db",&db_obj);
    cout << "Hello world!" << endl;
    return 0;
}
