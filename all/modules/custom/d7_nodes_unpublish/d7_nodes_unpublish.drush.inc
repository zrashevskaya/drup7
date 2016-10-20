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
  $time = time() - 60 * 60 * 24 * 2;
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->propertyCondition('changed', $time, '<');

  $data = $query->execute();
  if ($data) {
    $unpublished = 0;
    foreach ($data['node'] as $node) {
      $result = db_update('node')
        ->fields([
          'status' => 0,
          'changed' => time(),
        ])
        ->condition('nid', $node->nid)
        ->execute();
      if ($result) {
        $unpublished++;
      }
    }
    $unpublished == 0 ? $message = t('Process of unpublishing goes wrong!') : $message = t('!count nodes unpublished successfully!', ['!count' => $unpublished]);
  }
  else {
    $message = t('There are no nodes for unpublishing.');
  }
  drush_print($message);
}
