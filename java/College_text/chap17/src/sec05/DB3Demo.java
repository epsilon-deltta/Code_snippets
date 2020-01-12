package sec05;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class DB3Demo {
	public static Connection makeConnection() {
		String url = "jdbc:mysql://localhost/contacts";
		Connection con = null;
		try {
			Class.forName("com.mysql.jdbc.Driver");

			System.out.println("�����ͺ��̽� ������ ...");
			con = DriverManager.getConnection(url, "root", "password");
			System.out.println("�����ͺ��̽� ���� ����");
		} catch (ClassNotFoundException e) {
			System.out.println("JDBC ����̹��� ã�� ���߽��ϴ�...");
		} catch (SQLException e) {
			System.out.println("�����ͺ��̽� ���� ����");
		}
		return con;
	}

	public static void main(String[] args) throws SQLException {
		Connection con = makeConnection();
		StringBuilder sql = new StringBuilder();
		sql.append("INSERT INTO person (name, phone, email)");
		sql.append("VALUES (?, ?, ?)");
		PreparedStatement pstmt = con.prepareStatement(sql.toString());
		pstmt.setString(1, "����ȭ");
		pstmt.setString(2, "010-2222-2222");
		pstmt.setString(3, "bae@two.com");
		pstmt.execute();
	}
}