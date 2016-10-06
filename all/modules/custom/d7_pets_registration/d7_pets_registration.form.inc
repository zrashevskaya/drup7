<?php

function d7_pets_owners_delete_form($form, $form_state, $id) {
  $form = [];

  $form['owner_id'] = [
    '#title' => t('Owner id'),
    '#type' => 'hidden',
    '#maxlength' => 11,
    '#default_value' => $id['owner_id'],
  ];

  $form['submit'] = [
    '#type' => 'submit',
    '#value' => t('Delete'),
  ];

  $form['cancel'] = [
    '#markup' => l(t('Cancel'), 'pet-owners'),
  ];
  return $form;
}

function d7_pets_owners_delete_form_submit($form, &$form_state) {
  $id = $form_state['values']['owner_id'];
  $result = db_delete('d7_pets_owners')
    ->condition('owner_id', $id)
    ->execute();
  $placeholders = ['!id' => $form_state['build_info']['args'][0]['name']];
  if ($result) {
    cache_clear_all('d7_pets_registration_table', 'cache_d7_pets_registration');
    cache_clear_all('owners_by_pets', 'cache_views_data', TRUE);
    cache_clear_all('pet_owners', 'cache_views_data', TRUE);
    drupal_set_message(t('Record !id successfully removed.', $placeholders));
  }
  else {
    drupal_set_message(t('Record !id is undefined.', $placeholders), 'warning');
  }
  drupal_goto('pet-owners');
}

