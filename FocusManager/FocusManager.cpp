#include <iostream>
#include <string>

#include "ToDoList.h"
#include "JsonSerializer.h"
#include "SortingAndView.h"
#include "Timer.h"
#include "Blocker.h"

constexpr char endl = '\n';

// "C:\\Users\\Dimo\\AppData\\Roaming\\FocusManager\\data.json"

// "C:\\Users\\Dimo\\source\\repos\\Test\\Test\\TestFiles\\example.json"

int main()
{
    JsonSerializer jsonSerializer{ "C:\\Users\\Dimo\\AppData\\Roaming\\FocusManager\\test.json" };

    Timer timer{ initTimer(jsonSerializer) };
    timer.setPreviousTime(steady_clock::now()); // ??
    std::cout << "\033[?25l" << std::flush;

    while (true) {
        timer.updateTimer();
        timer.updateState();
    }

}
// TODO: class Blocker, Timer(вроде как готовый, но в будущем надо будет подправить, так как не знаю, что конкретно понадобиться).