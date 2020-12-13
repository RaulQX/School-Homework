import java.util.ArrayList;
import java.util.Iterator;

abstract class Type {

    abstract String getType();
    public abstract String toString();
}

class IntegerType extends Type {
    int myInt;

    public IntegerType(int n){
        myInt = n;
    }

    public String getType () {
        return "IntegerType";
    }

    @Override
    public String toString() {
        return "" + myInt;
    }
}

class StringType extends Type {
    String myString;

    public StringType(String str){
        myString = str;
    }

    public String getType () {
        return "StringType";
    }

    @Override
    public String toString() {
        return "" + myString;
    }
}

class CollectionType extends Type {
    private ArrayList <Type> coll;

    public CollectionType () {
        coll = new ArrayList<>(100);
    }

    public String getType () {
        StringBuilder content = new StringBuilder();

        content.append("CollectionType(");

        for (Type item: coll)
            content.append(item.getType()).append(", ");

        content.deleteCharAt(content.length()-1);
        content.deleteCharAt(content.length()-1);

        content.append(')');

        return String.valueOf(content);
    }

    public String toString () {
        StringBuilder collString = new StringBuilder();

        collString.append('(');

        Iterator<Type> iter = coll.iterator();

        while (iter.hasNext())
            collString.append(iter.next()).append(", "); // Bunch of errors

        //for (Type item:coll)
        //    collString.append(item.toString()).append(", ");

        collString.deleteCharAt(collString.length()-1);
        collString.deleteCharAt(collString.length()-1);

        collString.append(')');

        return String.valueOf(collString);
    }

    public Boolean addElement(Object toBeAdded) {
        if (toBeAdded instanceof Type) {
            coll.add((Type) toBeAdded);
            return true;
        }
        return false;
    }

    public boolean equals(Object compareWith) {
        if (compareWith instanceof CollectionType) {

            if (this.coll.size() != ((CollectionType) compareWith).coll.size())
                return false;
            else {
                Iterator <Type> thisIter = this.coll.iterator();
                Iterator <Type> otherIter = ((CollectionType) compareWith).coll.iterator();

                while (thisIter.hasNext())
                    if (!thisIter.next().equals(otherIter.next()))
                        return false;

            }

            return true;
        }
        return false;
    }
}

class HierClient {

    public static void main(String[] args) {
        IntegerType a = new IntegerType(7);
        IntegerType b = new IntegerType(4);
        IntegerType c = new IntegerType(12);
        StringType d = new StringType("Eu");
        IntegerType e = new IntegerType(2);
        IntegerType f = new IntegerType(8);

       /*
        StringType g = new StringType("sunt");
        StringType h = new StringType("Lica");
        StringType i = new StringType("Samadaul");
        StringType j = new StringType("voiesc");
        StringType k = new StringType("sa");
        StringType l = new StringType("stiu");
        StringType m = new StringType("ce");
        StringType n = new StringType("primim");
        StringType o = new StringType("la");
        StringType p = new StringType("test");

        CollectionType z = new CollectionType();
        CollectionType zz = new CollectionType();
        CollectionType zzz = new CollectionType();
        CollectionType zzzz = new CollectionType();
        z.addElement(d);
        z.addElement(g);
        zz.addElement(h);
        zz.addElement(i);
        zzz.addElement(d);
        zzz.addElement(j);
        zzz.addElement(k);
        zzz.addElement(l);
        zzz.addElement(m);
        zzz.addElement(n);
        zzzz.addElement(o);
        zzzz.addElement(p);
        zzz.addElement(zzzz);
        zz.addElement(zzz);
        z.addElement(zz);

        //System.out.println(z.getType());
        System.out.println(z);
*/

        CollectionType x = new CollectionType();
        CollectionType y = new CollectionType();
        CollectionType equalToX = new CollectionType();

        x.addElement(a);
        x.addElement(b);
        x.addElement(d);
        x.addElement(c);

        System.out.println("x:\n" + x.getType());
        System.out.println(x.toString());

        y.addElement(e);
        y.addElement(f);

        System.out.println("y:\n" + y.toString());

        x.addElement(y);

        System.out.println("x + y:\n" + x.getType());
        System.out.println(x.toString());

        equalToX.addElement(a);
        equalToX.addElement(b);
        equalToX.addElement(d);
        equalToX.addElement(c);
        equalToX.addElement(y);

        System.out.println(x.equals(y));
        System.out.println(x.equals(equalToX));

    }
}