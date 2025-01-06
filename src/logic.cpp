#include <stdio.h>
#include <string>
#include <curl/curl.h>
#include <iostream>
#include "logic.hpp"
#include <cstring>
#include <cstdlib>
#include <string>
#include <gumbo.h>
#include <fstream>

/* only logic.cpp functions */
// Callback function to write received data
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userinput);
void search_links(const GumboNode *node, std::vector<std::string> &links);
////

/*
[logic.hpp related funcitons]
- simple_https_get()
- return_body()
- grab_links()
- creat_file()
*/

void simple_https_get(char *url)
{
 CURL *curl;																												// make a request
 CURLcode res;																										// make a response
 curl_global_init(CURL_GLOBAL_DEFAULT); // set the environment as default
 curl = curl_easy_init();															// to handle $curl as a request

 if (curl) // if it does exist
 {
		curl_easy_setopt(curl, CURLOPT_URL, url); // set options
		dls_confirm("Inputs got handled")
						dls_wait("Sending request")
										res = curl_easy_perform(curl); // send the req and save the res
		if (res != CURLE_OK)																			// check if it works
		{
			dls_deny("Bad URL")
							printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl); // close the curl request | for curl_easy_init
 }
 curl_global_cleanup(); // clean environment | for curl_global_init
}

std::string return_body(char *url)
{
 CURL *curl;																												// make a request
 CURLcode res;																										// make a response
 std::string response;																		// where the response body will be stored
 curl_global_init(CURL_GLOBAL_DEFAULT); // set the environment as default
 curl = curl_easy_init();															// to handle the $curl request
 if (curl)																														// if it does work
 {
		curl_easy_setopt(curl, CURLOPT_URL, url);																					// set options url
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // set options write_back function
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);									// set options write_back data
		dls_confirm("Inputs got handled")
						dls_wait("Sending request")
										res = curl_easy_perform(curl); // send the req and save the res
		if (res != CURLE_OK)																			// check if it works
		{
			printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			return "fuck you";
		}
		curl_easy_cleanup(curl); // clean curl
 }
 curl_global_cleanup();																			// clean environment
 dls_confirm("Good URL") return response; // return the response body
}

std::vector<std::string> grab_links(std::string &html)
{
 // make a vector
 std::vector<std::string> links;
 // trans the html to a gumbo output
 GumboOutput *output = gumbo_parse(html.c_str());
 dls_wait("Searching for links [href]");
 // use the search_links() to fill the vector
 search_links(output->root, links);
 // destroy output
 gumbo_destroy_output(&kGumboDefaultOptions, output);
 dls_confirm("Search finished");
 // return the vector
 return links;
}

void create_file(std::string text, std::string name) // create file of links
{
 std::ofstream file(name);
 file << text << std::endl;
 file.close();
 dls_confirm("File created");
}

/////////////////////////////////////////////////////////////////////////////////

void search_links(const GumboNode *node, std::vector<std::string> &links)
{
 // check if this a gumbo element or not
 if (node->type != GUMBO_NODE_ELEMENT)
		return;
 // if it's an A tag grab the href
 if (node->v.element.tag == GUMBO_TAG_A)
 {
		GumboAttribute *href = gumbo_get_attribute(&node->v.element.attributes, "href");
		if (href)
			links.push_back(href->value);
 }
 // make a vector for gumbo nodes
 const GumboVector *children = &node->v.element.children;
 // do a for loop to the v.element.children the same check of there parent
 for (size_t i = 0; i < children->length; i++)
 {
		search_links(static_cast<const GumboNode *>(children->data[i]), links);
 }
}

// Callback function to write received data
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
 size_t totalSize = size * nmemb;																																// size is always 1 and nmemb is the size of response
 std::string *responseBody = static_cast<std::string *>(userp);		// convert to string
 responseBody->append(static_cast<char *>(contents), totalSize); // append
 return totalSize;																																															// return value

 /*
 you don't really understand what going on but thats normal,
 this function get handled by api at the end
 */
}
