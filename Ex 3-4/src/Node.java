public class Node<V, L> {
    V ELEM;
    L LABEL;

    //The Node method is the constructor, sets the element and the label of a node
    public Node(V ELEM, L LABEL){
        this.ELEM = ELEM;
        this.LABEL = LABEL;
    }

    //getElem returns the element inside the node
    public V getElem(){
        return ELEM;
    }

    //getLabel returns the label inside the node
    public L getLabel() {
        return LABEL;
    }

    //hashCode calculate the hashCode of the Node objects
    @Override
    public int hashCode() {
        final int FIRST = 31;
        int RESULT = 1;

        RESULT = FIRST * RESULT + ((ELEM == null) ? 0 : ELEM.hashCode());
        return RESULT;
    }

    //equals checks if the object passed is a Node instance
    @Override
    public boolean equals(Object obj){
        if(!(obj instanceof Node<?, ?> node)) return false;
        return this.ELEM.equals(node.ELEM);
    }

    //toString returns a string with the element and the label of a node
    @Override
    public String toString() {
        return ELEM + "[" + LABEL + "]";
    }
}
