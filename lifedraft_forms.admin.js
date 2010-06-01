Drupal.behaviors.lifedraft_forms = function(context) {
  
  var settings = Drupal.settings.lifedraft_forms,
      form = jQuery(settings.selector),
      textarea = form.find("#edit-themed-html"),
      fields = {};
  
  
  form.find(".lifedraft_forms_controller").live("click", function(event) {
    
    if(jQuery(this).hasClass("lifedraft_forms_item_inserted")) {
      
      var first_found_position = false;
      textarea.val(textarea.val().replace(new RegExp(this.innerHTML, "g"), function(match, position, rest) {
        if (first_found_position === false) {
          first_found_position = position;
        };
        return '';
      }));
      
      textarea.lifedraft_selection_set(first_found_position, first_found_position);
      
    } else {
      textarea.lifedraft_selection_add_value(this.innerHTML, true);
    }

    change();
    
    return false;
    
  }).each(function() {
    fields[this.innerHTML] = jQuery(this);
  });
  
  
  textarea.keyup(function() {
    change();
  });
  
  textarea.click(function(){
    change();
  });
  
  var change = function() {
    
    var value = textarea[0].value;
    
    for (var field in fields) {
      if (value.indexOf(field) != -1) {
        fields[field].addClass("lifedraft_forms_item_inserted");
      } else {
        fields[field].removeClass("lifedraft_forms_item_inserted");
      };
    };
    
    cursor_hover();
    
  };
  
  var field_active = false;
  var cursor_hover = function() {
    var selection = textarea.lifedraft_selection_get();
    var cursor_position = selection.selectionStart;
    
    if (selection.selectionStart < selection.selectionEnd) {
      cursor_position = selection.selectionStart+1;
    };
    
    var value = textarea.val();
    
    var start = false;
    var end = false;

    for (var i = cursor_position-1; i >= 0; i--) {
      
      if (value[i] == "}") {
        break;
      };
      
      if (value[i] == "{") {
        start = i;
        break;
      };

    };
    
    for (var i = cursor_position; i < value.length; i++) {
      
      if (start === false) {
        break;
      };
      
      if (value[i] == "{") {
        start = false;
        break;
      };
      
      if (value[i] == "}") {
        end = i;
        break;
      };
      
    };
    
    if (start !== false && end !== false) {
      var key = value.substring(start, end+1);
      
      
      if (key in fields) {

        if (field_active == fields[key]) {
          return;
        };
        
        if (field_active) {
          field_active.removeClass("lifedraft_forms_item_hover");
        };

        field_active = fields[key];
        field_active.addClass("lifedraft_forms_item_hover");
      };
    } else if(field_active) {
      field_active.removeClass("lifedraft_forms_item_hover");
      field_active = false;
    }
    
  };
  
  change();
};