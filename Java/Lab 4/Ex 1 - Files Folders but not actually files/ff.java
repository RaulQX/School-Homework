class File {

	private String name;
	private String information;

	public File (String givenName, String givenInformation){
		name = givenName;
		information = givenInformation;
	}

	public String getContent () {
		return this.information;
	}

	public boolean equals (Object secondFile) {

		if (secondFile instanceof File) {
			if ( this.name.compareTo ( ((File)secondFile).name) == 0 ) {
				if (this.information.compareTo( ((File)secondFile).information) == 0)
					return true;
			}
		}
		return false;
	}

	public String toString() {
		String nameAndInfo = "";
		nameAndInfo = nameAndInfo + name + ": " + information + "\n";

		return nameAndInfo;
	}

	public static void main (String[] argv) {

		File a = new File("Nelson Mondialul", "Cantecul invingatorilor");
		File b = new File("Giuvaier Politistul", "Primarul rodiilor va rasari din nou");
		File c = new File("Robu", "Inainte sa moara, m-a sunat Iohannis si mi-a spus, Robulee, fii tu presedinte in onoarea mea");
		File x = new File("Nelson Mondialul", "Cantecul invingatorilor");
		
		System.out.println(c.getContent());
		System.out.println(a.equals(b));
		System.out.println(a.equals(x));

	}
}

class Folder {

	private File[] entries;
	private int totalElements = 0;

	public Folder () {
		entries = new File[totalElements];
	}

	public boolean addFile (File addingFile) {

		for (int i = 0; i < totalElements; i++) {
			//System.out.println(i);
			if (entries[i].equals(addingFile) == true){
				return false;
			}
		}

		File [] newArray = new File[totalElements+1];
		if (totalElements != 0)
			System.arraycopy(entries, 0, newArray, 0, totalElements);
		newArray[totalElements] = addingFile;
		totalElements++;
		entries = newArray;

		return true;
	}

	public String getContent () {
		String concatenation = "";

		for (int i = 0; i < totalElements; i++){
			concatenation += entries[i].toString();
		}

		return concatenation;
	}


	public static void main (String [] argv) {
		
		Folder foldu = new Folder();
		Folder celalaltFoldu = new Folder();

		File a = new File("Nelson.txt", "Cantecul");
		File b = new File("Giuvaier Politistul", "Primarul rodiilor va rasari din nou");
		File c = new File("Robuut", "Fii tu presedinte in onoarea mea");
		File x = new File("Nelson.txt", "Cantecul");
		File z = new File("Capitanul", "Eu sunt capitanul");

		System.out.println(foldu.addFile(a));
		System.out.println(foldu.addFile(b));
		System.out.println(foldu.addFile(c));
		System.out.println(foldu.addFile(x));

		System.out.println(foldu.getContent());

		System.out.println(celalaltFoldu.addFile(c));
		System.out.println(celalaltFoldu.addFile(c));
		System.out.println(celalaltFoldu.addFile(c));
		System.out.println(celalaltFoldu.addFile(z));
		System.out.println(celalaltFoldu.getContent());
	}

}