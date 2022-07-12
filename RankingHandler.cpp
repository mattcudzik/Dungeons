#include "RankingHandler.h"

RankingHandler::RankingHandler() : m_currentPoints(0) {}

RankingHandler::~RankingHandler()
{
	SaveToFile();
}
void RankingHandler::Initialize()
{
	LoadFromFile();
}
bool RankingHandler::QualifiedToRanking()
{
	if (m_ranking.size() < 10)
		return true;
	SortRanking();
	return m_ranking.back().second < m_currentPoints;
}
void RankingHandler::LoadFromFile()
{
	std::fstream file;
	file.open("Ranking/ranking.txt");
	std::string line;

	std::string name;
	int score;

	if (file.good())
	{
		while (getline(file, line))
		{
			std::stringstream ss(line);

			ss >> name >> score;

			if (line == "")
				continue;
			m_ranking.push_back(std::pair<std::string, int>(name, score));
		}

	}
	file.close();
	SortRanking();
}
RankingHandler& RankingHandler::Instance()
{
	static RankingHandler instance;
	return instance;
}
void RankingHandler::ClearPoints()
{
	this->m_currentPoints = 0;
}
void RankingHandler::AddPoints(int amount)
{
	this->m_currentPoints += amount;
}
void RankingHandler::SortRanking()
{
	std::ranges::sort(m_ranking, [&](std::pair<std::string, int> a, std::pair<std::string, int> b)
		{
			return a.second > b.second;
		});
}
void RankingHandler::AddToRanking(std::string name)
{
	std::pair<std::string, int> entry = std::pair<std::string, int>(name, m_currentPoints);

	SortRanking();
	auto elIt = m_ranking.begin();
	while (elIt != m_ranking.end())
	{
		if (elIt->second <= entry.second)
		{
			m_ranking.insert(elIt, entry);
			if(m_ranking.size() > 10)
				m_ranking.pop_back();
			break;
		}
		else
			elIt++;
	}
}

std::vector< std::pair<std::string, int>>& RankingHandler::GetRanking()
{
	return this->m_ranking;
}
void RankingHandler::SaveToFile()
{
	std::ofstream file("Ranking/ranking.txt");

	if (file.good())
	{
		for (auto& el : m_ranking)
		{
			file << el.first << " " << el.second << std::endl;
		}
	}
	file.close();
}