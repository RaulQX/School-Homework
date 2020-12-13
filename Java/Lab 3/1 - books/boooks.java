class Book {
	private int pageNum;

	public Book (int n) {
		pageNum = n;
	}

	public boolean equals(Object secondBook) {
		if (secondBook instanceof book) {
			if (this.pageNum == ((Book)secondBook).pageNum)
				return true;
			else
				return false;
		}
		
	}

	public String compareBooks(Book secondBook) {
		if (this.pageNum == secondBook.pageNum)
			return "The books are equal";
		else if (this.pageNum > secondBook.pageNum)
			return "The first book is bigger";
		else return "The second book is bigger";
	}

	public static void main (String[] argv) {
		Book thisIsNotATest, aSongOfIceAndFire;

		thisIsNotATest = new Book (420);
		aSongOfIceAndFire = new Book (992);


		System.out.println("Are they equal?: " + thisIsNotATest.isEqual(aSongOfIceAndFire));

		System.out.println(thisIsNotATest.compareBooks(aSongOfIceAndFire));
	}
}