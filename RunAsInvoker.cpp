#include <chrono>
#include <iostream>
#include <thread>
#include <Windows.h>

const char *Title = "71ddba47-07d7-4253-ac33-3302dabc5098";

void pause(bool error)
{
    system("pause");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " \"<path_to_executable>\" [arguments...]" << std::endl;
        pause(true);
        return 1;
    }

    SetConsoleTitle(Title);
    std::this_thread::sleep_for(std::chrono::milliseconds(40));
    HWND hwnd = FindWindow(NULL, Title);
    if (hwnd)
    {
        ShowWindow(hwnd, SW_HIDE);
    }

    SetEnvironmentVariable("__COMPAT_LAYER", "RUNASINVOKER");
    std::string command_line = "\"" + std::string(argv[1]) + "\"";
    for (int i = 2; i < argc; ++i)
    {
        command_line += " ";
        command_line += "\"" + std::string(argv[i]) + "\"";
    }

    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION pi;

    if (CreateProcess(nullptr, const_cast<char *>(command_line.c_str()), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi))
    {
        std::cout << "command:" << std::endl
                  << command_line << std::endl
                  << "running..." << std::endl;

        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        std::cout << "The executable exited." << std::endl;

        return 0;
    }
    else
    {
        std::cerr << "Error starting the executable." << std::endl
                  << "command:" << std::endl
                  << command_line << std::endl;
        ShowWindow(hwnd, SW_NORMAL);
        pause(true);
        return 1;
    }
}