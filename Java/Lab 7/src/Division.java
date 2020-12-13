class Operation {

    public static void performDivision(int number, int divisor) throws ArithmeticException {
        if (divisor == 0) throw new ArithmeticException("You can't divide by 0");
        else System.out.println((float)number/divisor);

    }

    public static void main(String[] args) {

        try {
            Operation.performDivision(3,2);
            Operation.performDivision(2,0);
        }catch (ArithmeticException e) {
            System.out.println(e);
        }

    }
} 