#pragma once

#include <lua.hpp>
#include <string>

class LuaHandler {
        lua_State* lua;
    public:
        LuaHandler();
        ~LuaHandler();

        bool openFile(const std::string& fileName) const;
        bool getGlobalBoolean(const std::string& globalVariableName) const;
        int getGlobalInteger(const std::string& globalVariableName) const;
        float getGlobalNumber(const std::string& globalVariableName) const;
        std::string getGlobalString(const std::string& globalVariableName) const;

        bool getBoolFromTable(const std::string& key) const;
        int getIntegerFromTable(int index) const;
        int getIntegerFromTable(const std::string& key) const;
        float getNumberFromTable(int index) const;
        float getNumberFromTable(const std::string& key) const;
        std::string getStringFromTable(int index) const;
        std::string getStringFromTable(const std::string& key) const;

        bool getTableFromTable(int index) const;
        bool getTableFromTable(const std::string& key) const;
        ///Returns true or false if the top of the stack is a table.
        bool isTopOfStackATable() const;

        bool getFunction(const std::string& functionName) const;
        int callFunctionFromStack(int parameters, int returns) const;
        int getAndCallFunction(const std::string&, int returns) const;

        void pushBoolean(bool value) const;
        void pushInteger(int value) const;
        void pushNumber(float value) const;
        void pushString(const std::string& value) const;

        bool popBoolean() const;
        int popInteger() const;
        float popNumber() const;
        std::string popString() const;

        bool loadTable(const std::string& tableName) const;
        void popTable() const;

        ///Pop the top of the stack and return the stack top.
        int popTop() const;
        int getStackTop() const;
        int getLength() const;
};