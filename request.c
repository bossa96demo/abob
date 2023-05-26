#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <regex.h>

char* url_pattern = "^https?://[a-zA-Z0-9]+(\\.[a-zA-Z0-9]+)*(/[a-zA-Z0-9]+)*$";

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    // Write the received data to a buffer
    size_t realsize = size * nmemb;
    char *buffer = (char *)userdata;
    memcpy(buffer, ptr, realsize);
    return realsize;
}

int validate_url(char *url){
    regex_t regex;
    int reti;
    reti = regcomp(&regex, url_pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }
    reti = regexec(&regex, url, 0, NULL, 0);
    if (!reti) {
        // Free the memory used by the regular expression
        regfree(&regex);
        return 1;
    } else {
        // Free the memory used by the regular expression
        regfree(&regex);
        return 0;
    }


}

char buffer[2048 * 2048];

char *request(char *url) {
    CURL *curl;
    CURLcode res;
    //char buffer[1024 * 1024]; // Allocate a buffer to store the received data

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "ABOB/0.0");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }

    return buffer;
}

