vuser_end()
{
	lr_start_transaction("UC01_TR11_logout1");

	web_url("logout", 
		"URL=http://learning2.pflb.ru:56902/api/logout", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t61.inf", 
		"Mode=HTML", 
		LAST);

	web_add_cookie("sessionExpired=false; DOMAIN=learning2.pflb.ru");

	web_revert_auto_header("X-Requested-With");

	web_url("login_3", 
		"URL=http://learning2.pflb.ru:56902/login", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t62.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC01_TR11_logout1",LR_AUTO);
	return 0;
}
