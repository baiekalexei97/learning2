Action()
{

	lr_start_transaction("/api/task/countByState/");

	web_url("/api/task/countByState/", 
		"URL=http://{uri}:{port}/api/task/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		LAST);
	web_reg_save_param_json(
		"ParamName=TaskIDs",
		"QueryString=$..parentId",
	    "SelectAll=Yes",	           
	    LAST);

	web_custom_request("/api/task/?state=1&page=0&size=10", 
		"URL=http://{uri}:{port}/api/task/?state=1&page=0&size=10", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t10.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8",  
		LAST);
	
	lr_save_string(lr_paramarr_random("TaskIDs"),"TaskID");

	web_set_sockets_option("SSL_VERSION", "2&3");

	lr_end_transaction("UC03_TR02_tasks",LR_AUTO);

	lr_start_transaction("UC03_TR03_selectTask");

	web_url("/api/task/{TaskID}", 
		"URL=http://{uri}:{port}/api/task/{TaskID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t12.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/checkLogin", 
		"URL=http://{uri}:{port}/api/checkLogin", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t13.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/{TaskID}/comment/", 
		"URL=http://{uri}:{port}/api/ticket/{TaskID}/comment/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
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

	web_submit_data("/api/ticket/file/", 
		"Action=http://{uri}:{port}/api/ticket/file/", 
		"Method=POST", 
		"EncType=multipart/form-data", 
		"TargetFrame=", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t15.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=files", "Value=C:\\Users\\student\\Documents\\XDesk task details\\{filename_comment}", "File=Yes", ENDITEM, 
		LAST);

	lr_end_transaction("UC03_TR04_commentFile",LR_AUTO);

	lr_think_time(10);

	lr_start_transaction("UC03_TR05_commentFinish");

	web_custom_request("/api/ticket/{TaskID}/comment/", 
		"URL=http://{uri}:{port}/api/ticket/{TaskID}/comment/", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t16.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		"Body={\"text\":\"{comment}\",\"files\":[{FileID}]}", 
		LAST);

	web_url("/api/ticket/{TaskID}/comment/", 
		"URL=http://{uri}:{port}/api/ticket/{TaskID}/comment/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t17.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC03_TR05_commentFinish",LR_AUTO);

	lr_think_time(10);


	return 0;
}