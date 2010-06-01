<?php

function lifedraft_forms_admin_view_forms() {
  global $conf;
  
  module_load_include( 'inc', 'lifedraft_forms', 'lifedraft_forms.admin' );
  
  $table = array();
  
  foreach ($conf as $key => $value) {
    
    if (strpos($key, "lifedraft_forms_") !== FALSE) {
      $form_id = preg_replace('/lifedraft_forms_/', '', $key);
      
      $table[] = array(
        $form_id, 
        l(t('Edit'), 'admin/build/lifedraft_forms/edit/'.$form_id) . " | " .
        l(t('Delete'), 'admin/build/lifedraft_forms/delete/'.$form_id)
      );
      
    }
    
  }
  
  $table_header = array(
    t('Form ID'),
    t('Actions'),
  );
  
  $form = drupal_get_form('lifedraft_forms_admin_add_form');
  
  # lifedraft_forms_theme_exsists();
  
  return  $form . theme('table', $table_header, $table);
}