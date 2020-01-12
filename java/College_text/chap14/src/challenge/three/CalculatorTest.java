package challenge.three;

import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class CalculatorTest extends JFrame {
	CalculatorTest() {
		setTitle("°è»ê±â");

		JPanel p1 = new JPanel();
		JPanel p2 = new JPanel();

		p1.add(new JTextField(15));
		add("North", p1);

		JPanel p21 = new JPanel();
		p21.add(new JButton("on"));
		p21.add(new JButton("off"));

		JPanel p31 = new JPanel(new GridLayout(4, 4, 10, 10));
		p31.add(new JButton("7"));
		p31.add(new JButton("8"));
		p31.add(new JButton("9"));
		p31.add(new JButton("+"));

		p31.add(new JButton("4"));
		p31.add(new JButton("5"));
		p31.add(new JButton("6"));
		p31.add(new JButton("-"));

		p31.add(new JButton("1"));
		p31.add(new JButton("2"));
		p31.add(new JButton("3"));
		p31.add(new JButton("x"));

		p31.add(new JButton("0"));
		p31.add(new JButton("."));
		p31.add(new JButton("="));
		p31.add(new JButton("¡À"));

		p2.add(p21);
		p2.add(p31);

		add("Center", p2);

		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(250, 300);
		setVisible(true);
	}

	public static void main(String[] args) {
		new CalculatorTest();
	}
}