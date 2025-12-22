#include "Task.hpp"
#include <fstream>
#include <algorithm>
#include <string_view>

int main() {
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
                switch(line[i]) {
                    case '"':
                        if (line[i + 1] != ':') {
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

                            i++;
                        }

                        break;

                    case '{':
                        data.id = std::stoi(in_paren);
                        i++;

                        break;

                    case '}':
                        std::cout << data << "\n\n";
                        std::cout << "End of entry!\n";
                        data = {};

                    default:
                        i++;
                }
            }
        }
    }
}