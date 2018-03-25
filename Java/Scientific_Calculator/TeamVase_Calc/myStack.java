import java.util.ArrayList;
/**
 * This class extends the ArrayList class by adding methods for popping and pushing
 * stackPop removes the 'top' of the list and returns it
 * stackPush adds whatever you give it to the list.
 * 
 * @author Mike 
 * 
 */
public class myStack<X> extends ArrayList<X> //Using X is an abstract parameter, it "allows" any type 
{
    X stackPop()
    {
       return remove(size()-1);
    }
    void stackPush(X in)
    {
        add(in);
    }
}
