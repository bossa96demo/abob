#include <stdio.h>
#include <curl/curl.h>

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
  size_t written = fwrite(ptr, size, nmemb, (FILE *)userdata);
  return written;
}

int main() {
  CURL *curl;
  CURLcode res;
  FILE *html_file;

  curl = curl_easy_init();
  if (curl) {
    html_file = fopen("output.html", "wb");
    curl_easy_setopt(curl, CURLOPT_URL, "https://x.org");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, html_file);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl);
    fclose(html_file);
  }

  return 0;
}