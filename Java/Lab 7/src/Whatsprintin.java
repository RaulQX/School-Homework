class L1 extends Exception {
    public String toString() { return "L1"; }}
class L2 extends Exception {
    public String toString() { return "L2"; }}

class Test {
    public static void main(String[] args) {
        for (int i=0; i<4; i++) {
            try {
                if(i==0) throw new L1();
                else throw new L2();
            }
            catch (Exception e) {
                System.out.println(e);
            }
        }
    }
}

class Exam {
    public static void main(String[] argv) {
        try {
            for(int i = 0; i < 100; i++) {
                throw new Exception("FOR " + i);
            }
        }
        catch(Exception e) {
            System.out.println(e.getMessage());
        }
    }
}