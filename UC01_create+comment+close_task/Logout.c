Logout()
{
	lr_start_transaction("UC01_TR16_logout1");

	bytesBefore = web_get_int_property(HTTP_INFO_TOTAL_REQUEST_STAT);
	
	web_url("/api/logout", 
		"URL=http://{host}:{port}/api/logout", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t61.inf", 
		"Mode=HTML", 
		LAST);
	
	influx(lr_eval_string
	       ("http://{host}:{port}/api/logout"),
	       "/api/logout", bytesBefore);

	web_url("/login", 
		"URL=http://{host}:{port}/login", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t62.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC01_TR16_logout1",LR_AUTO);
	return 0;
}
