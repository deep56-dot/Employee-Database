#ifndef _Manager_
#define _Manager_

#include "Employee.h"
#include "../Helper.h"
#include "../LOG/log.h"
#include "../LOG/logger.h"

namespace Model {
    class Manager : public Model::Employee {
    public:
        Manager() = default;
        Manager(int id, const std::string_view& firstname, const std::string_view& lastname, const std::string_view& dob,
            const std::string_view& mobile, const std::string_view& email, const std::string_view& address,
            Gender gender, const std::string_view& doj,
            int manager_id, int department_id, Salary s, int management_experience,
            const std::string_view& project_title)
            : Employee(id, firstname, lastname, dob, mobile, email, address, gender, doj,
                manager_id, department_id, s),
            management_experience(management_experience), project_title(project_title) {}

        int getManagementExperience() const { return management_experience; }
        std::string getProjectTitle() const { return project_title; }

        void setManagementExperience(const int& yrs) { management_experience = yrs; }
        void setProjectTile(const std::string_view& title) { project_title = title; }

        bool viewManager();
        bool insertManager();
        bool deleteManager();
        bool updateManager();
        bool userInputManager();
        void action() noexcept;

    private:

        int management_experience{};
        std::string project_title;
    };
}


#endif