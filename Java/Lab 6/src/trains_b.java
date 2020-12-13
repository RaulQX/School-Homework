interface Carriages {

}

class PassengersCarA implements Carriages{
    //private int passengerCapacity = 40;
    //private int packageCapacity = 300;

    public String open () {
        return "Opening the doors";
    }

    public String close() {
        return "Closing the doors";
    }

}

class PassengersCarB implements Carriages{
    //private int passengerCapacity = 50;
    //private int packageCapacity = 400;

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

class LoadsCar implements Carriages{
    //int packageCapacity = 400;
}

class Train{
    private Carriages[] carr;

    public Train (Carriages ... arr) {
        carr = new Carriages[15];
        //carr = arr;

        for (int i = 0; i < arr.length && i < 15; i++) {
            carr[i] = arr[i];
        }
    }

    private int getSize(Train x) {
        int currTrain = 0;

        for (Carriages i: x.carr) {
            if (i instanceof LoadsCar || i instanceof PassengersCarB) {
                currTrain += 400;
            }
            else if (i instanceof PassengersCarA) {
                currTrain += 300;
            }
        }
        return currTrain;
    }

    public boolean equals (Object newTrain) {
        int currTrain = 0;
        int secTrain = 0;

        if (newTrain instanceof Train) {
            secTrain = getSize((Train)(newTrain));
        }
        else return false;

        currTrain = getSize(this);

        return currTrain == secTrain;
    }

    public static void main(String[] args) {
        PassengersCarA unu = new PassengersCarA();
        PassengersCarB doi = new PassengersCarB();
        PassengersCarA trei = new PassengersCarA();
        PassengersCarB patru = new PassengersCarB();
        LoadsCar cinci = new LoadsCar();

        Train a = new Train (unu,doi,trei,patru,cinci);
        Train b = new Train (unu,doi,patru,trei,cinci);
        Train c = new Train (cinci);

        System.out.println(a.equals(b));
        System.out.println(a.equals(c));
    }
}
