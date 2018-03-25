import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

/**
 * A graphical user interface for the calculator. No calculation is being
 * done here. This class is responsible just for putting up the display on 
 * screen. It then refers to the "CalcEngine" to do all the real work.
 * 
 * @author: Michael Kölling and David J. Barnes
 * @version 2011.07.31
 */
public class UserInterface
    implements ActionListener
{
    private CalcEngine calc;
    private boolean showingAuthor;

    private JFrame frame;
    private JTextField display;
    private JLabel status;

    /**
     * Create a user interface.
     * @param engine The calculator engine.
     */
    public UserInterface(CalcEngine engine)
    {
        calc = engine;
        showingAuthor = true;
        makeFrame();
        frame.setVisible(true);
    }

    /**
     * Set the visibility of the interface.
     * @param visible true if the interface is to be made visible, false otherwise.
     */
    public void setVisible(boolean visible)
    {
        frame.setVisible(visible);
    }

    /**
     * Make the frame for the user interface.
     */
    private void makeFrame()
    {
        frame = new JFrame(calc.getTitle());
        
        JPanel contentPane = (JPanel)frame.getContentPane();
        contentPane.setLayout(new BorderLayout(8, 8));
        contentPane.setBorder(new EmptyBorder( 10, 10, 10, 10));

        display = new JTextField();
        contentPane.add(display, BorderLayout.NORTH);

        JPanel buttonPanel = new JPanel(new GridLayout(6, 4));
            addButton(buttonPanel, "log");
            addButton(buttonPanel, "ln");
            addButton(buttonPanel, "CubeRoot");
            addButton(buttonPanel, "SQRT");
        
            addButton(buttonPanel, "7");
            addButton(buttonPanel, "8");
            addButton(buttonPanel, "9");
            addButton(buttonPanel, "C");
            
            addButton(buttonPanel, "4");
            addButton(buttonPanel, "5");
            addButton(buttonPanel, "6");
            addButton(buttonPanel, "*");
            
            addButton(buttonPanel, "1");
            addButton(buttonPanel, "2");
            addButton(buttonPanel, "3");
            addButton(buttonPanel, "^");
            
            addButton(buttonPanel, "0");
            addButton(buttonPanel, "+");
            addButton(buttonPanel, "-");
            addButton(buttonPanel, "=");
            
            addButton(buttonPanel, "TBD");
            addButton(buttonPanel, "TBD");
            addButton(buttonPanel, "(");
            addButton(buttonPanel, ")");
            
        contentPane.add(buttonPanel, BorderLayout.CENTER);

        status = new JLabel(calc.getAuthor());
        contentPane.add(status, BorderLayout.SOUTH);

        frame.pack();
    }

    /**
     * Add a button to the button panel.
     * @param panel The panel to receive the button.
     * @param buttonText The text for the button.
     */
    private void addButton(Container panel, String buttonText)
    {
        JButton button = new JButton(buttonText);
        button.addActionListener(this);
        panel.add(button);
    }

    /**
     * An interface action has been performed.
     * Find out what it was and handle it.
     * this takes the command given as passes it as a string to
     * methods defined in CalcEngine.
     */
    public void actionPerformed(ActionEvent event)
    {
        String command = event.getActionCommand();

        if(command.equals("0") ||
           command.equals("1") ||
           command.equals("2") ||
           command.equals("3") ||
           command.equals("4") ||
           command.equals("5") ||
           command.equals("6") ||
           command.equals("7") ||
           command.equals("8") ||
           command.equals("9")) {
           String guiInput = command.toString();
           calc.numberPressed(guiInput);
        }
    	else if(command.equals("+")) {
            String guiInput = command.toString();
            calc.plus();
        }
        else if(command.equals("-")) {
            calc.minus();
        }
         else if(command.equals("*")) {
            calc.times();
        }
        else if(command.equals("=")) {
            calc.equals();
        }
        else if(command.equals("C")) {
            calc.clear();
        }
        else if(command.equals("SQRT")){
            calc.SQRT();
        }
        else if(command.equals("log")){
            calc.log();
        }
        else if(command.equals("ln")){
            calc.ln();
        }
        else if(command.equals("CubeRoot")){
            calc.cuberoot();
        }
        //else if(command.equals("PI")){
        //    calc.pi();
        // }
        else if(command.equals("?")) {
            showInfo();
        }
        else if(command.equals("^")){
            calc.powerTo();
        }
        else if(command.equals("(")){
            calc.leftParenthesis();
        }
        else if(command.equals(")")){
            calc.rightParenthesis();
        }

        redisplay();
    }

    /**
     * Update the interface display to show the current value of the 
     * calculator.
     */
    private void redisplay()
    {
        display.setText("" + calc.getDisplayValue());
    }

    /**
     * Toggle the info display in the calculator's status area between the
     * author and version information.
     */
    private void showInfo()
    {
        if(showingAuthor)
            status.setText(calc.getVersion());
        else
            status.setText(calc.getAuthor());

        showingAuthor = !showingAuthor;
    }
}
