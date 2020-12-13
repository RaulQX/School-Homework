class Ex1 {
	public int x;

	private Ex1(int n){
		x = n;
	}

	public static void main (String[] argv){
		Ex1 inauntrulClasei = new Ex1 (50);

		System.out.println("Daca main se afla inauntrul clasei cu construcor de tip PRIVATE: " + inauntrulClasei.x);

	}

}

class Main {

	public static void main (String[] argv){
		/*
		Ex1 inAfaraClasei = new Ex1(51);
		System.out.println("Daca main se afla in afara clasei: " + inAfaraClasei.x);*/

	}
}