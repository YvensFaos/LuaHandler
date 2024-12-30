#include "luahandler.hpp"

#define LUA_LOG "###LUA_LOG :"

LuaHandler::LuaHandler() {
    this->lua = luaL_newstate();
    luaL_openlibs(lua);
}

LuaHandler::~LuaHandler() {
    if(this->lua) {
        lua_close(lua);
    }
}

bool LuaHandler::openFile(const std::string& fileName) const {
    luaL_loadfile(lua, fileName.c_str());
    if (lua_pcall(lua, 0, 0, 0) != 0) {
        printf("%sError at loading file %s. Message is: %s.\r\n", LUA_LOG, fileName.c_str(), lua_tostring(lua, -1));
        return false;
    }
    printf("%sSuccessfully loaded lua file named: %s.\r\n", LUA_LOG, fileName.c_str());
    return true;
}

bool LuaHandler::getGlobalBoolean(const std::string& globalVariableName) const{
    lua_getglobal(lua, globalVariableName.c_str());
    if(lua_isboolean(lua, -1)) {
        const bool value = lua_toboolean(lua, -1);
        lua_pop(lua, 1);
        return value;
    }
    printf("%sUnable to load boolean variable named: %s.\r\n", LUA_LOG, globalVariableName.c_str());
    lua_pop(lua, 1);
    return false;
}

int LuaHandler::getGlobalInteger(const std::string& globalVariableName) const {
    if(lua_getglobal(lua, globalVariableName.c_str()) == LUA_TNUMBER) {
        const int value = static_cast<int>(lua_tonumber(lua, -1));
        lua_pop(lua, 1);
        return value;
    }
    printf("%sUnable to load int variable named: %s.\r\n", LUA_LOG, globalVariableName.c_str());
    lua_pop(lua, 1);
    return -1;
}

float LuaHandler::getGlobalNumber(const std::string& globalVariableName) const {
    lua_getglobal(lua, globalVariableName.c_str());
    if(lua_isnumber(lua, -1)) {
        const float value = lua_tonumber(lua, -1);
        lua_pop(lua, 1);
        return value;
    }
    printf("%sUnable to load float variable named: %s.\r\n", LUA_LOG, globalVariableName.c_str());
    lua_pop(lua, 1);

    return -1.0f;
}

std::string LuaHandler::getGlobalString(const std::string& globalVariableName) const {
    lua_getglobal(lua, globalVariableName.c_str());
    if(lua_isstring(lua, -1)) {
        const std::string value = lua_tostring(lua, -1);
        lua_pop(lua, 1);
        return value;
    }
    printf("%sUnable to load string variable named: %s.\r\n", LUA_LOG, globalVariableName.c_str());
    lua_pop(lua, 1);
    return "";
}

bool LuaHandler::getBoolFromTable(const std::string& key) const {
    lua_pushstring(lua, key.c_str());
    lua_gettable(lua, -2);
    if(lua_isboolean(lua, -1)) {
        const bool value = lua_toboolean(lua, -1);
        lua_pop(lua, 1);
        return value;
    }
    printf("%sUnable to load boolean variable with key: %s.\r\n", LUA_LOG, key.c_str());
    lua_pop(lua, 1);
    return false;
}

int LuaHandler::getIntegerFromTable(const std::string& key) const {
    lua_pushstring(lua, key.c_str());
    lua_gettable(lua, -2);

    if(lua_isinteger(lua, -1)) {
        const int value = static_cast<int>(lua_tointeger(lua, -1));
        lua_pop(lua, 1);
        return value;
    }
    printf("%sUnable to load integer variable with key: %s.\r\n", LUA_LOG, key.c_str());
    lua_pop(lua, 1);
    return -1;
}

int LuaHandler::getIntegerFromTable(int index) const {
    lua_pushinteger(lua, index);
    lua_gettable(lua, -2);
    if(lua_isinteger(lua, -1)) {
        const int value = static_cast<int>(lua_tointeger(lua, -1));
        lua_pop(lua, 1);
        return value;
    }
    printf("%sUnable to load integer variable with index: %d.\r\n", LUA_LOG, index);
    lua_pop(lua, 1);
    return -1;
}

float LuaHandler::getNumberFromTable(const int index) const{
    lua_pushinteger(lua, index);
    lua_gettable(lua, -2);
    if(lua_isnumber(lua, -1)) {
        const float value = lua_tonumber(lua, -1);
        lua_pop(lua, 1);
        return value;
    }
    printf("%sUnable to load number variable with index: %d.\r\n", LUA_LOG, index);
    lua_pop(lua, 1);
    return -1.0f;
}

float LuaHandler::getNumberFromTable(const std::string& key) const {
    lua_pushstring(lua, key.c_str());
    lua_gettable(lua, -2);
    if(lua_isnumber(lua, -1)) {
        const float value = lua_tonumber(lua, -1);
        lua_pop(lua, 1);
        return value;
    }
    printf("%sUnable to load number variable with key: %s.\r\n", LUA_LOG, key.c_str());
    lua_pop(lua, 1);
    return -1.0f;
}

