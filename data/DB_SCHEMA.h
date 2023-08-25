#ifndef DB_SCHEMA_H_
#define DB_SCHEMA_H_

#pragma once
#include <string>
#include <unordered_map>

static const std::string SELECT_QUERY = "SELECT * FROM TIMERS;";

static const std::string DB_SCHEMA = "CREATE TABLE IF NOT EXISTS TIMERS( "
"ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
"TITLE          VARCHAR(255)  NOT NULL,"
"START_DATE     INT8          NOT NULL,"
"STATE          VARCHAR(255)  NOT NULL,"
"DURATION       INT8          NOT NULL,"
"ELAPSED        INT8,"
"PAUSED         INT8"
");";
static const std::string INSERT_QUERY = "INSERT INTO TIMERS (TITLE, START_DATE, STATE, DURATION, ELAPSED, PAUSED) "
"VALUES (?, ?, ?, ?, ?, ?);";
static const std::unordered_map<std::string, int> INSERT_BINDINGS = {
    {"TITLE", 1},
    {"START_DATE", 2},
    {"STATE", 3},
    {"DURATION", 4},
    {"ELAPSED", 5},
    {"PAUSED", 6},
};

static const std::string UPDATE_QUERY = "UPDATE TIMERS set "
"TITLE = ?, "
"STATE = ?, "
"DURATION = ?, "
"ELAPSED = ?, "
"PAUSED = ? "
"where ID = ?;";
static enum class UPDATE_BINDING: int {
    TITLE = 1,
    STATE = 2,
    DURATION = 3,
    ELAPSED = 4,
    PAUSED = 5,
    ID = 6
};
typedef std::underlying_type_t<UPDATE_BINDING> update_val;

#endif