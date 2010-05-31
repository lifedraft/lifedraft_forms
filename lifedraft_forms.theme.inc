<?php


function theme_lifedraft_form($form) {
  $themed_html = $form["#themed_html"];
  
  $form_fields = lifedraft_forms_get_form_fields($form);
  
  lifedraft_form_replace_tokens_cache_fields($form_fields);
  $themed_html = preg_replace_callback('(\{\w*\})','lifedraft_form_replace_tokens', $themed_html);
  
  $fields_found = array_unique(lifedraft_form_replace_tokens_cache_found_fields());
  
  foreach ($fields_found as $field_found) {
    if (isset($form[$field_found])) {
      unset($form[$field_found]);
    }
  }
  
  return $themed_html . drupal_render($form);
}

function lifedraft_form_replace_tokens($matches) {
  $key = preg_replace("(\{|\})", '', $matches[0]);
  
  $form_fields = lifedraft_form_replace_tokens_cache_fields();
  
  if ($form_fields[$key]) {
    lifedraft_form_replace_tokens_cache_found_fields($key);
    return $form_fields[$key];
  }
  
  return $matches[0];
  
}

function lifedraft_form_replace_tokens_cache_fields($fields) {
  static $fields_cache = array();
  
  if ($fields) {
    $fields_cache = $fields;
  }
  
  return $fields_cache;
  
}

function lifedraft_form_replace_tokens_cache_found_fields($field) {
  static $field_found_cache = array();
  
  if ($field) {
    $field_found_cache[] = $field;
  }

  return $field_found_cache;
}
