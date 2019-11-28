Action()
{
	

	lr_start_transaction("UC04_TR02_tasks");

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

	lr_end_transaction("UC04_TR02_tasks",LR_AUTO);
	
	lr_start_transaction("UC04_TR03_selectTask");

	web_url("/api/task/{TaskID}", 
		"URL=http://{uri}:{port}/api/task/{TaskID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/checkLogin", 
		"URL=http://{uri}:{port}/api/checkLogin", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t12.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/{TaskID}/comment/", 
		"URL=http://{uri}:{port}/api/ticket/{TaskID}/comment/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t13.inf", 
		"Mode=HTML", 
		LAST);

	web_set_sockets_option("SSL_VERSION", "2&3");

	lr_end_transaction("UC04_TR03_selectTask",LR_AUTO);

	lr_start_transaction("UC04_TR04_ToOrder");

	web_custom_request("/api/ticket/{TaskID}", 
		"URL=http://{uri}:{port}/api/ticket/{TaskID}", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t15.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/{TaskID}/comment/", 
		"URL=http://{uri}:{port}/api/ticket/{TaskID}/comment/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t16.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC04_TR04_ToOrder",LR_AUTO);

	lr_think_time(10);

	lr_start_transaction("UC04_TR05_closeOrder");

	web_custom_request("/api/ticket/{TaskID}/solve/", 
		"URL=http://{uri}:{port}/api/ticket/{TaskID}/solve/", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t17.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);
	
	web_url("/home", 
		"URL=http://{uri}:{port}/", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t18.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/checkLogin", 
		"URL=http://{uri}:{port}/api/checkLogin", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t19.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/user/info", 
		"URL=http://{uri}:{port}/api/user/info", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t20.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/4", 
		"URL=http://{uri}:{port}/api/ticket/countByState/4", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t21.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/", 
		"URL=http://{uri}:{port}/api/ticket/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t22.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/task/countByState/", 
		"URL=http://{uri}:{port}/api/task/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t23.inf", 
		"Mode=HTML", 
		LAST);

	web_custom_request("/api/task/?state=1&page=0&size=10", 
		"URL=http://{uri}:{port}/api/task/?state=1&page=0&size=10", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t24.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	web_custom_request("/api/ticket/?state=-1,0,1,5&page=0&size=10", 
		"URL=http://{uri}:{port}/api/ticket/?state=-1,0,1,5&page=0&size=10", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t25.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	lr_end_transaction("UC04_TR05_closeOrder",LR_AUTO);

	return 0;
}