package challenge.two;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class DBTest {
	public static Connection makeConnection() {
		String url = "jdbc:mysql://localhost/fruits";
		Connection con = null;
		try {
			Class.forName("com.mysql.jdbc.Driver");

			System.out.println("데이터베이스 연결중 ...");
			con = DriverManager.getConnection(url, "root", "password");
			System.out.println("데이터베이스 연결 성공");
		} catch (ClassNotFoundException e) {
			System.out.println("JDBC 드라이버를 찾지 못했습니다...");
		} catch (SQLException e) {
			System.out.println("데이터베이스 연결 실패");
		}
		return con;
	}

	public static void main(String[] args) throws SQLException {
		Connection conn = makeConnection();
		Statement stmt = null;
		try {
			Class.forName("com.mysql.jdbc.Driver");
			conn = DriverManager.getConnection("jdbc:mysql://localhost/fruits", "root", "password");
			System.out.println("객체 생성 중...");
			stmt = conn.createStatement();
			String sql;
			sql = "select id, name, color, price from fruit";
			ResultSet rs = stmt.executeQuery(sql);

			while (rs.next()) {
				int id = rs.getInt("id");
				String name = rs.getString("name");
				String color = rs.getString("color");
				int price = rs.getInt("price");

				System.out.print("ID: " + id);
				System.out.print(", 이름: " + name);
				System.out.print(", 색상: " + color);
				System.out.println(", 가격: " + price);
			}
			rs.close();
			stmt.close();
			conn.close();
		} catch (Exception e) {
		}
	}
}