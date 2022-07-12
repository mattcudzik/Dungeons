#include "Debugger.h"

//TMP Function
void Debugger::DebugSpawnSlime(sf::Window& window)
{
	LevelHandler::Instance().GetCurrentLevel()->AddEntity(Assembler::Instance().CreateSlime(sf::Vector2f(100.f * Tools::scale, 100.f * Tools::scale)));
}
void Debugger::DebugSpawnGhost(sf::Window& window)
{
	LevelHandler::Instance().GetCurrentLevel()->AddEntity(Assembler::Instance().CreateGhost(sf::Vector2f(100.f * Tools::scale, 100.f * Tools::scale)));
}
void Debugger::DebugSpawnZombie(sf::Window& window)
{
	LevelHandler::Instance().GetCurrentLevel()->AddEntity(Assembler::Instance().CreateBigZombie(sf::Vector2f(100.f * Tools::scale, 100.f * Tools::scale)));
}
void Debugger::DebugSpawnSkeleton(sf::Window& window)
{
	LevelHandler::Instance().GetCurrentLevel()->AddEntity(Assembler::Instance().CreateSkeleton(sf::Vector2f(100.f * Tools::scale, 100.f * Tools::scale)));
}