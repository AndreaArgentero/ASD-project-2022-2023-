// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.

import java.util.Comparator;

public class Main<E extends Comparator<E>> {
    public static void main(String[] args) {

        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue QUEUE= new PriorityQueue<>(COMPARATOR);

        System.out.println(QUEUE.push(10));
        System.out.println(QUEUE.push(5));
        System.out.println(QUEUE.push(20));
        System.out.println(QUEUE.push(0));

        System.out.println(QUEUE.MAP + "\n" + QUEUE.QUEUE);
    }
}