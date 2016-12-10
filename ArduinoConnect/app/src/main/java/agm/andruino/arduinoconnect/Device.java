package agm.andruino.arduinoconnect;

public class Device {

    private String Name;
    private String Adress;

    public Device (String name, String adress) {

        this.Name = name;
        this.Adress = adress;
    }

    public String getName() {

        return Name;
    }

    public String getAdress() {

        return Adress;
    }

}
