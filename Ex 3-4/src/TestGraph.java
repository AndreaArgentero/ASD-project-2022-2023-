import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.ArrayList;

import org.junit.*;

public class TestGraph {

    @Test
    public void addNode() {
        Graph<Integer, Integer> TEST = new Graph<Integer, Integer>(false, true);
        assertTrue(TEST.addNode(0));
    }

    @Test
    public void addArc() {
        Graph<Integer, Integer> TEST = new Graph<Integer, Integer>(false, true);
        TEST.addNode(0);
        TEST.addNode(1);
        assertTrue(TEST.addEdge(1, 0, 10));
    }

    @Test
    public void graphIsDirect() {
        Graph<Integer, Integer> TESTTRUE = new Graph<Integer, Integer>(true, true);
        assertTrue(TESTTRUE.isDirected());
    }

    @Test
    public void graphIsNotDirect() {
        Graph<Integer, Integer> TESTFALSE = new Graph<Integer, Integer>(false, false);
        assertFalse(TESTFALSE.isDirected());
    }

    @Test
    public void graphIsLabeled() {
        Graph<Integer, Integer> TESTTRUE = new Graph<Integer, Integer>(true, true);
        assertTrue(TESTTRUE.isLabeled());
    }

    @Test
    public void graphIsNotLabeled() {
        Graph<Integer, Integer> TESTFALSE = new Graph<Integer, Integer>(false, false);
        assertFalse(TESTFALSE.isLabeled());
    }

    @Test
    public void deleteNode() {
        Graph<Integer, Integer> TEST = new Graph<Integer, Integer>(false, true);
        TEST.addNode(0);
        TEST.removeNode(0);
        assertFalse(TEST.containsNode(0));
    }

    @Test
    public void deleteArc() {
        Graph<Integer, Integer> TEST = new Graph<Integer, Integer>(false, true);
        TEST.addNode(0);
        TEST.addNode(1);
        TEST.addEdge(1, 0, 10);
        TEST.removeEdge(1, 0);
        assertFalse(TEST.containsEdge(1, 0));
    }

    @Test
    public void numberOfNodes() {
        Graph<Integer, Integer> TEST = new Graph<Integer, Integer>(false, true);
        TEST.addNode(0);
        TEST.addNode(1);
        assertEquals(2, TEST.numNodes());
    }

    @Test
    public void numberOfArcs() {
        Graph<Integer, Integer> TEST = new Graph<Integer, Integer>(false, true);
        TEST.addNode(0);
        TEST.addNode(1);
        TEST.addNode(2);
        TEST.addEdge(1, 0, 10);
        TEST.addEdge(2, 0, 20);
        assertEquals(2, TEST.numEdges());
    }

    @Test
    public void graphGetAllNodes() {
        Graph<Integer, Integer> TEST = new Graph<Integer, Integer>(false, true);
        final Integer[] ARRAY = { 2, 1, 0 };
        TEST.addNode(0);
        TEST.addNode(1);
        TEST.addNode(2);
        TEST.addEdge(1, 0, 10);
        TEST.addEdge(2, 0, 20);

        assertArrayEquals(ARRAY, TEST.getNodes().toArray());
    }

    @Test
    public void graphGetAllArcs() {
        Graph<Integer, Integer> TEST = new Graph<Integer, Integer>(false, true);
        TEST.addNode(0);
        TEST.addNode(1);
        TEST.addNode(2);
        TEST.addEdge(1, 0, 10);
        TEST.addEdge(2, 0, 20);

        assertTrue(TEST.getEdges().contains(new Arc<Integer, Integer>(1, 0, 10, false, true)));
        assertTrue(TEST.getEdges().contains(new Arc<Integer, Integer>(2, 0, 20, false, true)));
    }

    @Test
    public void graphGetAdjacentNodes() {
        Graph<Integer, Integer> TEST = new Graph<Integer, Integer>(false, true);
        TEST.addNode(0);
        TEST.addNode(1);
        TEST.addNode(2);
        TEST.addEdge(1, 0, 10);
        TEST.addEdge(2, 0, 20);

        assertTrue(TEST.getNeighbours(1).contains(0));
    }

    @Test
    public void graphGetNotAdjacentNodes() {
        Graph<Integer, Integer> TEST = new Graph<Integer, Integer>(false, true);
        TEST.addNode(0);
        TEST.addNode(1);
        TEST.addNode(2);
        TEST.addEdge(1, 0, 10);
        TEST.addEdge(2, 0, 20);
        ArrayList<Node<Integer, Integer>> TESTADJ = new ArrayList<>();
        TESTADJ.add(new Node<Integer, Integer>(2, 20));
        assertFalse(TEST.getNeighbours(1).contains(TESTADJ.get(0)));
    }

}