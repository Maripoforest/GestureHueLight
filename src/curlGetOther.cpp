#include <iostream>
#include <string>
#include <curl/curl.h>

// // get method 3
// static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
// {
//     ((std::string*)userp)->append((char*)contents, size * nmemb);
//     return size * nmemb;
// }

// int main(void)
// {
//   CURL *curl;
//   CURLcode res;
//   std::string readBuffer;

//   curl = curl_easy_init();
//   if(curl) {
//     // curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com");
//     curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/get");
//     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//     curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
//     res = curl_easy_perform(curl);
//     curl_easy_cleanup(curl);

//     std::cout << readBuffer << std::endl;
//   }
//   return 0;
// }


//// method2 example
// size_t write(void* ptr, size_t size, size_t nmemb, std::string* data){
//     data->append((char*) ptr, size * nmemb);
//     return size * nmemb;
// }

// int main(int argc, char** argv)
// {
//     auto curl = curl_easy_init();
    

//     // curl_easy_setopt(curl,CURLOPT_URL, "http://www.google.com"); //chuanru url
//     curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/get"); //chuanru url
//     curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
//     curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
//     curl_easy_setopt(curl,CURLOPT_TCP_KEEPALIVE, 1L);

   
//     std::string response_text;
//     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write);
//     curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_text);
//     curl_easy_perform(curl);
//     curl_easy_cleanup(curl);
//     curl = NULL;
//     std::cout << "1111111111111111111111111111111111111111" << std::endl << std::endl;
//     std::cout << response_text << std::endl;
//     std::cout << "1111111111111111111111111111111111111111" << std::endl << std::endl;
// }




////method 1 easist
// int main(void)
// {
//     CURL *curl;
//     CURLcode res;

//     curl = curl_easy_init(); //chushihua
//     if(curl){


//     // curl_easy_setopt(curl,CURLOPT_URL, "http://www.google.com"); //chuanru url
//     curl_easy_setopt(curl,CURLOPT_URL, "https://httpbin.org/get"); //chuanru url

//     res = curl_easy_perform(curl);
//     std::cout << "1111111111111111111111111111111111111111" << std::endl << std::endl;
//     std::cout << res << std::endl;
//     std::cout << "1111111111111111111111111111111111111111" << std::endl << std::endl;
//     curl_easy_cleanup(curl);
    
//     }

//     return 0;
// }