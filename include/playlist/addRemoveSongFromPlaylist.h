#ifndef ADDREMOVESONGFROMPLAYLIST_H_INCLUDED
#define ADDREMOVESONGFROMPLAYLIST_H_INCLUDED

#include <mysql/mysql.h>
#include <iostream>
using namespace std;

MYSQL* connectDatabase() {
    MYSQL* conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "usename", "1234", "soundcloud", 0, NULL, 0)) {
        cerr << "Database connection failed: " << mysql_error(conn) << endl;
        exit(EXIT_FAILURE);
    }
    return conn;
}

void addSongToPlaylist(int userId, const string& playlistName, int songId) {
    MYSQL* conn = connectDatabase();
    string query = "INSERT INTO user_playlists (userid, name, songid) VALUES (" +
                   to_string(userId) + ", '" + playlistName + "', " + to_string(songId) + ");";
    
    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Song added to playlist successfully." << endl;
    } else {
        cerr << "Error adding song to playlist: " << mysql_error(conn) << endl;
    }
    mysql_close(conn);
}

void removeSongFromPlaylist(int userId, const string& playlistName) {
    MYSQL* conn = connectDatabase();
    string query = "DELETE FROM user_playlists WHERE userid = " + to_string(userId) +
                   " AND name = '" + playlistName + "';";
    
    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Playlist removed successfully." << endl;
    } else {
        cerr << "Error removing playlist: " << mysql_error(conn) << endl;
    }
    mysql_close(conn);
}

#endif // ADDREMOVESONGFROMPLAYLIST_H_INCLUDED
