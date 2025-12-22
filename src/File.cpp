#include "File.hpp"

void File::ReadTasksFromFile() {
    std::ifstream file(file_name);

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
                    TaskSpace::Task copy{data};
                    tasks.push_back(std::make_unique<TaskSpace::Task>(copy));
                    data = {};
                }

                i++;
            }
        }
    }
}

void File::WriteTasksToFile() {
    std::ofstream file(file_name);

    if (!file.is_open()) {
        std::cerr << "Could not open!";
    } else {
        file << "{\n";

        for (const auto& task : tasks) {
            file << task->GetData();
        }

        file << "}";
    }
}

void File::AddTask(const std::string &task_name) {
    TaskSpace::TaskData data{};
    data.id = tasks.size() + 1;
    data.status = "todo";
    data.description = task_name;
    data.creation_time = TaskSpace::GetTime();
    data.updated_time = TaskSpace::GetTime();
    TaskSpace::Task copy{data};
    tasks.push_back(std::make_unique<TaskSpace::Task>(copy));
}

void File::UpdateTask(const int &task_id, const std::string &new_task_name) {
    auto task = std::find_if(tasks.begin(), tasks.end(), [task_id](const auto &t) { return t->GetData().id == task_id; });

    if (task != tasks.end()) {
        TaskSpace::TaskData new_data = task->get()->GetData();
        new_data.description = new_task_name;
        new_data.updated_time = TaskSpace::GetTime();
        task->get()->SetData(new_data);
    } else {
        std::cerr << "Task not found!";
    }
}