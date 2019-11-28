CreateOrder()
{
	int i;
	lr_start_transaction("UC01_TR02_NewOrder");

	web_url("/api/user/catalog/node/0/children/", 
		"URL=http://{uri}:{port}/api/user/catalog/node/0/children/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t71.inf", 
		"Mode=HTML", 
		LAST);

	web_set_sockets_option("SSL_VERSION", "2&3");

	lr_end_transaction("UC01_TR02_NewOrder",LR_AUTO);

	lr_start_transaction("UC01_TR03_Location1");

	lr_think_time(10);
	
	web_reg_save_param_json("ParamName=ShopIDs",
	                        "QueryString=$..id",
	                        "SelectAll=Yes",	           
	                        LAST);

	web_url("/api/shops?q=&page=0", 
		"URL=http://{uri}:{port}/api/shops?q=&page=0", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t73.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_save_string(lr_paramarr_random("ShopIDs"), "ShopID");

	web_url("/api/user/catalog/node/0/children/", 
		"URL=http://{uri}:{port}/api/user/catalog/node/0/children/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
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

	web_url("/api/user/catalog/treeview?shopid={ShopID}", 
		"URL=http://{uri}:{port}/api/user/catalog/treeview?shopid={ShopID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t75.inf", 
		"Mode=HTML", 
		LAST);
	
	i = 1 + rand() % lr_paramarr_len("TreeIDs");	
	lr_save_string(lr_paramarr_idx("TreeIDs",i),"ServiceID");
	lr_save_string(lr_paramarr_idx("Names",i),"Name");
	lr_save_string(lr_paramarr_idx("Parents",i),"Parent");

	lr_end_transaction("UC01_TR03_Location1",LR_AUTO);

	
	lr_start_transaction("UC01_TR04_theme1");

	web_url("/api/user/catalog/node/{Parent}/children/", 
		"URL=http://{uri}:{port}/api/user/catalog/node/{Parent}/children/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t76.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/user/catalog/node/{Parent}/service/", 
		"URL=http://{uri}:{port}/api/user/catalog/node/{Parent}/service/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t77.inf", 
		"Mode=HTML", 
		LAST);

	web_reg_save_param_json("ParamName=Names2",
	                        "QueryString=$..name",
	                        "SelectAll=Yes",	           
	                        LAST);
	
	web_url("/api/user/catalog/breadcrumbs/{Parent}", 
		"URL=http://{uri}:{port}/api/user/catalog/breadcrumbs/{Parent}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t78.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_save_string(lr_paramarr_random("Names2"),"Name2");
		
	web_reg_save_param_json("ParamName=InventoryCount",
	                        "QueryString=$..totalElements",	                	           
	                        LAST);

	web_url("/api/inventoryNumbers?serviceId={ServiceID}&shopId={ShopID}", 
		"URL=http://{uri}:{port}/api/inventoryNumbers?serviceId={ServiceID}&shopId={ShopID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
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
	};

	web_url("/api/inventoryNumbers?serviceId={ServiceID}&shopId={ShopID}", 
		"URL=http://{uri}:{port}/api/inventoryNumbers?serviceId={ServiceID}&shopId={ShopID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t80.inf", 
		"Mode=HTML", 
		LAST);
	
	if(atoi(lr_eval_string("InventoryCount")) != 0){
	    	lr_save_string(lr_paramarr_random("InventoryNumbers"),"InventoryNumber");
	};

	lr_end_transaction("UC01_TR05_Description",LR_AUTO);

	lr_think_time(10);

	lr_start_transaction("UC01_TR06_inventoryNum");

	web_url("/api/inventoryNumbers?shopId={ShopID}&serviceId={ServiceID}&serviceId={ServiceID}&q=&page=0", 
		"URL=http://{uri}:{port}/api/inventoryNumbers?shopId={ShopID}&serviceId={ServiceID}&serviceId={ServiceID}&q=&page=0", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t81.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC01_TR06_inventoryNum",LR_AUTO);

	lr_think_time(10);

	/*lr_start_transaction("UC01_TR07_File");
	
	web_reg_save_param_json("ParamName=FileID",
	                        "QueryString=$..id",	           
	                       LAST);

	web_submit_data("/api/ticket/file/", 
		"Action=http://{uri}:{port}/api/ticket/file/", 
		"Method=POST", 
		"EncType=multipart/form-data", 
		"TargetFrame=", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t82.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=files", "Value={file_folder}{file}", "File=Yes", ENDITEM, 
		LAST);

	lr_end_transaction("UC01_TR07_File",LR_AUTO);*/

	lr_think_time(10);

	lr_start_transaction("UC01_TR08_descFinish");	
	
	if(atoi(lr_eval_string("InventoryCount")) != 0){
		lr_save_string(lr_eval_string("\"text\":\"{comments}\","),"Body");
		lr_save_string(lr_eval_string("{Body}\"header\":\"{Name}\","),"Body");
		lr_save_string(lr_eval_string("{Body}\"ticketStateId\":0,"),"Body");
		lr_save_string(lr_eval_string("{Body}\"serviceId\":\"{ServiceID}\","),"Body");
		//lr_save_string(lr_eval_string("{Body}\"files\":\[FileID}],"),"Body");
		lr_save_string(lr_eval_string("{Body}\"inventoryNumberId\":\"{InventoryNumber}\","),"Body");
		lr_save_string(lr_eval_string("{Body}\"shopId\":\"{ShopID}\""),"Body");
	    }else{		
	    lr_save_string(lr_eval_string("\"text\":\"{comments}\","),"Body");
		lr_save_string(lr_eval_string("{Body}\"header\":\"{Name}\","),"Body");
		lr_save_string(lr_eval_string("{Body}\"ticketStateId\":0,"),"Body");
		lr_save_string(lr_eval_string("{Body}\"serviceId\":\"{ServiceID}\","),"Body");
		//lr_save_string(lr_eval_string("{Body}\"files\":[{FileID}],"),"Body");
		lr_save_string(lr_eval_string("{Body}\"shopId\":\"{ShopID}\""),"Body");
	    };

	web_custom_request("/api/ticket/", 
		"URL=http://{uri}:{port}/api/ticket/", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t83.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		"BodyBinary={{Body}}",
		LAST);

	lr_end_transaction("UC01_TR08_descFinish",LR_AUTO);

	lr_start_transaction("UC01_TR09_descFinishOK");

	web_revert_auto_header("X-Requested-With");

	lr_think_time(10);

	web_url("/home", 
		"URL=http://{uri}:{port}/", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t84.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/checkLogin", 
		"URL=http://{uri}:{port}/api/checkLogin", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t85.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/user/info", 
		"URL=http://{uri}:{port}/api/user/info", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t86.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/4", 
		"URL=http://{uri}:{port}/api/ticket/countByState/4", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t87.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/", 
		"URL=http://{uri}:{port}/api/ticket/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t88.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/", 
		"URL=http://{uri}:{port}/api/ticket/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t89.inf", 
		"Mode=HTML", 
		LAST);

	web_custom_request("/api/ticket/?state=-1,0,1,5&page=0&size=10", 
		"URL=http://{uri}:{port}/api/ticket/?state=-1,0,1,5&page=0&size=10", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{uri}:{port}/", 
		"Snapshot=t90.inf", 
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
		"Snapshot=t91.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	lr_end_transaction("UC01_TR09_descFinishOK",LR_AUTO);

	return 0;
}