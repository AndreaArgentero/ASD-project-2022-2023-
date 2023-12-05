import java.util.*;

public class Graph<V, L> implements AbstractGraph<V, L> {

    private Hashtable<V, ArrayList<Node<V,L>>> NODES = null;
    private HashSet<Arc<V,L>> EDGE = null;
    boolean ISDIRECT, ISLABEL;

    //The Graph method is the constructor, sets the weight of the arc and whether direct or indirect
    public Graph(boolean DIRECTED, boolean LABELED){
        this.NODES=new Hashtable<V, ArrayList<Node<V,L>>>();
        this.EDGE= new HashSet<Arc<V, L>>();
        ISDIRECT = DIRECTED;
        ISLABEL = LABELED;
    }

    //isDirect returns true if the graph is direct or false if indirect
    @Override
    public boolean isDirected() {
        return ISDIRECT;
    }

    //isLabeled returns true if the graph is tagged
    @Override
    public boolean isLabeled() {
        return ISLABEL;
    }

    //addNode add a node to the graph
    @Override
    public boolean addNode(V TAG) {
        if (TAG != null){
            if(!NODES.containsKey(TAG)){
                NODES.put(TAG, new ArrayList<Node<V,L>>());
                return true;
            }
        }
        return false;
    }

    //addEdge create an arc between two nodes
    @Override
    public boolean addEdge(V NODE_S, V NODE_D, L LABEL) {
                if(isLabeled()) {
                    NODES.get(NODE_S).add(new Node<V,L>(NODE_D, LABEL));
                    if (!isDirected()) {
                            NODES.get(NODE_D).add(new Node<V,L>(NODE_S, LABEL));
                            EDGE.add(new Arc<>(NODE_D,NODE_S, LABEL, isDirected(), isLabeled()));
                    }
                    EDGE.add(new Arc<>(NODE_S, NODE_D, LABEL, isDirected(), isLabeled()));
                } else {
                    NODES.get(NODE_S).add(new Node<V,L>(NODE_D, null));
                    if (!isDirected()) {
                        NODES.get(NODE_D).add(new Node<V,L>(NODE_S, null));
                        EDGE.add(new Arc<>(NODE_D,NODE_S, null, isDirected(), isLabeled()));
                    }
                    EDGE.add(new Arc<>(NODE_S, NODE_D, null, isDirected(), isLabeled()));
                }
        return true;
    }

    //containsNode returns true if the node is in the graph
    @Override
    public boolean containsNode(V NODE) {
        return NODES.containsKey(NODE);
    }

    //containsEdge returns true if the arc is associated to two nodes
    @Override
    public boolean containsEdge(V NODE_S, V NODE_D) {
        if(containsNode(NODE_S) && containsNode(NODE_D)){
            return NODES.contains(new Node<V, L>(NODE_D, getLabel(NODE_S, NODE_D)));
        }
        return false;
    }

    //removeNode remove a specific node in the graph
    @Override
    public boolean removeNode(V NODE) {
        for(V ELEM : getNeighbours(NODE)){
            removeEdge(NODE, ELEM);
        }
        return NODES.remove(NODE) == null;
    }

    //removeEdge remove a specific arc in the graph, given two arcs
    @Override
    public boolean removeEdge(V NODE_S, V NODE_D) {
        ArrayList<Node<V, L>> NODE_S_ADJ = NODES.get(NODE_S);
        NODE_S_ADJ.remove(new Node<>(NODE_D, getLabel(NODE_S, NODE_D)));

        if(!isDirected()){
            ArrayList<Node<V, L>> NODE_D_ADJ = NODES.get(NODE_D);
            NODE_D_ADJ.remove(new Node<>(NODE_S, getLabel(NODE_D, NODE_S)));
        }

        return true;
    }

    //numNodes returns the exactly number of graph's node
    @Override
    public int numNodes() {
        return NODES.size();
    }

    //numEdges returns the exactly number of graph's arcs
    @Override
    public int numEdges() {
        if(isDirected()){
            return EDGE.size();
        } else {
            return EDGE.size()/2;
        }
    }

    //getNodes returns the node's number of the collection
    @Override
    public Collection<V> getNodes() {
        ArrayList<V> LIST = new ArrayList<>();
        LIST.addAll(NODES.keySet());
        return LIST;
    }

    //getEdges returns the arcs' number of the collection
    @Override
    public Collection<? extends AbstractEdge<V, L>> getEdges() {
        ArrayList<Arc<V, L>> ARRAYARC = new ArrayList<>();
        ARRAYARC.addAll(EDGE);
        return ARRAYARC;
    }

    //getNeighbours returns the neighbours of a node
    @Override
    public Collection<V> getNeighbours(V NODE) {
        ArrayList<V> NEIGHBOURS = new ArrayList<>();
        for(Node<V, L> E : NODES.get(NODE)) {
            NEIGHBOURS.add(E.getElem());
        }
        return NEIGHBOURS;
    }

    //getLabel returns the label between tho nodes
    @Override
    public L getLabel(V NODE_S, V NODE_D) {
        L LABEL = null;

        if(isLabeled()) {

            for (Node<V, L> E : NODES.get(NODE_S)) {
                if  (E.getElem().equals(NODE_D)) {
                    LABEL = E.getLabel();
                }
            }
            return LABEL;
        }
        return null;
    }
}
