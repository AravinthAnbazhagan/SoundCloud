#ifndef ARTISTPAGE_H_INCLUDED
#define ARTISTPAGE_H_INCLUDED

#include <mysql/mysql.h>
#include <iostream>
#include <string>
using namespace std;

// Function to connect to the database
MYSQL* connectDatabase() {
    MYSQL* conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "username", "1234", "soundcloud", 0, NULL, 0)) {
        cerr << "Failed to connect to database: " << mysql_error(conn) << endl;
        exit(EXIT_FAILURE);
    }
    return conn;
}

// Function to retrieve and show artist details by name or ID
void displayArtistDetails(const string& artistName) {
    MYSQL* conn = connectDatabase();
    string query = "SELECT id, name FROM artists WHERE name = '" + artistName + "';";

    if (mysql_query(conn, query.c_str()) != 0) {
        cerr << "Query Error: " << mysql_error(conn) << endl;
        mysql_close(conn);
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    if ((row = mysql_fetch_row(res))) {
        cout << "Artist Details:" << endl;
        cout << "ID    : " << row[0] << endl;
        cout << "Name  : " << row[1] << endl;
    } else {
        cout << "No artist found with the name '" << artistName << "'." << endl;
    }

    mysql_free_result(res);
    mysql_close(conn);
}

#endif // ARTISTPAGE_H_INCLUDED
