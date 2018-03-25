import java.util.ArrayList;
import java.lang.IllegalArgumentException;
import java.lang.Math;
/**
 * Write a description of class RPNEval here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class RPNCalc
{
    
    //private ArrayList<String> inpStack;
    public static final String[] Operators = { "+", "*", "-", "/", "^" };   // Declare  valid operators
    public static final String[] specialOps = { "sqrt","cbrt","log","ln" }; // Declare special operators, these only use 1 operand
    private static myStack<Double> inStack = new myStack<Double>(); // myStack is its own class, it is just an ArrayList with added methods of Push and Pop
    
    /** We check to see if the input is a basic operator, we need to know this so we know when to calculate and what the 
     * input parameters are going to be.
     * returns true if input is contained in 'Operators' array, else return false. 
     */
    public static Boolean hasOperator(String current)
    {
        for(String opSearch: Operators) {
            if(opSearch.equals(current)){
                return true;
            }
        }
        return false;
    }
    
    /**
     * This does the same thing but checks to see if the given operator is a special operation
     * aka only uses 1 operand.
     */
    
    public static Boolean hasSpecialOp(String current)
    {
        for(String specOpSearch: specialOps) {
            if(specOpSearch.equals(current)){
                return true;
            }
        }
        return false;
    }
     
    /** 
     * Below are two variations of the same method, their job is to calculate a result when given an operator and some operand(s)
     * One takes a string and one double, the next takes a string and two doubles
     * I made two separate methods because the number of operands is dependant on the type of operator we're applying.
     * If it is a special operator we only need to provide one input number with the operator, if it is a basic operator
     * we need both numbers involved with the operation. For '-' and '/' order matters, so that is addressed. 
     */
    
    public static Double performOperation(String currentOp, Double n1)
    {
        if(currentOp.equals("sqrt")){
            return Math.pow(n1,.5);
        }
        else if(currentOp.equals("cbrt")){
            return Math.cbrt(n1);
        }
        else if(currentOp.equals("log")){
            return Math.log10(n1);
        }
        else if(currentOp.equals("ln")){
            return Math.log(n1);
        }
     
        else{ throw new IllegalArgumentException("Operator Error");}
    }
    
    public static Double performOperation(String currentOp, Double n1, Double n2)
    {
        if(currentOp.equals("+")){
            return n2+n1;
        }
        else if(currentOp.equals("*")){
            return n2*n1;
        }
        else if(currentOp.equals("-")){
            return n2-n1;
        }
        else if(currentOp.equals("/")){
            return n2/n1;
        }
        else if(currentOp.equals("^")){
            return Math.pow(n2,n1);
        }
        else{ throw new IllegalArgumentException("Operator Error");}
    }

    /** This will evalulate the input String[] using the standard algorithm to solve in Reverse Polish Notation
     * So.. If you see a number, add it on to the stack. Once you see an operator, pop the top 2 numbers off 
     * the stack, make the first pop your RIGHT operand, and the second the LEFT, 
     * then apply the operator(done by the performOperation method).
     * Push the result to the stack. Check if the queue, aka your input string, is empty. If so , the result
     * should be the only thing on the stack, so we can return that as a double. 
     */ 
    public static Double getAnswer(String[] entries)
    {
        for(String token: entries)
        {
            if(hasOperator(token))
            {
                inStack.stackPush(performOperation(token, inStack.stackPop(), inStack.stackPop()));
            }
            else if(hasSpecialOp(token))
            {
                inStack.stackPush(performOperation(token, inStack.stackPop()));
            }
            else
            {
                inStack.stackPush(Double.parseDouble(token));
            }
        }
        return inStack.stackPop();
    }
}


