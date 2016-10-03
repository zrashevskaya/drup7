<?php
function d7_pets_owners_table_page() {
  $header = [
    t('ID'),
    t('Name'),
    t('Last Name'),
    t('E-mail'),
    t('Delete'),
    t('Edit')
  ];
  $rows = [];
  $query = db_select('d7_pets_owners')
    ->fields('d7_pets_owners')
    ->execute();
  foreach ($query as $value) {
    $rows[] = [
      $value->owner_id,
      htmlspecialchars($value->name),
      htmlspecialchars($value->last_name),
      htmlspecialchars($value->email),
      l(t('Edit'), "d7_pets_owners/" . $value->owner_id . "/update"),
      l(t('Delete'), "d7_pets_owners/" . $value->owner_id . "/delete"),
    ];
  }
  return theme('table', ['header' => $header, 'rows' => $rows]);
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
