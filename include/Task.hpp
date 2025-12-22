#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <chrono>
#include <array>

namespace TaskSpace {
    std::array<std::string, 5> TASK_FIELDS = {
        "id", "description", "status", "creation_time", "updated_time",
    };

    struct TaskData {
        TaskData() : id(1), description(""), status(""), creation_time(""), updated_time("") {};

        int id;
        std::string description;
        std::string status;
        std::string creation_time;
        std::string updated_time;

        friend std::ostream& operator<<(std::ostream &os, const TaskData &obj) {
            os << "Id: " << obj.id << "\n"
            << "Description: " << obj.description << "\n"
            << "Status: " << obj.status << "\n"
            << "Creation Time: " << obj.creation_time << "\n"
            << "Updated Time: " << obj.updated_time << "\n";

            return os;
        }
    };

    class Task {
    public:
        Task(const TaskSpace::TaskData &data) : data(data) {};
        TaskSpace::TaskData GetData() const { return data; }

    private:
        TaskSpace::TaskData data;
    };
};

#endif 