import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Comparator;
import java.util.HashMap;


public class Prim {
    //
    public static <V, L extends Number> Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(Graph<V, L> GRAPH)
    {
        ArrayList<V> LIST = (ArrayList<V>)GRAPH.getNodes();
        V START = LIST.get(0);
        ArrayList<V> VISITED = new ArrayList<>();
        return generator(START, GRAPH, VISITED);
    }

    //
    public static <V, L extends Number> Collection<? extends Arc<V, L>> generator(V START, Graph<V, L> GRAPH, ArrayList<V> VISITED) {
        PriorityQueue<Arc<V, L>> PRIORITYQUEUE = new PriorityQueue<>(new LabelComparator<>());
        ArrayList<Arc<V, L>> MINSPATREE = new ArrayList<>();
        HashMap<V, Arc<V,L>> DISTANCENODES = new HashMap<>();

        VISITED.add(START);
        ArrayList<V> ADJ = (ArrayList<V>) GRAPH.getNeighbours(START);
        L WEIGHT;

        for (V NEIGHBOR : ADJ) {
            if (!VISITED.contains(NEIGHBOR)) {
                WEIGHT = GRAPH.getLabel(START, NEIGHBOR);
                Arc<V,L> DISTANCEARC = new Arc<>(START, NEIGHBOR, WEIGHT, GRAPH.isDirected(), GRAPH.isLabeled());
                PRIORITYQUEUE.push(DISTANCEARC);
                DISTANCENODES.put(NEIGHBOR, DISTANCEARC);
            }
        }

        while (!PRIORITYQUEUE.empty()) {
            ADJ = (ArrayList<V>) GRAPH.getNeighbours(START);

            for (V NEIGHBOR : ADJ) {
                if(!VISITED.contains(NEIGHBOR)) {
                    WEIGHT = GRAPH.getLabel(START, NEIGHBOR);
                    Arc<V,L> COMPARC = new Arc<>(START, NEIGHBOR, WEIGHT, GRAPH.isDirected(), GRAPH.isLabeled());
                    if (DISTANCENODES.containsKey(NEIGHBOR)) {
                        Arc<V,L> CONTEINEDARC = DISTANCENODES.get(NEIGHBOR);
                        PRIORITYQUEUE.incPriority(CONTEINEDARC, COMPARC);
                        if(!PRIORITYQUEUE.contains(CONTEINEDARC)){
                            DISTANCENODES.replace(NEIGHBOR, COMPARC);
                        }
                    } else {
                        PRIORITYQUEUE.push(COMPARC);
                        DISTANCENODES.put(COMPARC.getEnd(), COMPARC);
                    }
                }
            }

            MINSPATREE.add(PRIORITYQUEUE.top());
            START = PRIORITYQUEUE.top().getEnd();
            DISTANCENODES.remove(PRIORITYQUEUE.top().getEnd());
            PRIORITYQUEUE.remove(PRIORITYQUEUE.top());
            VISITED.add(START);
        }

        if (VISITED.size() < GRAPH.numNodes())
        {
            int COUNT=0;
            ArrayList<V> NODE = new ArrayList<>(GRAPH.getNodes());

            while (COUNT<VISITED.size()) {
                NODE.remove(VISITED.get(COUNT));
                COUNT++;
            }

            START = NODE.get(0);
            MINSPATREE.addAll(generator(START, GRAPH, VISITED));
        }
        return MINSPATREE;
    }

    //LabelComparator is the method that compare two arc labels
    public static class LabelComparator<V, L> implements Comparator<Arc<V, L>> {
        @Override
        public int compare(Arc<V, L> OBJ1, Arc<V, L> OBJ2) {
            return Double.compare((double) OBJ1.getLabel(), (double) OBJ2.getLabel());
        }
    }

    //loadGraph is the method that load the graph from the file .csv
    public static Graph<String, Double> loadGraph(String filePath) throws IOException, Exception {

        Graph<String, Double> GRAPH = new Graph<>(false, true);
        Path MYPATH = Paths.get(filePath);

        BufferedReader FILEIN = Files.newBufferedReader(MYPATH);
        String DATA = null;

        System.out.println("\nLoading data...\n");

        while((DATA = FILEIN.readLine()) != null) {
            String[] TOKEN = DATA.split(",");
            GRAPH.addNode(TOKEN[0]);
            GRAPH.addNode(TOKEN[1]);
            GRAPH.addEdge(TOKEN[0], TOKEN[1], Double.parseDouble(TOKEN[2]));
        }

        System.out.println("\nData loaded.\n");
        return GRAPH;
    }

    public static void main(String[] args) throws Exception {
        Graph<String, Double> GRAPH = loadGraph(args[0]);

        ArrayList<Arc<String, Double>> MINSPATREE = (ArrayList<Arc<String, Double>>) minimumSpanningForest(GRAPH);

        double TOT = 0;
        for(Arc<String, Double> WEIGHT : MINSPATREE){
            TOT += WEIGHT.getLabel();
        }

        System.err.println("Number of nodes: " + GRAPH.numNodes());
        System.err.println("Number of edge in minimum spanning forest: " + MINSPATREE.size());
        System.err.printf("Weight: %.3f Km%n", TOT/1000);

        FileWriter OUTPUT = new FileWriter("Standard_Output.txt");

        for(Arc<String, Double> tmp : MINSPATREE){
            OUTPUT.write(tmp.getStart() + " - " + tmp.getEnd() + ": " + tmp.getLabel() + "\n");
        }

        OUTPUT.close();

    }
}
