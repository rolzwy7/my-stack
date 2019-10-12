from abc import ABC as AbstractBaseClass, abstractmethod


class Employee(AbstractBaseClass):
    def __init__(self, name, surname):
        self.name = name
        self.surname = surname

    @abstractmethod
    def calcSalary(self):
        raise NotImplementedError("Method not implemented")

    def __str__(self):
        return f"{self.name} {self.surname} <{self.employee_type}>"


class HourlyEmployee(Employee):
    employee_type = "Hourly Employee"

    def __init__(self, name, surname, hours, per_hour, days=5):
        super(HourlyEmployee, self).__init__(name, surname)
        self.hours = hours
        self.per_hour = per_hour
        self.days = days

    def calcSalary(self):
        return self.hours * self.per_hour * self.days


class CommissionEmployee(Employee):
    employee_type = "Commission Employee"

    def __init__(self, name, surname, fixed_salary, products_sold, comission):
        super(CommissionEmployee, self).__init__(name, surname)
        self.fixed_salary = fixed_salary
        self.products_sold = products_sold
        self.comission = comission

    def calcSalary(self):
        return self.fixed_salary + (self.products_sold * self.comission)


hourly_employee = HourlyEmployee("John", "Doe", hours=8, per_hour=15)
print(hourly_employee, hourly_employee.calcSalary())

commission_employee = CommissionEmployee("Jane", "Doe", fixed_salary=500, products_sold=51, comission=3)
print(commission_employee, commission_employee.calcSalary())
