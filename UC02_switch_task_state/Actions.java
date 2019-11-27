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
    		lr.save_string(lr.eval_string("{host}:{port}:{sid}"), "url");
        //String url = "jdbc:oracle:thin:@192.168.14.53:1522:orcl";
        connection = DriverManager.getConnection(lr.eval_string("{url}"),
                                                 lr.eval_string("{login}"),
                                                 lr.eval_string("{password}"));
	    lr.log_message("JDBC Connection Successful");
    } catch (SQLException e) {
    	e.printStackTrace();
	    lr.log_message("Database Connection Failed, Please check your connection string");
	    lr.abort();
	}
	    return 0;
    } 
    
    public int action() throws ClassNotFoundException, SQLException {
       Statement stmt = null;

       try {
		   connection.setAutoCommit(false);
		   stmt = connection.createStatement();
		   System.out.println("Adding Ticket to Tasks");
		   lr.log_message("Adding Ticket to Tasks");
		   
		   stmt.executeQuery("insert into task(id,change_id,ticket_id,guid,header,text,priority_id,state_id,client_id," +
		               "solution_group_id,create_date,sync_mask,last_edit_date,last_edit_user_login,engineer_id," +
		               "contractor_id,external_id,external_system) " +
		               "select id, 'IDC2D620524153zdzPWAoX9OFgW4UB', id, 'd830c5ee-9b77-4bd1-879a-0c4d2c282a67'," +
		               "header, text, '3', '1', applicant_id, '9', create_date,'0', last_edit_date," +
		               "last_edit_user_login,'103','102','TSK_1800000', external_system " +
		               "from ticket where rownum < 2 and state_id = -1");
		   
		   System.out.println("Updating Ticket Status");
		   lr.log_message("Updating Ticket Status");
		   
		   stmt.executeQuery("update ticket set state_id = 1 where id in(select ticket_id from task where state_id =1)");
		   
		   lr.log_message("Commit");
		   System.out.println("Commit");
		   connection.commit();
	} catch (SQLException e1) {
       	e1.printStackTrace();
       	lr.log_message("Rollback, Caught Exception -" + e1.getMessage());
		System.out.println("Rolling back");		    
		try{
			connection.rollback();
		}catch(SQLException e2){
	        	e2.printStackTrace();
	    	}
	    	return 1;
		}
		return 0;
    }
	public int end() throws Throwable {
    	connection.close();
	    return 0;
	}
}
