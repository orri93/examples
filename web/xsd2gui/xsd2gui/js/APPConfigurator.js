/* 
                    +----------------------------------------------+
                    |             XSD2GUI Tree (v0.0)              |
                    |                                              |
                    | Developed by:                Umesh Batra     |
                    | Created:                     Aug. 05, 2007   |
                    | Tested on :                  Safari, Firefox |
                    +----------------------------------------------+ 
*/ 
 
 
/** All the following variable must be defined globally */  
 
 
/** Browser **************************************************************************************/ 
Browser = new Object(); 
isFF = (navigator.userAgent.indexOf("Firefox") > -1) ? true : false;   // is FireFox 
isIE = (navigator.userAgent.indexOf("Microsoft") > -1 || navigator.userAgent.indexOf("MSIE") > -1) ? true : false; // is Internet Explorer 
isSF = (navigator.userAgent.indexOf("Safari") > -1) ? true : false;    // is Safari 
  
Browser.windowWidth = window.innerWidth; 
Browser.windowHeight = window.innerHeight; 
 
 
 
 
  
/** XML ******************************************************************************************/ 
var XML = new Object();       // Empty definition of XML class for implimenting XML related methods 
XML.XPath = new Object(); 														
XML.XPath.AccessOperator = new Object(); 										
 
XML.XPath.axis='/';                                                // XPath Seperator 
XML.XPath.AccessOperator.operator = '[]';                          // XPath child position operator 
XML.XPath.AccessOperator.start=XML.XPath.AccessOperator.operator.substr(0, 1); 	
XML.XPath.AccessOperator.end=XML.XPath.AccessOperator.operator.substr(1, 1); 
  
  
  
  
  
  
/** XSD ******************************************************************************************/ 
var XSD = new Object();      // Empty definitions of XSD class for implimenting XSD related methods 
XSD.XML = new Object(); 
XSD.node = new Object();
XSD.node.name = new Object();
XSD.attribute = new Object();
XSD.attribute.name = new Object(); 
XSD.attribute.type = new Object();
XSD.attribute.type.value =new Object(); 
 
XSD.nsPrefix = new Object(); 
XSD.nsURI = new Object(); 
XSD.node.name.complexType = 'complexType';                  // XSD related constants definition 
XSD.node.name.elementType = 'element'; 
XSD.node.name.attributeType = 'attribute'; 
XSD.attribute.name.name= 'name'; 
XSD.attribute.name.type= 'type'; 
XSD.attribute.name.nlchar= 'nlchar'; 
XSD.attribute.name.values= 'values'; 
XSD.attribute.name.isAttribute= 'isAttribute'; 
XSD.attribute.name.nillable= 'nillable'; 
XSD.attribute.name.maxOccurs='maxOccurs'; 
XSD.attribute.name.minOccurs='minOccurs'; 
XSD.attribute.type.value.unbounded='unbounded'; 
XSD.attribute.name.id= 'id'; 
XSD.attribute.name.xPath='xpath'; 
XSD.attribute.type.value.enumeration='enumeration'; 
XSD.attribute.type.value.bBoolean='boolean'; 
 
XSD.attribute.type.value.IsAttribute = function(type) { 
	if ( 
		 type.toLowerCase() == (XSD.nsPrefix + 'attribute').toLowerCase() 
	) return true; 
	else false; 	 
} 
XSD.attribute.type.value.Text = function(type) { 
	if ( 
		 type.toLowerCase() == (XSD.nsPrefix + 'string').toLowerCase()             || 
		 type.toLowerCase() == (XSD.nsPrefix + 'byte').toLowerCase()               || 
		 type.toLowerCase() == (XSD.nsPrefix + 'unsignedByte').toLowerCase()        
	) return true; 
	else false; 	 
} 
XSD.attribute.type.value.Integer = function(type) { 
	if ( 
		 type.toLowerCase() == (XSD.nsPrefix + 'int').toLowerCase()                || 
		 type.toLowerCase() == (XSD.nsPrefix + 'integer').toLowerCase()            || 
		 type.toLowerCase() == (XSD.nsPrefix + 'negativeInteger').toLowerCase()    || 
		 type.toLowerCase() == (XSD.nsPrefix + 'nonNegativeInteger').toLowerCase() || 
		 type.toLowerCase() == (XSD.nsPrefix + 'nonPositiveInteger').toLowerCase() || 
		 type.toLowerCase() == (XSD.nsPrefix + 'positiveInteger').toLowerCase()    || 
		 type.toLowerCase() == (XSD.nsPrefix + 'unsignedInt').toLowerCase()         
	) return true; 
	else false; 	 
} 
XSD.attribute.type.value.Float = function(type) { 
	if ( 
		 type.toLowerCase() == (XSD.nsPrefix + 'decimal').toLowerCase()            || 
		 type.toLowerCase() == (XSD.nsPrefix + 'int').toLowerCase()                || 
		 type.toLowerCase() == (XSD.nsPrefix + 'integer').toLowerCase()            || 
		 type.toLowerCase() == (XSD.nsPrefix + 'long').toLowerCase()               || 
		 type.toLowerCase() == (XSD.nsPrefix + 'negativeInteger').toLowerCase()    || 
		 type.toLowerCase() == (XSD.nsPrefix + 'nonNegativeInteger').toLowerCase() || 
		 type.toLowerCase() == (XSD.nsPrefix + 'nonPositiveInteger').toLowerCase() || 
		 type.toLowerCase() == (XSD.nsPrefix + 'positiveInteger').toLowerCase()    || 
		 type.toLowerCase() == (XSD.nsPrefix + 'short').toLowerCase()              || 
		 type.toLowerCase() == (XSD.nsPrefix + 'unsignedLong').toLowerCase()       || 
		 type.toLowerCase() == (XSD.nsPrefix + 'unsignedInt').toLowerCase()        || 
		 type.toLowerCase() == (XSD.nsPrefix + 'unsignedShort').toLowerCase()       
	) return true; 
	else false; 	 
} 
 
 
 
 
 
