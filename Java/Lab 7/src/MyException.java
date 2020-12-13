class MyException extends Exception{
    private static int instantiatedTimes = 0;

    public MyException(String parameter) {
        super(parameter);
        instantiatedTimes++;
    }

    public static int getInstantiatedTimes () {
        return instantiatedTimes;
    }

    public static void main(String[] args) {

        MyException e = new MyException("John");
        System.out.println(MyException.getInstantiatedTimes());
        System.out.println(e.toString());

        e = new MyException("Johnutz");
        System.out.println(MyException.getInstantiatedTimes());
        System.out.println(e.getLocalizedMessage());

        e = new MyException("Jonel");
        System.out.println(MyException.getInstantiatedTimes());
        System.out.println(e.getMessage());

    }
}
