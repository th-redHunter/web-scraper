#define LOGIC
#ifdef LOGIC
#include <iostream>
#include <string>
#include <vector>
#include <map>

typedef std::map<std::string, std::string> STR_MAP;
typedef std::vector<std::string> STR_VECTOR;

void simple_https_get(char *url);                       // simpe https get request
std::string return_body(char *url);                     // return the body
std::vector<std::string> grab_links(std::string &html); // grab links
void create_file(std::string text, std::string name);

/* allow SPOS */
#define dls_confirm(msg) printf("[+] %s\n", msg);        // confirm
#define dls_deny(msg) printf("[-] %s\n", msg);           // deny
#define dls_info(msg) printf("[$] %s\n", msg);           // info
#define dls_warn(msg) printf("[!] %s\n", msg);           // warn
#define dls_input(msg) printf("[~] %s : \n", msg);       // input
#define dls_wait(msg) printf("[&] %s...\n", msg);        // wait
#define dls_err(msg) printf("[!] ERROR : %s\n", msg);    // error
#define dls_head(msg) printf("[=====(%s)=====]\n", msg); // header

#endif
