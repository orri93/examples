/*
                                                   +----------------------------------------------+
                                                   |             XSD2GUI Tree (v0.0)              |
                                                   |                                              |
                                                   | Developed by:                Umesh Batra     |
                                                   | Created:                     Aug. 05, 2007   |
                                                   | Tested on :                  Safari, Firefox |
                                                   +----------------------------------------------+ 
*/ 
 
 
/** 
 * Reads the XSD and generates xml tree. 
 */  
XSD.Porous = new function() { 
	 
	this.xsdMaxOccursArray = new Array();                // Array containg all the nodes with maxOccurs attributes and GUI XML document as its last element 
	  
    /** Public method - XSD to GUI Specific XSD (XSD++) ***************************************************************************************************/ 
     
 	this.ConvertXSD2GUISpecificXSD = function(doc, startNodeName) { 

 		var self = XSD.Porous; 
 		 
 		/** Get first node of document passed *************************************************************************************************************/ 
 		var currentXSDNode = doc.firstChild; 
        loggerjs.info('\nXSD.Porous.ConvertXSD2XML(): currentXSDNode = ' + XML.Parser.serialize(currentXSDNode)); 
         
 		 
 		/** Create a new XSD document *********************************************************************************************************************/ 
 		loggerjs.debug('\n Prefix='+ XSD.nsPrefix + 'schema' + ', URI='+ XSD.nsURI); 
 		XSD.xsddoc = XML.Parser.newDocument(XSD.nsPrefix + 'schema', XSD.nsURI); 
 		loggerjs.debug('\n Trying fetching first child'); 
 		var newXSDNode = XSD.xsddoc.firstChild; 
        loggerjs.info('\nXSD.Porous.ConvertXSD2XML(): newXSDNode = ' + XML.Parser.serialize(newXSDNode)); 
         
 		 
 		/** Create xsd file to xml file, i.e. convert <name> attributes as tagnames instead of tagnames like xsd:complexType, xsd:element ..... 
 		    <xsd:element name="SAPDC" type="B2BSAPDC"/> would be converted to <SAPDC type="B2BSAPDC"/> ****************************************************/ 
        self.createSchemaTree(currentXSDNode, newXSDNode); 
        loggerjs.info('\nXSD.Porous.ConvertXSD2XML(): XSD.xsddoc = ' + XML.Parser.serialize(XSD.xsddoc)); 
         
         
        /** Select starting tag for further filteration ***************************************************************************************************/ 
        XSD.xmldoc = XML.Parser.newDocument(XSD.nsPrefix + startNodeName, XSD.nsURI); 
        var newXMLNode = XSD.xmldoc.firstChild; 
        loggerjs.info('\nXSD.Porous.ConvertXSD2XML(): newXSDNode = ' + XML.Parser.serialize(newXMLNode)); 
         
         
        var startNode = XSD.xsddoc.getElementsByTagName(startNodeName); 
        self.copyChildren(startNode[0], XSD.xmldoc.firstChild); 
        loggerjs.info('\nXSD.Porous.ConvertXSD2XML(): start node, XSD.xmldoc = ' + XML.Parser.serialize(XSD.xmldoc)); 
         
         
        /** Children from type declaration nodes would be attached to actual nodes ************************************************************************/ 
        self.porousTree(XSD.xmldoc); 
		loggerjs.info('\nXSD.Porous.ConvertXSD2XML(): porousTree, XSD.xmldoc = ' + XML.Parser.serialize(XSD.xmldoc)); 
		 
		 
		/** Nodes with attributes maxOccurs should not be rendered with children instead they would be rendered with button in front of it, Pressing this 
		    button would add the maxOccurs node along with its childrens; While generating the XML back from GUI the maxOccurs node with button would be 
		    ignored and array of its child would be added to its parent For the same purpose we will seperate out all such nodes and add them into global 
		    xsdMaxOccursArray for reference at the time of adding such nodes ******************************************************************************/ 
		self.filterMaxOccursNodes(XSD.xmldoc.firstChild); 
		loggerjs.info('\nXSD.Porous.ConvertXSD2XML(): filterMaxOccursNodes, XSD.xmldoc = ' + XML.Parser.serialize(XSD.xmldoc)); 
		 
		 
		/** Add the filtered document at last of xsdMaxOccursArray ****************************************************************************************/ 
		self.xsdMaxOccursArray[self.xsdMaxOccursArray.length] = XSD.xmldoc; 
		 
		 
		/** Remove children from all the maxOccurs nodes, Remember that all the parent documents in the array should not have children of nodes with 
		    maxoccurs attribute ***************************************************************************************************************************/  
		for(var i = 0; i < self.xsdMaxOccursArray.length; i++) { 
			self.removeMaxOccursNodes(self.xsdMaxOccursArray[i]); 
			loggerjs.info('\nXSD.Porous.ConvertXSD2XML(): removeMaxOccursNodes[' + i + '] : ' + XML.Parser.serialize(self.xsdMaxOccursArray[i])); 
		} 
		 		  
		return self.xsdMaxOccursArray; 
	}; 
	 
	this.createSchemaTree = function(node, newNode) {                                                                                     // Private method 
        var self = XSD.Porous; 
         
        var doc = newNode.ownerDocument; 
         
        if(XML.Parser.getAttribute(node, XSD.attribute.name.name)!=null) { 
        	var newElement = doc.createElement(XML.Parser.getAttribute(node, XSD.attribute.name.name)); 
        	 
        	newElement = XML.Parser.setAttribute(newElement, doc, XSD.attribute.name.type, XML.Parser.getAttribute(node, XSD.attribute.name.type)); 
        	newElement = XML.Parser.setAttribute(newElement, doc, XSD.attribute.name.maxOccurs, XML.Parser.getAttribute(node, XSD.attribute.name.maxOccurs));  
        	newElement = XML.Parser.setAttribute(newElement, doc, XSD.attribute.name.minOccurs, XML.Parser.getAttribute(node, XSD.attribute.name.minOccurs)); 
        	newElement = XML.Parser.setAttribute(newElement, doc, XSD.attribute.name.nlchar, XML.Parser.getAttribute(node, XSD.attribute.name.nlchar)); 
        	newElement = XML.Parser.setAttribute(newElement, doc, XSD.attribute.name.nillable, XML.Parser.getAttribute(node, XSD.attribute.name.nillable)); 
        	newElement = XML.Parser.setAttribute(newElement, doc, XSD.attribute.name.values, XML.Parser.getAttribute(node, XSD.attribute.name.values)); 
        	newElement = XML.Parser.setAttribute(newElement, doc, XSD.attribute.name.isAttribute, node.nodeName); 
			 
        	newNode.appendChild(newElement); 
        	newNode = newElement; 
        } 
 
        for (var i = 0; i < node.childNodes.length; i++) { 
           	if(node.childNodes[i].nodeType == 1 /* Node.ELEMENT_NODE */) { 
           		self.createSchemaTree(node.childNodes[i], newNode); 
           	} 
        } 
        newNode = newNode.parentNode; 
    }; 
     
    this.porousTree = function(node) {                                                                                                    // Private method 
        var self = XSD.Porous; 
         
        if( XML.Parser.getAttribute(node, XSD.attribute.name.type)!=null && 
            XML.Parser.getAttribute(node, XSD.attribute.name.type)!=XSD.nsPrefix + XSD.attribute.type.value.string && 
            XML.Parser.getAttribute(node, XSD.attribute.name.type)!=XSD.nsPrefix + XSD.attribute.type.value.bBoolean) { 
            	// alert(node.nodeName+', ' + XML.Parser.getAttribute(node, XSD.attribute.name.type)); 
            	node = self.addChildsFromTypeDeclarativeNode(node); 
        } 
          
        for (var i = 0; i < node.childNodes.length; i++) { 
           	if(node.childNodes[i].nodeType == 1 /* Node.ELEMENT_NODE */) { 
           		self.porousTree(node.childNodes[i]); 
           	} 
        } 
    }; 
     
    this.filterMaxOccursNodes = function(node) {                                                                                         // Private method 
        var self = XSD.Porous; 
         
        var doc = node.ownerDocument; 
         
        if( XML.Parser.getAttribute(node, XSD.attribute.name.maxOccurs)!=null) { 
            	// loggerjs.debug('XML.Porous.filterMaxOccursNodes() : maxOccurs node' + node.nodeName); 
            	 
            	// Add the maxOccurs to maxOccursArray
            	var newElement = doc.createElement(node.nodeName); 
            	newElement = XML.Parser.setAttribute(newElement, doc, XSD.attribute.name.type, XML.Parser.getAttribute(node, XSD.attribute.name.type)); 
            	 
            	// loggerjs.warning('Before copying : node.nodeName=' + node.nodeName + ', newElement.nodeName=' + newElement.nodeName); 
            	newElement = self.copyChildren(node, newElement); 
                 
            	self.xsdMaxOccursArray[self.xsdMaxOccursArray.length] = newElement; 
        		// loggerjs.warning('After copying : node.nodeName=' + node.nodeName + ', newElement.nodeName=' + newElement.nodeName); 
        } 
          
        for (var i = 0; i < node.childNodes.length; i++) { 
           	if(node.childNodes[i].nodeType == 1 /* Node.ELEMENT_NODE */) { 
           		self.filterMaxOccursNodes(node.childNodes[i]); 
           	} 
        } 
    }; 
     
    this.removeMaxOccursNodes = function(node) {                                                                                         // Private method 
        var self = XSD.Porous; 
         
       if( XML.Parser.getAttribute(node, XSD.attribute.name.maxOccurs)!=null) { 
            	// loggerjs.debug('XML.Porous.removeMaxOccursNodes() : maxOccurs node' + node.nodeName); 
            	 
            	// Remove childrens from the original node 
            	self.removeChildren(node); 
        		// alert('node.nodeName=' + node.nodeName); 
        } 
          
        for (var i = 0; i < node.childNodes.length; i++) { 
           	if(node.childNodes[i].nodeType == 1 /* Node.ELEMENT_NODE */) { 
           		self.removeMaxOccursNodes(node.childNodes[i]); 
           	} 
        } 
    }; 
     
    this.addChildsFromTypeDeclarativeNode = function(node) {                                                                             // Private method 
    	var self = XSD.Porous; 
    	 
    	var doc = node.ownerDocument; 
             	     	 
    	var typeNodes = XSD.xsddoc.getElementsByTagName(XML.Parser.getAttribute(node, XSD.attribute.name.type)); 
    	// loggerjs.debug('\n XSD.Porous.addChildsFromTypeDeclarativeNode(): node = ' + node.nodeName + ', typeNodes = ' + typeNodes.length); 
    	 
        for(var i = 0; i<typeNodes.length; i++) { 
             
        	if(typeNodes[i].hasChildNodes()) { 
        	     
           		for(var j = 0; j< typeNodes[i].childNodes.length; j++) { 
           		     
           			var clonedNode = XML.Parser.getClonedChild(typeNodes[i].childNodes[j], doc, true); 
           			node.appendChild(clonedNode); 
           			 
           		} 
           		break; 
           		 
            } 
             
       	} 
        
        // loggerjs.debug('\n'+XML.Parser.serialize(node)); 
       	return node; 
    }; 
     
    this.copyChildren = function(sourceNode, targetNode) {                                                                               // Private method 
    	var self = XSD.Porous; 
		     	 
    	var doc = targetNode.ownerDocument; 
    	 
        for(var j = 0; j< sourceNode.childNodes.length; j++) { 
             
            var clonedNode = XML.Parser.getClonedChild(sourceNode.childNodes[j], doc, true); 
            var nextSiblingOfSourceNode = self.getNextSibling(sourceNode); 
             
            // loggerjs.error(targetNode.nodeName + ', ' + nextSiblingOfSourceNode); 
             
            if(nextSiblingOfSourceNode!=null) { 
            	if(targetNode.getElementsByTagName(nextSiblingOfSourceNode.nodeName)[0]!=null) {  
           			doc.documentElement.insertBefore(clonedNode, nextSiblingOfSourceNode); 
           		} else { 
           			targetNode.appendChild(clonedNode); 
           		} 
           	} else { 
           		targetNode.appendChild(clonedNode); 
           	} 
        } 
        
        // loggerjs.info('\n'+XML.Parser.serialize(targetNode)); 
       	return targetNode; 
    }; 
     
    this.removeChildren = function(element) {                                                                                            // Private method 
    	var self = XSD.Porous; 
         
        while(element.hasChildNodes()) {  
             
           	if(element.childNodes[0]!=null) { 
           	     
           		element.removeChild(element.childNodes[0]); 
           		 
           	} 
           	 
        } 
         
        // loggerjs.debug('\n'+XML.Parser.serialize(targetNode)); 
    }; 
     
    /** Public method - Reverse process GUI Specific XSD (XML * XSD++) to XML ****************************************************************************/ 
     
    this.convertGUISpecificXSD2XML = function(porousXSD, startNode) { 
    	var self = XSD.Porous; 
         
        var finalDoc = XML.Parser.newDocument(XSD.nsPrefix + startNode, XSD.nsURI); 
   		loggerjs.info('\nXSD.Porous.convertPorousXSD2XML(): XML = ' + XML.Parser.serialize(finalDoc)); 
         
        self.copyChildren(porousXSD[porousXSD.length-1].firstChild, finalDoc.firstChild); 
        
        self.linkMaxOccursBack2ParentNode(finalDoc.firstChild); 
		 
 		self.removeNodeAttributes(finalDoc.firstChild); 
 		 
 		self.removeEmptyNodes(finalDoc.firstChild); 
 		 
 		loggerjs.info('\nXSD.Porous.convertPorousXSD2XML(): Final XML = ' + XML.Parser.serialize(finalDoc)); 
 		 
 		return XML.Parser.serialize(finalDoc); 
         
    }; 
     
    this.linkMaxOccursBack2ParentNode = function(node) {                                                                                 // Private method 
    	var self = XSD.Porous; 
         
        if( XML.Parser.getAttribute(node, XSD.attribute.name.maxOccurs)!=null) { 
        	self.copyChildren(node, node.parentNode); 
        	node.parentNode.removeChild(node); 
        } 
         
        for (var i = 0; i < node.childNodes.length; i++) { 
           	if(node.childNodes[i].nodeType == 1 /* Node.ELEMENT_NODE */) { 
           		self.linkMaxOccursBack2ParentNode(node.childNodes[i]); 
           	} 
        } 
    }; 
     
    this.removeNodeAttributes = function(node) {                                                                                         // Private method 
    	var self = XSD.Porous; 
         
       	// var attributesList = ''; 
       	// loggerjs.debug(node.attributes.length); 
       	 
   		while(node.attributes.length!=0) { 
       			// attributesList = attributesList + node.attributes.item(0).name + ', '; 
       			 
       			// If the XSD node type is attribute, remove it as a child and append it as a attribute of parent node 
       			if(XSD.attribute.type.value.IsAttribute(node.attributes.item(0).value)) { 
	       			loggerjs.error('node.attributes.item(0).value = ' + node.attributes.item(0).value + ', node.parentNode = ' + node.parentNode.nodeName + ', node.nodeName = ' + node.nodeName + ', node.nodeValue = ' + XML.Parser.getElementValue(node)); 
					parentNode = XML.Parser.setAttribute(node.parentNode, node.ownerDocument, node.nodeName, XML.Parser.getElementValue(node)); 
					previousSiblingNode = node.previousSibling; 
					node.parentNode.removeChild(node); 
					node = previousSiblingNode; 
				} else { 
      				node.removeAttribute(node.attributes.item(0).name); 
      			} 
       	} 

        for (var i = 0; i < node.childNodes.length; i++) { 
           	if(node.childNodes[i].nodeType == 1 /* Node.ELEMENT_NODE */) { 
           		self.removeNodeAttributes(node.childNodes[i]); 
           	} 
        } 
         
    }; 
     
    this.removeEmptyNodes = function(node) {                                                                                            // Private method 
    	var self = XSD.Porous; 
    	 
    	// loggerjs.debug('----- ' + node.nodeName + ', XML.Parser.IsChildrenEmpty(node) = ' + XML.Parser.IsChildrenEmpty(node)); 
    	 
    	if (XML.Parser.IsChildrenEmpty(node)) { 
    		var parent = node.parentNode; 
			var node1 = parent.removeChild(node); 
			node = parent; 
		} 
       	 
    	for (var i = 0; i < node.childNodes.length; i++) { 
           	if(node.childNodes[i].nodeType == 1 /* Node.ELEMENT_NODE */) { 
           		self.removeEmptyNodes(node.childNodes[i]); 
           	} 
        } 
    }; 
     
    this.getNextSibling = function(n) { 
		var self = XSD.Porous; 
		 
		if(n.nextSibling!=null)  
			x = n.nextSibling; 
		else 
			return null; 
		 
		while (x.nodeType!=1) { 
  			x = x.nextSibling; 
  		} 
  		 
  		return x; 
	}; 
}; 