Comment()
{

	lr_start_transaction("UC03_TR09_tasks");

	web_url("/api/task/countByState/", 
		"URL=http://{UC03_comment_task_host}:{UC03_comment_task_port}/api/task/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC03_comment_task_host}:{UC03_comment_task_port}/", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		LAST);
	web_reg_save_param_json(
		"ParamName=TaskIDs",
		"QueryString=$..parentId",
	    "SelectAll=Yes",	           
	    LAST);

	web_custom_request("/api/task/", 
		"URL=http://{UC03_comment_task_host}:{UC03_comment_task_port}/api/task/?state=1&page=0&size=10", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC03_comment_task_host}:{UC03_comment_task_port}/", 
		"Snapshot=t10.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8",  
		LAST);
	
	lr_save_string(lr_paramarr_random("TaskIDs"),"TaskID");

	web_set_sockets_option("SSL_VERSION", "2&3");

	lr_end_transaction("UC03_TR09_tasks",LR_AUTO);

	lr_start_transaction("UC03_TR10_selectTask");

	web_url("/api/task/id", 
		"URL=http://{UC03_comment_task_host}:{UC03_comment_task_port}/api/task/{TaskID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC03_comment_task_host}:{UC03_comment_task_port}/", 
		"Snapshot=t12.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/checkLogin", 
		"URL=http://{UC03_comment_task_host}:{UC03_comment_task_port}/api/checkLogin", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC03_comment_task_host}:{UC03_comment_task_port}/", 
		"Snapshot=t13.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/id/comment/", 
		"URL=http://{UC03_comment_task_host}:{UC03_comment_task_port}/api/ticket/{TaskID}/comment/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC03_comment_task_host}:{UC03_comment_task_port}/", 
		"Snapshot=t14.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC03_TR10_selectTask",LR_AUTO);

	lr_think_time(10);

	lr_start_transaction("UC03_TR11_commentFinish");
	
	bytesBefore = web_get_int_property(HTTP_INFO_TOTAL_REQUEST_STAT);

	web_custom_request("/api/ticket/id/comment/", 
		"URL=http://{UC03_comment_task_host}:{UC03_comment_task_port}/api/ticket/{TaskID}/comment/", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC03_comment_task_host}:{UC03_comment_task_port}/", 
		"Snapshot=t16.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		//"Body={\"text\":\"{UC03_comment_task_comment}\",\"files\":[{FileID}]}", 
		"Body={\"text\":\"{UC03_comment_task_comment}\"}",
		LAST);
	
	influx(lr_eval_string
	       ("http://{UC03_comment_task_host}:{UC03_comment_task_port}/api/ticket/{TaskID}/comment/"),
	       "/api/ticket/id/comment", bytesBefore);
	
	web_url("/api/ticket/id/comment/", 
		"URL=http://{UC03_comment_task_host}:{UC03_comment_task_port}/api/ticket/{TaskID}/comment/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC03_comment_task_host}:{UC03_comment_task_port}/", 
		"Snapshot=t17.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC03_TR11_commentFinish",LR_AUTO);

	lr_think_time(10);

	return 0;
}