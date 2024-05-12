#include "leaderBoard.h"
bool sortScore(playerScore a, playerScore b) {
	return (a.maxLevel < b.maxLevel);
}
void leaderBoard::setLeaderBoard(playerScore& a) {
	if (true) {
		printf("\n state %d\n", requestState);
		leaderBoardList.push_back(a);
		std::sort(leaderBoardList.begin(), leaderBoardList.end(), sortScore);
		std::reverse(leaderBoardList.begin(), leaderBoardList.end());
		for (int i = 0; i < leaderBoardList.size(); i++) {
			//std::cout << leaderBoardList.at(i).playerName << " " << leaderBoardList.at(i).maxLevel << std::endl;
		}
		std::cout << "before";
		while (leaderBoardList.size() > 5) {
			leaderBoardList.pop_back();
		}
	}
	for (int i = 0; i < leaderBoardList.size(); i++) {
		//std::cout << leaderBoardList.at(i).playerName << " " << leaderBoardList.at(i).maxLevel << std::endl;
	}
	leaderBoardData["1"]["playerName"] = leaderBoardList[0].playerName;
	leaderBoardData["1"]["playerScore"] = leaderBoardList[0].maxLevel;
	leaderBoardData["2"]["playerName"] = leaderBoardList[1].playerName;
	leaderBoardData["2"]["playerScore"] = leaderBoardList[1].maxLevel;
	leaderBoardData["3"]["playerName"] = leaderBoardList[2].playerName;
	leaderBoardData["3"]["playerScore"] = leaderBoardList[2].maxLevel;
	leaderBoardData["4"]["playerName"] = leaderBoardList[3].playerName;
	leaderBoardData["4"]["playerScore"] = leaderBoardList[3].maxLevel;
	leaderBoardData["5"]["playerName"] = leaderBoardList[4].playerName;
	leaderBoardData["5"]["playerScore"] = leaderBoardList[4].maxLevel;
}