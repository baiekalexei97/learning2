import lrapi.lr;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.*;
import java.util.ArrayList;

public class Actions
{
    public int init(){
    	
    	return 0;
    }
    
    public int action(){
		
    	ArrayList<String> id = new ArrayList<String>();
    	
    	lr.save_string(lr.eval_string("jdbc:oracle:thin:@" +
    		                              "{host}:{port}:{sid}"), "url");
    	
    	try (Connection connection = DriverManager.getConnection(lr.eval_string("{url}"),
    		                                         lr.eval_string("{login}"),
    		                                         lr.eval_string("{password}"));
    		                                         Statement stmt = connection.createStatement()) {
    		
    		lr.log_message("JDBC Connection Successful");
    		
    		connection.setAutoCommit(false);
    		
    		try(ResultSet rset = stmt.executeQuery("select id from ticket " +
    			                                       "where state_id = -1" +
    			                                       "and text like '%(alex)'")){
    			
    			lr.log_message("Selecting Ticket");
    			
    			while (rset.next()) id.add(rset.getString("id"));
    			
    			lr.log_message("Selected Ticket #" + id.get(0));
    		
    		}catch (SQLException e_rset1) {
    			
    			e_rset1.printStackTrace();
    			
    			lr.log_message("Could Not Select Ticket, " +
    			               "Exception: " + e_rset1.getMessage());
    			
    			return 1;
    		}
    		
    		lr.log_message("Updating Ticket Status");
    		
    		try(ResultSet rset = stmt.executeQuery("update ticket " +
    		                                       "set state_id = 1, " +
    		                                       "external_system = 'ASKO' " +
    		                                       "where id = "+id.get(0))){
    		lr.log_message("Status Updated");
    		
    		}catch (SQLException e_rset2) {
    			
    			e_rset2.printStackTrace();
    			
    			lr.log_message("Status Update Failed, " +
    			               "Exception: " + e_rset2.getMessage());
    			
    			lr.log_message("Rollback");
    			
    			connection.rollback();
    			
    			return 1;
    		}
    		
    		lr.log_message("Inserting New Task");
    		
    		try(ResultSet rset = stmt.executeQuery("insert into task(id," +
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
    		                                       "external_system " +
    		                                       "from ticket " +
    		                                       "where id = "+id.get(0))){
    		    	
    		    	lr.log_message("New Task Inserted");
    		
    		}catch (SQLException e_rset3) {
    			
    			e_rset3.printStackTrace();
    			
    			lr.log_message("Insert Operation Failed, " +
    			               "Exception: " + e_rset3.getMessage());
    			
    			lr.log_message("Rollback");
    			
    			connection.rollback();
    			
    			return 1;
    		}
    		
    		lr.log_message("Commit");
    		
    		connection.commit();
    		    		    		
    	} catch (SQLException e) {
    		
    		e.printStackTrace();
    		
    		lr.log_message("Could Not Connect, " +
    		               "Exception: " + e.getMessage());
    		
    		lr.abort();
    	}
    	
    	return 0;	
    }
	
    public int end(){
    	
    	return 0;
    }
    
}
