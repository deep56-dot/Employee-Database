#include "../include/Model/Department.h"
#include "../include/Model/Engineer.h" 
#include "../include/Model/Manager.h"

using namespace std;

void action(int j) {
	auto check{ true };
	while (check) {
		system("cls");
		std::cout << "Select The Operation You Want The Perform\n";
		std::cout << "1. View\n";
		std::cout << "2. Insert\n";
		std::cout << "3. Update\n";
		std::cout << "4. Delete\n";
		std::cout << "5. Go to Main Menu\n\n";

		int i;
		i = std::stoi(input("Enter Your Choice : ", std::regex{ "[1-5]" }));
		Engineer e;
		Manager m;
		Department d;
		switch (j) {
		case 1:
			switch (i) {
			case 1:
				e.viewEngineer();
				break;

			case 2:
				e.insertEngineer();
				break;

			case 3:
				e.updateEngineer();
				break;

			case 4:
				e.deleteEngineer();
				break;

			case 5:
				check = false;
				break;
			}
			break;

		case 2:
			switch (i) {
			case 1:
				m.viewManager();
				break;

			case 2:
				m.insertManager();
				break;

			case 3:
				m.updateManager();
				break;

			case 4:
				m.deleteManager();
				break;

			case 5:
				check = false;
				break;
			}
			break;

		case 3:
			switch (i) {
			case 1:
				d.viewDepartment();
				break;

			case 2:
				d.insertDepartment();
				break;

			case 3:
				d.updateDepartment();
				break;

			case 4:
				d.deleteDepartment();
				break;

			case 5:
				check = false;
				break;
			}
			break;

		default:
			std::cout << "Enter Valid Choice\n";
		}
	}
}
