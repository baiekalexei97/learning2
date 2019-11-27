Action()
{

	lr_start_transaction("UC03_TR02_tasks");

	web_url("countByState_2", 
		"URL=http://learning2.pflb.ru:56902/api/task/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		LAST);
	web_reg_save_param_json(
		"ParamName=TaskIDs",
		"QueryString=$..parentId",
	    "SelectAll=Yes",	           
	    LAST);

	web_custom_request("task", 
		"URL=http://learning2.pflb.ru:56902/api/task/?state=1&page=0&size=10", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t10.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8",  
		LAST);
	
	lr_save_string(lr_paramarr_random("TaskIDs"),"TaskID");

	web_set_sockets_option("SSL_VERSION", "2&3");

	lr_end_transaction("UC03_TR02_tasks",LR_AUTO);

	lr_start_transaction("UC03_TR03_selectTask");

	web_url("{TaskID}", 
		"URL=http://learning2.pflb.ru:56902/api/task/{TaskID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t12.inf", 
		"Mode=HTML", 
		LAST);

	web_url("checkLogin_2", 
		"URL=http://learning2.pflb.ru:56902/api/checkLogin", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t13.inf", 
		"Mode=HTML", 
		LAST);

	web_url("comment", 
		"URL=http://learning2.pflb.ru:56902/api/ticket/{TaskID}/comment/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t14.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC03_TR03_selectTask",LR_AUTO);

	lr_think_time(10);

	lr_start_transaction("UC03_TR04_commentFile");
	
	web_reg_save_param_json(
		"ParamName=FileID",
		"QueryString=$..id",           
	    LAST);

	web_submit_data("file", 
		"Action=http://learning2.pflb.ru:56902/api/ticket/file/", 
		"Method=POST", 
		"EncType=multipart/form-data", 
		"TargetFrame=", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t15.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=files", "Value=C:\\Users\\student\\Documents\\XDesk task details\\task_comment_1.txt", "File=Yes", ENDITEM, 
		LAST);

	lr_end_transaction("UC03_TR04_commentFile",LR_AUTO);

	lr_think_time(10);

	lr_start_transaction("UC03_TR05_commentFinish");

	web_custom_request("comment_2", 
		"URL=http://learning2.pflb.ru:56902/api/ticket/{TaskID}/comment/", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t16.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		"Body={\"text\":\"Comment(leha)\",\"files\":[{FileID}]}", 
		LAST);

	web_url("comment_3", 
		"URL=http://learning2.pflb.ru:56902/api/ticket/{TaskID}/comment/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t17.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC03_TR05_commentFinish",LR_AUTO);

	lr_think_time(10);


	return 0;
}