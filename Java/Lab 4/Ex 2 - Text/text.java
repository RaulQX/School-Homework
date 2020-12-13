class Text {

	String [] words;
	int [] counters;
	int totalWords;

	public Text () {
		words = new String[20];
		counters = new int[20];
		totalWords = 0;
	}

	public boolean addWord (String newWord) {

		for (int i = 0; i < totalWords; i++) {
			if (words[i].equals(newWord)) {
				counters[i]++;
				return true;
			}
		}

		if (totalWords == 20)
			return false;
		else {
			words[totalWords] = newWord;
			totalWords++;
			return true;
		}


	}

	public String printWordsAndOccurences () {
		String concatenation = "";

		for (int i = 0; i < totalWords; i++) {
			concatenation += words[i];
			concatenation += " - ";
			concatenation += counters[i] + 1;
			concatenation += "\n";
		}

		return concatenation;
	}

}

class TextClient {

	public static void main (String[] argv) {

		Text myWords = new Text();

		System.out.println(myWords.addWord("Warlords"));
		System.out.println(myWords.addWord("Of"));
		System.out.println(myWords.addWord("Sigrdrifa"));
		System.out.println(myWords.addWord("Moriarty"));
		System.out.println(myWords.addWord("The"));
		System.out.println(myWords.addWord("Patriot"));
		System.out.println(myWords.addWord("Of"));
		System.out.println(myWords.addWord("Britain"));

		System.out.println(myWords.printWordsAndOccurences());


	}
}