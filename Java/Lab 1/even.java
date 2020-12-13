class even {
	public static void main(String[] args) {
		
		int oddSum = 0;

		for (int i = 1; i <= 100; i++)
			if (i % 2 == 0)
				System.out.print(i + " ");
			else oddSum += i;

		System.out.print("\n");

		System.out.println("Sum: " + oddSum);

		printf("Sum: %d", oddSum);

	}
}