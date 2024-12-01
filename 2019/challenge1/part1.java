import java.util.Scanner;

public class MyClass {
    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        int n;
        long answer = 0;
        while (scanner.hasNextInt()) {
            n = scanner.nextInt();
            answer += (n/3) - 2;
        }
        System.out.println("Answer: " + answer);
    }
}
