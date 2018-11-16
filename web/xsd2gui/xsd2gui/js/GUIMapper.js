/*
                    +----------------------------------------------+
                    |             XSD2GUI Tree (v0.0)              |
                    |                                              |
                    | Developed by:                Umesh Batra     |
                    | Created:                     Aug. 05, 2007   |
                    | Tested on :                  Safari, Firefox |
                    +----------------------------------------------+ 
*/ 
 
 
GUI.Mapper = new function() { 
          
    /** Takes XML * XSD++ DOM and generate GUI++ user defined object for rendering it on browser */ 
 	this.createGUITree = function(porousXSD, treeGUI, xsdDocName, xmlDocName) { 
 		var self = GUI.Mapper; 
  			
  		/** Initialize class variables ***********************************************************/ 
  		self.arrayOfNodePrefix = new Array(); 
 		self.indexForArrayOfNodePrefix = 0; 
          		 
		/** Initialize tree GUI array ************************************************************/ 
		treeGUI.nodes = new Array(); 
         		 
		/** Populate tree GUI array from porousXSD, 
		    Arguments are GUITree, Document2Render, GUITreeindex, DocumentTreeCurrentNodeIndex, 
		    (string) nameOfPorousedXSDDoc (should be global scope), (string) nameOfDataXMLDoc 
		    (should be global scope) 
		******************************************************************************************/ 
		self.MAP2GUI( treeGUI, 
		              porousXSD[porousXSD.length-1].firstChild, 
		              0, 
		              0, 
		              false, 
		              '', 
		              xsdDocName, 
		              xmlDocName 
		            ); 
			 
		/** Render GUI array on treeGUI container already build on browser body ******************/ 
		treeGUI.create(); 
		 
	}; 
	 
	this.MAP2GUI = function ( treeGUI, 
	                          node, 
	                          indexGUI, 
	                          indexChild, 
	                          showChildIndex, 
	                          cordinates, 
	                          xsdDocName, 
	                          xmlDocName) {                                       // Private method 
	                          
        var self = GUI.Mapper; 
         
        /** Set the element position in GUI tree *************************************************/ 
         
        indexGUI++; 
        cordinates = cordinates + (indexChild + 1) + ',' ; 
         
        /** Get xPath for assigning it to element names ******************************************/ 
         
        var maxOccursFrequency = 
        	(node!=null && XML.Parser.getAttribute(node, XSD.attribute.name.maxOccurs)!=null) ? 
        	XML.Parser.getAttribute(node, XSD.attribute.name.maxOccurs) : null; 
        	 
        var dataType = 
        	(node!=null && XML.Parser.getAttribute(node, XSD.attribute.name.type)!=null) ? 
        	XML.Parser.getAttribute(node, XSD.attribute.name.type) : null; 
        	 
        var nlchar = (node!=null && 
                           XML.Parser.getAttribute(node, XSD.attribute.name.nlchar)!=null) ? 
        	               XML.Parser.getAttribute(node, XSD.attribute.name.nlchar) : null; 
        	                
        var values = (node!=null && nlchar==null && 
                           XML.Parser.getAttribute(node, XSD.attribute.name.values)!=null) ? 
        	               XML.Parser.getAttribute(node, XSD.attribute.name.values) : null; 
        	                
        var nillable = (node!=null && 
                           XML.Parser.getAttribute(node, XSD.attribute.name.nillable)!=null) ? 
        	               XML.Parser.getAttribute(node, XSD.attribute.name.nillable) : null; 
        	                
        var isAttribute = (node!=null && 
                           XML.Parser.getAttribute(node, XSD.attribute.name.isAttribute)!=null) ? 
        	               XML.Parser.getAttribute(node, XSD.attribute.name.isAttribute) : null; 
                  
        var text = '', element1 = '', element2 = '', href = '', argument = ''; 
         
        xPath = XML.Parser.getXPathOfNode(node); 
         
        argument = "this, \'" + node.nodeName + "\', " +  
                   node.childNodes.length + ", " + 
                   "\'" + maxOccursFrequency + "\', " + 
                   "\'" + dataType + "\', "+ 
                   "\'" + nlchar + "\', "+ 
                   "\'" + isAttribute + "\', "+ 
                   "\'" + xPath + "\', " + 
                   "\'" + cordinates + "\', " + 
                   xsdDocName + "," + xmlDocName; 
                    
        argument = argument.replace(/\'/g,'\''); 
                                    
        /** Map the node to GUI ******************************************************************/ 
                           
        if(node!=null) { 
         
        	if(XML.Parser.getAttribute(node, XSD.attribute.name.maxOccurs)!=null) { 
        	     
        	    // loggerjs.debug('Max occurs frequency=' 
        	    //                  + XML.Parser.getAttribute(node, XSD.attribute.name.maxOccurs)); 
        	                         
  				text = node.nodeName; 
        		element1 = '<input type=button value=add name=button' + xPath + 
        		           ' onclick="GUI.Mapper.addNode('+ argument + '); ' + 
        		           ' treeGUI.jumpTo('+ cordinates.substr(0, cordinates.length-1) +'); ' + 
        		           ' ">'; 
        		element2 = ' '; 
        		showChildIndex = true; 
        		 
        	} else if ( dataType!=null && 
        	            ( 
        	            	XSD.attribute.type.value.Text(dataType) || 
        	          		XSD.attribute.type.value.Integer(dataType) || 
        	          		XSD.attribute.type.value.Float(dataType)  
        	          	) 
        	) { 
        	     
        	    textWithIndex = node.nodeName + indexChild; 
        	    textWithoutIndex = node.nodeName;  
        	    text = (showChildIndex) ? textWithIndex : textWithoutIndex; 
        		element1 = ' '; 
        		if(nlchar!=null) { 
					element2 =  '<textarea name=text' + xPath + ' cols="15" rows="2" style="background-color: #f7f7f7; overflow:hidden;"' + 
        		           		' onchange="GUI.Mapper.updateNode('+ argument + '); ' + 
        		           		' treeGUI.jumpTo('+ cordinates.substr(0, cordinates.length-1) + '); ' + 
        		           		'">' + (XML.Parser.getElementValue(node)==null?"":XML.Parser.getElementValue(node).replace(new RegExp (nlchar, "g"), "\n")) + '</textarea>'; 
        		} else { 
        			element2 =  '&nbsp;<input type=text name=text' + xPath + ' size=29 ' + 
        		           		' onchange="GUI.Mapper.updateNode('+ argument + '); ' + 
        		           		' treeGUI.jumpTo('+ cordinates.substr(0, cordinates.length-1) + '); ' + 
        		           		' " value="' + (XML.Parser.getElementValue(node)==null?"":XML.Parser.getElementValue(node)) + 
        		           		'"></input>'; 
        		} 
        		            
        	} else if ( XML.Parser.getAttribute(node, XSD.attribute.name.type)!=null && 
        	            XML.Parser.getAttribute(node, XSD.attribute.name.type) == 
        	            XSD.nsPrefix + XSD.attribute.type.value.bBoolean
        	) { 
        	     
        	    textWithIndex = node.nodeName + indexChild; 
        	    textWithoutIndex = node.nodeName; 
        	    text = (showChildIndex) ? textWithIndex : textWithoutIndex; 
        		element1 = ' '; 
        		element2 = '&nbsp;<select name=select' + xPath + ' ' + 
        		            ' onchange="GUI.Mapper.updateNode('+ argument + '); ' + 
        		            ' treeGUI.jumpTo('+ cordinates.substr(0, cordinates.length-1) + ');">'; 
        		             
        		if (nillable!=null && nillable=="false") { 
        		} else { 
        			element2 = element2 + ' <option value=""> </option>'; 
        		} 
        		            ((XML.Parser.getElementValue(node)!=null && XML.Parser.getElementValue(node)=='true') ? '<option value=true selected>true</option>' : '<option value=true>true</option>') + 
        		            ((XML.Parser.getElementValue(node)!=null && XML.Parser.getElementValue(node)=='false') ? '<option value=false selected>false</option>': '<option value=false>false</option>') + 
        		           '</select>'; 
        	} else if ( XML.Parser.getAttribute(node, XSD.attribute.name.type)!=null && 
        	            XML.Parser.getAttribute(node, XSD.attribute.name.type) == 
        	            XSD.nsPrefix + XSD.attribute.type.value.enumeration 
        	) { 
        	     
        	    textWithIndex = node.nodeName + indexChild; 
        	    textWithoutIndex = node.nodeName; 
        	    text = (showChildIndex) ? textWithIndex : textWithoutIndex; 
        		element1 = ' '; 
        		element2 = '&nbsp;<select name=select' + xPath + ' ' + 
        		            ' onchange="GUI.Mapper.updateNode('+ argument + '); ' + 
        		            ' treeGUI.jumpTo('+ cordinates.substr(0, cordinates.length-1) + ');">';  
        		             
        		if (nillable!=null && nillable=="false") { 
        		} else { 
        			element2 = element2 + ' <option value=""> </option>'; 
        		} 
        		             
        		var valuesArray = values.split('^^^^^'); 
        		for(var i=0; i<valuesArray.length; i++) { 
        			element2 = element2 + ((XML.Parser.getElementValue(node)!=null && XML.Parser.getElementValue(node)==valuesArray[i]) ? '<option value="'+ valuesArray[i] + '" selected>' + valuesArray[i] + ' </option>' : '<option value="' + valuesArray[i] + '">' + valuesArray[i] + '</option>'); 
        		} 
        		 
        		element2 = element2 + '</select>'; 
        		 
        	} else { 
        	     
        	    textWithIndex = node.nodeName + indexChild; 
        	    textWithoutIndex = node.nodeName; 
        	    text = (showChildIndex) ? textWithIndex : textWithoutIndex; 
        	    
        	    element1 = (showChildIndex) ? '<input type=button value=delete name=button' + xPath + 
        		           ' onclick="GUI.Mapper.deleteNode('+ argument + '); ' + 
        		           ' treeGUI.jumpTo('+ cordinates.substr(0, cordinates.length-3) +'); ' + 
        		           ' ">' : '';  
        	    element2 = ''; 
        	 	showChildIndex = false; 
        	 	 
        	} 
        	 
        } 
         
        // href = 'alert("' + argument + '");'; 
         
        // loggerjs.debug('GUI.Mapper.createGUITree(): XSD.nsPrefix=' + XSD.nsPrefix + ', node.type=' + 
        //              XML.Parser.getAttribute(node, XSD.attribute.name.type) + ', indexGUI=' + 
        //              indexGUI + ', text='+ text + ', element1=' + element1 + ', element2=' + 
        //              element2 + ', href=' + href); 
                         
        /** GUI node should have (level, text, [URL], [target], [JavaScript]) ********************/
        treeGUI.addNode(indexGUI, XML.Parser.cleanText(text, 45), element1, element2, '', '', href); 
         
         
        /** Recurse the function for all child ***************************************************/ 
        for (var i = 0; i < node.childNodes.length; i++) { 
           	if(node.childNodes[i].nodeType == 1 /* Node.ELEMENT_NODE */) { 
           		self.MAP2GUI ( treeGUI, 
           		               node.childNodes[i], 
           		               indexGUI, 
           		               i, 
           		               showChildIndex, 
           		               cordinates, 
           		               xsdDocName, 
           		               xmlDocName
           		             ); 
           	} 
        } 
         
        indexGUI--; 
    }; 
     
    /** Get called when add button is pressed ****************************************************/ 
    this.addNode = function( guiElement, 
                             nodeName, 
                             childIndex, 
                             maxOccursFrequency, 
                             dataType, 
                             nlchar, 
                             isAttribute, 
                             xPath, 
                             cordinates, 
                             porousXSD, 
                             xmlDocName
    ) { 
        var self = GUI.Mapper; 
         
        loggerjs.warning( 'GUI.Mapper.addNode: guiElement [ name / value ] = [ ' + guiElement.name + 
                        ' / ' + guiElement.value + ' ]'+ 
                        ', nodeName=' + nodeName + 
                        ', childIndex=' + childIndex  + 
                        ', maxOccursFrequency=' + maxOccursFrequency + 
                        ', dataType=' + dataType + 
                        ', xPath=' + xPath + 
                        ', nlchar=' + nlchar + 
                        ', isAttribute=' + isAttribute + 
                        ', cordinates=' + cordinates + 
                        ', porousXSD.length=' + porousXSD.length + 
                        ', xmlDocName=' + xmlDocName); 
         
        if ( 
        	(maxOccursFrequency!=null && maxOccursFrequency==XSD.attribute.type.value.unbounded) || 
        	(maxOccursFrequency!=null && parseInt(maxOccursFrequency) > parseInt(childIndex)) 
        ) { 
                  
			// Get the document 
			var doc = porousXSD[porousXSD.length-1]; 
		 
			// loggerjs.warning('GUI.Mapper: doc = ' + doc.firstChild.nodeName); 
         
			// Get the node to be added 
			var node2Add; 
		 
			for(var i=0; i < porousXSD.length-1; i++) { 
				node2Add = porousXSD[i]; 
				if (node2Add.nodeName == nodeName) break; 
			} 
		 
   	    	loggerjs.debug('GUI.Mapper.createGUITree(): node.type=' + 
   	    	              XML.Parser.getAttribute(node2Add, XSD.attribute.name.type)); 
		 
			var newNode = XML.Parser.getClonedChild(node2Add, doc, true); 
			// loggerjs.warning('GUI.Mapper: newNode = ' + newNode.nodeName + 
			//                ', doc = ' + doc.firstChild.nodeName ); 
         		 
			var currentNode = XML.Parser.getNodeAtXPath(doc, xPath); 
			currentNode.appendChild(newNode); 
		 
			loggerjs.info('\nGUI.Mapper.addNode(): xsdDocName='+XML.Parser.serialize(doc)); 
		 
			/** Arguments : Array of DOM tree + maxOccurs node to render, GUI tree to create, 
			XSD tree variable name, XML tree variable name ***************************************/ 
		 
			self.createGUITree(porousXSD, treeGUI, 'porousXSD', 'docXML'); 
			 
		} else { 
		 
			alert('You have reached the max allowed'); 
			 
		} 
	} 
	 
	/** Get called when update button is pressed *************************************************/ 
	this.updateNode = function( guiElement, 
	                            nodeName, 
	                            childIndex, 
	                            maxOccursFrequency, 
	                            dataType, 
	                            nlchar, 
	                            isAttribute, 
	                            xPath, 
	                            cordinates, 
	                            porousXSD, 
	                            xmlDocName 
	) { 
        var self = GUI.Mapper; 
         
        loggerjs.warning( 'GUI.Mapper.updateNode: guiElement [name/vale]=[' + guiElement.name + 
                         '/' + guiElement.value + ']'+ 
                         ', nodeName=' + nodeName + 
                         ', childIndex=' + childIndex  + 
                         ', maxOccursFrequency=' + maxOccursFrequency + 
                         ', dataType=' + dataType + 
                         ', nlchar=' + nlchar + 
                         ', isAttribute=' + isAttribute + 
                         ', xPath=' + xPath + 
                         ', cordinates=' + cordinates + 
                         ', porousXSD.length=' + porousXSD.length + 
                         ', xmlDocName=' + xmlDocName); 
                          
        try { 
             
        	isValidated = FormValidator.validate(guiElement, dataType, '', 55, true); 
                
			// Get the document 
			var doc = porousXSD[porousXSD.length-1]; 
		 
			// loggerjs.warning('doc = ' + doc.firstChild.nodeName); 
		 
			var currentXSDNode = XML.Parser.getNodeAtXPath(doc, xPath); 
 			 
 			if(currentXSDNode!=null) { 
 		 
 				// loggerjs.warning( 'GUI.Mapper.updateNode(): xPath = ' + xPath + 
 				//                 ', currentXSDNode = ' + currentXSDNode.nodeName ); 
 			 
 				if(currentXSDNode.childNodes[0]!=null) 
 					currentXSDNode.removeChild(currentXSDNode.childNodes[0]); 
 			     
 			    var newTextNode = new Object();  
 			    if(guiElement.tagName.toUpperCase()=='TEXTAREA') { 
 					newTextNode=doc.createTextNode(guiElement.value.replace(new RegExp ("\r", "g"), nlchar).replace(new RegExp ("\n", "g"), nlchar).replace(/\x20\x10\x13/g, nlchar));  
 				} else { 
 					newTextNode=doc.createTextNode(guiElement.value); 
 				} 
 			 
 				currentXSDNode.appendChild(newTextNode); 
 			} 
         
			loggerjs.info('\nGUI.Mapper.addNode(): xsdDocName='+XML.Parser.serialize(doc)); 
		 
		} catch (e) { 
		 
			alert(e); 
			 
		} 
		
		/** Arguments : Array of DOM tree + maxOccurs node to render, GUI tree to create, 
			XSD tree variable name, XML tree variable name ***************************************/ 
		 
		self.createGUITree(porousXSD, treeGUI, 'porousXSD', 'docXML'); 
	} 
	 
	/** Get called when delete button is pressed *************************************************/ 
	this.deleteNode = function( guiElement, 
	                            nodeName, 
	                            childIndex, 
	                            maxOccursFrequency, 
	                            dataType, 
	                            nlchar, 
	                            isAttribute, 
	                            xPath, 
	                            cordinates, 
	                            porousXSD, 
	                            xmlDocName
	) { 
		var self = GUI.Mapper; 
         
        loggerjs.warning( 'GUI.Mapper.deleteNode: guiElement [name/vale]=[' + guiElement.name + 
                         '/' + guiElement.value + ']'+ 
                         ', nodeName=' + nodeName + 
                         ', childIndex=' + childIndex  + 
                         ', maxOccursFrequency=' + maxOccursFrequency + 
                         ', dataType=' + dataType + 
                         ', nlchar=' + nlchar + 
                         ', isAttribute=' + isAttribute + 
                         ', xPath=' + xPath + 
                         ', cordinates=' + cordinates.substr(0, cordinates.length-3) + 
                         ', porousXSD.length=' + porousXSD.length + 
                         ', xmlDocName=' + xmlDocName); 
                          
	    // Get the document 
		var doc = porousXSD[porousXSD.length-1]; 
		// loggerjs.warning('GUI.Mapper.deleteNode: doc = ' + doc.firstChild.nodeName); 
		 
		var currentXSDNode = XML.Parser.getNodeAtXPath(doc, xPath); 
		// loggerjs.warning('GUI.Mapper.deleteNode: currentXSDNode = ' + currentXSDNode.nodeName); 
 		 
 		if(currentXSDNode!=null) { 
 			currentXSDNode.parentNode.removeChild(currentXSDNode); 
			// loggerjs.warning('GUI.Mapper.deleteNode: currentXSDNode = ' + currentXSDNode.nodeName); 
 		} 
 		 
 		
		/** Arguments : Array of DOM tree + maxOccurs node to render, GUI tree to create, 
			XSD tree variable name, XML tree variable name ***************************************/ 
		 
		self.createGUITree(porousXSD, treeGUI, 'porousXSD', 'docXML'); 
	} 
	 
}; 