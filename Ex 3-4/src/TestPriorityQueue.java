import org.junit.*;

import java.util.Comparator;

import static org.junit.Assert.*;

public class TestPriorityQueue {

    //testCreateQueue create a queue and checks if it isn't null
    @Test
    public void testCreateQueue() {
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);

        Assert.assertNotNull(TEST);
    }

    //testZeroElem checks if a queue with zero element is empty
    @Test
    public void testZeroElem(){
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);

        Assert.assertEquals(0, TEST.size());

        Assert.assertTrue(TEST.empty());
    }

    //testInsertElem checks if the insert of one element is successful
    @Test
    public void testInsertElem() {
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);

        Integer S = 15;
        Assert.assertTrue(TEST.push(S));
    }

    //testInsert3elem checks if the insert of three elements is successful
    @Test
    public void testInsert3elem() {
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);

        Integer[] EXP = { 8, 15, 12 };
        TEST.push(EXP[1]);
        TEST.push(EXP[0]);
        TEST.push(EXP[2]);

        assertArrayEquals(EXP, TEST.QUEUE.toArray());
    }

    //testSizeZero checks if the size of an empty queue is zero
    @Test
    public void testSizeZero() {
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);

        Assert.assertEquals(0, TEST.size());
    }

    //testSizeOne checks if the size of a queue with one element is one
    @Test
    public void testSizeOne() {
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);

        Integer S = 15;
        TEST.push(S);

        Assert.assertEquals(1, TEST.size());
    }

    //testSizeThree checks if the size of a queue with three element is three
    @Test
    public void testSizeThree() {
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);

        Integer[] S = {15,11,33};
        TEST.push(S[0]);
        TEST.push(S[1]);
        TEST.push(S[2]);

        Assert.assertEquals(3, TEST.size());
    }

    //testRemoveZeroElem checks if the remove with zero element return false
    @Test
    public void testRemoveZeroElem(){
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);

        Assert.assertTrue(TEST.empty());

        Assert.assertFalse(TEST.remove(10));
    }

    //testRemoveElem checks if the remove of one element is successful
    @Test
    public void testRemoveElem() {
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);

        Integer S = 15;
        TEST.push(S);
        Assert.assertTrue(TEST.remove(S));

        assertEquals(0, TEST.size());
    }

    //testRemoveThreeElem checks if the remove of three elements is successful
    @Test
    public void testRemoveThreeElem() {
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);

        Integer[] S = {1, 15, 26, 33, 30, 28};
        Integer[] EXP = {26, 28, 30};

        TEST.push(S[0]);
        TEST.push(S[1]);
        TEST.push(S[2]);
        TEST.push(S[3]);
        TEST.push(S[4]);
        TEST.push(S[5]);

        TEST.remove(S[3]);
        TEST.remove(S[1]);
        TEST.remove(S[0]);

        Assert.assertArrayEquals(EXP, TEST.QUEUE.toArray());
    }

    //testContainsElem checks if a element is in the queue
    @Test
    public void testContainsElem(){
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);

        Integer[] EXP = {10, 5, 20, 0};

        TEST.push(EXP[0]);
        TEST.push(EXP[1]);
        TEST.push(EXP[2]);
        TEST.push(EXP[3]);

        Assert.assertTrue(TEST.contains(EXP[0]));
    }

    //testNotContainsElem checks if a element isn't in the queue
    @Test
    public void testNotContainsElem(){
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);

        Integer[] EXP = {10, 5, 20, 0};

        TEST.push(EXP[0]);
        TEST.push(EXP[1]);
        TEST.push(EXP[2]);
        TEST.push(EXP[3]);

        Assert.assertFalse(TEST.contains(30));
    }

    //testPopZeroElem checks if the pop method works with an empty queue without errors
    @Test
    public void testPopZeroElem(){
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);

        TEST.pop();

        Assert.assertTrue(TEST.empty());
    }

    //testPopElem checks if the first element of the queue pops out
    @Test
    public void testPopElem(){
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);
        Integer[] S = {10, 5, 20, 0};

        TEST.push(S[0]);
        TEST.push(S[1]);
        TEST.push(S[2]);
        TEST.push(S[3]);

        TEST.pop();

        Assert.assertFalse(TEST.contains(S[3]));
    }

    //testPopThreeElem checks if the three elements of the queue pops out
    @Test
    public void testPopThreeElem() {
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);

        Integer[] S = {1, 15, 26, 33, 30, 28};
        Integer[] EXP = {28, 33, 30};

        TEST.push(S[0]);
        TEST.push(S[1]);
        TEST.push(S[2]);
        TEST.push(S[3]);
        TEST.push(S[4]);
        TEST.push(S[5]);

        TEST.pop();
        TEST.pop();
        TEST.pop();

        Assert.assertArrayEquals(EXP, TEST.QUEUE.toArray());
    }

    //testTopZeroElem checks if the top method works with an empty queue without errors
    @Test
    public void testTopZeroElem(){
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);

        Assert.assertNull(TEST.top());
    }

    //testTopElem checks if top method return the correct first element in the queue
    @Test
    public void testTopElem(){
        Comparator<Integer> COMPARATOR = Comparator.naturalOrder();
        PriorityQueue TEST= new PriorityQueue<>(COMPARATOR);

        TEST.push(15);
        TEST.push(10);
        TEST.push(20);
        TEST.push(5);

        Assert.assertEquals(5, TEST.top());
    }

}