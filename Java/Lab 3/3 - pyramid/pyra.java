class Pyramid {
	private int lines;

	public Pyramid (int n) {
		lines = n;

	}

	public void printPyramid() {
		for (int i = 0; i < this.lines; i++){
			for (int j = i; j < this.lines; j++) {
				System.out.print(lines - i + " ");
			}
			System.out.print("\n");
		}
	}

	public static void main (String [] argv) {
		Pyramid a,b;
		a = new Pyramid (4);
		b = new Pyramid (10);

		a.printPyramid();
		System.out.print("\n");
		b.printPyramid();

	}
}