import java.lang.Math.*;
import java.lang.StringBuffer;
import java.util.ArrayList;
/**
 * The main part of the calculator doing the calculations.
 * 
 * @author: (none yet)
 * @version 0.1 (incomplete)
 */
public class CalcEngine
{
    private ArrayList<String> input = new ArrayList<>();    // List for input, we need something we can add on to this will be converted to a String array and passed to the RPN converter
    private boolean buildingDisplayValue;   // We need to know if we're building a display value for multiple digit numbers    
    private String strDisplay = "";
    private double displayValue;    // double used here to display the value on screen, we need this because we cant perform operations on strings easily
    private String operand;     // Declaring operand as a string, this is used so we can pass the Double to the String Array

    /**
     * Create a CalcEngine instance.
     */
    public CalcEngine()
    {
        clear();
    }

    /**
     * Return the value that should currently be displayed
     * on the calculator display.
     */
    public String getDisplayValue()
    {    
        return strDisplay; //displayValue as string;
    }
    
    /**
     * This method first gets a double of what number was pressed on the calculator, (We passed it as a String called 'number' in the method parameters)
     * It then checks if a display value is being built. If we're not building a display value, display the number on screen, and set it to be our left operand for now, and 
     * make it known that we are done building a display value. If we're not building a display value(we already have one) and a number is pressed, 'append' the 
     * second number to the first by doing the simple math. Each time we're updating what the operand is but not adding it onto our String array until '=' is pressed.
     */
    public void numberPressed(String number)
    {
        double inputNum = Double.parseDouble(number);
        if(!buildingDisplayValue) {
            displayValue = displayValue*10 + inputNum;
            operand = Double.toString(displayValue);
            strDisplay = operand;
        }
        else {
            // Start building a new number.
            displayValue = inputNum;
            operand = Double.toString(displayValue);
            strDisplay = strDisplay + Double.toString(displayValue);
            buildingDisplayValue = false;
        }
    }
       
    /**
     * The 'plus' button was pressed. 
     */
    public void plus()
    {
        applyOperator("+");
    }
    /**
     * The 'minus' button was pressed.
     */
    public void minus()
    {
        applyOperator("-");
    }
    public void times()
    {
         applyOperator("*");
    }
    public void SQRT()
    {
        applyOperator("sqrt");
    }
    
    public void log()
    {
        applyOperator("log");
    }
    
    public void ln()
    {
        applyOperator("ln");
    }
    
    public void cuberoot()
    {
        applyOperator("cbrt");
    }
    public void powerTo()
    {
        applyOperator("^");
    }
    //Parenthesis go right into the non converted string[] input
    public void leftParenthesis()
    {
        applyOperator("(");
    }
    
    public void rightParenthesis()
    {
        applyOperator(")");
    }
    
    /**
     * Pi is a slightly special case, when the method is called it assigns Pi directly to the Operand, bypassing display Values
     */
    public void pi()
    {
        displayValue = Math.PI;
        operand = Double.toString(displayValue);
    }
    
    /**
     * The '=' button was pressed. This does a lot here, first a new String array is made that that is the size of the input List.
     * then we pass the list of input to the String array, and pass it to the RPN converter. This changes the infix notation to
     * post fix, which, in the next step, we evaluate. This result is returned to the display value. 
     */
    public void equals()
    {
        if(operand!="")
        {
            input.add(operand);
        }
        String[] inputArray = new String[input.size()];
        input.toArray(inputArray);
        String[] convertedInput = RPNConverter.infixToRPN(inputArray);
        displayValue = RPNCalc.getAnswer(convertedInput);
        strDisplay = Double.toString(displayValue);        
    }
    
    /**
     * The 'C' (clear) button was pressed.
     * Reset everything to a starting state. We need to reset the String list we were adding input on to,
     * luckily ArrayList has a built in method clear() which does this for us. We also reset the display value and
     * status of building the display. 
     */
     public void clear()
    {
        input.clear();
        operand = "";
        buildingDisplayValue = true;
        displayValue = 0;
        strDisplay = "";
    }

    /**
     * Return the title of this calculation engine.
     */
    public String getTitle()
    {
        return "Calculator";
    }

    /**
     * Return the author of this engine.
     */
    public String getAuthor()
    {
        return "Team Vase";
    }

    /**
     * Return the version number of this engine.
     */
    public String getVersion()
    {
       return "Version 0.0";
    }

    /**
     * When an operator is applied, first it will finally add the left operand we have been saving to the list
     * then it will add the operator itself to the list. We also use this to reset the status of building display value
     * 
     */
    

  
   //Apply the given operator.
     
   private void applyOperator(String operator)
    {
        if(operand!=""){
            input.add(operand);
        }
        buildingDisplayValue = true;
        input.add(operator);
        strDisplay = strDisplay + operator;
        operand = "";
    }

}

