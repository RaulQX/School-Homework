abstract class Planes {

    private int planeID;
    private int enginePower;
    private static int currID = 1;

    public Planes (int power) {
        this.enginePower = power;
        this.planeID = currID;
        currID++;
    }

    public String getPlaneID () {
        String pID ="";
        return pID + planeID;
    }

    public int getTotalEnginePower () {
        return enginePower;
    }

    public void takeOff() {
        System.out.println("takeOff - " + this.getPlaneID());
    }

    public void land () {
        System.out.println("land - " + this.getPlaneID());
    }

    public void fly () {
        System.out.println("fly - " + this.getPlaneID());
    }

}

abstract class PassengerPlane extends Planes {
    private int maxPassengers;

    public PassengerPlane (int enginePower, int maxPassengers) {
        super(enginePower);
        this.maxPassengers = maxPassengers;
    }

    public int getMaxPassengers() {
        return maxPassengers;
    }

}

abstract class FighterPlane extends Planes {

    public FighterPlane (int enginePower) {
        super(enginePower);
    }

    public void launchMissilesToTheUnfaithful() {
        System.out.println("Launching rocket - " + this.getPlaneID());
    }
}

class MIG extends FighterPlane {

    public MIG (int enginePower) {
        super(enginePower);
    }

    public void highSpeedGeometry() {
        System.out.println("High speed selected geometry - " + this.getPlaneID());
    }

    public void normalSpeedGeometry() {
        System.out.println("Normal selected geometry - " + this.getPlaneID());
    }
}

class TomCat extends FighterPlane {

    public TomCat (int enginePower) {
        super(enginePower);
    }

    public void refuel() {
        System.out.println("TomCat - Refuelling - " + this.getPlaneID());
    }
}

class Concorde extends PassengerPlane {

    public Concorde (int enginePower, int maxPassengers) {
        super(enginePower, maxPassengers);
    }

    public void goSuperSonic() {
        System.out.println("Go supersonic - " + this.getPlaneID());
    }

    public void goSubSonic() {
        System.out.println("Go subsonic - " + this.getPlaneID());
    }
}

class Boeing extends PassengerPlane {

    public Boeing (int enginePower, int maxPassengers) {
        super(enginePower, maxPassengers);
    }
}

class PlaneClient {

    public static void main(String[] args) {

        System.out.println("Passengers: ");

        Boeing unu = new Boeing(10, 10);
        Boeing doi = new Boeing(101, 12);

        System.out.println("1: " + unu.getPlaneID() + " " + unu.getTotalEnginePower() + " " + unu.getMaxPassengers());
        System.out.println("2: " + doi.getPlaneID() + " " + doi.getTotalEnginePower() + " " + doi.getMaxPassengers());

        Concorde trei = new Concorde(42, 960);
        Concorde patru = new Concorde(42, 22);

        System.out.println("3: " + trei.getPlaneID() + " " + trei.getTotalEnginePower() + " " + trei.getMaxPassengers());
        System.out.println("4: " + patru.getPlaneID() + " " + patru.getTotalEnginePower() + " " + patru.getMaxPassengers());

        trei.goSuperSonic();
        patru.goSubSonic();

        trei.takeOff();
        patru.land();

        trei.fly();
        patru.fly();

        System.out.println("-------------------------------------------\nFighters:");

        MIG alfa = new MIG(0);
        MIG beta = new MIG (1);

        alfa.highSpeedGeometry();
        beta.normalSpeedGeometry();

        TomCat gamma = new TomCat(2);
        TomCat nextGreekLetter = new TomCat(9);

        gamma.refuel();
        nextGreekLetter.refuel();
    }
}