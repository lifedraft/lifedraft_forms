/*
 * # lifedraft_selection
 * utilities for handling user cursor selections and mouse position 
 * http://lifedraft.de/
 *
 * Copyright (c) 2010 Stanislav Müller
 * Licensed under the GPL licenses.
 * http://lifedraft.de
 *
 */

(function(jQuery){
  
  // sets cursor position / selection
  jQuery.fn.lifedraft_selection_set = function(selectionStart, selectionEnd) {
    
    if (!this.length) {
      return false;
    };
    
    var element = this[0];
    
    if (element.setSelectionRange) {
      element.focus();
      element.setSelectionRange(selectionStart, selectionEnd);
    } 
    // IE special method to set selection
    else if (element.createTextRange) {
      var range = element.createTextRange();
      range.collapse(true);
      range.moveEnd('character', selectionStart);
      range.moveStart('character', selectionEnd);
      range.select();
    }
    
    return this.lifedraft_selection_get();
  };
  
  // gets cursor position and selection
  jQuery.fn.lifedraft_selection_get = function() {

    if (!this.length) {
      return false;
    };
    
    var element = this[0];

    // IE has another way to find out the cursor position, so go on:
    if(jQuery.browser.msie) {
      
      var bookmark = document.selection.createRange().getBookmark();
      element.selection = element.createTextRange();
      element.selection.moveToBookmark(bookmark);
      element.selectLeft = element.createTextRange();
      element.selectLeft.collapse(true);
      element.selectLeft.setEndPoint("EndToStart", element.selection);

      return {
        selectionStart: element.selectLeft.text.length,
        selectionEnd: element.selectLeft.text.length +
                      ((element.selection.text.length == 0) ? 0 : element.selection.text.length)
      };
    
    }
     
    // All good browsers support standard methods.
    return {
      selectionStart: element.selectionStart,
      selectionEnd: element.selectionEnd
    };
  };
  
  
  
  jQuery.fn.lifedraft_selection_add_value = function(new_value, select) {
    
    var selection = this.lifedraft_selection_get(),
        selectionStart = selection.selectionStart,
        selectionEnd = selection.selectionEnd;

    var value = this.val();
    
    // Save strings before and after the selection/cursor.
    var before = value.substr(0, selectionStart);
        after = value.substr(selectionEnd);
    
    this.val(before + new_value + after);
    
    if (select) {
      this.lifedraft_selection_set(before.length, before.length + new_value.length);
    };
    
    this.lifedraft_selection_get();
    
  };
  
})(jQuery);