#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <algorithm>

using namespace std;

bool isNotPrintable(char c)
{
    return !(c >= 32 && c <= 126);
}

string strip(const string& str)
{
    auto tmp = str;
    tmp.erase(remove_if(tmp.begin(), tmp.end(), isNotPrintable), tmp.end());
    return tmp;
}

string trim(const string& str)
{
    auto tmp = str;
    static const auto UPPERCASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const auto start = tmp.find_first_of(UPPERCASE);
    if (start != string::npos)
        tmp = tmp.substr(start, tmp.length());
    return tmp;
}

int main() {
    while (true) {
        // parse stdout of nordvpn status
        FILE* pipe = popen("nordvpn status", "r");
        stringstream ss;
        ss << "{\"title\": \"NordVPN Status\"";
        bool success = true;
        if (!pipe) {
            ss << ", \"what\": \"Broken pipe in the native application\"";
            success = false;
        } else if (fgetc(pipe) == EOF) {
            ss << ", \"what\": \"Failed to call 'nordvpn status' in shell\"";
            success = false;
        } else {
            char buffer[64];
            while (fgets(buffer, sizeof(buffer), pipe)) {
                // get line
                string line = string(buffer);

                // strip line from undesired characters
                line = trim(strip(line));

                // split into key and value
                const auto pos = line.find(':');
                if (pos == string::npos) {
                    success = false;
                    ss << ", \"what\": \"Failed to parse NordVPN status\"";
                } else {
                    const auto key = strip(line.substr(0, pos));
                    const auto val = strip(line.substr(pos + 2, line.length()));
                    ss << ", \"" << key << "\": " << "\"" << val << "\"";
                }
            }
        }
        pclose(pipe);

        ss << ", \"success\":";
        if (success)
            ss << "true";
        else
            ss << "false";

        ss << "}";

        // send message to stdout
        const auto msg = ss.str();
        unsigned int len = msg.length();
        auto blen = reinterpret_cast<char *>(&len);
        cout.write(blen, 4);
        cout << msg << flush;

        // sleep
        this_thread::sleep_for (chrono::seconds(2));
    }
}
