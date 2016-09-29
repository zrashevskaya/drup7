<?php

$plugin = array(
  'title' => t('Pets Registration layout'),
  'description' => t('The output of pets registration form'),
  'render callback' => 'pets_registration_layout_content_type_render',
  'category' => t('Custom panes'),
  'single' => TRUE,
);

/**
 * Render callback for the content type.
 */
function pets_registration_layout_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->content = drupal_get_form('d7_pets_registration_form');
  return $block;
}
