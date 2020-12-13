class Sum {

	public static int sum (int a, int b) {
		return a + b;
	}

	public static int sum (int a, int b, int c) {
		return sum (a,b) + c;
	}

	public static int sum (int a, int b, int c, int d) {
		return sum (a,b,c) + d;
	}

	public static void main (String[] argv) {
		int a = 10, b = 5, c = 2, d = 2;

		System.out.println(a + " + " + b + " = " + sum(a,b));
		System.out.println(a + " + " + b + " + " + c + " = " + sum(a,b,c));
		System.out.println(a + " + " + b + " + " + c + " + " + d + " = " + sum(a,b,c,d));
	}

}