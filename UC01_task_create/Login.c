Login()
{
	web_url("/login", 
		"URL=http://{uri}:{port}/login", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t32.inf", 
		"Mode=HTML", 
		LAST);

	lr_start_transaction("UC01_TR01_login");

	web_submit_data("/api/login", 
		"Action=http://{uri}:{port}/api/login", 
		"Method=POST", 
		"TargetFrame=", 
		"Referer=http://{uri}:{port}/login", 
		"Snapshot=t33.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=login", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=rememberMe", "Value=false", ENDITEM, 
		LAST);

	web_url("/home", 
		"URL=http://{uri}:{port}/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{uri}:{port}/login", 
		"Snapshot=t34.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/checkLogin", 
		"URL=http://{uri}:{port}/api/checkLogin", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t35.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/user/info", 
		"URL=http://{uri}:{port}/api/user/info", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t36.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/4", 
		"URL=http://{uri}:{port}/api/ticket/countByState/4", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t37.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/", 
		"URL=http://{uri}:{port}/api/ticket/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t38.inf", 
		"Mode=HTML", 
		LAST);

	web_custom_request("/api/ticket/?state=-1,0,1,5&page=0&size=10", 
		"URL=http://{uri}:{port}/api/ticket/?state=-1,0,1,5&page=0&size=10", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t39.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	lr_end_transaction("UC01_TR01_login",LR_AUTO);
	return 0;
}
