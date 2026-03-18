#include <iostream>
#include <Core/Application.hpp>
#include <Game.hpp>
#include <string>
#include <filesystem>
#include <Logger.hpp>

#ifdef _WIN32
#include <windows.h>
#endif

#define PROJECT_NAME "SleakEngine"

std::string HelpMessage =
  "Usage: SleakEngine [OPTION...] \n\
  help : Shows this help message \n\
  -w :    Sets width of the window. \n\
  -h :    Sets height of the window \n\
  -t :    Sets title of the window, to set space between words put _ character \n\
  ";

static void SetWorkingDirToExePath(char* argv0) {
#ifdef _WIN32
    char path[MAX_PATH];
    if (GetModuleFileNameA(nullptr, path, MAX_PATH) != 0) {
        std::filesystem::current_path(
            std::filesystem::path(path).parent_path());
        return;
    }
#endif
    auto exeDir = std::filesystem::path(argv0).parent_path();
    if (!exeDir.empty())
        std::filesystem::current_path(exeDir);
}

int main(int argc, char** argv) {

  SetWorkingDirToExePath(argv[0]);

  Sleak::Logger::Init((char*)PROJECT_NAME);

  Sleak::ApplicationDefaults defaults
  {
    .Name = PROJECT_NAME,
    .CommandLineArgs = Sleak::Arguments(argc, argv)
  };

  Game* game = new Game();
  Sleak::Application app(defaults);

  return app.Run( game );
}
