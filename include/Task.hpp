#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <array>
#include <string>
#include <string_view>

namespace TaskSpace {
    extern const std::array<std::string_view, 5> TASK_FIELDS;
    
    std::string GetTime();

    struct TaskData {
        int id;
        std::string description;
        std::string status;
        std::string creation_time;
        std::string updated_time;

        TaskData();
        friend std::ostream& operator<<(std::ostream &os, const TaskData &obj);
    };

    class Task {
    public:
        Task(const TaskSpace::TaskData &data);
        void SetData(const TaskSpace::TaskData &data);
        TaskSpace::TaskData GetData() const;
    private:
        TaskSpace::TaskData data;
    };
}

#endif