/** GUI ******************************************************************************************/ 
XSD.xsddoc = new Object();                                 // Holds original XSD DOM tree structure 
XSD.xmldoc = new Object();          // Holds intermidiate transformations on XSD DOM tree structure 
 
 
 
 
/** APP ******************************************************************************************/ 
  
var porousXSD = new Object;  // Array to hold refined GUI XSD at last index and its maxoccurs nodes 
var docXSD = new Object;     // Holds original XSD data as a DOM tree 
var docXML = new Object;     // Holds original XML data as a DOM tree 
var treeGUI = new Object;    // Responsible for rendering GUI tree 
 
APP = new Object();          // Empty definition of APP class for implimenting APP related methods 
APP.Base = new Object(); 
APP.Base.Path = new Object(); 
  
/** Public method: Since porousXSD array holds all maxOccurs nodes, 
    The function checks existance 4 passed nodeName **********************************************/
APP.isMaxOccursNode = function(nodeName, porousXSD) { 
	for(var i=0; i < porousXSD.length-1; i++) { 
		currentMaxOccursNode = porousXSD[i]; 
		if (currentMaxOccursNode.nodeName == nodeName) { 
			return true; 
		} 
	} 
	return false; 
}; 
 
/** Public method: Returns the maxOccurs DOM tree structure **************************************/
APP.getMaxOccursNode = function(nodeName, porousXSD) { 							
	for(var i=0; i < porousXSD.length-1; i++) { 
		currentMaxOccursNode = porousXSD[i]; 
		if (currentMaxOccursNode.nodeName == nodeName) { 
				return currentMaxOccursNode; 
		} 
	} 
	return null; 
};  
 
/** Public method: JS sleep functionality implimentation *****************************************/ 
APP.Sleep = function(millisecondi) { 
    var now = new Date();
    var exitTime = now.getTime() + millisecondi;

    while(true)
    {
        now = new Date();
        if(now.getTime() > exitTime) break;
    }
}; 
 
/** Public method : Character to Ascii Ints ******************************************************/
APP.String2Ascii = function(str) { 
	var ascii = ''; 
	for(var x=0; x<str.length; x++){
		ascii = ascii + (str.charCodeAt(x)) + ','; 
	} 
	return ascii; 
} 
 
/** Loads dependencies ***************************************************************************/  
APP.ScriptLoader = {                                                              // Private method 
	request: null, 
	loaded: {}, 
	load: function() { 
		for (var i = 0; i < arguments.length; i++) { 
			var filename = arguments[i]; 
			if (!this.loaded[filename]) { 
				if (!this.request) { 
					if (window.XMLHttpRequest) this.request = new XMLHttpRequest; 
					else if (window.ActiveXObject) { 
						try { 
							this.request = new ActiveXObject('MSXML2.XMLHTTP'); 
						} catch (e) { 
							this.request = new ActiveXObject('Microsoft.XMLHTTP'); 

						} 
					}
				} 
				 
				if (this.request) { 
					this.request.open('GET', filename, false); // synchronous request! 
					this.request.send(null); 
					if (this.request.status == 0 || this.request.status == 200 ) { 
						this.globalEval(this.request.responseText); 
						this.loaded[filename] = true; 
					} 
				} 
			} 
		} 
	}, 
	globalEval: function(code) { 
		if (window.execScript) { 
			window.execScript(code, 'javascript'); 
		} else { 
			window.eval(code); 
		} 
	} 
}; 
 
