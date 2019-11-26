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
    // Create global connection variable
    private Connection connection;

    // VUser Init
    public int init() throws ClassNotFoundException, SQLException {
        // Initialize DB connection
        //connection = null;
        try {
	    // Load Oracle JDBC Driver
            Class.forName("oracle.jdbc.driver.OracleDriver");
        } catch (Exception ex) {
	    // If driver load is unsuccessful
	    lr.log_message("Database Driver not found");
	    lr.abort();
	}
	try {
        // Specify the JDBC Connection String
        String url = "jdbc:oracle:thin:@192.168.14.53:1522:orcl";
        // Connect to URL using USERNAME and PASSWORD
        connection = DriverManager.getConnection(url,"c##x5","c##x5");
	    lr.log_message("JDBC Connection Successful");
        } catch (SQLException e) {
	    // If Connection Failed
	    lr.log_message("Database Connection Failed, Please check your connection string");
	    lr.abort();
	}
	    return 0;
    } //end of init

    public int action() throws ClassNotFoundException, SQLException {

	// Database Query 1
	lr.start_transaction("Database_Query_1");
	database_query("insert into task(id,change_id,ticket_id,guid,header,text,priority_id,state_id,client_id,solution_group_id,create_date,sync_mask,last_edit_date,last_edit_user_login,engineer_id,contractor_id,external_id,external_system) select id, 'IDC2D620524153zdzPWAoX9OFgW4UB', id, 'd830c5ee-9b77-4bd1-879a-0c4d2c282a67', header, text, '3', '1', applicant_id, '9', create_date,'0', last_edit_date, last_edit_user_login,'103','102','TSK_1800000', external_system from ticket where rownum < 2 and state_id = -1");
	lr.end_transaction("Database_Query_1", lr.AUTO);

	// Database Query 2
	lr.start_transaction("Database_Query_2");
	database_query("update ticket set state_id = 1 where id in(select ticket_id from task where state_id =1)");
	lr.end_transaction("Database_Query_2", lr.AUTO);

	return 0;
    } //end of action

    public int end() throws Throwable {
	connection = null;
        return 0;
    } //end of end

    // Function: database_query
    // Argument: SQL Query String
    // Performs an SQL Query String, and returns pass or fail for the current transaction
    //
    public int database_query(String SQL_QUERY) {
       Statement stmt = null;
       ResultSet rset = null;

       try {
	   connection.setAutoCommit(true);
	   stmt = connection.createStatement();
	   rset = stmt.executeQuery(SQL_QUERY);
	   lr.set_transaction_status(lr.PASS);
	   //while (rset.next()) {				// Print the results of the query
	   //     lr.log_message(rset.getString(1));  		// Note: This should be used for debugging only,
	   // }							// as it slows down execution time
	   //lr.log_message("SQL Query Executed Successfully");
	   rset.close();
	} catch (SQLException e) {
	    // SQL Query has failed
	    lr.log_message("Caught Exception: " + e.getMessage());
	    lr.set_transaction_status(lr.FAIL);
	    return 1;
	}
	return 0;
    }
}
