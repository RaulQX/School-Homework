interface Item {
    String getContent();
}

class File implements Item {
    private String information;

    public File (String info) {
        information = info;
    }

    @Override
    public String getContent() {
        return this.information;
    }
}

class Folder implements Item {
    private Item[] entries;
    private int currentElements = 0;

    public Folder (){
        entries = new Item[currentElements];
    }

    private Item[] enlargeArray () {

        Item [] newArray = new Item[currentElements+1];

        if (currentElements != 0)
            System.arraycopy(entries, 0, newArray, 0, currentElements);

        return newArray;
    }

    public boolean addFile (Item addingItem) {

        entries = enlargeArray();
        entries[currentElements] = addingItem;
        currentElements++;

        return true;
    }

    @Override
    public String getContent() {
        StringBuilder concatenation = new StringBuilder();
        for (int i = 0; i < currentElements; i++)
            concatenation.append(entries[i].getContent());

        return concatenation.toString();
    }

    public static void main(String[] args) {
        File newLine = new File("\n");

        Folder a = new Folder ();

        File x = new File("This ");
        File y = new File("Is ");
        File z = new File("F1");

        Folder b = new Folder();
        File i = new File ("This ");
        File o = new File("F2");

        Folder c = new Folder ();
        File q = new File("This ");
        File e = new File("F3");

        a.addFile(x);
        a.addFile(y);
        a.addFile(z);
        a.addFile(newLine);

        b.addFile(i);
        b.addFile(o);
        b.addFile(newLine);

        c.addFile(q);
        c.addFile(e);
        c.addFile(newLine);

        c.addFile(b);

        a.addFile(b);
        a.addFile(b);
        a.addFile(c);

        System.out.println(a.getContent());
    }
}