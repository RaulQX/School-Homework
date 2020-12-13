interface Carriages_a {
    int getSize();
}

class PassengersCarA_a implements Carriages_a{
    private int passengerCapacity = 40;
    private int packageCapacity = 300;

    public int getSize() {
        return packageCapacity;
    }

    public String open () {
        return "Opening the doors";
    }

    public String close() {
        return "Closing the doors";
    }
}

class PassengersCarB_a implements Carriages_a{
    private int passengerCapacity = 50;
    private int packageCapacity = 400;

    public int getSize() {
        return packageCapacity;
    }

    public String open () {
        return "Opening the doors";
    }

    public String close() {
        return "Closing the doors";
    }

    public String blockW () {
        return "Blocking the windows";
    }
}

class LoadsCar_a implements Carriages_a{
    int packageCapacity = 400;
    public int getSize() {
        return packageCapacity;
    }
}

class Train_a{
    private Carriages_a[] carr;
    private int total_carr = 0;

    public Train_a (Carriages_a ... arr) {
        carr = new Carriages_a[15];
        //carr = arr;

        for (int i = 0; i < arr.length && i < 15; i++) {
            carr[i] = arr[i];
            total_carr++;
        }
    }

    private int getSize(Train_a x) {
        int currTrain = 0;

        for (int i = 0; i < x.total_carr; i++) {
            currTrain += x.carr[i].getSize();
        }
        return currTrain;
    }

    public boolean equals (Object newTrain) {
        int currTrain = 0;
        int secTrain = 0;

        if (newTrain instanceof Train_a) {
            secTrain = getSize((Train_a)(newTrain));
        }
        else return false;

        currTrain = getSize(this);

        return currTrain == secTrain;
    }

    public static void main(String[] args) {
        PassengersCarA_a unu = new PassengersCarA_a();
        PassengersCarB_a doi = new PassengersCarB_a();
        PassengersCarA_a trei = new PassengersCarA_a();
        PassengersCarB_a patru = new PassengersCarB_a();
        LoadsCar_a cinci = new LoadsCar_a();

        Train_a a = new Train_a (unu,doi,trei,patru,cinci);
        Train_a b = new Train_a (unu,doi,patru,trei,cinci);
        Train_a c = new Train_a (cinci);

        System.out.println(a.equals(b));
        System.out.println(a.equals(c));
    }
}
