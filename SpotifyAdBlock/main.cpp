// made by const - github.com/yfz

#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const std::string spotify_path = std::string(std::getenv("APPDATA")) + "\\Spotify\\Spotify.exe";
const std::string hosts_path = "C:\\Windows\\System32\\drivers\\etc\\hosts";

const std::vector<std::string> allahyok = {
    "0.0.0.0 audio-ads.spotify.com",
    "0.0.0.0 pubads.g.doubleclick.net",
    "0.0.0.0 googleads.g.doubleclick.net",
    "0.0.0.0 spclient.wg.spotify.com"
};

enum class log_level { info, success, error };

void log(log_level level, const std::string& message) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    static const struct { const char* prefix; WORD color; } settings[] = {
        { "[#] ", FOREGROUND_RED | FOREGROUND_GREEN },
        { "[+] ", FOREGROUND_GREEN | FOREGROUND_INTENSITY },
        { "[-] ", FOREGROUND_RED | FOREGROUND_INTENSITY }
    };

    auto& [prefix, color] = settings[static_cast<size_t>(level)];

    SetConsoleTextAttribute(hConsole, color);
    std::cout << prefix;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << message << std::endl;
}

void hi_spotify() {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return;

    PROCESSENTRY32 pe{ sizeof(PROCESSENTRY32) };
    bool killed = false;

    if (Process32First(snapshot, &pe)) {
        do {
            if (!_wcsicmp(pe.szExeFile, L"Spotify.exe")) {
                HANDLE proc = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
                if (proc) {
                    TerminateProcess(proc, 0);
                    CloseHandle(proc);
                    killed = true;
                }
            }
        } while (Process32Next(snapshot, &pe));
    }

    CloseHandle(snapshot);

    if (killed) {
        log(log_level::success, "Operation completed: Spotify process has been successfully terminated.");
    }
    else {
        log(log_level::info, "Status check: Spotify process was not found among running applications. No action required.");
    }
}

void start_spotify() {
    if (GetFileAttributesA(spotify_path.c_str()) == INVALID_FILE_ATTRIBUTES) {
        log(log_level::error, "Unable to locate Spotify. Please ensure Spotify is installed correctly at: " + spotify_path);
        return;
    }

    ShellExecuteA(NULL, "open", spotify_path.c_str(), nullptr, nullptr, SW_SHOW);
    log(log_level::success, "Launching Spotify... Please wait for initialization to complete.");
}

bool write_hosts(const std::string& content, std::ios_base::openmode mode) {
    std::ofstream hosts(hosts_path, mode);
    if (!hosts) return false;
    hosts << content;
    hosts.close();
    return true;
}

void update_hosts() {
    std::string content = "\n# Block Spotify advertisements - made by Const\n";
    for (const auto& line : allahyok) content += line + "\n";

    if (write_hosts(content, std::ios::app)) {
        log(log_level::success, "Hosts file successfully updated with Spotify advertisement blocking rules." +
            std::to_string(allahyok.size()) + " domains have been blocked.");
    } else {
        log(log_level::error, "Failed to modify hosts file. Access denied. Please run the application with administrator privileges to apply changes.");
    }
}

int main() {
    SetConsoleTitleA("Spotify AdBlock Tool | made by const");

    log(log_level::info, "Starting Spotify AdBlock Tool initialization process...");

    log(log_level::info, "Scanning system for active Spotify processes...");
    hi_spotify();

    log(log_level::info, "Updating system hosts file with advertisement domain blocks...");
    update_hosts();

    log(log_level::info, "Launching Spotify application with advertisement protection...");
    start_spotify();

    log(log_level::info, "AdBlock completed. press enter to exit...");
    log(log_level::info, "Thank you for using Spotify AdBlock Tool! Please remember: this tool is provided as-is, and any use is your own responsibility. If you want to reach me, you can do so here: https://t.me/xconst");

    std::cin.get();

    return 0;
}