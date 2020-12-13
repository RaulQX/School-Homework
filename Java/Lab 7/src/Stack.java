import java.util.ArrayList;

class PushEx extends Exception {
    public String toString() { return "Too many elements in the stack"; }
}

class PopEx extends Exception {
    public String toString() { return "Not enough elements in the stack"; }
}

class MyStack {
    private int MAX_ELEMENTS;
    private int totalElems;

    ArrayList<Object> a;

    public MyStack(int n){
        MAX_ELEMENTS = n;
        if (MAX_ELEMENTS >= 500) {
            throw new RuntimeException("Too many elements for the stack");
        }

        a  = new ArrayList<>(MAX_ELEMENTS);
        totalElems = 0;
    }

    public void push (Object newObj) {

        try {
            if (totalElems >= MAX_ELEMENTS) {
                throw new PushEx();
            }
            else
            {
                a.add(newObj);
                totalElems++;
            }


        } catch (PushEx e) {
            System.out.println(e);
        }
    }

    public Object pop () throws PopEx {
        if (totalElems == 0)
            throw new PopEx();

        totalElems--;
        return a.get(totalElems);


    }

    public static void main(String[] args) //throws Exception {
    {
        MyStack b = new MyStack(2);


        String x = new String("E");
        String y = new String("Ee");
        String z = new String("Eee");

        try {
            b.push(x);
            b.push(y);
            b.push(z);
        }catch (Exception e) {
            System.out.println(e);
        }

        try {
            System.out.println(b.pop());
            System.out.println(b.pop());
            System.out.println(b.pop());
        }catch (Exception e) {
            System.out.println(e);
        }

        MyStack a = new MyStack(501);

    }
}