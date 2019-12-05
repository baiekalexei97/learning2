CreateOrder()
{
	int i;
	lr_start_transaction("UC01_TR02_NewOrder");

	web_url("/api/user/catalog/node/0/children/", 
		"URL=http://{host}:{port}/api/user/catalog/node/0/children/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t71.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC01_TR02_NewOrder",LR_AUTO);

	lr_start_transaction("UC01_TR03_Location1");

	lr_think_time(10);
	
	web_reg_save_param_json("ParamName=ShopIDs",
	                        "QueryString=$..id",
	                        "SelectAll=Yes",	           
	                        LAST);

	web_url("/api/shops", 
		"URL=http://{host}:{port}/api/shops?q=&page=0", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t73.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_save_string(lr_paramarr_random("ShopIDs"), "ShopID");

	web_url("/api/user/catalog/node/0/children/", 
		"URL=http://{host}:{port}/api/user/catalog/node/0/children/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t74.inf", 
		"Mode=HTML", 
		LAST);
	
	web_reg_save_param_json("ParamName=TreeIDs",
	                        "QueryString=$..services[*].id",
	                        "SelectAll=Yes",	           
	                        LAST);
	web_reg_save_param_json("ParamName=Names",
	                        "QueryString=$..services[*].name",
	                        "SelectAll=Yes",	           
	                        LAST);
	web_reg_save_param_json("ParamName=Parents",
	                        "QueryString=$..services[*].parentId",
	                        "SelectAll=Yes",	           
	                        LAST);

	web_url("/api/user/catalog/treeview", 
		"URL=http://{host}:{port}/api/user/catalog/treeview" 
		"?shopid={ShopID}",
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t75.inf", 
		"Mode=HTML", 
		LAST);
	
	i = 1 + rand() % lr_paramarr_len("TreeIDs");	
	lr_save_string(lr_paramarr_idx("TreeIDs",i),"ServiceID");
	lr_save_string(lr_paramarr_idx("Names",i),"Name");
	lr_save_string(lr_paramarr_idx("Parents",i),"Parent");

	lr_end_transaction("UC01_TR03_Location1",LR_AUTO);

	
	lr_start_transaction("UC01_TR04_theme1");

	web_url("/api/user/catalog/node/parentId/children/", 
		"URL=http://{host}:{port}/api/user/catalog/node/{Parent}/children/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t76.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/user/catalog/node/parentId/service/", 
		"URL=http://{host}:{port}/api/user/catalog/node/{Parent}/service/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t77.inf", 
		"Mode=HTML", 
		LAST);

	web_reg_save_param_json("ParamName=Names2",
	                        "QueryString=$..name",
	                        "SelectAll=Yes",	           
	                        LAST);
	
	web_url("/api/user/catalog/breadcrumbs/parentId", 
		"URL=http://{host}:{port}/api/user/catalog/breadcrumbs/{Parent}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t78.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_save_string(lr_paramarr_random("Names2"),"Name2");
		
	web_reg_save_param_json("ParamName=InventoryCount",
	                        "QueryString=$..totalElements",	                	           
	                        LAST);

	web_url("/api/inventoryNumbers", 
		"URL=http://{host}:{port}/api/inventoryNumbers" 
		"?serviceId={ServiceID}&shopId={ShopID}",
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t79.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("UC01_TR04_theme1",LR_AUTO);

	lr_think_time(10);

	lr_start_transaction("UC01_TR05_Description");
	
	if(atoi(lr_eval_string("{InventoryCount}")) != 0){
	    	web_reg_save_param_json("ParamName=InventoryNumbers",
		                        "QueryString=$..id",
		                        "SelectAll=Yes",
		                        LAST);
	}

	web_url("/api/inventoryNumbers", 
		"URL=http://{host}:{port}/api/inventoryNumbers" 
		"?serviceId={ServiceID}&shopId={ShopID}",
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t80.inf", 
		"Mode=HTML", 
		LAST);
	
	if(atoi(lr_eval_string("InventoryCount")) != 0){
	    	lr_save_string(lr_paramarr_random("InventoryNumbers"),
		               "InventoryNumber");
	}

	lr_end_transaction("UC01_TR05_Description",LR_AUTO);

	lr_think_time(10);

	lr_start_transaction("UC01_TR06_inventoryNum");

	web_url("/api/inventoryNumbers", 
		"URL=http://{host}:{port}/api/inventoryNumbers?" 
		"shopId={ShopID}&serviceId={ServiceID}" 
		"&serviceId={ServiceID}&q=&page=0",
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t81.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC01_TR06_inventoryNum",LR_AUTO);

	lr_think_time(10);

	lr_start_transaction("UC01_TR07_descFinish");	
	
	if(atoi(lr_eval_string("InventoryCount")) != 0){
		lr_save_string(lr_eval_string("\"text\":\"{comments}\"," 
		                              "\"header\":\"{Name}\"," 
		                              "\"ticketStateId\":0," 
		                              "\"serviceId\":\"{ServiceID}\"," 
		                              "\"inventoryNumberId\":\"{InventoryNumber}\"," 
		                              "\"shopId\":\"{ShopID}\""),"Body");
	    }else{
		lr_save_string(lr_eval_string("\"text\":\"{comments}\"," 
		                              "\"header\":\"{Name}\"," 
		                              "\"ticketStateId\":0," 
		                              "\"serviceId\":\"{ServiceID}\"," 
		                              "\"shopId\":\"{ShopID}\""),"Body");
	}
	
	bytesBefore = web_get_int_property(HTTP_INFO_TOTAL_REQUEST_STAT);

	web_custom_request("/api/ticket/", 
		"URL=http://{host}:{port}/api/ticket/", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t83.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		"BodyBinary={{Body}}",
		LAST);
	
	influx(lr_eval_string
	       ("http://{host}:{port}/api/ticket/"),
	       "/api/ticket", bytesBefore);
	


	lr_end_transaction("UC01_TR07_descFinish",LR_AUTO);

	lr_start_transaction("UC01_TR08_descFinishOK");

	lr_think_time(10);

	web_url("/", 
		"URL=http://{host}:{port}/", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t84.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/checkLogin", 
		"URL=http://{host}:{port}/api/checkLogin", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t85.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/user/info", 
		"URL=http://{host}:{port}/api/user/info", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t86.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/4", 
		"URL=http://{host}:{port}/api/ticket/countByState/4", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t87.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/", 
		"URL=http://{host}:{port}/api/ticket/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t88.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/", 
		"URL=http://{host}:{port}/api/ticket/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t89.inf", 
		"Mode=HTML", 
		LAST);

	web_custom_request("/api/ticket/", 
		"URL=http://{host}:{port}/api/ticket/" 
		"?state=-1,0,1,5&page=0&size=10",
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t90.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	web_custom_request("/api/ticket/", 
		"URL=http://{host}:{port}/api/ticket/" 
		"?state=-1,0,1,5&page=0&size=10",
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{host}:{port}/", 
		"Snapshot=t91.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	lr_end_transaction("UC01_TR08_descFinishOK",LR_AUTO);

	return 0;
}