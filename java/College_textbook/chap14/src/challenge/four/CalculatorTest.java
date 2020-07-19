package challenge.four;

import java.awt.BorderLayout;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.EmptyBorder;

public class CalculatorTest extends JFrame {
	String[] name = { "on", "off", "bs", "C", "7", "8", "9", "*", "4", "5", "6", "-", "1", "2", "3", "x", "0", ".", "=",
			"¡À" };
	JTextField display;

	CalculatorTest() {
		setTitle("°è»ê±â");

		JPanel p1 = new JPanel();
		display = new JTextField(20);
		p1.add(display);
		add("North", p1);

		JPanel p2 = new JPanel(new GridLayout(5, 4, 3, 3));


		for (int i = 0; i < 20; i++)
			addButton(p2, name[i]);

		add("Center", p2);

		p2.setBorder(new EmptyBorder(5, 5, 5, 5));
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(260, 280);
		// pack();
		setVisible(true);
	}

	private void addButton(JPanel p, final String label) {
		JButton button = new JButton(label);
		p.add(button);
	}

	public static void main(String[] args) {
		new CalculatorTest();
	}
}