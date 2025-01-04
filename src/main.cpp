#include <iostream>
#include <vector>
#include "logic.hpp"

// debug mode
const bool debug_mode {false};

// function
void debug(std::string str);
void debug(int num);

// help menus
const std::string help = R"(
usage: web-scrapper -u [URL] [options]
options:
-u, --url	for your url
-h, --help	for help
)";
const std::string fucked_up = R"(
bad argument: try -h or --help for ... you know, it's name\n
)";

// main code
int main(int argc, char* argv[])
{
	char* url {"nothing"}; // for the url
	std::string html; // for the response body

	//==[handling arguments]]==//
	debug(argc);//]
	for (int i=0; i < argc; i++)
	{
		debug(i);//]
		debug(argv[i]);//]

		std::string arg = std::string(argv[i]); // flag
		char* vlu = argv[i + 1]; // value

		if (arg == "-h" || arg == "--help")
		{
			std::cout << help;
			return 0;
		}
		else if (arg == "-u" || arg == "--url")
		{
			if (i != argc-1)
			{
				url = vlu;
			}
			else
			{
				dls_deny("you miss the -u value");
				std::cout << fucked_up;
				return 1;
			}
		}
	}
	if (url == "nothing")
	{
		std::cout << fucked_up;
		return 1; // no url
	}
	//=========================//

	dls_wait("Proccessing the inputs");
	// simple_https_get("https://example.com");
	html = return_body(url);
	if (html == "fuck you")
	{
		dls_deny("Bad URL");
		return 1;
	}
	std::vector<std::string> links = grab_links(html);
	dls_head("LINKS");
 for (auto const& link: links)
	{
		dls_confirm(link.c_str());
	}

	return 0;
}

void debug(std::string str)
{
	if (debug_mode)
		std::cout << str << std::endl;
	else
		return;
}
void debug(int num)
{
	if (debug_mode)
		std::cout << num << std::endl;
	else
		return;
}