std::string LuaHandler::getStringFromTable(const int index) const {
    lua_pushinteger(lua, index);
    lua_gettable(lua, -2);
    if(lua_isstring(lua, -1)) {
        const std::string value = lua_tostring(lua, -1);
        lua_pop(lua, 1);
        return value;
    }
    printf("%sUnable to load string variable with index: %d.\r\n", LUA_LOG, index);
    lua_pop(lua, 1);
    return "";
}

std::string LuaHandler::getStringFromTable(const std::string& key) const {
    lua_pushstring(lua, key.c_str());
    lua_gettable(lua, -2);
    if(lua_isstring(lua, -1)) {
        const std::string value = lua_tostring(lua, -1);
        lua_pop(lua, 1);
        return value;
    }
    printf("%sUnable to load string variable with key: %s.\r\n", LUA_LOG, key.c_str());
    lua_pop(lua, 1);
    return "";
}

bool LuaHandler::getTableFromTable(const int index) const {
    lua_pushinteger(lua, index);
    lua_gettable(lua, -2);
    const bool success = isTopOfStackATable();
    if(!success) {
        printf("%sUnable to read table indexed %d from current table.\r\n", 
        LUA_LOG, index);
        lua_pop(lua, 1);
    }
    return success;
}

bool LuaHandler::getTableFromTable(const std::string& key) const {
    lua_pushstring(lua, key.c_str());
    lua_gettable(lua, -2);
    const bool success = isTopOfStackATable();
    if(!success) {
        printf("%sUnable to read table named %s from current table.\r\n", 
        LUA_LOG, key.c_str());
        lua_pop(lua, 1);
    }
    return success;
}

bool LuaHandler::isTopOfStackATable() const {
    return lua_istable(lua, -1);
}

bool LuaHandler::loadTable(const std::string& tableName) const {
    lua_getglobal(lua, tableName.c_str());
    if(!isTopOfStackATable()) {
        printf("%sUnable to read table named: %s.\r\n", LUA_LOG, tableName.c_str());
        return false;
    }
    return true;
}

void LuaHandler::popTable() const {
    if(isTopOfStackATable()) {
        lua_pop(lua, 1);
    } else {
        printf("%sAttempt to pop a table failed. No table found in the stack top.\r\n", LUA_LOG);
    }
}

bool LuaHandler::getFunction(const std::string& functionName) const {
    lua_getglobal(lua, functionName.c_str());
    const bool validFunction = lua_isfunction(lua, -1);
    if(!validFunction) {
        printf("%sAttempt to load function named \"%s\" failed.\r\n", LUA_LOG, functionName.c_str());
        lua_pop(lua, 1);
    }
    return validFunction;
}

int LuaHandler::callFunctionFromStack(const int parameters, const int returns) const {
    return lua_pcall(lua, parameters, returns, 0);
}

/**
 * Get a global function and call it immediately using lua_pcall.
 * Returns the lua_pcall method return.
 * Results will be pushed to the stack.
 */
int LuaHandler::getAndCallFunction(const std::string& functionName, const int returns) const {
    lua_getglobal(lua, functionName.c_str());
    return lua_pcall(lua, 0, returns, 0);
}

void LuaHandler::pushBoolean(const bool value) const {
    lua_pushboolean(lua, value);
}

void LuaHandler::pushInteger(const int value) const {
    lua_pushinteger(lua, value);
}

void LuaHandler::pushNumber(const float value) const {
    lua_pushnumber(lua, value);
}

void LuaHandler::pushString(const std::string& value) const {
    lua_pushstring(lua, value.c_str());
}

bool LuaHandler::popBoolean() const {
    if(!lua_isnil(lua, -1)) {
        const bool value = lua_toboolean(lua, -1);
        lua_pop(lua, 1);
        return value;
    }
    printf("%sUnable to pop boolean value from top. Top is nil.\r\n", LUA_LOG);
    return false;
}

int LuaHandler::popInteger() const {
    if(!lua_isnil(lua, -1)) {
        const int value = lua_tointeger(lua, -1);
        lua_pop(lua, 1);
        return value;
    }
    printf("%sUnable to pop integer value from top. Top is nil.\r\n", LUA_LOG);
    return -1;
}

float LuaHandler::popNumber() const {
    if(!lua_isnil(lua, -1)) {
        const float value = lua_tonumber(lua, -1);
        lua_pop(lua, 1);
        return value;
    }
    printf("%sUnable to pop float value from top. Top is nil.\r\n", LUA_LOG);
    return -1.0f;
}

std::string LuaHandler::popString() const {
    if(!lua_isnil(lua, -1)) {
        std::string value = lua_tostring(lua, -1);
        lua_pop(lua, 1);
        return value;
    }
    printf("%sUnable to pop string value from top. Top is nil.\r\n", LUA_LOG);
    return "";
}

int LuaHandler::popTop() const{
    if(this->getStackTop() > 0) {
        lua_pop(lua, 1);
    }
    return this->getStackTop();
}

int LuaHandler::getStackTop() const {
    return lua_gettop(lua);
}

///Get the length of the object on top of the stack.
int LuaHandler::getLength() const {
    return static_cast<int>(lua_rawlen(lua, -1));
}