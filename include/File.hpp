#ifndef FILE_HPP
#define FILE_HPP

#include "Task.hpp"
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>

class File {
public:
    File(const std::string &file_name) : file_name(file_name) {};
    void ReadTasksFromFile();
    void WriteTasksToFile();
    void AddTask(const std::string &task_name);
    void UpdateTask(const int &task_id, const std::string &new_task_name);
    void DeleteTask(const int &task_id);
    void ListTasks(const std::string &status);
    void MarkTask(const int &task_id, const std::string &status);

private:
    std::string file_name;
    std::vector<std::unique_ptr<TaskSpace::Task>> tasks;
};

#endif 