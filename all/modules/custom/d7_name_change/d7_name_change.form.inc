<?php

/**
 * Form for user selection criteria.
 */
function d7_name_change_form($form, $form_state) {
  $form = [];

  $form['oldName'] = [
    '#type' => 'textfield',
    '#title' => t('Old name'),
    '#size' => 20,
    '#maxlength' => 20,
    '#attributes' => [
      'placeholder' => t('Old name'),
    ],
    '#rules' => [
      [
        'rule' => 'regexp[/^[a-zA-Z ]*$/]',
        'error' => t('Only letters and white spaces allowed in Your Name.'
        )
      ]
    ],
    '#required' => TRUE,
  ];

  $form['newName'] = [
    '#type' => 'textfield',
    '#title' => t('New name'),
    '#size' => 20,
    '#maxlength' => 20,
    '#attributes' => [
      'placeholder' => t('New name'),
    ],
    '#rules' => [
      [
        'rule' => 'regexp[/^[a-zA-Z ]*$/]',
        'error' => t('Only letters and white spaces allowed in Your Name.'
        )
      ]
    ],
    '#required' => TRUE,
  ];

  $form['submit'] = [
    '#type' => 'submit',
    '#value' => t('Update'),
  ];

  return $form;
}

/**
 * Make selection from db and process it through batch.
 */
function d7_name_change_form_submit($form, $form_state) {
  $values = [
    'oldName' => trim($form_state['values']['oldName']),
    'newName' => trim($form_state['values']['newName']),
  ];

  $result = db_select('d7_pets_owners', 'po')
    ->fields('po', ['owner_id', 'name'])
    ->condition('name', $values['oldName'])
    ->orderBy('owner_id')
    ->execute();
  $names = [];
  foreach ($result as $items) {
    $names[] = [
      'id' => $items->owner_id,
      'old' => $items->name,
      'new' => $values['newName'],
    ];
  }

  $batch = [
    'title' => t('Names processing'),
    'operations' => [
      ['d7_name_change_processing', [$names]],
    ],
    'finished' => 'd7_name_change_finished_callback',
    'file' => drupal_get_path('module', 'd7_name_change') . '/d7_name_change.batch.inc',
  ];

  batch_set($batch);

  batch_process();
}
