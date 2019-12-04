Login()
{
	web_url("/login", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/login", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t32.inf", 
		"Mode=HTML", 
		LAST);

	lr_start_transaction("UC01_TR01_login");
	
	bytesBefore = web_get_int_property(HTTP_INFO_TOTAL_REQUEST_STAT);

	web_submit_data("/api/login", 
		"Action=http://{UC01_create_task_host}:{UC01_create_task_port}/api/login", 
		"Method=POST", 
		"TargetFrame=", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/login", 
		"Snapshot=t33.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=login", "Value={UC01_create_task_login}", ENDITEM, 
		"Name=password", "Value={UC01_create_task_password}", ENDITEM, 
		"Name=rememberMe", "Value=false", ENDITEM, 
		LAST);
	
	influx(lr_eval_string
	       ("http://{UC01_create_task_host}:{UC01_create_task_port}/api/login"),
	       "/api/login", bytesBefore);

	web_url("/", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/login", 
		"Snapshot=t34.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/checkLogin", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/checkLogin", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t35.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/user/info", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/user/info", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t36.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/4", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/ticket/countByState/4", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t37.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/ticket/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t38.inf", 
		"Mode=HTML", 
		LAST);

	web_custom_request("/api/ticket/", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/ticket/" 
		"?state=-1,0,1,5&page=0&size=10",
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t39.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	lr_end_transaction("UC01_TR01_login",LR_AUTO);
	return 0;
}
