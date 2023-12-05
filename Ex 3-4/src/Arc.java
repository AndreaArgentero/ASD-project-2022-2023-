import javax.xml.stream.events.Comment;

class Arc<V,L> implements AbstractEdge<V, L> {
    public V START;
    public V END;
    public L LABEL;
    boolean LABELED, DIRECTED;

    //The first Arc method is the constructor, sets the origin and destination nodes of the arc, the weight of the arc and whether direct or indirect
    public Arc(V START, V END, L LABEL, boolean LABELED, boolean DIRECTED) {
        this.START = START;
        this.END = END;
        this.LABEL = LABEL;
        this.LABELED = LABELED;
        this.DIRECTED = DIRECTED;
    }

    //The second Arc method is the constructor, sets the origin and destination nodes of the arc and whether direct or indirect
    public Arc(V START, V END, boolean LABELED, boolean DIRECTED) {
        this.START = START;
        this.END = END;
        this.LABELED = LABELED;
        this.DIRECTED = DIRECTED;
    }

    //getStart returns the source node
    @Override
    public V getStart() {
        return this.START;
    }

    //getEnd returns the target node
    @Override
    public V getEnd() {
        return this.END;
    }

    //getLabel returns the weight of the arc
    @Override
    public L getLabel() {
        return this.LABEL;
    }


    //toString returns a string with the start node, the weight of the arc and the target node
    @Override
    public String toString() {
        if(LABELED){
            return "[" + this.START + ", " + this.LABEL + ", " + this.END + "]";
        }
        return "[" + this.START +  ", " + this.END + "]";
    }

    //hashCode calculate the hashCode of the Arc objects
    @Override
    public int hashCode() {
        final int FIRST = 31;
        int RESULT = 1;

        if (DIRECTED) {
            RESULT = FIRST * RESULT + ((END == null) ? 0 : END.hashCode());
            RESULT = FIRST * RESULT + ((START == null) ? 0 : START.hashCode());
        }
        else{
            RESULT = FIRST * RESULT + (((END == null) ? 0 : END.hashCode()) + ((START == null) ? 0 : START.hashCode()));
        }

        return RESULT;
    }

    //equals checks two things: if the arc of the source node and the target node are equal and if the arc is not directed
    @Override
    public boolean equals(Object obj) {
        if((!(obj instanceof Arc<?, ?> ARC))) return false;
        return (this.START.equals(ARC.getStart()) && this.END.equals(ARC.getEnd()) ||
                (!this.DIRECTED && this.END.equals(ARC.getEnd()) && this.START.equals(ARC.getStart())));
    }
}