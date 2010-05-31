# lifedraft_selection

This is an jQuery plugin. It helps you to find out current cursor position or an complete text selection inside of whole document, set selection and even insert some text after user's cursor. Should work in all browsers. I hope.

## Example #1

Image you have an textarea where user just typing in and you would like to find out at which position users cursor is placed.

`<script type="text/javascript" charset="utf-8">  
  jQuery("textarea").eq(0).lifedraft_selection_get();  
</script>`

This returs an object with the following values: `{ selectionStart, selectionEnd }`


## Example #2

Image you would like select an text passage from the specific start and end point:

`<script type="text/javascript" charset="utf-8">  
  jQuery("textarea").eq(0).textarea.lifedraft_selection_set(5, 22);  
</script>`

This returs also an object with the following values: `{ selectionStart, selectionEnd }`


## Example #3

Image you would like to insert smth. at the current position of the cursor.

`<script type="text/javascript" charset="utf-8">  
  jQuery("textarea").eq(0).textarea.lifedraft_selection_add_value('lorem impsum...', true);  
</script>`

The second argument of the function `lifedraft_selection_add_value`, selects the snippet after insertion.

This returs also an object with the following values: `{ selectionStart, selectionEnd }`