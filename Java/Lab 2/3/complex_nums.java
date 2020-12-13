class Complex {
	public double re, im;
	private double module;
	private static int printingCounter = 0;

	public Complex(double real, double imaginary) {
		re = real;
		im = imaginary;
	}

	public void printComplex() {
		System.out.print("(" + re + " + " + im + "i" + ")");
		printingCounter++;
	}

	public double computeModule() {
		module = Math.sqrt(re*re + im*im);

		return module;
	}

	public Complex complexSum(Complex toBeAdded) {
		Complex sum = new Complex(0,0);
		sum.re = this.re + toBeAdded.re;
		sum.im = this.im + toBeAdded.im;
		return sum;
	}

	public static int printCounter() {
		return printingCounter;
	}
}

class ClientComplex {

	public static void main (String[] argv) {
		Complex a, b, c;

		a = new Complex(1, 1);
		b = new Complex(2.7, 3.14);
		

		System.out.print("a is: ");
		a.printComplex();
		System.out.print("\n");

		System.out.print("b is: ");
		b.printComplex();
		System.out.print("\n");

		System.out.println("Module of a is: " + a.computeModule());

		c = a.complexSum(b);
		System.out.print("c (the sum of a and b) is: ");
		c.printComplex();
		System.out.print("\n");

		System.out.println("In total we printed " + Complex.printCounter() + " complex numbers");



	}

}