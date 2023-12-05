import java.util.Comparator;

public class ComparatorLabelField<V, L> implements Comparator<Arc<V,L>> {

    /*@Override
    public int compare(Node<V, L> o1, Node<V, L> o2) {
        int result = Double.compare(Double.parseDouble(o1.getLabel().toString()), Double.parseDouble(o2.getLabel().toString()));
        if(result != 0){
            return result;
        }
        return 0;
    }*/

    //compare is a method that compare two arcs
    @Override
    public int compare(Arc<V, L> o1, Arc<V, L> o2) {
        return Double.compare((double) o1.getLabel(), (double) o2.getLabel());
    }
}
