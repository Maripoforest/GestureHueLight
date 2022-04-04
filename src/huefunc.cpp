/*
Arthor: Jiyuan He (Hjyyjh), Xiangmin Xu (Marioforest) 04.04.2022
cURL HTTP method, wrapped for Hue APIs
Relies on curl library.
*/

#include "huefunc.h"

void HUEMSG::curlPut(void) {
       
	CURLcode res;
	struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
	
	curl = curl_easy_init();

	if (curl) {
		
        std::string jsoncmd = "{\"on\": true, \"bri\":" + MSG + "}"; //brightness 
        
        if(MSG == "0") {
            jsoncmd = "{\"on\": false}"; //turns off
        }
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT"); /* !!! */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsoncmd.c_str());


		res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cout << res << std::endl;
        }
		std::cout << std::endl;
		curl_slist_free_all(headers);
	}
	curl_easy_cleanup(curl);
}

void HUEMSG::curlPost(void) {
    
	CURLcode res; //curl return stat
    curl = curl_easy_init();
  
	if (curl)
	{
		// set params
       
		struct curl_slist* header_list = NULL;
		header_list = curl_slist_append(header_list, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, MSG.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

		
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callBack);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);

		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    
		res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cout << res << std::endl;
        }
	}
	curl_easy_cleanup(curl);
}


void HUEMSG::curlGet(){
	
    CURLcode res;
    curl = curl_easy_init();
	
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callBack);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

		res = curl_easy_perform(curl);
        if (res != CURLE_OK)
	    {
		    std::cout << response << std::endl;
	    }
	}
	curl_easy_cleanup(curl);
}

std::string HUEMSG::getResponse(void) {
    return response;
}

size_t HUEMSG::write_callBack(void *ptr, size_t size, size_t nmemb, void *stream)
{
	std::string *str = (std::string*)stream;
	(*str).append((char*)ptr, size*nmemb);
	return size * nmemb;
}