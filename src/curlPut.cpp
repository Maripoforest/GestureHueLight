#include <iostream>
#include <string>
#include <curl/curl.h>

int main(void)
{
  CURL *curl;
  CURLcode res;
  struct curl_slist *headers = NULL;
  

  curl = curl_easy_init();
  if (curl) {
    // headers = curl_slist_append(headers, client_id_header);
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
    // curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");  
    // curl_easy_setopt(curl, CURLOPT_URL, "127.0.0.1/test.php"); 
    // curl_easy_setopt(curl, CURLOPT_URL, "https://www.atool99.com/httptest.php"); 
    curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/put"); 
    // curl_easy_setopt(curl, CURLOPT_URL, "https://reqbin.com/echo/put/json"); 
    // curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com");
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT"); /* !!! */

    // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "target data"); /* data goes here */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{'name':'team20'}");

    res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
}
  return 0;
}