import java.util.ArrayList;

class EmployeeExcept extends Exception {
    public String toString() { return "Employee already stored"; }
}

abstract class Employee {
    private String name;
    private String personalID;

    public Employee (String name, String personalID) {
        this.name = name;
        this.personalID = personalID;
    }

    public String getName () {
        return this.name;
    }

    abstract public double getSalary ();

    public boolean equals(Object o) {
        if (o instanceof Employee) {
            return this.name.equals(((Employee) o).name) && this.personalID.equals(((Employee) o).personalID);
        }

        return false;
    }

    @Override
    public String toString() {
        return "Employee " + name + ", " + personalID;
    }
}

class PermanentEmployee extends Employee{
    private int payment;

    public PermanentEmployee (String name, String personalID, int salary) {
        super(name, personalID);
        payment = salary;
    }

    public double getSalary () {
        return payment;
    }
}

class HourlyEmployee extends Employee{
    private int workedHrs = 0;
    private int moneyPerHour;

    public HourlyEmployee (String name, String personalID, int moneyPerHour) {
        super(name, personalID);
        this.moneyPerHour = moneyPerHour;
    }

    public void SetWorkHours (int workedHrs) {
        this.workedHrs= workedHrs;
    }

    public double getSalary () {
        return workedHrs * moneyPerHour;
    }
}

interface Strategy {
    boolean isCondition(Employee employee);
}

class StrategyString implements Strategy{
    String name;

    public StrategyString (String name) {
        this.name = name;
    }

    @Override
    public boolean isCondition(Employee employee) {
        return this.name.equals(employee.getName());
    }
}

class StrategyInt implements Strategy {
    @Override
    public boolean isCondition(Employee employee) {

        return employee.getSalary() > 1000;
    }
}

class Company {
    ArrayList <Employee> angajati;

    public Company () {
        angajati  = new ArrayList<>();
    }

    public void addEmployee(Employee newEmployee) throws EmployeeExcept {

       for (Employee angajat: angajati)
           if (angajat.equals(newEmployee)) {
               throw new EmployeeExcept();
           }

       angajati.add(newEmployee);

    }

    @Override
    public String toString() {
        StringBuilder employeetData = new StringBuilder();

        for (Employee angajat: angajati)
            employeetData.append(angajat.toString()).append(", salariu = ").append(angajat.getSalary()).append('\n');

        return String.valueOf(employeetData);
    }

    public boolean isInCompany(Strategy strategy) {

        for (Employee angajat: angajati)
            if (strategy.isCondition(angajat))
                return true;

        return false;
    }

    public static void main(String[] args)
    {
        Company myCompany = new Company();

        PermanentEmployee a = new PermanentEmployee("Juan","255", 10);
        PermanentEmployee b = new PermanentEmployee("Juan","255", 555);
        HourlyEmployee c = new HourlyEmployee("Calu", "22", 1001);

        try{
            myCompany.addEmployee(a);
            myCompany.addEmployee(b);
            myCompany.addEmployee(c);
        }catch (EmployeeExcept e) {
            System.out.println(e);
        }


        System.out.println(myCompany.toString());

        StrategyString juanStrat = new StrategyString("Juan");
        StrategyString dogStrat = new StrategyString("Dog");
        StrategyInt intStrat = new StrategyInt();

        System.out.println("Is there a Juan? " + myCompany.isInCompany(juanStrat));
        System.out.println("Is there a Dog? " + myCompany.isInCompany(dogStrat));
        System.out.println("Are employees paid more than 1k? " + myCompany.isInCompany(intStrat));

        c.SetWorkHours(1);
        System.out.println("\n" + myCompany.toString());

        System.out.println("Are employees paid more than 1k? " + myCompany.isInCompany(intStrat));
    }
}
