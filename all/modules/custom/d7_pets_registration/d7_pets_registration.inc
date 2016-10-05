<?php

/**
 * Displays form with built-in Drupal function.
 *
 * @param form
 *  The form which should be displayed.
 *
 * @return
 *  An html-form with all fileds.
 */
function d7_pets_registration_create_form($form) {

  return drupal_get_form($form);
}


function d7_pets_registration_selectbox_contents($voc) {
  $vocabulary = taxonomy_vocabulary_machine_name_load($voc);
  $terms = taxonomy_get_tree($vocabulary->vid);

  foreach ($terms as $data) {
    $output[$data->tid] = $data->name;
  }

  return $output;
}
