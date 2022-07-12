#include "GameHandler.h";
#include <iostream>

int main()
{
    std::cout << "Sterowanie: WSAD - poruszanie, IJKL - strzelanie" << std::endl;
    GameHandler::Instance().Initialize();
    GameHandler::Instance().GameLoop();

    return 0;
}