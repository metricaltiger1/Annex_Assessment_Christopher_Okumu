// Question 3: Top Articles API (C++)
// Problem Statement
// Implement a function that retrieves and ranks the top articles from the HackerRank Articles API.

// API Endpoint
// https://jsonmock.hackerrank.com/api/articles?page=<pageNumber>
// Requirements
// Pagination: Fetch all pages of article data using the total_pages field from the API response.
// Article Name Determination:
// If title is not null, use title
// Otherwise, if story_title is not null, use story_title
// If both are null, skip the article
// Sorting:
// Primary: Decreasing by num_comments (treat null as 0)
// Secondary: Alphabetically decreasing by article name
// Return: The top limit article names
// Function Signature
// vector<string> topArticles(int limit) {
//     // Your code here
// }
// Sample
// Input: limit = 2
// Output:

// UK votes to leave EU
// F.C.C. Repeals Net Neutrality Rules
// JSON Response Structure
// {
//   "page": 1,
//   "per_page": 10,
//   "total": 100,
//   "total_pages": 10,
//   "data": [
//     {
//       "title": "Article Title",
//       "story_title": "Story Title",
//       "num_comments": 50,
//       ...
//     }
//   ]
// }

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <curl/curl.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *output)
{
    size_t totalSize = size * nmemb;
    output->append((char *)contents, totalSize);
    return totalSize;
}

string getRequest(string url)
{
    CURL *curl = curl_easy_init();
    string response;

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return response;
}

vector<string> topArticles(int limit)
{
    vector<string> articleNames;
    vector<pair<int, string>> articles;

    int pageNumber = 1;
    int totalPages = 1;

    while (pageNumber <= totalPages)
    {
        string apiUrl = "https://jsonmock.hackerrank.com/api/articles?page=" + to_string(pageNumber);
        string response = getRequest(apiUrl);

        json data = json::parse(response);
        totalPages = data["total_pages"];

        for (auto &item : data["data"])
        {
            string name = "";

            if (!item["title"].is_null())
                name = item["title"];
            else if (!item["story_title"].is_null())
                name = item["story_title"];
            else
                continue;

            int comments = 0;
            if (!item["num_comments"].is_null())
                comments = item["num_comments"];

            articles.push_back({comments, name});
        }

        pageNumber++;
    }

    sort(articles.begin(), articles.end(), [](auto &a, auto &b)
         {
        if (a.first != b.first)
            return a.first > b.first;
        return a.second > b.second; });

    for (int i = 0; i < min(limit, (int)articles.size()); i++)
    {
        articleNames.push_back(articles[i].second);
    }

    return articleNames;
}

int main()
{
    int limit = 2;
    vector<string> top = topArticles(limit);

    for (const string &article : top)
    {
        cout << article << endl;
    }

    return 0;
}