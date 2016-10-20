<?php

/**
 * @file
 * Drush integration for the d7 nodes unpublish module.
 */

/**
 * Implements hook_drush_command().
 */
function d7_nodes_unpublish_drush_command() {
  $items = [];
  $items['content-unpublish'] = [
    'description' => 'Unpublish old content',
    'drupal dependencies' => ['d7_nodes_unpublish'],
    'aliases' => ['upcont'],
  ];
  return $items;
}

/**
 * Provide data set for unpublishing via cron.
 * @return mixed Data set.
 */
function drush_d7_nodes_unpublish_content_unpublish() {
  $result = d7_nodes_unpublish_cron();
  if ($result){
    drush_print('Nodes are in queue for unpublishing');
  }
  else{
    drush_print('There are no nodes for unpublishing.');
  }
}
