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
		
		String query = new String();
    	ArrayList<String> id = new ArrayList<String>();    	
    	lr.save_string(lr.eval_string("jdbc:oracle:thin:@{host}:{port}:{sid}"), "connection");    	
    	try (Connection connection = DriverManager.getConnection(lr.eval_string("{connection}"),
    		                                         lr.eval_string("{login}"),
    		                                         lr.eval_string("{password}"));
    		                                         Statement stmt = connection.createStatement()) {
    		
    		lr.log_message("JDBC Connection Successful");
    		connection.setAutoCommit(false);
    		query = "select id from ticket where state_id = -1 and text like '%(alex)'";
    		
    		try(ResultSet rset = stmt.executeQuery(query)){
    			
    			lr.log_message("Selecting Ticket");    			
    			while (rset.next()) id.add(rset.getString("id"));  
    		
    		}catch (SQLException e_rset1) {
    			
    			e_rset1.printStackTrace();    			
    			lr.log_message("Could Not Select Ticket, " +
    			               "Exception: " + e_rset1.getMessage());    			
    			return 1;
    		}
    		
    		
    		for(int i = 0; i < id.size(); i++){
	    		try{
	    			
	    			query = "update ticket set state_id = 1, external_system = 'ASKO' " +
	    			                  "where id = " + id.get(i);
	    			
	    			lr.log_message("Updating Ticket Status");
	    			lr.log_message("Selected Ticket #" + id.get(i));
	    			stmt.executeQuery(query);
	    			lr.log_message("Status Updated");
	    			
	    			query = "insert into task(id, change_id, ticket_id," +
	    				"guid, header, text, priority_id, state_id, client_id," +
	    				"solution_group_id, create_date, sync_mask," +
	    				"last_edit_date, last_edit_user_login, engineer_id," +
	    				"contractor_id, external_id, external_system) " +
	    				"select " +
	    				"id, 'IDC2D620524153zdzPWAoX9OFgW4UB', id,  " +
	    				"'d830c5ee-9b77-4bd1-879a-0c4d2c282a67', header, " +
	    				"text,  '3',  '1',  applicant_id, '9', create_date, " +
	    				"'0',  last_edit_date, last_edit_user_login, '103', " +
	    				"'102', 'TSK_1800000', external_system " +
	    				"from ticket where id = " + id.get(i);
	    			
	    			lr.log_message("Inserting New Task");
	    			stmt.executeQuery(query);
	    			
	    			lr.log_message("Commit");
	    			connection.commit();
	    			
	    		}catch (SQLException e2) {
	    			
	    			e2.printStackTrace();    			
	    			lr.log_message("Caught Exception: " + e2.getMessage());    			
	    			lr.log_message("Rollback");    			
	    			connection.rollback();    			
	    			return 1;
	    		}
    		}
    		    		    		
    	} catch (SQLException e) {
    		
    		e.printStackTrace();    		
    		lr.log_message("Could Not Connect, Exception: " + e.getMessage());    		
    		lr.abort();
    	}
    	
    	return 0;	
    }
	
    public int end(){
    	
    	return 0;
    }
    
}
