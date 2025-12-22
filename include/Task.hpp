#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <chrono>
#include <array>
#include <string>
#include <string_view>

namespace TaskSpace {
    constexpr inline std::array<std::string_view, 5> TASK_FIELDS = {
        "id", "description", "status", "creation_time", "updated_time",
    };

    inline std::string GetTime() {
        auto now = std::chrono::system_clock::now();
        std::string time_string = std::format("{:%Y-%m-%d %H:%M:%S}", now);

        return time_string;
    }

    struct TaskData {
        TaskData() : id(1), description(""), status(""), creation_time(""), updated_time("") {};

        int id;
        std::string description;
        std::string status;
        std::string creation_time;
        std::string updated_time;

        friend std::ostream& operator<<(std::ostream &os, const TaskData &obj) {
            os << '"' << obj.id << "\": {\n";
            os << "\t\"status\": \"" << obj.status << "\",\n";
            os << "\t\"description\": \"" << obj.description << "\",\n";
            os << "\t\"creation_time\": \"" << obj.creation_time << "\",\n";
            os << "\t\"updated_time\": \"" << obj.updated_time << "\"\n";
            os << "},\n";

            return os;
        }
    };

    class Task {
    public:
        Task(const TaskSpace::TaskData &data) : data(data) {};
        void SetData(const TaskSpace::TaskData &data) { this->data = data; }
        TaskSpace::TaskData GetData() const { return data; }

    private:
        TaskSpace::TaskData data;
    };
};

#endif 