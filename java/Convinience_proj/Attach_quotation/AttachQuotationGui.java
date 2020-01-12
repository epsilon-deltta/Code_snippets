package Convinience;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.TextArea;
import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.StringSelection;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class AttachQuotationGui extends JFrame implements ActionListener {

	@Override
	public void actionPerformed(ActionEvent e) {
		switch (e.getActionCommand()) {
		case "exe":
			exeFunction();
			break;
		case "clear":
			clearFuntion();
		default:
		}
	}

	void clearFuntion() {
		textarea.setText("");
		output_textarea.setText("");
	}

	void exeFunction() {
		String str = textarea.getText();
		String attachedStr;
		
		AttachQuotation attaching = new AttachQuotation(str);
		
		attachedStr=attaching.getAttachedStr();
		//to output_text
		output_textarea.setText(attachedStr);
		//clibboard _copy
		copyFunction(attachedStr);
		//clear (only input text area
		textarea.setText("");

	}
	void copyFunction(String str){
		Toolkit toolkit = Toolkit.getDefaultToolkit();

		Clipboard clipboard = toolkit.getSystemClipboard();

		StringSelection strSel = new StringSelection(str);

		clipboard.setContents(strSel, null);

	}

	AttachQuotationGui() {
		setTitle("Attach quotation");
		setLayout(new BorderLayout());

		showNorth();
		showCenter();
		showSouth();

		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(500, 600);
		setVisible(true);
	}

	JTextArea textarea;

	public void showNorth() {
		JPanel panel = new JPanel();

		textarea = new JTextArea(6, 40);
		JScrollPane scroll = new JScrollPane(textarea);
		// textarea_setting
		textarea.setBackground(Color.DARK_GRAY);
		textarea.setForeground(Color.CYAN);
		// scroll_setting
		scroll.setHorizontalScrollBarPolicy(31);

		panel.add(scroll);
		add(panel, BorderLayout.NORTH);
	}

	public void showCenter() {
		JPanel panel = new JPanel();
		JButton exe_button = new JButton("exe");
		JButton clear_button = new JButton("clear");
		JButton copy_button = new JButton("copy");
		// Button_setting
		exe_button.addActionListener(this);
		clear_button.addActionListener(this);
		copy_button.addActionListener(this);

		panel.add(exe_button);
		panel.add(clear_button);
		panel.add(copy_button);
		add(panel, BorderLayout.CENTER);
	}

	TextArea output_textarea;

	public void showSouth() {
		JPanel panel = new JPanel();

		output_textarea = new TextArea(15, 40);
		JScrollPane scroll = new JScrollPane(output_textarea);
		// output_textarea_setting
		output_textarea.setBackground(Color.DARK_GRAY);
		output_textarea.setForeground(Color.CYAN);
		// scroll_setting
		scroll.setHorizontalScrollBarPolicy(31);

		panel.add(scroll);

		add(panel, BorderLayout.SOUTH);
	}

	public static void main(String[] args) {
		new AttachQuotationGui();
	}

}
