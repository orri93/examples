/*
                    +----------------------------------------------+
                    |             XSD2GUI Tree (v0.0)              |
                    |                                              |
                    | Developed by:                Umesh Batra     |
                    | Created:                     Aug. 05, 2007   |
                    | Tested on :                  Safari, Firefox |
                    +----------------------------------------------+ 
*/ 
 
 
XML.Parser = new function() { 
         
    /** Create a new Document object. If no arguments are specified, the document will be empty. If
        root tag is specified, the document will contain that single root tag. If the root tag has 
        namespace prefix, the second argument must specify the URL that identifies namespace **/  
       
	this.newDocument = function(rootTagName, namespaceURL) { 
         	 
    	if (!rootTagName) rootTagName = ''; 
    	if (!namespaceURL) namespaceURL = ''; 
    	 
    	loggerjs.debug('XML.Parser.newDocument(): root=' + rootTagName + ', ns=' + namespaceURL); 
    	 
    	if(isSF) { 
    		var prefix = ""; 
    		var tagname = rootTagName; 
    		var p = rootTagName.indexOf(':'); 
            if (p != -1) { 
            	prefix = rootTagName.substring(0, p); 
            	tagname = rootTagName.substring(p+1); 
            } 
            // If we have a namespace, we must have a namespace prefix 
            // If we don't have a namespace, we discard any prefix 
            if (namespaceURL) { 
            	if (!prefix) prefix = "a0";                                    // What Firefox uses 
            } 
            else prefix = ""; 
                          
    		var text = "<" + (prefix?(prefix+":"):"") +  tagname + 
            (namespaceURL ? (" xmlns:" + prefix + '="' + namespaceURL +'"') : "") + "/>"; 
            loggerjs.debug('XML.Parser.newDocument(): text='+ text); 
             
    		var url = "data:text/xml;charset=utf-8," + encodeURIComponent(text); 
    		loggerjs.debug('XML.Parser.newDocument(): url='+ url); 
    		 
    		try { 
    			
    			xmlParser = new DOMParser(); 
    			xmlDocument = xmlParser.parseFromString(text, 'text/xml'); 
    			loggerjs.debug('XML.Parser.newDocument(): xmlDocument='+ xmlDocument); 
                 		     		 
        		if(xmlDocument!=null) { 
    				return xmlDocument; 
        		} else { 
                                throw e;  
        		} 
        	} catch(e) { 
        		var xmlhttp = new XMLHttpRequest(); 
        		loggerjs.error('XML.Parser.newDocument(): Trying calling URL'); 
        		xmlhttp.open("GET", url, false); 
        		loggerjs.error('XML.Parser.newDocument(): URL called'); 
        		xmlhttp.send(null); 
        		loggerjs.error('XML.Parser.newDocument(): xmlhttp.responseXML='+xmlhttp.responseXML); 
        	} 
        } else if(isIE) {                                                     // This is the IE way  
        	// Create an empty document as an ActiveX object 
        	// If there is no root element, this is all we have to do 
        	var doc = new ActiveXObject("MSXML2.DOMDocument"); 
        	// If there is a root tag, initialize the document 
        	if (rootTagName) { 
            	var prefix = "";                                       // Look for namespace prefix 
            	var tagname = rootTagName; 
            	var p = rootTagName.indexOf(':'); 
            	if (p != -1) { 
                	prefix = rootTagName.substring(0, p); 
                	tagname = rootTagName.substring(p+1); 
            	} 
            	// If we have a namespace, we must have a namespace prefix 
            	// If we don't have a namespace, we discard any prefix 
            	if (namespaceURL) { 
                	if (!prefix) prefix = "a0";                                // What Firefox uses 
            	} 
            	else prefix = ""; 
            	// Create the root element (with optional namespace) as a 
            	// string of text 
            	var text = "<" + (prefix?(prefix+":"):"") +  tagname + 
                (namespaceURL ? (" xmlns:" + prefix + '="' + namespaceURL +'"') : "") + "/>"; 
            	doc.loadXML(text);                                     // parse into empty document 
        	} 
        } else if (document.implementation && document.implementation.createDocument) { 
        	return document.implementation.createDocument(namespaceURL, rootTagName, null); 
        } else { 
        	alert('XML operations not supported on this browser'); 
    	} 
        return doc; 
	}; 
  
    /** Synchronously load the XML document at the specified URL & return it as Document object **/ 
	this.loadSynchronously = function(url) { 
	    var self = XML.Parser; 
         
    	if(isIE || isFF) { 
    	    loggerjs.error("XML.parser.loadSynchronously(): newDocument"); 
    		// Create a new document with the previously defined function 
    		var xmldoc = self.newDocument(); 
    		xmldoc.async = false;                                    // Load synchronously 
    		xmldoc.load(url);                                        // Load and parse 
    		return xmldoc;                                           // Return the document 
    	} else { 
    	    loggerjs.error("XML.parser.loadSynchronously(): XMLHttpRequest"); 
    		var xmlhttp = new XMLHttpRequest(); 
        	xmlhttp.open("GET", url, false); 
        	xmlhttp.send(null); 
        	return xmlhttp.responseXML; 
    	} 
	}; 
 
    /** Asynchronously load and parse an XML document from the specified URL.  When the document is 
        ready, pass it to the specified callback function. This function returns immediately with 
        no return value. *************************************************************************/  
	this.LoadAsynchronously = function(url, callback) { 
	    var self = XML.Parser; 
	     
    	var xmldoc = self.newDocument(); 
    	// If we created the XML document using createDocument, use 
    	// onload to determine when it is loaded 
    	if (document.implementation && document.implementation.createDocument) { 
    	   	loggerjs.error("XML.parser.LoadAsynchronously(): document.implementation"); 
        	xmldoc.onload = function() { callback(xmldoc); }; 
    	} 
    	// Otherwise, use onreadystatechange as with XMLHttpRequest 
    	else { 
    	  	loggerjs.error("XML.parser.LoadAsynchronously(): xmldoc"); 
        	xmldoc.onreadystatechange = function() { 
            	if (xmldoc.readyState == 4) callback(xmldoc); 
        	}; 
    	} 
    	// Now go start the download and parsing 
    	xmldoc.load(url); 
	}; 
 
    /** Parse XML document contained in the string argument & return document object *************/  
	this.parse = function(text) { 
	    var self = XML.Parser; 
	     
    	if (typeof DOMParser != "undefined") { 
    		loggerjs.error("XML.parser.parse(): DOMParser"); 
        	// Mozilla, Firefox, and related browsers 
        	return (new DOMParser()).parseFromString(text, "application/xml"); 
    	} else if (typeof ActiveXObject != "undefined" && !isFF) { 
    	   	loggerjs.error("XML.parser.parse(): ActiveXObject"); 
        	// Internet Explorer. 
        	var doc = self.newDocument();                           // Create an empty document 
        	doc.loadXML(text);                                      // Parse text into it 
        	return doc;                                             // Return it 
    	} else { 
    	   	loggerjs.error("XML.parser.parse(): XMLHttpRequest"); 
        	// As a last resort, try loading the document from a data: URL 
        	var url = "data:text/xml;charset=utf-8," + encodeURIComponent(text); 
        	var xmlhttp = new XMLHttpRequest(); 
        	xmlhttp.open("GET", url, false); 
        	xmlhttp.send(null); 
        	return xmlhttp.responseXML; 
    	} 
	}; 
 
    /** Serializes a document or node of any DOM structure ***************************************/ 
	this.serialize = function(node) { 
	    var self = XML.Parser; 
	      
	    
	   /* if(node.nodeType==9) 
	    	 self.prettifyXMLDOM(self.newDocument(), node.firstChild, 0); 
	   else 
	    	 self.prettifyXMLDOM(self.newDocument(), node, 0); 
        */ 
         
    	if (typeof XMLSerializer != "undefined") { 
    		// loggerjs.error('XML.Parser.serialize() : XMLSerializer: node = ' + node.nodeName); 
        	return (new XMLSerializer()).serializeToString(node); 
        } 
    	else if (node.xml) { 
    		return node.xml; 
    	} 
    	else { 
    		throw "XML.serialize is not supported or can't serialize " + node; 
    	} 
	}; 
	 
	this.prettifyXMLDOM = function(doc, node, index) { 
	 	var self = XML.Parser; 
	 	 
	 	if(node.nodeType==1) { 
	 		loggerjs.debug(node.firstChild.nodeName); 
	 		node.appendChild(doc.createTextNode('\n')); 
	 	 
	 		for(var i = 0; i < index; i++) {  
	 			node.appendChild(doc.createTextNode(' ')); 
	 		} 
	 	} 
	 	  
	 	for (var i = 0; i < node.childNodes.length; i++) { 
           	if(node.childNodes[i].nodeType == 1 /* Node.ELEMENT_NODE */) { 
           		self.prettifyXMLDOM(doc, node.childNodes[i], index++); 
           	} 
        } 	 	
	} 
     
    /** Get specified attribute value of a node **************************************************/ 
	this.getAttribute = function(node, name) { 
    	var nodeAttributes = node.attributes; 
    	if(nodeAttributes!=null) { 
        	if( nodeAttributes.getNamedItem(name)!=null && 
        	    nodeAttributes.getNamedItem(name).value !=null) { 
        		// loggerjs.debug('\nXML.Parser.getAttribute(): name=' + name + ', value=' + 
        		// nodeAttributes.getNamedItem(name).value); 
        		return nodeAttributes.getNamedItem(name).value; 
        	} else if ( nodeAttributes.getNamedItem(name.toLowerCase())!=null && 
        	            nodeAttributes.getNamedItem(name.toLowerCase()).value !=null) { 
        		/* Checking for attributes in lower case since safari has a bug while seriaizing it 
        		   convers all the attribute names in lower case */ 
        		// loggerjs.debug('\nXML.Parser.getAttribute(): name=' + name + ', value=' + 
        		// nodeAttributes.getNamedItem(name.toLowerCase).value); 
        		return nodeAttributes.getNamedItem(name.toLowerCase()).value; 
        	} 
        } 
    }; 
     
    /** Set specified attribute value of a node **************************************************/ 
    this.setAttribute = function(node, doc, name, value) { 
    	 var self = XML.Parser; 
    	 // loggerjs.debug('\nXML.Parser.setAttribute(): doc='+ doc); 
    	  
    	if(value!=null) { 
    		// var newAttribute=doc.createAttribute(name); 
        	// newAttribute.nodeValue=value; 
        	// node.setAttributeNode(newAttribute); 
        	node.setAttribute(name, value); 
        } 
        return node; 
    }; 
     
    /** Get last child of specified node *********************************************************/ 
    this.get_lastchild = function(node) { 
		var lastNode = node.lastChild;
		while (lastNode.nodeType!=1) {
  			lastNode = lastNode.previousSibling;
  		}
		return lastNode;
	}
     
   /** Get element value of specified node *******************************************************/ 
   this.getElementValue = function(node) { 
    	var self = XML.Parser; 
    	 
		if( node != null) { 
			if (node.hasChildNodes()) { 
				for( var kid = node.firstChild; kid != null; kid = kid.nextSibling ) { 
					if( kid.nodeType == 3 /* Node.TEXT_NODE */  ) { 
						return self.cleanText(kid.nodeValue);
					} 
				} 
				return ''; 
			}
		}
 		return ''; 
	}; 
	 
   /** Checks if all the children are empty ******************************************************/ 
   this.IsChildrenEmpty = function(node) { 
    	var self = XML.Parser; 
    	isEmpty = true; 
    	 
    	self.checkIfAllChildsAreEmpty(node); 
    	 
    	return isEmpty; 
		
	}; 
	 
    this.checkIfAllChildsAreEmpty = function(node) { 							  // Private method
    	var self = XML.Parser; 
    	 
		if(self.getElementValue(node)!=='' && self.getElementValue(node)!=null) { 
			isEmpty = false; 
		} 
		 
		for (var i = 0; i < node.childNodes.length; i++) { 
           	if(node.childNodes[i].nodeType == 1 /* Node.ELEMENT_NODE */) { 
           		self.checkIfAllChildsAreEmpty(node.childNodes[i]); 
           	} 
        } 
	 }; 
	 
	this.cleanText = function(str) {                                              // Private method 
        var self = XSD.XML.Unifier; 
         
        if(!str || typeof str != 'string') 
        	return null; 
        else {          
        	var ret = str;
        	ret = ret.replace(/\n/g, ''); 
        	ret = ret.replace(/\r/g, ''); 
        	ret = ret.replace(/\x13/g,'');  // Hexadecimal value of return  
        	ret = ret.replace(/\x10/g,'');  // Hexadecimal value of linefeed  
        	ret = ret.replace(/\t/g, '');
        	ret = ret.replace(/\'/g, "\\'");
        	ret = ret.replace(/\[CDATA\[/g, '');
        	ret = ret.replace(/\]]/g, '');
        	ret = ret.replace(/^[\s]+/,''); 
        	ret = ret.replace(/[\s]+$/,''); 
        	// ret = ret.replace(/\x20/g,' ');  // Hexadecimal value of space 
        	ret = ret.replace(/\xA0/g,'');  // Hexadecimal of 160, safari is taking this character  
        	ret = ret.replace(/\f/g,'');    // form feed   

        	// loggerjs.debug('ret.length=<' + ret.length + '>, <' + APP.String2Ascii(ret) + '>'); 
        	
        	if(ret.length!=0) return ret; 
        	else return ''; 
        } 
    }; 
     
    this.removeNonAsciiCharacters = function(str) {           // Private method : Filter only ascii 
		var ascii = ''; 
		for(var x=0; x < str.length; x++) { 
			var chr = str.charAt(x); 
			if(isNaN(chr.charCodeAt(chr))) { 
				loggerjs.info('<' +chr + '> is NaN'); 
			} else { 
				loggerjs.info('<' +chr + '> is not NaN'); 
				ascii = ascii;  
			} 
		} 
		return ascii; 
	} 
	 
	/** get node at specified xPath **************************************************************/ 
	this.getNodeAtXPath = function(doc, xPath) { 
		var self = XML.Parser; 
		 
		var currentNode = doc.firstChild; 
		 
		 // loggerjs.debug('XML.Parser.getNodeAtXPath(): xPath = ' + xPath + ', doc = ' + 
		 // doc.firstChild.nodeName + 'doc\'s xPath = ' + self.getXPathOfNode(currentNode) ); 
	     
	    if(self.getXPathOfNode(currentNode) != xPath) { 
			splitXPath = xPath.split(XML.XPath.axis); 
			for(var i = 2; i < splitXPath.length; i++) { 
    			var currentNodeName = splitXPath[i].split(XML.XPath.AccessOperator.start)[0];     		 
    			var currentNodeIndex = splitXPath[i].split(
    				XML.XPath.AccessOperator.start)[1].split(XML.XPath.AccessOperator.end
    			)[0]; 
    		
    			var nodes = currentNode.getElementsByTagName(currentNodeName); 
    			 
    			 // loggerjs.debug( 'XML.Parser: currentNodeName = ' + currentNodeName + 
    			 //               ', \ncurrentNodeIndex = ' + currentNodeIndex + 
    			 //               ', \ncurrentNode = ' + currentNode.nodeName + 
    			 //               ', \nnodes.length = ' + nodes.length ); 
    			 
    			if(nodes!=null) { 
    				if(nodes[currentNodeIndex]) currentNode = nodes[currentNodeIndex]; 
    			} 
    		} 
    	} 
    		 
    	 // loggerjs.debug( 'XML.Parser.getNodeAtXPath(): currentNode xPath = ' + 
    	 //                self.getXPathOfNode(currentNode) + ', xPath= ' + xPath ); 
    	 
    	if(self.getXPathOfNode(currentNode) == xPath) { 
    		return currentNode; 
    	} else { 
    		return null; 
    	} 
    }; 
     
    /** get xPath at specified node **************************************************************/
    this.getXPathOfNode = function(node) { 
    	var self = XML.Parser; 
    	 
    	// loggerjs.debug('XML.Parser.getXPathOfNode : node = ' + node.nodeName); 
    	 
      	var path = ""; 
      	 
    	try { 
      	 
      		// loggerjs.debug('XML.Parser.getXPathOfNode : node= ' + node.nodeName); 
      	 
     		for (; node && node.nodeType == 1; node = node.parentNode) { 
   				idx = self.getNodeIndex(node); 
				xname = node.nodeName; 
				xname += "[" + idx + "]";
				path = "/" + xname + path; 
			} 
			 
     	} catch (e) { 
     		loggerjs.error('XML.Parser.getXPathOfNode() : ' + e); throw e; 
     	} 
         
        // loggerjs.debug('XML.Parser.getXPathOfNode : path = ' + path); 
     	return path;	
	}; 
     
    /** get relative sibling position of specified node ******************************************/
	this.getNodeIndex = function(currentNode) { 
		var self = XML.Parser; 
    	var count = 0; 
    	 
    	// loggerjs.debug('XML.Parser.getNodeIndex = ' + currentNode.nodeName); 
    	try { 
      	 
           for (var sibling = currentNode.previousSibling; 
           		    sibling; 
           		    sibling = sibling.previousSibling
           	) { 
    			// loggerjs.debug('XML.Parser.getNodeIndex = ' + sibling.nodeName); 
        		if(sibling.nodeType == 1 && sibling.nodeName == currentNode.nodeName)	count++; 
    		} 
    	} catch (e) { 
     		loggerjs.error('XML.Parser.getNodeIndex() : ' + e); throw e; 
     	} 
         
    	return count; 
	}; 
	 
	/** Return a clone of specified node *********************************************************/ 
    this.getClonedChild = function(node, docDOM, isCopyRecursive) { 
     	var self = XML.Parser; 
         
     	var clonedNode = null; 
     	 
     	var doc = docDOM; 
     	if( doc==null) doc = node.ownerDocument; 
     	 
     	if(doc.importNode) { 
     		// loggerjs.debug('XML.Parser.getClonedChild(): Safari fix, node = ' + node.nodeName ); 
			clonedNode = doc.importNode(node, isCopyRecursive); 
		} else { 
     		// loggerjs.debug('XML.Parser.getClonedChild(): Normal cloning, node = ' + node.nodeName); 
     		clonedNode = node.cloneNode(true); 
     	} 
     		 
     	return clonedNode;  
     }; 
	  
	this.getXPathArray = function(node, path) {                                   // Private method 
	    var self = XML.Parser; 
	     
        path = path || []; 
         
        if(node.parentNode) {
        	path = self.getXPathArray(node.parentNode, path);
        }

        if(node.previousSibling) {
        	var count = 1;
        	var sibling = node.previousSibling
        	do {
          		if(sibling.nodeType == 1 && sibling.nodeName == node.nodeName) {count++;}
          		sibling = sibling.previousSibling;
        	} while(sibling);
       		if(count == 1) {
       			count = null;
       		} 
        } else if(node.nextSibling) {
          	var sibling = node.nextSibling;
          	do {
            	if(sibling.nodeType == 1 && sibling.nodeName == node.nodeName) {
              		var count = 1;
              		sibling = null;
            	} else {
              		var count = null;
              		sibling = sibling.previousSibling;
            	}
       		} while(sibling);
        }

        if(node.nodeType == 1) { 
        	path.push( node.nodeName + 
        	           (node.id ? "[@id='"+node.id + "']" : count > 0 ? "[" + count + "]" : '')
        	         );
        } 
         
        return path; 
         
      };        
}; 
