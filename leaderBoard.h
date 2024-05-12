#pragma once
#define CURL_STATICLIB
#include "curl\curl.h"
#include"json.hpp";
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include"playerScore.h">
using namespace nlohmann::json_abi_v3_11_3;
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}
extern std::vector<playerScore> leaderBoardList;
class leaderBoard
{
public:
	std::string apiLBIndentifier = "daf40bf0-105b-11ef-bc53-59e8e73b3d77";
	//std::vector<playerScore> leaderBoardList;
	bool requestState=false;
	std::string jsonData;
	std::string returnDataString;
	std::string requestDataString;
	json readRequest=json::object();
	json leaderBoardData=json::object();
	json returnData = json::object();
	CURL* curl_get;
	leaderBoard() {//init curl
		curl_get = curl_easy_init();
		curl_easy_setopt(curl_get, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl_get, CURLOPT_URL, "https://json-storage-api.p.rapidapi.com/datalake");
		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "content-type: application/json");
		headers = curl_slist_append(headers, "X-RapidAPI-Key: 8b7fc259c7mshf02f150bb58261cp13fbcfjsn875ce2098acc");
		headers = curl_slist_append(headers, "X-RapidAPI-Host: json-storage-api.p.rapidapi.com");
		curl_easy_setopt(curl_get, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl_get, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl_get, CURLOPT_WRITEDATA, &returnDataString);
		readRequest["@context"] = json::array();
		leaderBoardData["@type"] = "LeaderBoardData";
		leaderBoardData["getState"] = false;
		leaderBoardData["1"] = json::object();
		leaderBoardData["1"]["playerName"] = "xHatsu";
		leaderBoardData["1"]["playerScore"] = 1;
		leaderBoardData["2"] = json::object();
		leaderBoardData["2"]["playerName"] = "None";
		leaderBoardData["2"]["playerScore"] = -1;
		leaderBoardData["3"] = json::object();
		leaderBoardData["3"]["playerName"] = "None";
		leaderBoardData["3"]["playerScore"] = -1;
		leaderBoardData["4"] = json::object();
		leaderBoardData["4"]["playerName"] = "None";
		leaderBoardData["4"]["playerScore"] = -1;
		leaderBoardData["5"] = json::object();
		leaderBoardData["5"]["playerName"] = "None";
		leaderBoardData["5"]["playerScore"] = -1;
	}
	void updateLeaderBoard() {
		requestState = false;
		CURLcode res;
		readRequest["@type"] = "UpdateAction";
		json result = json::object();
		result["@type"] = "DataLakeItem";
		result["Identifier"] = apiLBIndentifier;
		result["About"] = leaderBoardData;
		readRequest["Result"] = result;
		requestDataString = readRequest.dump(2);
		std::cout << requestDataString << "\n";
		curl_easy_setopt(curl_get, CURLOPT_POSTFIELDS, requestDataString.c_str());
		res = curl_easy_perform(curl_get);
		if (res != CURLE_OK) {
			std::cout << "error request: " << curl_easy_strerror(res) << "\n";
		}
		else {
			std::cout << returnDataString<<"\n";
			requestState = true;
		}
	}
	void setLeaderBoard(playerScore& a);
	void createLeaderBoard() {
		requestState = false;
		CURLcode res;
		readRequest["@type"] = "CreateAction";
		json result = json::object();
		result["@type"] = "DataLakeItem";
		result["About"] = leaderBoardData;
		readRequest["Result"] = result;
		requestDataString = readRequest.dump(2);
		std::cout << requestDataString<<"\n";
		curl_easy_setopt(curl_get, CURLOPT_POSTFIELDS, requestDataString.c_str());
		res = curl_easy_perform(curl_get);
		if (res != CURLE_OK) {
			std::cout << "error request: "<< curl_easy_strerror(res)<<"\n";
		}
		else {
			std::cout << returnDataString;
			requestState = true;
		}
		
		}
	void getLeaderBoard() {
		CURLcode res;
		readRequest["@type"] = "SearchAction";
		json Object = json::object();
		Object["@type"] = "Filter";
		json filterItem = json::object();
		filterItem["@type"] = "DataLakeItem";
		filterItem["Identifier"] = apiLBIndentifier;
		Object["FilterItem"] = filterItem;
		readRequest["Object"] = Object;
		requestDataString = readRequest.dump(2);
		std::cout << requestDataString << "\n";
		curl_easy_setopt(curl_get, CURLOPT_POSTFIELDS, requestDataString.c_str());
		res = curl_easy_perform(curl_get);
		if (res != CURLE_OK) {
			std::cout << "error request: " << curl_easy_strerror(res) << "\n";
			requestState = false;
		}
		else {
			std::cout << returnDataString;
			requestState = true;
			returnData = json::parse(returnDataString);
			json itemList = returnData["Result"]["ItemListElement"];
			leaderBoardData = itemList[1]["Item"]["About"];
			//printf("\n lb size: %d", leaderBoardList.size());
			leaderBoardList.clear();
			for (int i = 0; i < 5; i++) {
				playerScore a;
				leaderBoardList.push_back(a);
			}
			leaderBoardList[0].playerName = leaderBoardData["1"]["playerName"];
			leaderBoardList[0].maxLevel = leaderBoardData["1"]["playerScore"];
			leaderBoardList[1].playerName = leaderBoardData["2"]["playerName"];
			leaderBoardList[1].maxLevel = leaderBoardData["2"]["playerScore"];
			leaderBoardList[2].playerName = leaderBoardData["3"]["playerName"];
			leaderBoardList[2].maxLevel = leaderBoardData["3"]["playerScore"];
			leaderBoardList[3].playerName = leaderBoardData["4"]["playerName"];
			leaderBoardList[3].maxLevel = leaderBoardData["4"]["playerScore"];
			leaderBoardList[4].playerName = leaderBoardData["5"]["playerName"];
			leaderBoardList[4].maxLevel = leaderBoardData["5"]["playerScore"];
			//test
			for (int i = 0; i < leaderBoardList.size(); i++) {
				std::cout << leaderBoardList.at(i).playerName << " " << leaderBoardList.at(i).maxLevel << std::endl;
			}
		}

	}
	void deleteLB() {
		CURLcode res;
		readRequest["@type"] = "DeleteAction";
		json Object = json::object();
		Object["@type"] = "Filter";
		json filterItem = json::object();
		filterItem["@type"] = "DataLakeItem";
		filterItem["Identifier"] = apiLBIndentifier;
		Object["FilterItem"] = filterItem;
		readRequest["Object"] = Object;
		requestDataString = readRequest.dump(2);
		std::cout << requestDataString << "\n";
		curl_easy_setopt(curl_get, CURLOPT_POSTFIELDS, requestDataString.c_str());
		res = curl_easy_perform(curl_get);
		if (res != CURLE_OK) {
			std::cout << "error request: " << curl_easy_strerror(res) << "\n";
			requestState = false;
		}
		else {
			std::cout << returnDataString;
		}
	}
	~leaderBoard() {
		curl_easy_cleanup(curl_get);
	}
};

