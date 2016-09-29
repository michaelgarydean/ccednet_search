<?php

/**
 * @file
 * Formats search results displayed using search-result.tpl.php and search-results.tpl.php, from the Search module.
 *
 * @author
 * Michael Dean
 * mike@koumbit.org
 * 
 * @see ccednet_search.module
 */
 
/**
 * Form constructor for the CCEDNET Search settings.
 */
function ccednet_search_settings() {
  //get a list of available node types
  $node_types = node_type_get_names();
  
  // The email settings section of the form.
  $form['search_settings'] = array(
    '#title'          => t('Search Display Settings'),
    '#type'           => 'fieldset',
    '#description'    => t('Configure which views should be associated to each custom content type.
                            These are used to link the content type in the site\'s search results.'),
  );
  
  //create a field for each content type
  //each field will contain the URL for a view.
  //the view should be one that aggregates content of this content type
  foreach($node_types as $machine_name=>$human_name) {
    
    //for each language installed on the site, create each field for the current content type 
    foreach(language_list() as $language ) {
      
      //generate a variable name
      $views_path = 'ccednet_search_' . $machine_name . '_' . $language->language . '_view_path';
      
      //create the form element
      $form['search_settings'][$views_path] = array(
        '#title'          => t($human_name . ' (' . $language->name . ')'),
        '#type'           => 'textfield',
        '#description'    => t('The path of the ' . $language->name . ' language view.'),
        '#default_value'  => variable_get($views_path, '')
      );         
    }

  }
  
  return system_settings_form($form);
}