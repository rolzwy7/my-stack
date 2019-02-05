class Employee():
    ID = 0

    def __init__(self, name, surname, age, gender):
        self.id       = Employee.getID()
        self.name     = name.split(" ")[0]
        self.names    = name.split(" ")[1:]
        self.surname  = surname
        self.age      = age
        self.gender   = gender

    def get_fullname(self, surname_first=False):
        ret = "{surname} {name} {names}" if surname_first else "{name} {names} {surname}"
        return ret.format(name=self.name, surname=self.surname, names=" ".join(self.names))

    @staticmethod
    def getID():
        Employee.ID += 1
        return Employee.ID

class Organization(Employee):
    def __init__(self, name, address):
        self.name             = name
        self.address          = address
        self.employees        = []

    def add_employee(self, **kwargs):
        self.employees.append(Employee(**kwargs))

    def print_employees(self):
        all_print = []
        for employee in self.employees:
            to_print = '''
            ID       : {id}
            Employee : {fullname}
            Gender   : {gender}
            Age      : {age}
            '''.format(
                **employee.__dict__,
                fullname=employee.get_fullname(surname_first=True)
            )
            print(to_print)
            all_print.append(to_print)
        return all_print


organization = Organization("Gapple", "Somewhere Nice 17/45")

organization.add_employee(name="John George", surname="Doe", age=35, gender="M")
organization.add_employee(name="Jane", surname="Doe", age=28, gender="M")
organization.print_employees()
