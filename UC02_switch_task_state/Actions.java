/*
 * LoadRunner Java script.
 * Description: Oracle Database Testing via JDBC
 */

import lrapi.lr;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.*;

public class Actions
{
    private Connection connection;

    public int init() throws ClassNotFoundException, SQLException {
        try {
            Class.forName("oracle.jdbc.driver.OracleDriver");
        } catch (Exception ex) {
	    lr.log_message("Database Driver not found");
	    lr.abort();
	}
	try {
        String url = "jdbc:oracle:thin:@192.168.14.53:1522:orcl";
        connection = DriverManager.getConnection(url,"c##x5","c##x5");
	    lr.log_message("JDBC Connection Successful");
        } catch (SQLException e) {
	    lr.log_message("Database Connection Failed, Please check your connection string");
	    lr.abort();
	}
	    return 0;
    } 

    public int action() throws ClassNotFoundException, SQLException {

	lr.start_transaction("Database_Query_1");
	database_query("insert into task(id,change_id,ticket_id,guid,header,text,priority_id,state_id,client_id," +
	               "solution_group_id,create_date,sync_mask,last_edit_date,last_edit_user_login,engineer_id," +
	               "contractor_id,external_id,external_system) " +
	               "select id, 'IDC2D620524153zdzPWAoX9OFgW4UB', id, 'd830c5ee-9b77-4bd1-879a-0c4d2c282a67'," +
	               "header, text, '3', '1', applicant_id, '9', create_date,'0', last_edit_date," +
	               "last_edit_user_login,'103','102','TSK_1800000', external_system " +
	               "from ticket where rownum < 2 and state_id = -1");
	lr.end_transaction("Database_Query_1", lr.AUTO);

	lr.start_transaction("Database_Query_2");
	database_query("update ticket set state_id = 1 where id in(select ticket_id from task where state_id =1)");
	lr.end_transaction("Database_Query_2", lr.AUTO);

	return 0;
    }

    public int end() throws Throwable {
	connection = null;
        return 0;
    }
    public int database_query(String SQL_QUERY) {
       Statement stmt = null;
       ResultSet rset = null;

       try {
	   connection.setAutoCommit(false);
	   stmt = connection.createStatement();
	   rset = stmt.executeQuery(SQL_QUERY);
	   lr.set_transaction_status(lr.PASS);
	   connection.commit();
	   rset.close();
	} catch (SQLException e1) {
	    lr.log_message("Caught Exception: " + e1.getMessage());
	    lr.set_transaction_status(lr.FAIL);
	    try{
	    connection.rollback();
	    }catch(SQLException e2){
         lr.log_message("Caught Exception During Rollback: " + e2.getMessage());
	    }
	    return 1;
	}
	return 0;
    }
}
