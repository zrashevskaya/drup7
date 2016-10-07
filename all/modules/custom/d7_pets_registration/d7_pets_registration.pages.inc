<?php
function d7_pets_owners_table_page() {
  $header = [
    t('ID'),
    t('Name'),
    t('Last Name'),
    t('Birthday'),
    t('Pet type'),
    t('E-mail'),
    t('Delete'),
    t('Edit')
  ];
  $rows = [];
  $cache_id = 'd7_pets_registration_table';
  $cache = cache_get($cache_id, 'cache_d7_pets_registration');
  if (!empty($cache->data)) {
    $array = $cache->data;

  }
  else {
    $query = db_select('d7_pets_owners')
      ->fields('d7_pets_owners')
      ->execute();

    $petList = d7_pets_registration_selectbox_contents('pets');
    foreach ($query as $value) {
      $rows[] = [
        $value->owner_id,
        htmlspecialchars($value->name),
        htmlspecialchars($value->last_name),
        htmlspecialchars($value->owner_birthday),
        $petList[($value->pet_type)],
        htmlspecialchars($value->email),
        l(t('Edit'), "d7_pets_owners/" . $value->owner_id . "/update"),
        l(t('Delete'), "d7_pets_owners/" . $value->owner_id . "/delete"),
      ];
    }
    $array = theme('table', ['header' => $header, 'rows' => $rows]);

    cache_set($cache_id, $array, 'cache_d7_pets_registration');
  }
  return $array;
}

function d7_pets_owners_delete_page_title($id) {
  return t('Are you sure you want to delete user "!num"?', ['!num' => $id['name']]);
}

function d7_pets_owners_update_page_title($id) {
  if ($id['name']) {
    return t('Are you sure you want to update user "!num"?', ['!num' => $id['name']]);
  }
  else {
    return t('User not found.');
  }
}

function id_load($uid) {
  $id = db_select('d7_pets_owners', 't')
    ->fields('t')
    ->condition('owner_id', $uid)
    ->execute()
    ->fetchAssoc();

  return $id;
}

function d7_pets_menu_callback() {
  drupal_add_js('misc/ajax.js');
  drupal_add_js(drupal_get_path('module', 'd7_pets_registration') . '/js/colored_menu_tubs.js');
  return 'Hello!';
//  drupal_goto('d7_pets_menu/d7_pets_registration');
}

function d7_pets_registration_ajax_menu_callback() {
  $color = '#';
  $key = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 'a', 'b', 'c', 'd', 'e', 'f'];
  for ($i = 0; $i <= 2; $i++) {
    $color = $color . $key[rand(10,15)]. $key[rand(0,8)];
  }
  $result = [
    '#type' => 'ajax',
    '#commands' => [
    [
      'command' => 'change_color',
      'color' => $color,
    ]
    ],
  ];
  return $result;
}
