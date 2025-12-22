#include "File.hpp"
#include <unordered_map>
#include <functional>

int main(int argc, char* argv[]) {
    // Start by reading from the file.
    File file("tasks.json");
    file.ReadTasksFromFile();

    int i = 1;
    using CommandFunc = std::function<void()>;

    std::unordered_map<std::string, CommandFunc> commands = {
        {"add", [&]() { 
            if (i + 1 < argc) {
                std::string task_name = argv[++i];
                file.AddTask(task_name);
            }
        }},
        {"update", [&]() {
            if (i + 2 < argc) {
                int task_id = std::stoi(argv[++i]);
                std::string new_task_name = argv[++i];
                file.UpdateTask(task_id, new_task_name);
            }
        }},
        {"delete", [&]() { 
            if (i + 1 < argc) {
                int task_id = std::stoi(argv[++i]);
                file.DeleteTask(task_id);
            }
        }},
        {"list", [&]() { 
            if (i + 1 < argc) {
                std::string status = argv[i + 1];

                if (status == "done" || status == "todo" || status == "in-progress") {
                    file.ListTasks(status);
                    i++;
                } else {
                    file.ListTasks("");
                }
            } else {
                file.ListTasks("");
            }
        }},
        {"mark-in-progress", [&]() { 
            if (i + 1 < argc) {
                int task_id = std::stoi(argv[++i]);
                file.MarkTask(task_id, "in-progress");
            }
        }},
        {"mark-done", [&]() { 
            if (i + 1 < argc) {
                int task_id = std::stoi(argv[++i]);
                file.MarkTask(task_id, "done");
            }
        }}
    };

    while (i < argc) {
        std::string command = argv[i];
        commands[command]();
        i++;
    }

    // End by writing to the file.
    file.WriteTasksToFile();
}