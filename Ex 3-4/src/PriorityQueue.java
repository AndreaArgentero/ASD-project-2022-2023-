import java.util.ArrayList;
import java.util.Comparator;
import java.util.Hashtable;

public class PriorityQueue<E> implements AbstractQueue<E>{

    ArrayList<E> QUEUE;
    Hashtable<E, Integer> MAP;
    Comparator<E> COMPARE;

    //The PriorityQueue is the constructor, sets a queue, a map and a one comparator
    public PriorityQueue(Comparator<E> COMPARATOR){
        this.QUEUE = new ArrayList<>();
        this.MAP = new Hashtable<>();
        this.COMPARE = COMPARATOR;
    }

    //empty return true if the queue is empty
    @Override
    public boolean empty() {
        return (this.QUEUE).isEmpty() && (this.MAP).isEmpty();
    }

    //push insert a value to the queue
    @Override
    public boolean push(E VALUE) {
        if(!this.contains(VALUE)){
            int INDEX=this.size();
            this.add(VALUE);
            while(INDEX>0 && COMPARE.compare(this.get(INDEX), (this.get(MAP.get(getFather(VALUE)))))<0){
                int INDEX_FATHER = MAP.get(getFather(VALUE));
                this.set(INDEX, this.getFather(VALUE));
                this.set(INDEX_FATHER, VALUE);
                INDEX=INDEX_FATHER;
            }
            return true;
        }

        return false;
    }

    //contains returns true if the element passed is in the queue
    @Override
    public boolean contains(E O) {
        return (this.QUEUE).contains(O);
    }

    //top returns the first value in the queue, without remove it
    @Override
    public E top() {
        if(this.size() > 0) {
            return (this.QUEUE).get(0);
        } else {
            return null;
        }
    }

    //remove return true if the element passed is successful remove from the queue
    @Override
    public boolean remove(E E) {
        if(!this.empty()){
            if(this.contains(E)){
                E VALUE=this.get(this.size()-1);
                if(VALUE == null){
                    System.out.println(1);
                    return false;
                }
                int INDEX= (MAP.get(E));
                this.erase(VALUE);
                if(this.size()==0){
                    return true;
                }
                if(this.contains(this.get(INDEX))){
                    MAP.remove(this.get(INDEX));
                }
                MAP.put(VALUE, INDEX);
                swap(VALUE, INDEX);
                return true;
            }
        }
        return false;
    }

    //swap exchange two values with each other
    private void swap(E VALUE, int INDEX) {
        int INDEX_SON;
        this.set(INDEX,VALUE);
        while(COMPARE.compare(getLeftSon(VALUE), VALUE)<0 || COMPARE.compare(getRightSon(VALUE), VALUE)<0){
            if(COMPARE.compare(getLeftSon(VALUE), getRightSon(VALUE))<0){
                INDEX_SON=MAP.get(getLeftSon(VALUE));
                this.set(INDEX,getLeftSon(VALUE));
            }
            else{
                INDEX_SON=MAP.get(getRightSon(VALUE));
                this.set(INDEX,getRightSon(VALUE));
            }
            this.set(INDEX_SON,VALUE);
            INDEX=INDEX_SON;
        }
    }

    //pop remove the first element in the queue
    @Override
    public void pop() {
        if(this.size()>0){
            E VALUE=this.get(this.size()-1);
            int INDEX=0;
            this.erase(VALUE);
            if(this.size()==0){
                return;
            }
            MAP.remove(get(0));
            MAP.put(VALUE, 0);
            swap(VALUE, INDEX);
        }
    }

    //incPriority increase the priority of a value in the queue
    public void incPriority(E OLD_VAL, E NEW_VAL){
        if(this.contains(OLD_VAL)) {
            if (COMPARE.compare(OLD_VAL, NEW_VAL) >= 0) {
                int INDEX = MAP.get(OLD_VAL);
                this.set(INDEX, NEW_VAL);
                MAP.remove(OLD_VAL);
                MAP.put(NEW_VAL, INDEX);
                while (INDEX >= 0 && COMPARE.compare(NEW_VAL, getFather(NEW_VAL)) < 0) {
                    int X = MAP.get(getFather(NEW_VAL));
                    this.set(INDEX, getFather(NEW_VAL));
                    this.set(X, NEW_VAL);
                    INDEX = X;
                }
            }
        }
    }

    //erase delete an element from the map and the queue
    public void erase(E E) {
        int INDEX = MAP.get(E);
        MAP.remove(E);
        (this.QUEUE).remove(INDEX);
    }

    //size return the number of the elements in the queue
    public int size(){
        return (this.QUEUE).size();
    }

    //add is a method that add a value to the queue and to the map
    public void add(E VALUE){
        (this.QUEUE).add(VALUE);
        MAP.put(VALUE, this.size()-1);
    }

    //get return the element in the index passed
    public E get(Integer INDEX){
        if(INDEX >= 0 && INDEX < this.size()) {
            return (this.QUEUE).get(INDEX);
        }
        return null;
    }

    //getFather returns the element father of the value passed
    public E getFather(E VALUE){
        int INDEX = MAP.get(VALUE);
        int INDEX_FATHER=(int)(((float) INDEX/2)-0.5);
        return this.get(INDEX_FATHER);
    }

    //getLeftSon returns the left son of the value passed
    public E getLeftSon(E VALUE){
        int INDEX=MAP.get(VALUE);
        int INDEX_LEFT_SON=2*INDEX+1;
        if(INDEX_LEFT_SON>this.size()-1){
            return VALUE;
        }
        else{
            return this.get(INDEX_LEFT_SON);
        }
    }

    //getRightSon returns the right son of the value passed
    public E getRightSon(E VALUE){
        int INDEX=MAP.get(VALUE);
        int INDEX_RIGHT_SON=2*INDEX+2;
        if(INDEX_RIGHT_SON>this.size()-1){
            return VALUE;
        }
        else{
            return this.get(INDEX_RIGHT_SON);
        }
    }

    //set change the index of a value
    public void set(int NEW_INDEX, E VALUE){
        if(NEW_INDEX >= 0 && NEW_INDEX < this.size()) {
            (this.QUEUE).set(NEW_INDEX, VALUE);
            MAP.replace(VALUE, NEW_INDEX);
        }
    }
}