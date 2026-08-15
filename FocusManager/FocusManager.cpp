#include <iostream>
#include <string>
#include <cstdlib>

#include "ToDoList.h"
#include "JsonSerializer.h"
#include "SortingAndView.h"

constexpr char endl = '\n';

// "C:\\Users\\Dimo\\AppData\\Roaming\\FocusManager\\data.json"

// "C:\\Users\\Dimo\\source\\repos\\Test\\Test\\TestFiles\\example.json"

int main()
{
    JsonSerializer jsonSerializer{ "C:\\Users\\Dimo\\AppData\\Roaming\\FocusManager\\test.json" };
    ToDoList toDoList{ initToDoList(jsonSerializer) };
    //jsonSerializer.clearData();
    
    std::vector<Task> v{ toDoList.cbegin(), toDoList.cend() };

    auto viewS{ View::viewByStatus(v, Status::Inactive) };
    auto viewP{ View::viewByPriority(v, Priority::High) };

    for (const auto& el : viewS) {
        std::cout << myTransform::to_string(el.getStatus()) << endl;
    }

    //saveToDoList(jsonSerializer, toDoList);
}