/** Public method : Initialize the application ***************************************************/ 
APP.Initialize = function(basePath) { 
	
	APP.Base.Path = basePath; 
	 	 
    // Load dependent JS files 
    APP.ScriptLoader.load( APP.Base.Path + '/js/ub.loggerjs.js', 
                           APP.Base.Path + '/js/FormValidator.js', 
        				   APP.Base.Path + '/js/XMLParser.js', 
    					   APP.Base.Path + '/js/XSDPorous.js', 
    					   APP.Base.Path + '/js/XSDXMLUnifier.js', 
    					   APP.Base.Path + '/js/GUIGenerator.js', 
    					   APP.Base.Path + '/js/GUIMapper.js'); 
    					    
	loggerjs.enable(); 
	       
	// Initialize GUI array of tree structure 
	treeGUI = new GUI.Tree(false); 
}; 
 
/** Public method : Initialize the application ***************************************************/ 
APP.processXSD = function(isXSDContent, xsdContentOrFileName, startNode, isXMLContent, xmlContentsOrFileName) { 
     
    // Load xsd file 
    if(isXSDContent) { 
    	docXSD = XML.Parser.parse(xsdContentOrFileName); 
    } else { 
		docXSD = XML.Parser.loadSynchronously(xsdContentOrFileName); 
	} 
	XSD.nsPrefix = docXSD.firstChild.prefix + ':'; 
	XSD.nsURI = docXSD.firstChild.namespaceURI; 
	 
	// Filter xsd file for the start node for rendering 
	porousXSD = XSD.Porous.ConvertXSD2GUISpecificXSD(docXSD, startNode); 
	 
	if(xmlContentsOrFileName!=null && xmlContentsOrFileName!='') { 
	     
		// Load data xml file 
		if(isXMLContent) { 
			docXML = XML.Parser.parse(xmlContentsOrFileName); 
		} else { 
			docXML = XML.Parser.loadSynchronously(xmlContentsOrFileName); 
		} 
     		 
		// Populate XML data to filtered XSD tree 
		XSD.XML.Unifier.populateXML2XSD(porousXSD, docXML); 
	} 
}; 
 
/** URL *****************************************************************************************/
URLEncoder = new Object();   // Empty definition of URL related methods 
URLDecoder = new Object();   // Empty definition of URL related methods 
 
/** Public method to encode/decode URL **********************************************************/ 
URLEncoder = new function() { 

	this.encode = function (string) { 
		var self = URL; 
		return escape(self._utf8_encode(string));
	}; 
 
	// private method for UTF-8 encoding
	this._utf8_encode = function (string) {
        string = string.replace(/\r\n/g,"\n");
        var utftext = "";

        for (var n = 0; n < string.length; n++) {

        	var c = string.charCodeAt(n);
			if (c < 128) {
            	utftext += String.fromCharCode(c);
            } else if((c > 127) && (c < 2048)) {
            	utftext += String.fromCharCode((c >> 6) | 192);
                utftext += String.fromCharCode((c & 63) | 128);
            } else {
            	utftext += String.fromCharCode((c >> 12) | 224);
                utftext += String.fromCharCode(((c >> 6) & 63) | 128);
                utftext += String.fromCharCode((c & 63) | 128);
            }
		}

        return utftext;
    }; 
}; 
	 
URLDecoder = new function() { 
      
    this.decode = function (string) { 
		var self = URL; 
		return self._utf8_decode(unescape(string));
	}; 
	 
    // private method for UTF-8 decoding
    this._utf8_decode = function (utftext) {
    	var string = "";
        var i = 0;
        var c = c1 = c2 = 0;

        while ( i < utftext.length ) {

        	c = utftext.charCodeAt(i);

        	if (c < 128) {
        		string += String.fromCharCode(c);
            	i++;
       		} else if((c > 191) && (c < 224)) {
        		c2 = utftext.charCodeAt(i+1);
            	string += String.fromCharCode(((c & 31) << 6) | (c2 & 63));
            	i += 2;
       		} else {
        		c2 = utftext.charCodeAt(i+1);
            	c3 = utftext.charCodeAt(i+2);
            	string += String.fromCharCode(((c & 15) << 12) | ((c2 & 63) << 6) | (c3 & 63));
            	i += 3;
       		}
		} 
    	return string;
	}; 
}; 