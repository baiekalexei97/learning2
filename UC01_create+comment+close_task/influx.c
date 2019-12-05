int influx(char * URL, char * Label, int bytesBefore){
	char * success;
	if (web_get_int_property(HTTP_INFO_RETURN_CODE) >= 400){
		success="false";
	}else{
		success="true";
	}
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
	                 Label,
	                 web_get_int_property(HTTP_INFO_RETURN_CODE),
	                 success,
	                 web_get_int_property(HTTP_INFO_DOWNLOAD_TIME),
	                 web_get_int_property(HTTP_INFO_DOWNLOAD_SIZE),
	                 lr_eval_string("{sentBytes}"),
	                 URL,
	                 lr_eval_string("{currtime}"));
	
	web_custom_request("DB Request",
	                   "Method=POST",
	                   "URL=http://localhost:8086/write?db=loadrunner",
	                   "Body={Result}",
	                   LAST);
	return 0;
}