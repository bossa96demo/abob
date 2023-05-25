#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    // Write the received data to a buffer
    size_t realsize = size * nmemb;
    char *buffer = (char *)userdata;
    memcpy(buffer, ptr, realsize);
    return realsize;
}

int main(void) {
    CURL *curl;
    CURLcode res;
    char *url = "https://stallman.org";
    char buffer[1024 * 1024]; // Allocate a buffer to store the received data

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

    printf("%s\n", buffer); // Print the received data
    return 0;
}

