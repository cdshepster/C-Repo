#include <iostream>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <cmath>
#include <chrono>
#include <sys/wait.h>
#include <errno.h>
#include <err.h>
#include <unistd.h>
#include <signal.h>


using namespace std;

void sigintHandler(int sig_num) {
    signal(SIGINT, sigintHandler);
    printf("\n Cannot be terminated using Ctrl+C \n");
    printf("[cmd]: ");
    fflush(stdout);
}

bool foundCarrot(string cmd) {
    std::size_t found = cmd.find('^');
    return found == 0;
}

bool foundPipe(string cmd) {
    std::size_t found = cmd.find('|');
    return found != string::npos;
}

bool isCD(string cmd) {
    std::size_t foundC = cmd.find('c' | 'C');
    std::size_t foundD = cmd.find('d' | 'D');
    std::size_t found = cmd.find(' ');
    return foundC == 0 && foundD == 1 && found == 2;
}

int main() {
    signal(SIGINT, sigintHandler);
    vector<string> commandHistory;
    std::chrono::microseconds time(0);

    while (true) {

        string cmdString;
        string input;
        vector<string> argBuilder;

        cout << "[cmd]: ";
        std::getline(std::cin, cmdString);
        commandHistory.push_back(cmdString);

        if (foundPipe(cmdString)) {
            int pipefd[2];
            pipe(pipefd);

            string cmdString1;
            string cmdString2;
            vector<string> argBuilder1;
            vector<string> argBuilder2;

            string sb;

            for (int i = 0; i < cmdString.length(); i++) {
                if (cmdString[i] == '|') {
                    sb.erase(sb.begin() + i - 1);
                    cmdString1 = sb;
                    sb = "";
                }
                sb += cmdString[i];
            }
            sb.erase(0, 2);
            cmdString2 = sb;

            string sb1;
            for (int i = 0; i <= cmdString1.size(); i++) {
                if (i == cmdString1.size()) {
                    argBuilder1.push_back(sb1);
                } else if (cmdString1[i] != ' ') {
                    sb1 += cmdString1[i];
                } else {
                    argBuilder1.push_back(sb1);
                    sb1 = "";
                }
            }
            string sb2;
            for (int i = 0; i <= cmdString2.size(); i++) {
                if (i == cmdString2.size()) {
                    argBuilder2.push_back(sb2);
                } else if (cmdString2[i] != ' ') {
                    sb2 += cmdString2[i];
                } else {
                    argBuilder2.push_back(sb2);
                    sb2 = "";
                }
            }

            if (cmdString == "ptime") {
                auto seconds = std::chrono::duration_cast<std::chrono::seconds>(time);
                auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(time);
                auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(time);

                double time =
                        seconds.count() + (milliseconds.count() * pow(10, -3)) + (microseconds.count() * pow(10, -6));

                std::cout << "Time spent running child processes: " << time << " seconds." << endl;
            } else {
                if (fork() == 0) {

                    dup2(pipefd[1], STDOUT_FILENO);

                    time = std::chrono::milliseconds::zero();
                    auto startTime = std::chrono::system_clock::now();
                    // wait for child process to finish
                    wait(NULL);
                    // stop the clock
                    auto endTime = std::chrono::system_clock::now();

                    time += std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

                    char **args = new char *[argBuilder1.size()];

                    for (int i = 0; i < argBuilder1.size(); i++) {
                        args[i] = (char *) argBuilder1[i].c_str();
                    }

                    args[argBuilder1.size()] = (char *) NULL;
                    if (execvp(args[0], args) < 0)
                        cerr << args[0] << endl << " did something wrong\n";

                }
                if (fork() == 0) {

                    // close(p[WRITE]);
                    dup2(pipefd[0], STDIN_FILENO);

                    char **args = new char *[argBuilder2.size()];

                    for (int i = 0; i < argBuilder2.size(); i++) {
                        args[i] = (char *) argBuilder2[i].c_str();
                    }

                    args[argBuilder2.size()] = (char *) NULL;

                    if (execvp(args[0], args) < 0)
                        cerr << args[0] << endl << " did something wrong\n";
                }
                close(pipefd[0]);
                close(pipefd[1]);
            }
        } else {
            string sb;
            for (int i = 0; i <= cmdString.size(); i++) {
                if (i == cmdString.size()) {
                    argBuilder.push_back(sb);
                } else if (cmdString[i] != ' ') {
                    sb += cmdString[i];
                } else {
                    argBuilder.push_back(sb);
                    sb = "";
                }
            }
            if (foundCarrot(cmdString)) {
                argBuilder.clear();
                string str;
                int index;
                try {
                    for (int i = 2; i < cmdString.length(); i++) {
                        str += cmdString[i];
                    }
                    index = stoi(str);

                    cmdString = commandHistory[index - 1];

                    string sb1;
                    for (int i = 0; i <= cmdString.size(); i++) {
                        if (i == cmdString.size()) {
                            argBuilder.push_back(sb1);
                        } else if (cmdString[i] != ' ') {
                            sb1 += cmdString[i];
                        } else {
                            argBuilder.push_back(sb1);
                            sb1 = "";
                        }
                    }

                } catch (exception &e) {
                    cout << "Try again. " << endl;
                }
            }

            if (cmdString == "exit") {
                break;
            } else if (cmdString == "history") {
                commandHistory.pop_back();

                cout << "-- Command History --" << endl;
                cout << endl;

                for (int i = 0; i < commandHistory.size(); i++) {
                    cout << i + 1 << " : " << commandHistory[i] << endl;
                }
                cout << endl;
            } else if (cmdString == "ptime") {
                auto seconds = std::chrono::duration_cast<std::chrono::seconds>(time);
                auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(time);
                auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(time);

                double time =
                        seconds.count() + (milliseconds.count() * pow(10, -3)) + (microseconds.count() * pow(10, -6));

                std::cout << "Time spent running child processes: " << time << " seconds." << endl;
            } else if (isCD(cmdString)) {
                cmdString.erase(0, 3);
                chdir(cmdString.c_str());

                char buffer[200];
                char *path = getcwd(buffer, 200);
                if (!path) {
                } else {
                    string CurrentPath;
                    CurrentPath = path;
                    cout << CurrentPath << endl;
                }


            } else {
                if (fork()) {

                    time = std::chrono::milliseconds::zero();
                    auto startTime = std::chrono::system_clock::now();
                    // wait for child process to finish
                    wait(NULL);
                    // stop the clock
                    auto endTime = std::chrono::system_clock::now();

                    time += std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

                } else {
                    char **args = new char *[argBuilder.size()];

                    for (int i = 0; i < argBuilder.size(); i++) {
                        args[i] = (char *) argBuilder[i].c_str();
                    }

                    args[argBuilder.size()] = (char *) NULL;

                    execvp(args[0], args);

                    cerr << args[0] << endl << " did something wrong\n";
                    exit(1);
                }
            }
        }
    }

    return 0;
}
