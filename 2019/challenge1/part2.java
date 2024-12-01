import java.util.Scanner;

public class MyClass {
    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        long answer = 0;
        while (scanner.hasNextInt()) {
            answer += recursiveFuel(scanner.nextInt());
        }
        System.out.println("Answer: " + answer);
    }

    public static int recursiveFuel(int ship) {
        int answer = fuelStep(ship);
        int currentIteration = answer;
        int nextIteration = 0;
        while ( (nextIteration = fuelStep(currentIteration)) > 0) {
            answer += nextIteration;
            currentIteration = nextIteration;
        }
        return answer;
    }

    public static int fuelStep(int mass) {
        int answer = (mass/3) - 2;
        return (answer > 0) ? answer : 0;
    }
}
