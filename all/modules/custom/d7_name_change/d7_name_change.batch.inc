<?php

/**
 * Process every item in batch
 */
function d7_name_change_processing($names, &$context) {

  $limit = 100;

  if (empty($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($names);
  }

  if (empty($context['sandbox']['items'])) {
    $context['sandbox']['items'] = $names;
  }

  $counter = 0;
  if (!empty($context['sandbox']['items'])) {

    if ($context['sandbox']['progress'] != 0) {
      array_splice($context['sandbox']['items'], 0, $limit);
    }

    foreach ($context['sandbox']['items'] as $values) {
      if ($counter != $limit) {

        db_update('d7_pets_owners')
          ->fields(['name' => $values['new'],])
          ->condition('owner_id', $values['id'])
          ->execute();

        $counter++;
        $context['sandbox']['progress']++;

        $context['message'] = t('Now processing name %progress of %count', [
          '%progress' => $context['sandbox']['progress'],
          '%count' => $context['sandbox']['max']
        ]);
        $context['results']['processed'] = $context['sandbox']['progress'];
      }
    }
  }

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Finish callback for Batch
 */
function d7_name_change_finished_callback($success, $results, $operations) {
  if ($success) {
    $message = format_plural($results['processed'], 'One name processed.', '@count names processed.');
  }
  else {
    $message = t('Finished with an error.');
  }
  drupal_set_message($message);
}
