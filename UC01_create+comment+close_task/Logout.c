Logout()
{
	lr_start_transaction("UC01_TR16_logout1");

	web_url("/api/logout", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/logout", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t61.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/login", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/login", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t62.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC01_TR16_logout1",LR_AUTO);
	return 0;
}
