#pragma once
#define CURL_STATICLIB
#include <curl\curl.h>
#include"json.hpp";
#include<string>
#include<vector>
#include<iostream>
using namespace nlohmann::json_abi_v3_11_3;
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}
struct playerScore {
	std::string playerName;
	int maxLevel;
	
};
class leaderBoard
{
public:
	std::vector<playerScore> leaderBoardList;
	std::string jsonData;
	std::string returnDataString;
	std::string requestDataString;
	json readRequest=json::object();
	json leaderBoardData=json::object();
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
		leaderBoardData["1"] = "0";
		leaderBoardData["2"] = "0";
		leaderBoardData["3"] = "0";
		leaderBoardData["4"] = "0";
		leaderBoardData["5"] = "0";
	}
	void setLeaderBoard() {
		if (leaderBoardData["getState"] == true) {

		}
	}
	void createLeaderBoard() {
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
		}
		}
	void getLeaderBoard() {
		CURLcode res;
		readRequest["@type"] = "SearchAction";
		json Object = json::object();
		Object["@type"] = "Filter";
		json filterItem = json::object();
		filterItem["@type"] = "DataLakeItem";
		filterItem["Identifier"] = "d3390ce0-100f-11ef-bc53-59e8e73b3d77";
		Object["FilterItem"] = filterItem;
		readRequest["Object"] = Object;
		requestDataString = readRequest.dump(2);
		std::cout << requestDataString << "\n";
		curl_easy_setopt(curl_get, CURLOPT_POSTFIELDS, requestDataString.c_str());
		res = curl_easy_perform(curl_get);
		if (res != CURLE_OK) {
			std::cout << "error request: " << curl_easy_strerror(res) << "\n";
		}
		else {
			std::cout << returnDataString;
		}
	}
	~leaderBoard() {
		curl_easy_cleanup(curl_get);
	}
};

