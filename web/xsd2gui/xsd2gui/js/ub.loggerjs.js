/* 
                    +----------------------------------------------+
                    |             loggerjs (v0.0)                  |
                    |                                              | 
                    | Developed by:                Umesh Batra     |
                    | Created:                     Aug. 05, 2007   |
                    | Tested on :                  Safari, Firefox |
                    +----------------------------------------------+ 
                     
- This script may be used and modified freely for business or personal use 
- This script may not be resold in any form 
- This script may only be redistributed in its original form 
- The script file name may not be changed. 
 
*/ 
 
 
/** ub.loggerjs.js ******************************************************************************* 
 
Usage: 
 
<script language="JavaScript" src="/scripts/ub.loggerjs.js"></script> 
loggerjs.debug('hello!'); 
 
Logging can be switched off/on by passing <&com.ub.utilities.loggerjs=enable> in URL as parameter 
or by calling loggerjs.enable() method; 
 
*************************************************************************************************/ 
 
/** PUBLIC class : Logs messages in container ***************************************************/ 
loggerjs = new function () { 
	 
	/** PRIVATE: name space definition **********************************************************/ 
	var com_ub_utilities_ns="com_ub_utilities"; 
	var com_ub_utilities_instance="loggerjs"; 
	var com_ub_utilities_loggerjs_ns_instance 
		= com_ub_utilities_ns + "_" + com_ub_utilities_instance; 
	 
	/** PRIVATE: variable definition ************************************************************/ 
	var isInitialized=false;
	var messageCounter = 0;	
	var availableWidth = 0; 
	var availableHeight = 0; 
	var popupWidth = 0; 
	var popupHeight = 0; 
	var offsetX = 429; 
	var offsetY = 599; 
	 
	/** PRIVATE: Configuration settings: Switch logging off/on **********************************/ 
	var isEnabled = false; 
	 
	if( isEnabled == false && 
	    location.href.match(/com.ub.utilities.loggerjs=enable/) 
	) { 
		isEnabled = true; 
	} 
	 
	if (isEnabled) { 
		loggerjs(); 
	} 
	 	 
	/** PRIVATE method : to refer a DOM object **************************************************/ 
	function $(id) { return document.getElementById(id) }; 
	 
	/** PRIVATE method : Log message ************************************************************/ 
	function log(level, msg) {                                 				 
		if (isEnabled) { 
			// increment count 
			messageCounter +=1; 
			$(com_ub_utilities_loggerjs_ns_instance+'_frame').innerHTML 
			= 'LogViewer:' + messageCounter; 
             
			var viewPallate =$(com_ub_utilities_loggerjs_ns_instance + 
			    '_view'); 
			     
			if (viewPallate.childNodes.length == 0 ) { 
				viewPallate.appendChild(append(level,msg)); 
			} else { 
				viewPallate.insertBefore(append(level,msg),viewPallate.childNodes[0]); 
			} 
  		} 
 	} 
     
    /** PRIVATE method : create row that displays message using W3C DOM APIs ********************/ 
	function append(level, msg) { 
		 
		if (document.all) { // browser detection 
			var style="styleFloat"; //ie
		} else {
			var style="csstyle"; //firefox
		} 
		 
		var result = document.createElement("div");
		result.style.borderBottom  = "1px solid #AAA";
		result.style.verticalAlign = "top";
		var message=document.createElement("div");
		message.style.width = (popupWidth-19) + "px"; 
		message.style.paddingLeft  = "3px"; 
		message.style[style]       = "left"; 
		
		// different styles for different severities
		if (level == "DEBUG") { 
			if (messageCounter/2 == Math.floor(messageCounter/2)) {
				message.style.backgroundColor="#ffffee";
			} else {
				message.style.backgroundColor="#ffffdd";
			} 
		} else if (level == "INFO") {
			if (messageCounter/2 == Math.floor(messageCounter/2)) {
				message.style.backgroundColor="#ddffdd";
			} else {
				message.style.backgroundColor="#ddeedd";
			} 
		} else if (level == "WARN") {
			if (messageCounter/2 == Math.floor(messageCounter/2)) {
				message.style.backgroundColor="#eeeeee";
			} else {
				message.style.backgroundColor="#dddddd";
			} 
		} else if (level == "ERROR") {
			if (messageCounter/2 == Math.floor(messageCounter/2)) {
				message.style.backgroundColor="#ffdddd";
			} else {
				message.style.backgroundColor="#eedddd";
			} 
		}
		
		message.appendChild(document.createTextNode(level + ": " + msg)); 
		result.appendChild(message); 
		message.style[style]="left"; 
		 
		var eraseDiv=document.createElement("div"); 
		eraseDiv.style.erase="both"; 
		result.appendChild(eraseDiv); 
		 
		return result; 
	} 

	/** PRIVATE method : create logger container ************************************************/
	function loggerjs() {                                                                   	 
		 
		var isFF = (navigator.userAgent.indexOf("Firefox") > -1) ? true : false;   // is FireFox 
 
		var isIE = ( 
			navigator.userAgent.indexOf("Microsoft") > -1 || 
			navigator.userAgent.indexOf("MSIE") > -1
		) ? true : false; // is Internet Explorer 
 
		var isSF = (navigator.userAgent.indexOf("Safari") > -1) ? true : false;    // is Safari 
 
		if(isIE) { 
			availableWidth = document.body.offsetWidth; 
			availableHeight = document.body.offsetHeight; 
		} else { 
			availableWidth = window.innerWidth; 
			availableHeight =  window.innerHeight; 
		} 
		 
		popupWidth = availableWidth - offsetX; 
	 	popupHeight = availableHeight - offsetY; 
	 	 
		if (!isInitialized) { 
		 
			try { 
             
				var popupTop = 19; 
				var popupLeft = availableWidth - 99; 
				var display = "none"; 
				 
				document.write(' <div id="' + 
				                 com_ub_utilities_loggerjs_ns_instance + '_container"' + 
				               ' style="font-family:arial; ' + 
				               ' color: black; ' + 
				               ' font-size: 9px; ' + 
				               ' z-index: 99; ' + 
				               ' position: absolute; ' + 
				               ' top: ' + popupTop + 'px; ' + 
				               ' left: '+ popupLeft +'px; "> ' + 
				                 
							   ' <div id="' + 
							     com_ub_utilities_loggerjs_ns_instance + '_frame"' + 
							   ' style="cursor:move; ' + 
							   ' position: absolute; ' + 
							   ' Z-index: 9999; ' + 
							   ' background-color: #aaaaaa; ' + 
							   ' border: 1px solid #4f4f4f; ' + 
							   ' color: black; ' + 
							   ' padding: 2px;" ' + 
							   ' onclick="' + 
							     com_ub_utilities_instance + '.toggle()">' + 
							   ' LogViewer:0</div> ' + 
							    
							   ' <div id="' + 
							     com_ub_utilities_loggerjs_ns_instance + '_body" ' + 
							   ' style="text-align: left; ' + 
							   ' border: 1px solid #4f4f4f; ' + 
							   ' width: ' + popupWidth + 'px; ' + 
							   ' position: absolute; ' + 
							   ' top: 19px; ' + 
							   ' left: -' + (popupWidth-55) + 'px; ' + 
							   ' background-color: white; ' + 
							   ' display: ' + display + '"> '+ 
							    
							   ' <div id="' + 
							     com_ub_utilities_loggerjs_ns_instance + '_toolbar" ' + 
							   ' style="height: 10px; ' + 
							   ' padding: 2px; ' + 
							   ' border-bottom: 1px solid black; ' + 
							   ' background-color: #777777;"> ' + 
							    
							   ' <span id="' + 
							     com_ub_utilities_loggerjs_ns_instance + '_erase" ' + 
							   ' style="color: #eeeeee;" ' + 
							   ' onclick="' + 
							     com_ub_utilities_instance+'.erase()">Erase logs</span>' + 
							      
							       
							   ' </div> ' + 
							    
							   ' <div id="' + 
							     com_ub_utilities_loggerjs_ns_instance+'_view" ' + 
							   ' style="height: ' + popupHeight + 'px; ' + 
							   ' overflow: auto;"></div> ' + 
							    
							   ' </div></div></div> ' ); 
                  
				$(com_ub_utilities_loggerjs_ns_instance+'_frame').style.cursor 
				= "pointer"; 
				
				isInitialized=true; 
				 
			} catch (e) { 
				alert("Code-level error initializing loggerjs: " + e.description); 
			}
		} 
	} 
	 
	/** PUBLIC method : debug *******************************************************************/ 	
	function debug(msg) { 
		log("DEBUG",msg);
	} 
	 
	/** PUBLIC method : info ********************************************************************/ 	
	function info(msg) { 
		log("INFO",msg);
	} 
	 
	/** PUBLIC method : warning *****************************************************************/ 	
	function warning(msg) {
		log("WARN",msg);
	} 
	 
	/** PUBLIC method : error *******************************************************************/ 	
	function error(msg) {
		log("ERROR",msg); 
	} 
	 
	/**  PUBLIC method : Toggles the log window display on or off *******************************/
	function toggle() {                                                            				 
		var loggerjsContainer = $(com_ub_utilities_loggerjs_ns_instance+'_body'); 
		if (loggerjsContainer.style.display == 'none') {
			loggerjsContainer.style.display = 'block';
		} else {
			loggerjsContainer.style.display = 'none';
		} 
	}
	
	/** PUBLIC method : this function erases the logs *******************************************/
	function erase() {                                                         				  
		$(com_ub_utilities_loggerjs_ns_instance+'_view').innerHTML = '';
		numberOfLogs = 0;
		$(com_ub_utilities_loggerjs_ns_instance+'_frame').innerHTML='LogViewer:'+numberOfLogs;
	}
	
	/** PUBLIC method : Programmatically enable loggerjs, 
	    even if it's turned off via the config, If already enabled, does nothing. ***************/
	function enable(_offsetX, _offsetY) { 
	 	 
		if(_offsetX!=null) 
			offsetX = _offsetX; 
		 
		if(_offsetY!=null) 
			offsetY = _offsetY; 
			 
		if (!isInitialized) { 
			isEnabled = true; 
			loggerjs(); 
		} 
	} 
	 
	this.debug   = debug; 
	this.error   = error; 
	this.warning = warning; 
	this.info    = info; 
	this.toggle  = toggle; 
	this.erase   = erase; 
	this.enable  = enable; 
	 
}; 