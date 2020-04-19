import java.util.Scanner;
import animals.Animal;

public class Main {
    public static void main(String[] args) {
        System.out.print("Enter animal name: ");
        Scanner userInput = new Scanner(System.in);

        if(userInput.hasNextLine()) {
            Animal theAnimal = new Animal(userInput.nextLine());
            System.out.println(theAnimal.makeSound());
        }

        userInput.close();
    
        // Obczaj (Introduction to the Standard Directory Layout)
        // http://maven.apache.org/guides/introduction/introduction-to-the-standard-directory-layout.html

        // 10 Things Java Programmer should learn in 2020
        // https://hackernoon.com/10-things-java-developer-should-learn-in-2020-px9j309i
    }
}