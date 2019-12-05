import lrapi.lr;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.*;
import java.util.ArrayList;

public class Actions
{
    public int init() throws Throwable {
    	
    	return 0;
    }
    
    public int action() throws ClassNotFoundException, SQLException {
    	ArrayList<String> id = new ArrayList<String>();
    	
    	try {
            Class.forName("oracle.jdbc.driver.OracleDriver");
        } catch (ClassNotFoundException ex) {
	    	lr.log_message("Database Driver not found");
	    	lr.abort();
    	}
    	
    	lr.save_string(lr.eval_string("jdbc:oracle:thin:@" +
    		                              "{host}:{port}:{sid}"), "url");
    	
    	try (Connection connection = DriverManager.getConnection(lr.eval_string("{url}"),
    		                                         lr.eval_string("{login}"),
    		                                         lr.eval_string("{password}"))) {
    		lr.log_message("JDBC Connection Successful");
    		connection.setAutoCommit(false);
    		try(Statement stmt = connection.createStatement()) {
			   
    			try(ResultSet rset = stmt.executeQuery("select id from ticket " +
    			                                       "where state_id = -1" +
    			                                       "and text like '%(alex)'")){
    				lr.log_message("Selecting Ticket");
    				
    				while (rset.next()){
    					id.add(rset.getString("id"));
    				}
    				
    			}catch (SQLException e_rset) {
    				e_rset.printStackTrace();
    				lr.log_message("Couldn't select ticket, " +
    				               "Exception - " + e_rset.getMessage());
    				return 1;
    			}
    			
	    		lr.log_message("Updating Ticket Status");
	    		System.out.println(id.get(0));
	    		
	    		stmt.executeQuery("update ticket set state_id = 1, external_system = 'ASKO' " +
	    		                  "where id="+id.get(0));
	    		
			  
	    		lr.log_message("Adding Ticket to Tasks");		   
	    		stmt.executeQuery("insert into task(id," +
	    		                  "change_id," +
	    		                  "ticket_id," +
	    		                  "guid," +
	    		                  "header," +
	    		                  "text," +
	    		                  "priority_id," +
	    		                  "state_id," +
	    		                  "client_id," +
	    		                  "solution_group_id," +
	    		                  "create_date," +
	    		                  "sync_mask," +
	    		                  "last_edit_date," +
	    		                  "last_edit_user_login," +
	    		                  "engineer_id," +
	    		                  "contractor_id," +
	    		                  "external_id," +
	    		                  "external_system) " +
	    		                  "select id, " +
	    		                  "'IDC2D620524153zdzPWAoX9OFgW4UB', " +
	    		                  "id, " +
	    		                  "'d830c5ee-9b77-4bd1-879a-0c4d2c282a67', " +
	    		                  "header, " +
	    		                  "text, " +
	    		                  "'3', " +
	    		                  "'1', " +
	    		                  "applicant_id, " +
	    		                  "'9', " +
	    		                  "create_date," +
	    		                  "'0', " +
	    		                  "last_edit_date, " +
	    		                  "last_edit_user_login," +
	    		                  "'103'," +
	    		                  "'102'," +
	    		                  "'TSK_1800000', " +
	    		                  "external_system" +
	    		                  " from ticket where id = "+id.get(0));
			 	
	    		lr.log_message("Commit");
	    		connection.commit();
    		} catch (SQLException e1) {
	    		e1.printStackTrace();
	    		lr.log_message("Rolling back, " +
	    		               "Exception - " + e1.getMessage());
	    		try{
	    			connection.rollback();
	    		}catch(SQLException e2){
	    			e2.printStackTrace();
	    		}
		    	return 1;
    		}
    		    		
    	} catch (SQLException e) {
    		e.printStackTrace();
    		lr.log_message("Database Connection Failed, " +
    		               "Please check your connection string");
    		lr.abort();
    	}
    	return 0;
    }
    public int end() throws Throwable {
    	
    	return 0;
    }
    
}
