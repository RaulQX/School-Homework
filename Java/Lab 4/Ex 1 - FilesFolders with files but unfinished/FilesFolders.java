import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

class Filez {

	private String name;
	private String information = "";
	
	public Filez () {

		Scanner console = new Scanner(System.in);
		System.out.print("Insert the name of the file: ");
		name = console.nextLine();

		try {

			File readingFile = new File (name);
			Scanner reader = new Scanner (readingFile);

			while (reader.hasNextLine()) {
				information += reader.nextLine();
			}

			//System.out.println(name + "\n" + information);
			reader.close();

		} catch (FileNotFoundException e) {
			System.out.println("Ayaye");
			//e.printStackTrace();
		}
	}

	public boolean equals(Object comparingFile) {
		if (comparingFile instanceof Filez) {
			if ( (this.name.compareTo( (((Filez)comparingFile).name) ) == 0) && ( this.information.compareTo( ((Filez)comparingFile).information) == 0) ){
				return true;
			}
		}

		return false;
	}

	public String getFormattedContent () {

		return  "\nFilename is: " + name + "\n\nContent is:\n" + information + "\n";
	} 

	public String getContent () {

		return  name + "\n" + information;
	} 

	public static void main (String [] argv) {

		Filez a = new Filez ();
		Filez b = new Filez();


		System.out.println(a.equals(b));

	}
}

class Folder {
	
	private Filez [] entries;
	private counter = 0;

	public Folder () {
		entries = new Filez[1];
	}

	public boolean addFile () {
		Filez temp = new Filez();

		for (int i = 0; i < 10; i++)
			if ()
	}


}