<?php

$plugin = array(
  'title' => t('Subscription layout'),
  'description' => t('The output of subscription form'),
  'render callback' => 'subscription_layout_content_type_render',
  'category' => t('Custom panes'),
  'single' => TRUE,
);

/**
 * Render callback for the content type.
 */
function subscription_layout_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->content =drupal_get_form('d7_subscription_form');
  return $block;
}
