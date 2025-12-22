#include "Task.hpp"
#include <fstream>
#include <algorithm>
#include <string_view>
#include <memory>

std::vector<std::unique_ptr<TaskSpace::Task>> tasks;

void ReadTasksFromFile() {
    std::ifstream file("tasks.json");

    if (!file.is_open()) {
        std::cerr << "Could not open!";
    } else {
        std::string line;
        TaskSpace::TaskData data{};

        while (std::getline(file, line)) {
            if (line.size() <= 1) { continue; } // The first and last lines with just brackets on the first character.

            int i = 0;
            std::string curr_key = "", in_paren = "";

            while (i < line.size()) {
                if (line[i] == '"' && line[i + 1] != ':') {
                    i++;

                    while (line[i] != '"') {
                        in_paren += line[i];
                        i++;
                    }

                    // If the previous token was a key, then this new value is the value for that key
                    if (curr_key != "") {
                        if (curr_key == "status") {
                            data.status = in_paren;
                        } else if (curr_key == "description") {
                            data.description = in_paren;
                        } else if (curr_key == "creation_time") {
                            data.creation_time = in_paren;
                        } else if (curr_key == "updated_time") {
                            data.updated_time = in_paren;
                        }

                        curr_key = "";
                    } else {
                        bool found = std::ranges::contains(TaskSpace::TASK_FIELDS, in_paren);
                        
                        if (found) {
                            curr_key = in_paren;
                            in_paren = "";
                        }
                    }
                } else if (line[i] == '{') {
                    data.id = std::stoi(in_paren);
                } else if (line[i] == '}') {
                    TaskSpace::Task copy = data;
                    tasks.push_back(std::make_unique<TaskSpace::Task>(copy));
                    data = {};
                }

                i++;
            }
        }
    }
}

void ListenToUserInput() {

}

int main() {
    ReadTasksFromFile();
    ListenToUserInput();
}