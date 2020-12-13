abstract class Figure {
    private String color;

    public Figure (String color) {
        this.color = color;
    }

    public String getColor(){
        return color;
    }

    public void setColor(String newColor) {
        color = newColor;
    }

    abstract public double computePerimeter();
}

class Circle extends Figure{
    private double radius;

    public Circle (String color, double radius) {
        super(color);
        this.radius = radius;
    }

    public double computePerimeter() {
        return 2 * Math.PI * radius;
    }

    public String toString(){
        return "Figure type: Circle - Color: " + this.getColor() + " - Perimeter: " + this.computePerimeter();
    }

    public boolean equals(Object o) {
        return (o instanceof Circle) && ((Circle)o).radius == radius;
    }

    public void setRadius(double newRadius) {
        radius = newRadius;
    }
}

class Triangle extends Figure {
    private double sideA, sideB, sideC;

    public Triangle(String color, double a, double b, double c) {
        super(color);
        sideA = a;
        sideB = b;
        sideC = c;
    }

    public double computePerimeter() {
        return sideA + sideB + sideC;
    }

    public String toString() {
        return "Figure type: Triangle - Color: " + this.getColor() + " - Perimeter: " + this.computePerimeter();
    }

    public boolean equals(Object o) {
        return ((o instanceof Triangle) && ((Triangle) o).computePerimeter() == (sideA + sideB + sideC));
    }

    public void setSides (double a, double b, double c) {
        sideA = a;
        sideB = b;
        sideC = c;
    }
}

class Rectangle extends Figure {
    private double sideA, sideB;

    public Rectangle(String color, double a, double b) {
        super(color);
        sideA = a;
        sideB = b;
    }

    public double computePerimeter() {
        return ((sideA * 2) + (sideB * 2));
    }

    public String toString() {
        return "Figure type: Rectangle - Color: " + this.getColor() + " - Perimeter: " + this.computePerimeter();
    }

    public boolean equals(Object o) {
        return ((o instanceof Rectangle) && ((Rectangle) o).computePerimeter() == (sideA * 2 + sideB * 2));
    }

    public void setSides (double a, double b) {
        sideA = a;
        sideB = b;
    }
}

class Observer {
    private Figure figures[];
    private int currentID = 0;

    public Observer () {
        figures = new Figure[currentID];
    }

    public boolean addFigure (Figure o) {
        if (o instanceof Rectangle || o instanceof Triangle || o instanceof Circle) {

            Figure[] tempFigures = new Figure[currentID+1];
            if (currentID != 0)
                System.arraycopy(figures, 0, tempFigures, 0, currentID);

            tempFigures[currentID] = o;
            figures = tempFigures;
            currentID++;

            return true;
        }
        else return false;
    }

    public String getObserverString () {
        String sir = "";
        for (Figure i : figures) {
            sir = sir + i.toString() + "\n";
        }

        return sir;
    }

}

class ObsClient {
    public static void main(String[] args) {
        Observer name = new Observer();

        Circle a = new Circle("red", 2);
        Rectangle b = new Rectangle("verde", 10, 1);
        Triangle c = new Triangle ("maro", 1, 2, 4);
        Circle d = new Circle ("red", 2);

        System.out.println(name.addFigure(a));
        name.addFigure(b);
        name.addFigure(c);
        name.addFigure(d);

        System.out.println(name.getObserverString());

        System.out.println(d.equals(a));
        System.out.println(d.equals(b));
    }
}