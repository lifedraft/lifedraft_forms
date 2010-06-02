<?php

/**
 * admin/build/lifedraft_forms/edit/%
 */

function lifedraft_forms_admin_edit_forms($form_id) {
  
  $lifedraft_forms_path = drupal_get_path("module", "lifedraft_forms");
  
  jquery_ui_add( array( 'ui.draggable', 'ui.droppable', 'ui.sortable' ) );
  drupal_add_js(  $lifedraft_forms_path . "/vendor/lifedraft_selection/jquery.lifedraft_selection.js" );
  drupal_add_js(  $lifedraft_forms_path . "/lifedraft_forms.admin.js" );
  drupal_add_css( $lifedraft_forms_path . "/lifedraft_forms.admin.css" );
  drupal_add_css( drupal_get_path("module", "jquery_ui") . "/jquery.ui/themes/base/jquery-ui.css" );
  
  drupal_add_js(array(
    "lifedraft_forms" => array(
      "selector" => "#lifedraft-forms-admin-form",
      "save_url" => url("admin/build/lifedraft_forms/save/$form_id"),
    ),
  ), "setting");
  
  $breadcrumb = drupal_get_breadcrumb();
  $breadcrumb[] = l($form_id, 'admin/build/lifedraft_forms/'.$form_id );
  drupal_set_breadcrumb($breadcrumb);
  
  return drupal_get_form( "lifedraft_forms_admin_form", $form_id );
  
}

function lifedraft_forms_admin_form(&$form_state, $theming_form_id) {
  
  $theming_form = lifedraft_forms_get_form($theming_form_id);
  $theming_form_fields = lifedraft_forms_get_form_fields($theming_form);
  
  $form_fields_controlls = "";
  
  foreach ($theming_form_fields as $form_id => $form_item) {
    $form_fields_controlls .= theme("lifedraft_forms_form_item", $form_id, $form_item);
  }
  
  $themed_html = "";
  if($themed_html_saved = lifedraft_forms_theme_get($theming_form_id)) {
    $themed_html = $themed_html_saved;
  }
  
  $form = array(
    'themed_html' => array(
      '#prefix' => '<div class="lifedraft_forms_left">',
      '#type' => 'textarea',
      '#title' => t('HTML'),
      '#default_value' => $themed_html,
      '#description' => t('You can also save this snippet as template file in your theme: <code><pre>!template</pre></code>', array("!template" => "form-theme--$theming_form_id.tpl.php")),
      '#rows' => '10',
    ),
    'themed_submit' => array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#suffix' => '</div>',
    ),
    'theming_form_id' => array(
      '#type' => 'hidden',
      '#value' => $theming_form_id,
      '#required' => TRUE
    ),
    
    'form_fields_controlls' => array(
      '#prefix' => '<div class="lifedraft_forms_right">',
      '#value' => $form_fields_controlls,
      '#suffix' => '</div>',
    ),
  );
  
  return $form;
  
}

function lifedraft_forms_admin_form_submit(&$form, &$form_state) {
  $theming_form_id = $form_state["values"]["theming_form_id"];
  $themed_html = $form_state["values"]["themed_html"];
  
  if ($theming_form_id) {
    lifedraft_forms_theme_save($theming_form_id, $themed_html);
  }
  
  drupal_set_message("Successfully saved/updated.");
}


function lifedraft_forms_admin_add_form(&$form_state) {
  
  $form = array(
    'id' => array(
      '#type' => "textfield",
      '#title' => t("Form ID"),
      '#required' => TRUE,
      '#description' => t('This is the hidden input field inside of each drupal form named form_id. 
                           Please enter here the value of this hidden field. <br/>
                           For example this form has this form id <code><pre>@example</pre></code>', 
                           array("@example" => '<input type="hidden" name="form_id" id="edit-lifedraft-forms-admin-add-form" value="lifedraft_forms_admin_add_form" />')),
    ),
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Edit'),
    ),
  );
  
  return $form;
  
}

function lifedraft_forms_admin_add_form_submit(&$form, &$form_state) {
  
  if ($form_state["values"]["id"]) {
    $form["#redirect"] = 'admin/build/lifedraft_forms/edit/' . check_plain($form_state["values"]["id"]);
  }
  
}


function theme_lifedraft_forms_form_item($form_item_id, $form_item) {
  return
  "<div class='lifedraft_forms_item'>
    <a class='lifedraft_forms_controller' title='Push in/out'>{{$form_item_id}}</a>
    $form_item
  </div>";
}

/* admin/build/lifedraft_forms/delete/% */

function lifedraft_forms_admin_delete_form($form_id) {
  if(lifedraft_forms_theme_delete($form_id)) {
    drupal_set_message(t("Form ID: !form_id has been successfully deleted.", array("!form_id" => $form_id)));
  } else {
    drupal_set_message(t("Form ID: !form_id was not found.", array("!form_id" => $form_id)));
  }
  
  drupal_goto("admin/build/lifedraft_forms");
}