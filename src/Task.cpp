#include "Task.hpp"
#include <chrono>
#include <format>

namespace TaskSpace {
    const std::array<std::string_view, 5> TASK_FIELDS = {
        "id", "description", "status", "creation_time", "updated_time"
    };

    std::string GetTime() {
        auto now = std::chrono::system_clock::now();
        return std::format("{:%Y-%m-%d %H:%M:%S}", now);
    }

    TaskData::TaskData() : id(1), description(""), status(""), 
                           creation_time(""), updated_time("") {}

    std::ostream& operator<<(std::ostream &os, const TaskData &obj) {
        os << '"' << obj.id << "\": {\n"
           << "\t\"status\": \"" << obj.status << "\",\n"
           << "\t\"description\": \"" << obj.description << "\",\n"
           << "\t\"creation_time\": \"" << obj.creation_time << "\",\n"
           << "\t\"updated_time\": \"" << obj.updated_time << "\"\n"
           << "},\n";
        return os;
    }

    Task::Task(const TaskSpace::TaskData &data) : data(data) {}
    void Task::SetData(const TaskSpace::TaskData &data) { this->data = data; }
    TaskSpace::TaskData Task::GetData() const { return data; }
}