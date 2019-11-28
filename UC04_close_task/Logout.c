Logout()
{
	lr_start_transaction("UC03_TR06_logout");

	web_url("/api/logout", 
		"URL=http://{uri}:{port}/api/logout", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t18.inf", 
		"Mode=HTML", 
		LAST);
	
	web_url("/login", 
		"URL=http://{uri}:{port}/login", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t19.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC03_TR06_logout",LR_AUTO);
	return 0;
}
