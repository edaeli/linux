#include <iostream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstring>

using namespace std;

int runCommand(const string &cmd, bool silentMode = false) {
    stringstream ss(cmd);
    string token;
    vector<string> args;
    string outfile = "";
    bool append = false;

    while (ss >> token) {
        if (token == ">" || token == ">>") {
            append = (token == ">>");
            ss >> outfile;
            break;
        } else {
            args.push_back(token);
        }
    }

    if (args.empty()) 
	    return 0;
    vector<char*> argv;
    for (auto &a : args) argv.push_back((char*)a.c_str());
    argv.push_back(nullptr);

    pid_t pid = fork();

    if (pid == 0) {

        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        string newPath = string(cwd) + ":" + getenv("PATH");
        setenv("PATH", newPath.c_str(), 1);

        if (silentMode) {
            string filename = to_string(getpid()) + ".log";
            int fd = open(filename.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            close(fd);
        }

        if (!outfile.empty()) {
            int flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
            int fd = open(outfile.c_str(), flags, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        execvp(argv[0], argv.data());
        perror("execvp");
        exit(1);
    } 
    else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        return WEXITSTATUS(status);
    } 
    else {
        cerr << "Error: fork failed" << endl;
        return 1;
    }
}

int main() {
    string line;

    while (true) {
        cout << "shell> ";
        if (!getline(cin, line)) break;
        if (line == "exit") break;
        if (line.empty()) continue;

        bool silentMode = false;

        if (line.rfind("silent ", 0) == 0) {
            silentMode = true;
            line = line.substr(7);
        }

        stringstream ss(line);
        string part, curr;
        vector<string> commands;
        vector<string> ops;

        while (ss >> part) {
            if (part == ";" || part == "&&" || part == "||") {
                commands.push_back(curr);
                curr = "";
                ops.push_back(part);
            } else {
                if (!curr.empty()) curr += " ";
                curr += part;
            }
        }
        if (!curr.empty()) commands.push_back(curr);

        int lastStatus = 0;
        for (size_t i = 0; i < commands.size(); ++i) {
            if (i == 0) {
                lastStatus = runCommand(commands[i], silentMode);
            } else {
                string op = ops[i - 1];

                if (op == ";") {
                    lastStatus = runCommand(commands[i], silentMode);
                } 
                else if (op == "&&") {
                    if (lastStatus == 0)
                        lastStatus = runCommand(commands[i], silentMode);
                } 
                else if (op == "||") {
                    if (lastStatus != 0)
                        lastStatus = runCommand(commands[i], silentMode);
                }
            }
        }
    }

    return 0;
}

