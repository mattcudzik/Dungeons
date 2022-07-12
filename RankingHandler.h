#pragma once
#include <vector>
#include <string>
#include <ranges>
#include <algorithm>
#include <fstream>
#include <sstream>

#include <iostream>

class RankingHandler
{
public:
	static RankingHandler& Instance();
	void AddPoints(int amount);
	void ClearPoints();
	void AddToRanking(std::string name);
	void Initialize();
	bool QualifiedToRanking();
	std::vector< std::pair<std::string, int>>& GetRanking();
private:
	RankingHandler();
	~RankingHandler();
	void LoadFromFile();
	void SaveToFile();
	void SortRanking();
	int m_currentPoints;
	std::vector< std::pair<std::string, int>> m_ranking;
};

