FormValidator = new Object(); 
 
FormValidator.validate = function(formElement, dataType, min, max, isOptional) { 
	
	loggerjs.debug( 'FormValidator.validate: formElement [name/vale]=[' + formElement.name + 
                         '/' + formElement.value + ']'+ 
                         ', dataType=' + dataType + 
                         ', min=' + min + 
                         ', max=' + max);  
                          
	with (formElement) { 
	 
		value2Validate = value; 
		 
		if(isOptional && (value2Validate=='' || value2Validate==null)) { 
		 
			if ( 
					(value2Validate.length == min && value2Validate.length < min) || 
					(value2Validate.length == max && value2Validate.length > max) || 
					value2Validate.length != value2Validate
			) { 
				throw "Validation failed: Field length should not be less than <" + min + ">" + " and greater than <" + max + ">"; 
			} 
			 
		} else { 
 		 
 			if (XSD.attribute.type.value.Text(dataType)) { 
 			 
 				// Do nothing 
 				 
 			} else if (XSD.attribute.type.value.Integer(dataType)) { 
 			 
				if (isNaN(value2Validate)) { 
				 
					throw "Validation failed: Incorrect datatype entered, Expected <" + dataType + ">"; 
					 
				} else { 
				 
					value2Validate=parseInt(value) 
					 
					if (
							(parseFloat(min) == min && value2Validate < min) || 
							(parseFloat(max) == max && value2Validate > max) || 
							value != value2Validate
					) { 
						throw "Validation failed: Value should not be less than <" + min + ">" + " and greater than <" + max + ">"; 
					} 
				} 
				 
			} 
		} 
	} 
	 
	loggerjs.debug('FormValidator.validate: Validation passed'); 
	return true; 
} 
 
