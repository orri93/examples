/*
                                                                    +----------------------------------------------+
                                                                    |             XSD2GUI Tree (v0.0)              |
                                                                    |                                              |
                                                                    | Developed by:                Umesh Batra     |
                                                                    | Created:                     Aug. 05, 2007   |
                                                                    | Tested on :                  Safari, Firefox |
                                                                    +----------------------------------------------+ 
*/ 
 
 
XSD.XML.Unifier = new function() { 
    
    /** Public method - Populate XML data in to GUI specific XSD (i.e. outputs XML * XSD++) ***********************************************************************************************/
     	  	
 	this.populateXML2XSD = function(porousXSD, docXML) { 
 		var self = XSD.XML.Unifier; 
 		 
 		var xsdNode = porousXSD[porousXSD.length-1].firstChild; 
 		var xmlNode = docXML.firstChild; 
 		 
 		// loggerjs.debug('\nXSD.XML.Unifier.populateXML2XSD(): xsdNode=' + xsdNode.nodeName + ', \nxmlNode = ' +xmlNode.nodeName ); 
 		loggerjs.info('\nXSD.XML.Unifier.populateXML2XSD(): xmlDocument : ' + XML.Parser.serialize(docXML)); 
 		 
 		self.mergeXML2XSD(xmlNode, xsdNode); 
 		 
 		loggerjs.info('\nXSD.XML.Unifier.populateXML2XSD(): xsdGUIDocument : ' + XML.Parser.serialize(porousXSD[porousXSD.length-1])); 
    	 
    	// loggerjs.debug('\nXSD.XML.Unifier.populateXML2XSD(): ' + porousXSD); 
	}; 
 
	this.mergeXML2XSD = function(xmlNode, xsdNode) {                                                                                                                      // Private method 
 		var self = XSD.XML.Unifier; 
 		 
 		var doc = xsdNode.ownerDocument; 
 		 
 		loggerjs.debug( '\nXSD.XML.Unifier.mergeXML2XSD(): xsdNode = ' + xsdNode.nodeName + ', \nxmlNode = ' + xmlNode.nodeName + 
 		               ', \nxmlNodeType = ' + xmlNode.nodeType + ', xmlNode\'s current value = <' + XML.Parser.getElementValue(xmlNode) + '>'); 
 		 
 		// Append all the attributes as its child to be displayed as a GUI element 
 		for(var i=0; i < xmlNode.attributes.length; i++) { 
 			 
 			var currAttr = xmlNode.attributes[i]; 
 			attributeName = currAttr.nodeName; 
 			attributeValue = XML.Parser.getElementValue(currAttr); 
          	 
          	loggerjs.info('\nXSD.XML.Unifier.mergeXML2XSD(): attributeName = ' + attributeName + ', attributeValue = ' + attributeValue); 
          	 
          	var newElement = doc.createElement(attributeName); 
          	var newTextNode = doc.createTextNode(attributeValue); 
          	newElement.appendChild(newTextNode); 
          	xmlNode.appendChild(newElement); 
        } 
 		 
 		if(XML.Parser.getElementValue(xmlNode)!=null && XML.Parser.getElementValue(xmlNode)!='') { 
 		     
 			var currentXMLNodeXPath = self.getGUISpecificXPath(xmlNode, porousXSD); 
 			 
 			var currentXSDNode = XML.Parser.getNodeAtXPath(doc, currentXMLNodeXPath); 
 			if(currentXSDNode!=null) {  			 
 				var newTextNode=doc.createTextNode(XML.Parser.getElementValue(xmlNode)); 
 				currentXSDNode.appendChild(newTextNode); 
 			  
 				loggerjs.info('\nXSD.XML.Unifier.mergeXML2XSD(): currentXSDNode = ' + currentXSDNode.nodeName + ', \nhas been set value as = ' + XML.Parser.getElementValue(xmlNode)); 
 				 
 			} else { 
 			 	
 			    /** If xPath is a maxOccurs node append GUI specific duplicate maxOccurs child to show button in front of it 
 			        e.g. XML xPath /xsd:AppleGroupTPA[0]/AdditionalRouting[1] would appear as /xsd:AppleGroupTPA[0]/AdditionalRouting[0]/AdditionalRouting[1] in XSD xPath ****************/ 
 				 
 				loggerjs.info('\nXSD.XML.Unifier.mergeXML2XSD(): currentXMLNodeXPath = ' + currentXMLNodeXPath + ', currentXSDNode is null, Appending duplicate node as its own parent'); 
 				 
 				var splitCurrentXMLNodeXPath = currentXMLNodeXPath.split('/'); 
 				 
 				var guiParentNodeXPath = ''; 
 				var guiCurrentNodeXPath = ''; 
 				var currentXSDNode = new Object(); 
 				 
 				// This is to prevent rendering attribute xmlns of the root element 
 				if(splitCurrentXMLNodeXPath.length-2 > 1) { 
 					for( var i = splitCurrentXMLNodeXPath.length-2; i > 0; i--) { 
 					 
 						var tempNode = splitCurrentXMLNodeXPath[i].split('[')[0]; 
 						if(APP.isMaxOccursNode(tempNode, porousXSD)) { 
 						 
 							loggerjs.info('XSD.XML.Unifier.mergeXML2XSD: splitCurrentXMLNodeXPath[i] = '+ splitCurrentXMLNodeXPath[i] + ' is a max occurs node'); 
 							var currentXMLNodeXPathArray = currentXMLNodeXPath.split(splitCurrentXMLNodeXPath[i]); 
 						 
 							guiParentNodeXPath = currentXMLNodeXPathArray[0] + tempNode + '[0]'; 
 							guiCurrentNodeXPath = currentXMLNodeXPathArray[0] + tempNode + '[0]/' + splitCurrentXMLNodeXPath[i] + currentXMLNodeXPathArray[1]; 
 							loggerjs.info('XSD.XML.Unifier.mergeXML2XSD : guiParentNodeXPath = ' + guiParentNodeXPath + ', guiCurrentNodeXPath = ' + guiCurrentNodeXPath); 
 						 
 							currentXSDNode = XML.Parser.getNodeAtXPath(doc, guiCurrentNodeXPath); 
 							loggerjs.info('XSD.XML.Unifier.mergeXML2XSD : guiParentNodeXPath = ' + guiParentNodeXPath + ', guiCurrentNodeXPath = ' + guiCurrentNodeXPath + ', currentXSDNode = ' + currentXSDNode ); 
 						 
 							if(currentXSDNode==null) { 
 								var where2Add = XML.Parser.getNodeAtXPath(doc, guiParentNodeXPath ); 
								loggerjs.info('where2Add = '+ where2Add.nodeName); 
					 
								var node2Add = APP.getMaxOccursNode(tempNode, porousXSD); 
								loggerjs.info('node2Add = '+ node2Add.nodeName); 
					 
								var cloneOfNode2Add = XML.Parser.getClonedChild(node2Add, doc, true); 
								loggerjs.info('clonedOfNode2Add = '+ cloneOfNode2Add.nodeName); 
					 
								where2Add.appendChild(cloneOfNode2Add); 
								loggerjs.info(cloneOfNode2Add.nodeName + ' Added' ); 
							 
								loggerjs.info('Doc after adjustment of = ' + cloneOfNode2Add.nodeName + ', ' + XML.Parser.serialize(cloneOfNode2Add)); 
 								loggerjs.info('Doc after adjustment = ' + XML.Parser.serialize(xsdNode)); 
 							} 
 							break; 
 						} 
 					} 
 				 
					// Populate value from XML file 
					var newTextNode=doc.createTextNode(XML.Parser.getElementValue(xmlNode)); 
 					currentXSDNode = XML.Parser.getNodeAtXPath(doc, guiCurrentNodeXPath); 
 					currentXSDNode.appendChild(newTextNode); 
 				} 
 			} 
 		} 
         
        for (var i = 0; i < xmlNode.childNodes.length; i++) { 
           	if(xmlNode.childNodes[i].nodeType == 1 /* Node.ELEMENT_NODE */) { 
           		self.mergeXML2XSD(xmlNode.childNodes[i], xsdNode); 
           	} 
        } 
    }; 
     
    this.getGUISpecificXPath = function(node, porousXSD) {                                                                                                                 // Private method 
    	var self = XSD.XML.Unifier;  
    	 
    	// loggerjs.debug('XSD.XML.Unifier.getGUISpecificXPath : node = ' + node.nodeName + ', porousXSD = ' + porousXSD.length ); 
    	 
      	var path = ""; 
      	 
      	// Get the document 
		var doc = porousXSD[porousXSD.length-1]; 
      	 
    	try { 
      	       	 
     		for (; node && node.nodeType == 1; node = node.parentNode) { 
     		 
   				idx = self.getGUINodeIndex(node); 
				xname = node.nodeName; 
				 
				xname += "[" + idx + "]"; 
				path = "/" + xname + path; 
				 
			} 
			 
     	} catch (e) { 
     		loggerjs.error('XSD.XML.Unifier.getGUISpecificXPath() : ' + e); throw e; 
     	} 
         
        // loggerjs.debug('self.getGUISpecificXPath : path = ' + path); 
     	return path; 
	}; 
     
	this.getGUINodeIndex = function(currentNode) {                                                                                                                         // Private method 
		var self = XSD.XML.Unifier; 
    	var count = 0; 
    	 
    	// loggerjs.debug(XSD.XML.Unifier.getGUINodeIndex = ' + currentNode.nodeName); 
    	try { 
      	 
    		for (var sibling = currentNode.previousSibling; sibling; sibling = sibling.previousSibling) { 
    			// loggerjs.debug('XML.Parser.getNodeIndex = ' + sibling.nodeName); 
        		if(sibling.nodeType == 1 && sibling.nodeName == currentNode.nodeName)	count++; 
    		} 
    	} catch (e) { 
     		loggerjs.error('XSD.XML.Unifier.getGUINodeIndex() : ' + e); throw e; 
     	} 
         
    	return count; 
	}; 
}; 