class Square {
	private int side;

	public Square () {
		side = 15;
	}

	public Square (int n) {
		side = n;
	}

	public String toString () {
		return "Square " + this.side + "; area " + side*side;
	}

	public static void main (String[] argv) {
		Square a,b,c;
		a = new Square();
		b = new Square(5);
		c = new Square(100);

		System.out.println(a);
		System.out.println(b);
		System.out.println(c);
	}


}