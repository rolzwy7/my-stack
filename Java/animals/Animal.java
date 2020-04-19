package animals;

// "The public type <<classname>> must be defined in its own file"
// https://stackoverflow.com/questions/19814713/the-public-type-classname-must-be-defined-in-its-own-file-error-in-eclipse
// "we can't have two public classes in one .java file."
// "why though ?"
// "Coming from C#, this limitation is very irritating"
public class Animal {
    //protected
    //private
    //public

    public static final double NUM = 3.1516;
    // [Final] Classes CAN'T Be Subclassed
    // [Final] Methods CAN'T Be Overriden

    // Java static == Python @staticmethod

    private String name; // string is capitalized XD
    //private int weight;
    //private boolean hasOwner; // Jesus Christ why not bool ...
    //private byte age; // 0-255
    //private long uniqueID; // -2^64 to 2^64
    //private char favChar;
    //private double speed;
    //private float height;

    // System.in -> keyboard stream ??
    // when this deconstructs ?

    // Constructor
    // is/are there a default/s constructor/s ?
    public Animal(String name) {
        super(); // same as python
        this.name = name;
        System.out.println("Constructing " + this.name);
    }

    public String makeSound() {
        return "Woof";
    }   

}