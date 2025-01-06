#include <iostream>
#include <vector>
#include "logic.hpp"

// debug mode
const bool debug_mode{false};

// function
void debug(std::string str);
void debug(int num);

// help menus
const std::string help = R"(
usage: web-scrapper -u [URL] [options]
options:
-u, --url	for your url
-h, --help	for help
-x, --export	choose export file
)";
const std::string fucked_up = R"(
bad argument: try -h or --help for ... you know, it's name\n
)";

// Global
bool check_export {false}; // export or not
std::string expoert_file_name; // for the nameof the file

// main code
int main(int argc, char *argv[])
{
 char *url{"nothing"}; // for the url
 std::string html;					// for the response body

 //==[handling arguments]==//
 debug(argc); //]
 for (int i = 0; i < argc; i++)
 {
		debug(i);							//]
		debug(argv[i]); //]

		std::string arg = std::string(argv[i]); // flag
		char *vlu = argv[i + 1];																// value

		if (arg == "-h" || arg == "--help") // HELP
		{
			std::cout << help;
			return 0;
		}
		else if (arg == "-u" || arg == "--url") // URL
		{
			if (i != argc - 1)
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
		else if (arg == "-x" || arg == "--export") // EXPORT
		{
			check_export= true;
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
	if (!check_export)
	{
		dls_head("LINKS");
		for (auto const &link : links)
		{
			dls_confirm(link.c_str());
		}
	}
	else
	{
		std::string data;
		data += "===[LINKS]===(inside->\t";
		data += std::string(url);
		data += '\n';
		for (auto const &link : links)
		{
			data += "[+] ";
			data += link;
			data += '\n';
		}

		create_file(data, expoert_file_name);
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