GUI = new Object();       // Empty definition of GUI class for implimenting GUI related methods 
  
mObj = new Array(); 
 
GUI.Tree = function(openAll) { 
 
/** Configuration ********************************************************************************/ 

  this.guiWidth = 599;                             // GUI width (pixels) 
  this.tdWidthLabel = 255;                         // td width (pixels) 
  this.tdHeight = 25;                              // td width (pixels) 
  this.tdWidthElement1 = 55; 
  this.tdWidthElement2 = 255; 
   
  this.guiBGColor = "#f7f7f7";                       // GUI background color
  this.levelOneAutoClose = false;                  // close level-one-nodes (true/false)
  this.floating = false;                           // floating menu (true or false)*

  this.title = "";                                 // GUI title
   
  this.nodeMargin = 1;                             // node margin (pixels)
  this.nodePadding = 1;                            // node padding (pixels)
  this.nodeColor = "#aaaaaa";                      // node font color
  this.nodeBGColor = "#f7f7f7";                      // node background color
  this.nodeBGColor4Level1 = "#f7f7f7";               // node background color for level-one-items
  this.nodeTextFont = "Verdana, Arial, Helvetica"; // node font family (CSS spec.) 
  this.nodeTextSize = "12";                          // node font size (pixels)
  this.nodeTextBold = false;                       // node bold font (true or false)
  this.isWrappingRequired = true;                 // node word wrap (true or false)
  this.nodeActiveColor = "#ffffff";                // active node font color
  this.ActiveNodeUnderlineRequired = false;        // active node underline (true or false)
  this.nodeOnClickAction = "open";                 // action node item is clicked (open/close node) 
   
  /** Pre load icons for fast rendering  *********************************************************/ 

  this.iconWidth = 22;                             // icon width (pixels) 
  this.iconHeight = 19;                            // icon height (pixels) 
   
  this.iconClosed = new Image(); 
  this.iconClosed.src = APP.Base.Path + "/img/folder.gif";          // icon closed 
   
  this.iconOpen = new Image();                     
  this.iconOpen.src = APP.Base.Path + "/img/open.gif";              // icon open  
   
  this.iconPoint = new Image();                     
  this.iconPoint.src = APP.Base.Path + "/img/page.gif";             // icon point 
   
  this.imgBlank = new Image();                      
  this.imgBlank.src = APP.Base.Path + "/img/blank.gif";             // blank image 
   
/** Methods **************************************************************************************/ 
 
  this.objectIndex = 0; 
  this.currentItem = -1; 
  this.highlightItem = -1; 
  this.targetWindow = 0; 
  this.interval = 0;
  this.nodes = new Array();

  if(openAll == null) openAll = false;
  this.openAll = openAll;
 
  /** Public method - Add nodes to GUI user defined object ***************************************/ 
  this.addNode = function(level, text, element1, element2, url, target, onClick) { 
    var i = this.nodes.length; 
    this.nodes[i] = new makeItem(level, text, element1, element2, url, target, onClick); 
  } 

  this.getObject = function(id) {                                                 // Private method
    var obj; 
     
    if(document.getElementById) 
    	obj = document.getElementById(id);
    else if(document.all) 
    	obj = document.all[id];
     
    return obj;
  }

  this.openNode = function(item, rebuild) {                                       // Private method
     
    if(this.nodes[item].node) {
      this.currentItem = item;
      this.nodes[item].icon = (item == this.highlightItem) ? this.iconOpen : this.iconOpen;
    } 
     
    if(rebuild) this.newMenu(); 
     
  }

  this.closeNode = function(item, rebuild) {                                      // Private method
    this.currentItem = -1; 
     
    if(this.nodes[item].node) {
      this.nodes[item].icon = (item == this.highlightItem) ? this.iconClosed : this.iconClosed;
    } 
     
    if(rebuild) this.newMenu(); 
     
  }

  this.viewNode = function(item) {                                                // Private method
    var icon = this.nodes[item].icon; 
     
    if(icon == this.iconOpen || icon == this.iconOpen) 
    	this.closeNode(item, true);
    else 
    	this.openNode(item, true); 
     
  }

  this.jump = function(item) {                                                    // Private method
     
    this.setHilight(item); 
     
    if(this.nodeOnClickAction.toLowerCase() == 'close') 
    	this.closeNode(item, true); 
    else 
    	this.openNode(item, true); 
    	 
    if(this.nodes[item].onClick) eval(this.nodes[item].onClick); 
     
    if(this.nodes[item].url) { 
     
      if(this.nodes[item].target) { 
       
        if( this.nodes[item].target.indexOf('parent.') == -1 && 
             
            this.nodes[item].target.indexOf('top.') == -1) {
             
            if(this.targetWindow && !this.targetWindow.closed) 
            	this.targetWindow.location.href = this.nodes[item].url;
          	else 
          		this.targetWindow = window.open(this.nodes[item].url, 'targetWindow');
          	
          	this.targetWindow.focus();
     
     	} 
        else eval(this.nodes[item].target + '.location.href = "' + this.nodes[item].url + '"'); 
         
      } 
       
      else document.location.href = this.nodes[item].url; 
    }
  } 
   
  /* Arguments: position level 1, [position level 2], ... [position level n]
     Example:   jumpTo(1, 3, 2, 1) ==> this jumps to menu item 1.3.2.1 ***************************/ 
  this.jumpTo = function() { 
   
    var pos, curPos, i;
    var item = 0;
    var level = 1;
    this.currentItem = -1;
     
    if(arguments == null) arguments = this.jumpTo.arguments; 
          
    for(i = 0; i < arguments.length; i++, level++) {
      pos = arguments[i]; 
       
      for(curPos = 0; item < this.nodes.length && curPos < pos; item++) { 
       
        if(this.nodes[item].level == level) curPos++; 
         
      } 
       
      if(curPos == pos) {
        item -= 1;
        this.openNode(item, false);
      } 
       
    }
    if(item) this.jump(item);
  } 
  
  this.floatIt = function() {                                                     // Private method
    var obj = this.getObject('divTreeMenu' + this.objectIndex);
    var scrTop = this.getScreenTop();
    var elmTop = (obj.style.top != '') ? parseInt(obj.style.top) : 0; 
     
    if(elmTop != scrTop) this.smoothIt(obj, elmTop, scrTop);
  }

  this.smoothIt = function(obj, elmTop, scrTop) {                                 // Private method
   
    if(scrTop != elmTop) {
      var percent = .1 * (scrTop - elmTop); 
       
      if(percent > 0) 
      	percent = Math.ceil(percent);
      else 
      	percent = Math.floor(percent); 
      	 
      elmTop += percent;
      obj.style.top = elmTop + 'px';
    } 
     
  } 

  this.content = function(item) {                                                 // Private method
    var text = '';
    var bgc = (this.nodes[item].level <= 1) ? this.nodeBGColor4Level1 : this.nodeBGColor;
    text += '<table border=0 cellspacing=' + this.nodeMargin + ' cellpadding=0 width=100%><tr>' +
            '<td ' + (bgc ? ' bgcolor=' + bgc  : '') + '>' +
            '<table border=0 cellspacing=0 cellpadding=' + this.nodePadding + '><tr valign=top>'; 
             
    if(this.nodes[item].level > 1) {
      for(i = 1; i < this.nodes[item].level; i++) {
        text += '<td><img src="' + this.imgBlank.src + '" width=' + this.iconWidth +
                ' height=' + this.iconHeight + '></td>';
      }
    } 
     
    text += '<td height=' + this.tdHeight + '>'; 
     
    if(this.nodes[item].node) 
    	text += '<a href="javascript:mObj[' + this.objectIndex + '].viewNode(' + item + ')">'; 
    	 
    text += '<img src="' + this.nodes[item].icon.src + '" border=0' + ' width=' + this.iconWidth + 
            ' height=' + this.iconHeight + '></a></td>' + 
            '<td width=' + this.tdWidthLabel + 'px ' + (this.isWrappingRequired ? '>' : ' nowrap>') 
             + '<a href="javascript:mObj[' + this.objectIndex + '].jump(' + item + ')" >' + 
             // class="' + ((item == this.highlightItem) ? 'cssLinkHilight':'cssLink') + this.objectIndex + '">' + 
            ((this.nodeTextBold) ? '<b>' + this.nodes[item].text + '</b>' : this.nodes[item].text )  
            + '</a></td><td width=' + this.tdWidthElement1 + 'px>' + this.nodes[item].element1 + 
            '</td>'+
            '<td width=' + this.tdWidthElement2 + 'px>' + this.nodes[item].element2 + '</td>' + 
            ' </tr></table></td></tr></table>'; 
    return text; 
  }

  this.newMenu = function() {                                                     // Private method
    var menu = '';
    var i, j; 
     
    var obj = this.getObject('divTreeMenu' + this.objectIndex); 
     
    if(obj) {
      if(this.levelOneAutoClose && this.currentItem >= 0) {
        if(this.nodes[this.currentItem].level <= 1) {
          for(i = 0; i < this.nodes.length; i++) {
            if(i != this.currentItem && this.nodes[i].node && this.nodes[i].level == 1) {
              this.nodes[i].icon = this.iconClosed;
            }
          }
        }
      } 
       
      if(this.title) menu += '<div class="cssTitle">' + this.title + '</div>'; 
      for(i = 0; i < this.nodes.length; i++) {
        menu += this.content(i); 
        if(this.nodes[i].icon == this.iconClosed || this.nodes[i].icon == this.iconClosed) {
          for(j = i+1; j < this.nodes.length && this.nodes[j].level > this.nodes[i].level; j++);
          i = j - 1;
        }
      } 
       obj.innerHTML = menu; 
    } 
  }

  /** Public method: To build container **********************************************************/ 
  this.buildContainer = function() { 
    var lnk1 = '.cssLink' + this.objectIndex;
    var lnk2 = '.cssLinkHilight' + this.objectIndex; 
     
    var style = ('<style> .cssTree' + this.objectIndex + ' { ' + 'position: relative; ' + 
                   'width: ' + this.guiWidth + 'px; ' + (this.floating ? 'z-index: 69; ' : '') + 
                   (this.guiBGColor ? 'background-color:' + this.guiBGColor + '; ' : '') + 
                   '} ' + lnk1 + ', ' + lnk1 + ':visited, ' + lnk1 + ':active { ' + 
                   'color: ' + this.nodeColor + '; ' + 'font-family: ' + this.nodeTextFont + '; ' + 
                   'font-size: ' + this.nodeTextSize + 'px; ' + 'text-decoration: none; ' + '} ' + 
                   '.cssTitle { color: #ffffff; background-color: #ffffff ; ' + 
                   'font-family: Arial, Helvetica; font-size: 35px; font-weight: bold; ' + 
                   '} ' + lnk1 + ':hover { ' + 'text-decoration: underline; ' + 
                   '} ' + lnk2 + ', ' + lnk2 + ':visited, ' + lnk2 + ':active { ' + 
                   'color: ' + this.nodeActiveColor + '; ' + 'font-family: ' + this.nodeTextFont + 
                   '; font-size: ' + this.nodeTextSize + 'px; ' + 
                   (this.ActiveNodeUnderlineRequired ? 'text-decoration: underline; ' : '') + 
                   '} </style>' + 
                   '<div id="divTreeMenu' + this.objectIndex + '" class="cssTree' + 
                   this.objectIndex + '">'+'</div>'); 
      return style; 
  } 

  this.createStructure = function() {                                             // Private method 
    for(i = 0; i < this.nodes.length; i++) { 
     
      if(!this.nodes[i].icon) { 
        
       if(i < this.nodes.length-1 && this.nodes[i+1].level > this.nodes[i].level) {
          this.nodes[i].icon = this.openAll ? this.iconOpen : this.iconClosed;
          this.nodes[i].node = true;
        }
        else this.nodes[i].icon = this.iconPoint; 
         
      }
       
    }
  }

  this.create = function() {                                                      // Private method
  	mObj = new Array(); 
    this.objectIndex = mObj.length; 
     
    if(mObj[this.objectIndex] = this) { 
      this.createStructure(); 
      this.newMenu(); 
      if(this.floating) {
        if(this.interval) clearInterval(this.interval);
        this.interval = setInterval('mObj[' + this.objectIndex + '].floatIt()', 1);
      } 
    } 
    else alert("Could not create menu!"); 
     
  }

  this.open = function() {                                                        // Private method 
    for(var i = 0; i < this.nodes.length; i++) {
      this.openNode(i, false);
    }
    this.newMenu();
  }

  this.close = function() {                                                       // Private method 
    for(var i = 0; i < this.nodes.length; i++) {
      this.closeNode(i, false);
    }
    this.newMenu();
  }

function makeItem(level, text, element1, element2, url, target, onClick) {        // Private method 
  this.level = level;
  this.text = text; 
  this.element1 = element1; 
  this.element2 = element2; 
  this.url = url;
  this.target = target;
  this.onClick = onClick;
  this.icon = '';
  this.node = false; 
}; 
 
 this.getScreenTop = function() {                                                 // Private method
    var scrTop = 0;
    if(document.documentElement && document.documentElement.scrollTop)
      scrTop = document.documentElement.scrollTop;
    else if(document.body && document.body.scrollTop)
      scrTop = document.body.scrollTop;
    else if(window.pageYOffset) scrTop = window.pageYOffset;
    return scrTop;
  } 
  
 this.setHilight = function(item) {                                               // Private method
    if(this.highlightItem >= 0) {
      var i = this.highlightItem;
      if(this.nodes[i].icon == this.iconOpen) this.nodes[i].icon = this.iconOpen;
      else if(this.nodes[i].icon == this.iconClosed) this.nodes[i].icon = this.iconClosed;
      else if(this.nodes[i].icon == this.iconPoint) this.nodes[i].icon = this.iconPoint;
    }
    this.highlightItem = item;
    if(this.nodes[item].icon == this.iconOpen) this.nodes[item].icon = this.iconOpen;
    else if(this.nodes[item].icon == this.iconClosed) this.nodes[item].icon = this.iconClosed;
    else if(this.nodes[item].icon == this.iconPoint) this.nodes[item].icon = this.iconPoint;
  }
   
}; 