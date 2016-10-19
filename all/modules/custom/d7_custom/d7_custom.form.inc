<?php

/**
 * Form definition for adding / editing a project.
 */
function d7_custom_form($form, &$form_state, $d7_custom = NULL) {

  $langcode = entity_language('d7_custom', $d7_custom);

  if (empty($langcode)) {
    $langcode = LANGUAGE_NONE;
  }

  $form['name'] = array(
    '#title' => t('D7 Custom name'),
    '#type' => 'textfield',
    '#default_value' => isset($d7_custom->name) ? $d7_custom->name : '',
    '#required' => TRUE,
  );

  $form['description'] = array(
    '#title' => t('D7 Custom description'),
    '#type' => 'textarea',
    '#default_value' => isset($d7_custom->description) ? $d7_custom->description : '',
    '#required' => TRUE,
  );

  $form['created'] = array(
    '#title' => t('D7 Custom created'),
    '#type' => 'textfield',
    '#default_value' => isset($d7_custom->created) ? $d7_custom->created : '',
    '#required' => TRUE,
  );

  $form['language'] = array(
    '#type' => 'value',
    '#default_value' => $langcode,
  );

  field_attach_form('d7_custom', $d7_custom, $form, $form_state, $langcode);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => isset($d7_custom->id) ? t('Update project') : t('Save project'),
    '#weight' => 50,
  );

  return $form;
}

/**
 * Submit handler for the project add/edit form.
 */
function d7_custom_form_submit($form, &$form_state) {
  $d7_custom = entity_ui_form_submit_build_entity($form, $form_state);
  $d7_custom->save();
  drupal_set_message(t('The D7 Custom Entity: @name has been saved.', array('@name' => $d7_custom->name)));
  $form_state['redirect'] = 'admin/d7_custom';
}