function d7_pets_owners_update_form($form, $form_state, $id = NULL) {
  $form = [];

//  if (empty($id) || empty($id['owner_id'])) {
//    $placeholders = [
//      '!back' => l(t('Go back'), 'd7_pets_owners_table'),
//    ];
//    $form['text'] = [
//      '#markup' => t('Undefined user. !back.', $placeholders),
//    ];
//    return $form;
//  }

  if ($id) {
    $form['owner_id'] = [
      '#title' => t('Owner id'),
      '#type' => 'hidden',
      '#maxlength' => 11,
      '#value' => $id['owner_id'],
    ];
  }

  $form['userName'] = [
    '#type' => 'textfield',
    '#title' => t('What is your name?'),
    '#size' => 20,
    '#maxlength' => 20,
    '#default_value' => $id ? $id['name'] : '',
    '#attributes' => [
      'placeholder' => t('Name *'),
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

  $form['lastName'] = [
    '#type' => 'textfield',
    '#title' => t('What is your last name?'),
    '#size' => 30,
    '#maxlength' => 30,
    '#default_value' => $id ? $id['last_name'] : '',
    '#attributes' => [
      'placeholder' => t('Last name *'),
    ],
    '#rules' => [
      [
        'rule' => 'regexp[/^[a-zA-Z ]*$/]',
        'error' => t('Only letters and white spaces allowed in Your Last Name.'
        )
      ]
    ],
    '#required' => TRUE,
  ];

  $form['ownerBirthday'] = [
    '#type' => 'date',
    '#title' => t('What is your birthday?'),
    '#required' => TRUE,
  ];

  if ($id){
    $date = explode('-',$id['owner_birthday']);
    $form['ownerBirthday']['#default_value'] = [
      'year' => intval($date[0]),
      'month' => intval($date[1]),
      'day' => intval($date[2])
    ];
  }

  $form['pets'] = [
    '#type' => 'select',
    '#title' => t('Choose your pet type'),
    '#options' => d7_pets_registration_selectbox_contents('pets'),
    '#default_value' => $id ? $id['pet_type'] : '',
    '#required' => TRUE,
  ];


  $form['email'] = [
    '#type' => 'textfield',
    '#title' => t('What is your e-mail?'),
    '#size' => 30,
    '#maxlength' => 30,
    '#default_value' => $id ? $id['email'] : '',
    '#attributes' => [
      'placeholder' => t('E-mail *'),
    ],
    '#rules' => [
      [
        'rule' => 'email',
        'error' => t('Invalid email format.'
        )
      ]
    ],
    '#required' => TRUE,
  ];


  $form['confirm_email'] = [
    '#type' => 'textfield',
    '#title' => t('Please, repeat your e-mail.'),
    '#size' => 30,
    '#maxlength' => 30,
    '#attributes' => [
      'placeholder' => t('Repeate E-mail *'),
    ],
    '#rules' => [
      [
        'rule' => 'email',
        'error' => t('Invalid email format.'
        )
      ]
    ],
    '#required' => TRUE,
  ];

  $form['actions'] = ['#type' => 'actions'];

  $form['actions']['submit'] = [
    '#type' => 'submit',
    '#value' => $id ? t('Update') : t('Registry!'),
  ];

  $form['actions']['cancel'] = [
    '#type' => $id ? 'markup' : 'hiddedn',
    '#markup' => l(t('Cancel '), 'pet-owners')
  ];

  $form['actions']['delete'] = [
    '#type' => $id ? 'markup' : 'hiddedn',
    '#markup' => l(t('Delete'), "d7_pets_owners/" . $id['owner_id'] . "/delete")
  ];

  return $form;
}

/**
 * Implements hook_validate().
 */
function d7_pets_owners_update_form_validate($form, &$form_state) {
  $datefields = $form_state['values']['ownerBirthday'];
  $birthday = "{$datefields['year']}-{$datefields['month']}-{$datefields['day']}";
  $values = [
    'userName' => trim($form_state['values']['userName']),
    'lastName' => trim($form_state['values']['lastName']),
    'ownerBirthday' => $birthday,
    'pets' => trim($form_state['values']['pets']),
    'email' => trim($form_state['values']['email']),
    'confirm_email' => trim($form_state['values']['confirm_email'])
  ];

  if (strtotime($birthday)>strtotime(date('Y-m-d'))){
    form_set_error('ownerBirthday',
      t("This date is incorrect. It refers to future.")
    );
  }
  elseif ($values['email'] == $values['confirm_email']) {
    if (isset($form_state['values']['owner_id'])) {
      $values ['owner_id'] = $form_state['values']['owner_id'];
      $check = db_select('d7_pets_owners')
        ->condition('email', $values['email'])
        ->condition('owner_id', $values['owner_id'], '<>')
        ->countQuery()
        ->execute()
        ->fetchField();

      if ($check) {
        form_set_error('email',
          t("This e-mail is used by another user.")
        );
      }
      else{
        $person = db_select('d7_pets_owners')
          ->condition('name', $values['userName'])
          ->condition('last_name', $values['lastName'])
          ->condition('owner_birthday', $values['ownerBirthday'])
          ->condition('owner_id', $values['owner_id'], '<>')
          ->countQuery()
          ->execute()
          ->fetchField();

        if ($person) {
          form_set_error('email',
            t("There is a user with the same Name, Last Name and Birthday.")
          );
        }
      }
    }
    else {
      $result = db_select('d7_pets_owners')
        ->condition('email', $values['email'])
        ->countQuery()
        ->execute()
        ->fetchField();

      if ($result) {
        form_set_error('email',
          t("!name, your e-mail is already registered.", ['!name' => $values['userName']])
        );
      }
      else{
        $person = db_select('d7_pets_owners')
          ->condition('name', $values['userName'])
          ->condition('last_name', $values['lastName'])
          ->condition('owner_birthday', $values['ownerBirthday'])
          ->countQuery()
          ->execute()
          ->fetchField();

        if ($person) {
          form_set_error('email',
            t("There is a user with the same Name, Last Name and Birthday.")
          );
        }
      }
    }
  }
  else {
    form_set_error('email',
      t("Please check e-mail repeat.")
    );
  }
}

/**
 * Implements hook_submit().
 */
function d7_pets_owners_update_form_submit($form, $form_state) {
  $datefields = $form_state['values']['ownerBirthday'];
  $birthday = "{$datefields['year']}-{$datefields['month']}-{$datefields['day']}";
  $values = [
    'userName' => trim($form_state['values']['userName']),
    'lastName' => trim($form_state['values']['lastName']),
    'ownerBirthday' => $birthday,
    'pets' => trim($form_state['values']['pets']),
    'email' => trim($form_state['values']['email']),
    'confirm_email' => trim($form_state['values']['confirm_email'])
  ];
  if (isset($form_state['values']['owner_id'])) {
    $values ['owner_id'] = $form_state['values']['owner_id'];
    $result = db_update('d7_pets_owners')
      ->fields([
        'name' => $values['userName'],
        'last_name' => $values['lastName'],
        'owner_birthday' => $values['ownerBirthday'],
        'pet_type' => $values['pets'],
        'email' => $values['email'],
      ])
      ->condition('owner_id', $values['owner_id'])
      ->execute();

    if ($result) {
      cache_clear_all('d7_pets_registration_table', 'cache_d7_pets_registration');
      cache_clear_all('owners_by_pets', 'cache_views_data', TRUE);
      cache_clear_all('pet_owners', 'cache_views_data', TRUE);
      drupal_set_message(t('Data updated successfully'));
      drupal_goto('pet-owners');
    }
    else {
      drupal_set_message(t('Data is not updated'), 'warning');
    }
  }
  else {
    db_insert('d7_pets_owners')
      ->fields([
        'name' => $values['userName'],
        'last_name' => $values['lastName'],
        'owner_birthday' => $values['ownerBirthday'],
        'pet_type' => $values['pets'],
        'email' => $values['email']
      ])
      ->execute();
    cache_clear_all('d7_pets_registration_table', 'cache_d7_pets_registration');
    cache_clear_all('owners_by_pets', 'cache_views_data', TRUE);
    cache_clear_all('pet_owners', 'cache_views_data', TRUE);
    drupal_set_message(
      t("!name, you have registered successfully! Congrats!", ['!name' => $values['userName']])
    );
  }
}

