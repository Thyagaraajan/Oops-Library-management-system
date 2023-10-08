#include <iostream>
#include <string>
#include <vector>

class Employee {
protected:
    std::string name;
    int employeeID;
    double salary;

public:
    Employee(std::string name, int employeeID, double salary) : name(name), employeeID(employeeID), salary(salary) {}

    virtual double calculatePay() const = 0;
    virtual void displayDetails() const = 0;
};

class Manager : public Employee {
private:
    int numberOfSubordinates;

public:
    Manager(std::string name, int employeeID, double salary, int numberOfSubordinates)
        : Employee(name, employeeID, salary), numberOfSubordinates(numberOfSubordinates) {}

    double calculatePay() const override {
        return salary + 0.1 * salary * numberOfSubordinates;
    }

    void displayDetails() const override {
        std::cout << "Manager Name: " << name << ", ID: " << employeeID << ", Salary: " << salary << ", Subordinates: "
                  << numberOfSubordinates << "\n";
    }
};

class Engineer : public Employee {
private:
    std::string specialization;

public:
    Engineer(std::string name, int employeeID, double salary, std::string specialization)
        : Employee(name, employeeID, salary), specialization(specialization) {}

    double calculatePay() const override {
        return salary;
    }

    void displayDetails() const override {
        std::cout << "Engineer Name: " << name << ", ID: " << employeeID << ", Salary: " << salary
                  << ", Specialization: " << specialization << "\n";
    }
};

class HourlyEmployee : public Employee {
private:
    int hoursWorked;
    double hourlyRate;

public:
    HourlyEmployee(std::string name, int employeeID, double salary, int hoursWorked, double hourlyRate)
        : Employee(name, employeeID, salary), hoursWorked(hoursWorked), hourlyRate(hourlyRate) {}

    double calculatePay() const override {
        return salary + hoursWorked * hourlyRate;
    }

    void displayDetails() const override {
        std::cout << "Hourly Employee Name: " << name << ", ID: " << employeeID << ", Salary: " << salary
                  << ", Hours Worked: " << hoursWorked << ", Hourly Rate: " << hourlyRate << "\n";
    }
};

class SalaryEmployee : public Employee {
public:
    SalaryEmployee(std::string name, int employeeID, double salary)
        : Employee(name, employeeID, salary) {}

    double calculatePay() const override {
        return salary;
    }

    void displayDetails() const override {
        std::cout << "Salary Employee Name: " << name << ", ID: " << employeeID << ", Salary: " << salary << "\n";
    }
};

class Department {
private:
    std::string name;
    std::vector<Employee*> employees;

public:
    Department(std::string name) : name(name) {}

    void addEmployee(Employee* employee) {
        employees.push_back(employee);
    }

    void displayEmployees() const {
        std::cout << "Employees in Department " << name << ":\n";
        for (const Employee* employee : employees) {
            employee->displayDetails();
        }
    }
};

class TeamLeader : public Employee {
private:
    Department* department;

public:
    TeamLeader(std::string name, int employeeID, double salary, Department* department)
        : Employee(name, employeeID, salary), department(department) {}

    double calculatePay() const override {
        return salary + 0.05 * salary; // Team leader bonus
    }

    void displayDetails() const override {
        std::cout << "Team Leader Name: " << name << ", ID: " << employeeID << ", Salary: " << salary << "\n";
        department->displayEmployees();
    }
};

class EmployeeManagementSystem {
private:
    std::vector<Department> departments;
    std::vector<Employee*> employees;

public:
    void addDepartment(const Department& department) {
        departments.push_back(department);
    }

    void addEmployee(Employee* employee) {
        employees.push_back(employee);
    }

    void displayEmployeeDetails() const {
        std::cout << "Employee Details:\n";
        for (const Employee* employee : employees) {
            employee->displayDetails();
            std::cout << "Calculated Pay: " << employee->calculatePay() << "\n";
        }
    }
};

int main() {
    EmployeeManagementSystem ems;

    Department hr("HR Department");
    Department engineering("Engineering Department");

    Manager manager("John", 1, 50000, 5);
    Engineer engineer("Alice", 2, 60000, "Software");
    HourlyEmployee hourlyEmployee("Bob", 3, 20000, 160, 10);
    SalaryEmployee salaryEmployee("Eve", 4, 70000);

    hr.addEmployee(&manager);
    engineering.addEmployee(&engineer);
    engineering.addEmployee(&hourlyEmployee);
    engineering.addEmployee(&salaryEmployee);

    ems.addDepartment(hr);
    ems.addDepartment(engineering);

    TeamLeader teamLeader("Mike", 5, 60000, &engineering);

    ems.addEmployee(&teamLeader);

    ems.displayEmployeeDetails();

    return 0;
}
