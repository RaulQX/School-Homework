class Acronyms {

	private String [] words;
	private String [] acrs;
	private int totalWords = 0;

	public Acronyms () {
		words = new String[20];
		acrs = new String[20];
	}

	public boolean addWord (String newWord, String newAcronym) {
		for (int i = 0; i < totalWords; i++) {
			if (words[i].equals(newWord)) {
				acrs[i] = newAcronym;
				return true;
			}
		}

		if (totalWords == 20)
			return false;
		else {
			words[totalWords] = newWord;
			acrs[totalWords] = newAcronym;
			totalWords++;
			return true;
		}
	}

	public String exists(String acronym) {
		for (int i = 0; i < totalWords; i++) {
			if (acrs[i] == acronym)
				return words[i];
		}
		return "XXXX";
	}
}

class AcronymClient {

	public static void main (String[] argv) {
		
		Acronyms myWords = new Acronyms();

		System.out.println(myWords.addWord("Warlords", "WLDS"));
		System.out.println(myWords.exists("WLDS"));

		System.out.println(myWords.addWord("Of", "OF"));

		System.out.println(myWords.addWord("Sigrdrifa", "SGRDR"));
		System.out.println(myWords.exists("SGRDR"));
		
		System.out.println(myWords.addWord("Sigrdrifa", "SGD"));
		System.out.println(myWords.exists("SGRDR"));
		System.out.println(myWords.exists("SGD"));

		System.out.println(myWords.exists("OF"));
	}

}