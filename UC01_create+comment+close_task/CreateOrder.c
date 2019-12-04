CreateOrder()
{
	int i;
	lr_start_transaction("UC01_TR02_NewOrder");

	web_url("/api/user/catalog/node/0/children/", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/user/catalog/node/0/children/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
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

	web_url("/api/shops", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/shops?q=&page=0", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t73.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_save_string(lr_paramarr_random("ShopIDs"), "ShopID");

	web_url("/api/user/catalog/node/0/children/", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/user/catalog/node/0/children/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
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
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/user/catalog/treeview" 
		"?shopid={ShopID}",
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
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
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/user/catalog/node/{Parent}/children/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t76.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/user/catalog/node/parentId/service/", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/user/catalog/node/{Parent}/service/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t77.inf", 
		"Mode=HTML", 
		LAST);

	web_reg_save_param_json("ParamName=Names2",
	                        "QueryString=$..name",
	                        "SelectAll=Yes",	           
	                        LAST);
	
	web_url("/api/user/catalog/breadcrumbs/parentId", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/user/catalog/breadcrumbs/{Parent}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t78.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_save_string(lr_paramarr_random("Names2"),"Name2");
		
	web_reg_save_param_json("ParamName=InventoryCount",
	                        "QueryString=$..totalElements",	                	           
	                        LAST);

	web_url("/api/inventoryNumbers", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/inventoryNumbers" 
		"?serviceId={ServiceID}&shopId={ShopID}",
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
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

	web_url("/api/inventoryNumbers", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/inventoryNumbers" 
		"?serviceId={ServiceID}&shopId={ShopID}",
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t80.inf", 
		"Mode=HTML", 
		LAST);
	
	if(atoi(lr_eval_string("InventoryCount")) != 0){
	    	lr_save_string(lr_paramarr_random("InventoryNumbers"),
		               "InventoryNumber");
	};

	lr_end_transaction("UC01_TR05_Description",LR_AUTO);

	lr_think_time(10);

	lr_start_transaction("UC01_TR06_inventoryNum");

	web_url("/api/inventoryNumbers", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/inventoryNumbers?" 
		"shopId={ShopID}&serviceId={ServiceID}" 
		"&serviceId={ServiceID}&q=&page=0",
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t81.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC01_TR06_inventoryNum",LR_AUTO);

	lr_think_time(10);

	lr_start_transaction("UC01_TR07_descFinish");	
	
	if(atoi(lr_eval_string("InventoryCount")) != 0){
		lr_save_string(lr_eval_string("\"text\":\"{UC01_create_task_comments}\"," 
		                              "\"header\":\"{Name}\"," 
		                              "\"ticketStateId\":0," 
		                              "\"serviceId\":\"{ServiceID}\"," 
		                              "\"inventoryNumberId\":\"{InventoryNumber}\"," 
		                              "\"shopId\":\"{ShopID}\""),"Body");
	    }else{
		lr_save_string(lr_eval_string("\"text\":\"{UC01_create_task_comments}\"," 
		                              "\"header\":\"{Name}\"," 
		                              "\"ticketStateId\":0," 
		                              "\"serviceId\":\"{ServiceID}\"," 
		                              "\"shopId\":\"{ShopID}\""),"Body");
	    };
	
	bytesBefore = web_get_int_property(HTTP_INFO_TOTAL_REQUEST_STAT);

	web_custom_request("/api/ticket/", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/ticket/", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t83.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		"BodyBinary={{Body}}",
		LAST);
	
	if (web_get_int_property(HTTP_INFO_RETURN_CODE) >= 400){
		success="false";
	}else{success="true";};
	lr_save_int(web_get_int_property(HTTP_INFO_TOTAL_REQUEST_STAT)-bytesBefore,"sentBytes");
	lr_save_timestamp("currtime",
	                  "DIGITS=16", 
	                  LAST);
	lr_param_sprintf("Result",
	                 "loadrunner,"
	                 "label=%s,"
	                 "responseCode=%d,"
	                 "success=%s " 
	                 "responseTime=%d000,"
	                 "bytes=%d," 
	                 "sentBytes=%s,"
	                 "URL=\"%s\" " 
	                 "%s000\n",
	                 ///////////////////////
	                 "/api/ticket",
	                 web_get_int_property(HTTP_INFO_RETURN_CODE),
	                 success,
	                 web_get_int_property(HTTP_INFO_DOWNLOAD_TIME),
	                 web_get_int_property(HTTP_INFO_DOWNLOAD_SIZE),
	                 lr_eval_string("{sentBytes}"),
	                 lr_eval_string("http://{UC01_create_task_host}:{UC01_create_task_port}/api/ticket/"),
	                 lr_eval_string("{currtime}"));
	
	web_custom_request("DB Request",
	                   "Method=POST",
	                   "URL=http://localhost:8086/write?db=loadrunner",
	                   "Body={Result}",
	                   LAST);


	lr_end_transaction("UC01_TR07_descFinish",LR_AUTO);

	lr_start_transaction("UC01_TR08_descFinishOK");

	lr_think_time(10);

	web_url("/", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t84.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/checkLogin", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/checkLogin", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t85.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/user/info", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/user/info", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t86.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/4", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/ticket/countByState/4", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t87.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/ticket/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t88.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/ticket/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t89.inf", 
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
		"Snapshot=t90.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	web_custom_request("/api/ticket/", 
		"URL=http://{UC01_create_task_host}:{UC01_create_task_port}/api/ticket/" 
		"?state=-1,0,1,5&page=0&size=10",
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://{UC01_create_task_host}:{UC01_create_task_port}/", 
		"Snapshot=t91.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	lr_end_transaction("UC01_TR08_descFinishOK",LR_AUTO);

	return 0;
}