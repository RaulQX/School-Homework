class Book {
	private String author;
	private String title;

	public Book (String auth, String tit) {
		author = auth;
		title = tit;
	}

	public String getStringBook() {
		return author + " - " +  title;
	}

	/*public static void main (String [] argv) {
		Book a = new Book ("Raul", "eee");
		Book b = new Book ("Gena", "www");

		System.out.println(a.getStringBook());
	}*/

}

class Set {
	private int capacity;
	private int currentBooks = 0;
	private Book[] shelf;

	public Set (int n) {
		capacity = n;
		shelf = new Book[capacity];
	}

	public boolean addBook(Book newBook) {

		if (currentBooks == capacity)
			return false;

		/*for (Book i: shelf) {
			if (i.getStringBook() == newBook.getStringBook())
				return false;
		}*/

		for (int i = 0; i < currentBooks; i++) {
			if (shelf[i].getStringBook().equals(newBook.getStringBook()))
				return false;
		}

		shelf[currentBooks] = newBook;
		this.currentBooks++;

		return true;
	}

	public void printSet () {
		for (int i=0; i < this.currentBooks; i++)
			System.out.println(this.shelf[i].getStringBook() + "\n");
	}

 	
	public static Set makeUnion (Set firstSet, Set secondSet) {

		int switcher = 0;

		Set newSet = new Set (firstSet.capacity + secondSet.capacity);

		for (int i = 0; i < firstSet.currentBooks; i++) {

			switcher = 0;

			for (int j = 0; j < secondSet.currentBooks; j++) {
				if ( firstSet.shelf[i].getStringBook().equals ( secondSet.shelf[i].getStringBook()) )
					switcher = 1;
			}

			if (switcher == 0) {
				newSet.addBook(firstSet.shelf[i]);
			}

		}

		for (int i = 0; i < secondSet.currentBooks; i++)
			newSet.addBook(secondSet.shelf[i]);

		return newSet;
		
	}

	public static void main (String[] argv) {

		Set a = new Set (2);
		Set b = new Set (4);

		Book x = new Book ("Raul", "eee");
		Book y = new Book ("Gena", "www");

		Book xx = new Book ("zzz", "eee");
		Book yy = new Book ("xxx", "www");
		Book zz = new Book ("Gena", "www");

		a.addBook(x);
		a.addBook(y);

		b.addBook(xx);
		b.addBook(yy);
		b.addBook(zz);

		Set c = makeUnion(a,b);

		a.printSet();
		System.out.println("----------------------");
		b.printSet();
		System.out.println("----------------------");
		c.printSet();


	}

}