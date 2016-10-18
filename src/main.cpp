#include <stdio.h>
#include <twitcurl.h>
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include "include/json.hpp"

using namespace std;
using json = nlohmann::json;

void setKeys(char* consumerKey, char* consumerSecret,
             char* accessKey, char* accessSecret, twitCurl& twitterObj) {
    twitterObj.getOAuth().setConsumerKey(string(consumerKey));
    twitterObj.getOAuth().setConsumerSecret(string(consumerSecret));
    twitterObj.getOAuth().setOAuthTokenKey(string(accessKey));
    twitterObj.getOAuth().setOAuthTokenSecret(string(accessSecret));
}    

int main(int argc, char** args) {
    if (argc < 6) {
        printf("No consumer / access token or key, or missing number of sloth pictures");
    }
    int numberOfSlothPictures = atoi(args[5]);
    int counter = 0;
    while (1) {
        std::string str = "img/" + std::to_string((counter % numberOfSlothPictures) + 1) + ".jpg";
        try {
            twitCurl twitterObj;
            setKeys(args[1], args[2], args[3], args[4], twitterObj);
            if (!twitterObj.accountVerifyCredGet()) {
                twitterObj.getLastCurlError(str);
                printf("Error validating credentials:%s", str.c_str());
                return 1;
            }

            std::string response = twitterObj.uploadMedia(str);
            auto response_json = json::parse(response);
            std::string id = response_json["media_id_string"].get<std::string>();
            std::string* media = new std::string[1] { id };
            if (!twitterObj.statusUpdateWithMedia(" ", media, 1)) {
                printf("fug\n");
            }
        } catch(char* err) {
            printf("Error:\n%s", err);
            return 1;
        }
        std::this_thread::sleep_for(std::chrono::minutes(114));
    }
    return 0;
}