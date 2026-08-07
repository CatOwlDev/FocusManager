#include <iostream>
#include <string>
#include <cstdlib>

#include "ToDoList.h"
#include "JsonSerializer.h"

constexpr wchar_t endl = L'\n';

// L"C:\\Users\\Dimo\\AppData\\Roaming\\FocusManager\\data.json"

int main()
{
    JsonSerializer jsonSerializer{ L"C:\\Users\\Dimo\\source\\repos\\Test\\Test\\TestFiles\\example.json" };
    ToDoList toDoList{ initToDoList(jsonSerializer.getData()) };
    std::cout << Task::getIdCounter() << std::endl;
       
}
