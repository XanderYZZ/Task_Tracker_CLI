#include "File.hpp"

int main(int argc, char* argv[]) {
    // Start by reading from the file.
    File file("tasks.json");
    file.ReadTasksFromFile();

    int i = 1;

    while (i < argc) {
        std::string command = argv[i];

        if (command == "add") {
            if (i + 1 < argc) {
                std::string task_name = argv[++i];
                file.AddTask(task_name);
            }
        } else if (command == "update") {
            if (i + 2 < argc) {
                int task_id = std::stoi(argv[++i]);
                std::string new_task_name = argv[++i];
                file.UpdateTask(task_id, new_task_name);
            }
        } else if (command == "delete") {
            if (i + 1 < argc) {
                int task_id = std::stoi(argv[++i]);
                file.DeleteTask(task_id);
            }
        } else if (command == "list") {
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
        }

        i++;
    }

    // End by writing to the file.
    file.WriteTasksToFile();
}