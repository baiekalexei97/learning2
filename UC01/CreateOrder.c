CreateOrder()
{
	int i;
	lr_start_transaction("UC01_TR02_NewOrder");

	web_url("children", 
		"URL=http://learning2.pflb.ru:56902/api/user/catalog/node/0/children/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t71.inf", 
		"Mode=HTML", 
		LAST);

	web_set_sockets_option("SSL_VERSION", "2&3");

	lr_end_transaction("UC01_TR02_NewOrder",LR_AUTO);

	web_revert_auto_header("X-Requested-With");

	web_add_header("UA-CPU", 
		"AMD64");

	lr_start_transaction("UC01_TR03_Location1");

	web_add_auto_header("X-Requested-With", 
		"XMLHttpRequest");

	lr_think_time(16);
	
	web_reg_save_param_json("ParamName=ShopIDs",
	                        "QueryString=$..id",
	                        "SelectAll=Yes",	           
	                        LAST);

	web_url("shops", 
		"URL=http://learning2.pflb.ru:56902/api/shops?q=&page=0", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t73.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_save_string(lr_paramarr_random("ShopIDs"), "ShopID");

	web_url("children_2", 
		"URL=http://learning2.pflb.ru:56902/api/user/catalog/node/0/children/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
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

	web_url("treeview", 
		"URL=http://learning2.pflb.ru:56902/api/user/catalog/treeview?shopid={ShopID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t75.inf", 
		"Mode=HTML", 
		LAST);
	
	i = 1 + rand() % lr_paramarr_len("TreeIDs");	
	lr_save_string(lr_paramarr_idx("TreeIDs",i),"ServiceID");
	lr_save_string(lr_paramarr_idx("Names",i),"Name");
	lr_save_string(lr_paramarr_idx("Parents",i),"Parent");

	lr_end_transaction("UC01_TR03_Location1",LR_AUTO);

	
	lr_start_transaction("UC01_TR04_theme1");

	web_url("children_3", 
		"URL=http://learning2.pflb.ru:56902/api/user/catalog/node/{Parent}/children/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t76.inf", 
		"Mode=HTML", 
		LAST);

	web_url("service", 
		"URL=http://learning2.pflb.ru:56902/api/user/catalog/node/{Parent}/service/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t77.inf", 
		"Mode=HTML", 
		LAST);

	web_reg_save_param_json("ParamName=Names2",
	                        "QueryString=$..name",
	                        "SelectAll=Yes",	           
	                        LAST);
	
	
	web_url("{Parent}", 
		"URL=http://learning2.pflb.ru:56902/api/user/catalog/breadcrumbs/{Parent}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t78.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_save_string(lr_paramarr_random("Names2"),"Name2");
		
	web_reg_save_param_json("ParamName=InventoryCount",
	                        "QueryString=$..totalElements",	                	           
	                        LAST);

	web_url("inventoryNumbers", 
		"URL=http://learning2.pflb.ru:56902/api/inventoryNumbers?serviceId={ServiceID}&shopId={ShopID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t79.inf", 
		"Mode=HTML", 
		LAST);
	
	/*lr_param_sprintf("Test1", "%d", atoi(lr_eval_string("{InventoryCount}")));
	if(atoi(lr_eval_string("InventoryCount")) != 0){
	    	lr_save_string(lr_paramarr_random("InventoryNumbers"),"InventoryNumber");
	};*/
	
	
	lr_end_transaction("UC01_TR04_theme1",LR_AUTO);

	lr_think_time(21);

	lr_start_transaction("UC01_TR05_Description");
	
	if(atoi(lr_eval_string("{InventoryCount}")) != 0){
	    	web_reg_save_param_json("ParamName=InventoryNumbers",
		                        "QueryString=$..id",
		                        "SelectAll=Yes",
		                        LAST);
	};

	web_url("inventoryNumbers_2", 
		"URL=http://learning2.pflb.ru:56902/api/inventoryNumbers?serviceId={ServiceID}&shopId={ShopID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t80.inf", 
		"Mode=HTML", 
		LAST);
	
	if(atoi(lr_eval_string("InventoryCount")) != 0){
	    	lr_save_string(lr_paramarr_random("InventoryNumbers"),"InventoryNumber");
	};

	lr_end_transaction("UC01_TR05_Description",LR_AUTO);

	lr_think_time(26);

	lr_start_transaction("UC01_TR06_inventoryNum");

	web_url("inventoryNumbers_3", 
		"URL=http://learning2.pflb.ru:56902/api/inventoryNumbers?shopId={ShopID}&serviceId={ServiceID}&serviceId={ServiceID}&q=&page=0", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t81.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC01_TR06_inventoryNum",LR_AUTO);

	lr_think_time(26);

	lr_start_transaction("UC01_TR07_File");
	
	web_reg_save_param_json("ParamName=FileID",
	                        "QueryString=$..id",	           
	                       LAST);

	web_submit_data("file", 
		"Action=http://learning2.pflb.ru:56902/api/ticket/file/", 
		"Method=POST", 
		"EncType=multipart/form-data", 
		"TargetFrame=", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t82.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=files", "Value=C:\\Users\\student\\Documents\\XDesk task details\\task_detail_1.txt", "File=Yes", ENDITEM, 
		LAST);

	lr_end_transaction("UC01_TR07_File",LR_AUTO);

	lr_think_time(38);

	lr_start_transaction("UC01_TR08_descFinish");	
	
	if(atoi(lr_eval_string("InventoryCount")) != 0){
		lr_param_sprintf("Body","\"text\":\"zdes' bil leha\",\"header\":\"%s\",\"ticketStateId\":0,\"serviceId\":\"%s\",\"files\":[%s],\"inventoryNumberId\":\"%s\",\"shopId\":\"%s\"",lr_eval_string("{Name}"),lr_eval_string("{ServiceID}"),lr_eval_string("{FileID}"),lr_eval_string("{InventoryNumber}"),lr_eval_string("{ShopID}"));
	    }else{		
	    lr_param_sprintf("Body","\"text\":\"zdes' bil leha\",\"header\":\"%s\",\"ticketStateId\":0,\"serviceId\":\"%s\",\"files\":[%s],\"shopId\":\"%s\"",lr_eval_string("{Name}"),lr_eval_string("{ServiceID}"),lr_eval_string("{FileID}"),lr_eval_string("{ShopID}"));
	    };

	web_custom_request("ticket_2", 
		"URL=http://learning2.pflb.ru:56902/api/ticket/", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t83.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		//"BodyBinary={\"text\":\"zdes' bil leha\",\"header\":\"\\xD0\\x9F\\xD0\\xBB\\xD0\\xB5\\xD0\\xBD\\xD0\\xBA\\xD0\\xB0 \\xD0\\xB2\\xD1\\x8B\\xD0\\xB3\\xD0\\xBE\\xD1\\x80\\xD0\\xB5\\xD0\\xBB\\xD0\\xB0(\\xD1\\x82\\xD1\\x80\\xD0\\xB5\\xD0\\xB1\\xD1\\x83\\xD0\\xB5\\xD1\\x82\\xD1\\x81\\xD1\\x8F \\xD0\\xB7\\xD0\\xB0\\xD0\\xBC\\xD0\\xB5\\xD0\\xBD\\xD0\\xB0)\",\"ticketStateId\":0,\"serviceId\":\"2998\",\"files\":[4579],\"inventoryNumberId\":\"6\",\"shopId\":\"4\"}", 
		"BodyBinary={{Body}}",
		LAST);

	lr_end_transaction("UC01_TR08_descFinish",LR_AUTO);

	lr_start_transaction("UC01_TR09_descFinishOK");

	web_revert_auto_header("X-Requested-With");

	lr_think_time(20);

	web_url("learning2.pflb.ru:56902_2", 
		"URL=http://learning2.pflb.ru:56902/", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t84.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=/js/core/jqueryformplugin.js?_=1574752664222", ENDITEM, 
		"Url=/engineer/wrapper/wrapper.dust", ENDITEM, 
		"Url=/engineer/wrapper/wrapper.js", ENDITEM, 
		"Url=/engineer/tickets/tickets.dust", ENDITEM, 
		"Url=/engineer/tickets/tickets.js", ENDITEM, 
		LAST);

	web_add_auto_header("X-Requested-With", 
		"XMLHttpRequest");

	web_url("checkLogin_2", 
		"URL=http://learning2.pflb.ru:56902/api/checkLogin", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t85.inf", 
		"Mode=HTML", 
		LAST);

	web_url("info_2", 
		"URL=http://learning2.pflb.ru:56902/api/user/info", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t86.inf", 
		"Mode=HTML", 
		LAST);

	web_url("4_2", 
		"URL=http://learning2.pflb.ru:56902/api/ticket/countByState/4", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t87.inf", 
		"Mode=HTML", 
		LAST);

	web_url("countByState_2", 
		"URL=http://learning2.pflb.ru:56902/api/ticket/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t88.inf", 
		"Mode=HTML", 
		LAST);

	web_url("countByState_3", 
		"URL=http://learning2.pflb.ru:56902/api/ticket/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t89.inf", 
		"Mode=HTML", 
		LAST);

	web_custom_request("ticket_3", 
		"URL=http://learning2.pflb.ru:56902/api/ticket/?state=-1,0,1,5&page=0&size=10", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t90.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	web_custom_request("ticket_4", 
		"URL=http://learning2.pflb.ru:56902/api/ticket/?state=-1,0,1,5&page=0&size=10", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://learning2.pflb.ru:56902/", 
		"Snapshot=t91.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	lr_end_transaction("UC01_TR09_descFinishOK",LR_AUTO);

	return 0;
}