<?php
/**
 * Implements of hook_views_data().
 */
function d7_pets_registration_views_data() {
  $data['d7_pets_owners']['table']['group'] = t('Pets owners table');
  $data['d7_pets_owners']['table']['base'] = [
    'field' => 'owner_id',
    'title' => t('Pets owners example table'),
    'help' => t('Example table contains example content and can be related to nodes.'),
    'weight' => -10,
  ];
  $data['d7_pets_owners']['table']['join'] = [
    'node' => [
      'left_field' => 'owner_id',
      'field' => 'owner_id',
    ],
  ];
  $data['d7_pets_owners']['owner_id']=[
    'title' => t('Owner ID'),
    'help' => t('Some example content that references a node.'),
    'relationship' => [
      'base' => 'node',
      'base field' => 'owner_id',
      'handler' => 'views_handler_relationship',
      'label' => t('Default label for the relationship'),
      'title' => t('Title shown when adding the relationship'),
      'help' => t('More information on this relationship'),
    ],
    'field' => [
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ],
    'filter' => [
      'handler' => 'views_handler_filter_numeric',
    ],
    'sort' => [
      'handler' => 'views_handler_sort',
    ],
  ];
  $data['d7_pets_owners']['name']=[
    'title' => t('Name'),
    'help' => t('Name of pets owner.'),
    'field' => [
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ],
    'sort' => [
      'handler' => 'views_handler_sort',
    ],
    'filter' => [
      'handler' => 'views_handler_filter_string',
    ],
    'argument' => [
      'handler' => 'views_handler_argument_string',
    ],
  ];
  $data['d7_pets_owners']['last_name']=[
    'title' => t('Last Name'),
    'help' => t('Last Name of pets owner.'),
    'field' => [
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ],
    'sort' => [
      'handler' => 'views_handler_sort',
    ],
    'filter' => [
      'handler' => 'views_handler_filter_string',
    ],
    'argument' => [
      'handler' => 'views_handler_argument_string',
    ],
  ];

  $data['d7_pets_owners']['owner_birthday']=[
    'title' => t('Owner birthday'),
    'help' => t('Owner birthday.'),
    'field' => [
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ],
    'sort' => [
      'handler' => 'views_handler',
    ],
    'filter' => [
      'handler' => 'views_handler_filter',
    ],
    'argument' => [
      'handler' => 'views_handler_argument',
    ],
  ];

  $data['d7_pets_owners']['pet_type']=[
    'title' => t('Pet type'),
    'help' => t('Pet type.'),
    'field' => [
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ],
    'sort' => [
      'handler' => 'views_handler_sort',
    ],
    'filter' => [
      'handler' => 'views_handler_filter_string',
    ],
    'argument' => [
      'handler' => 'views_handler_argument_string',
    ],
    'relationship' => [
      'base' => 'taxonomy_term_data',
      'base field' => 'tid',
      'handler' => 'views_handler_relationship',
      'label' => t('pets types'),
      'relationship table' => 'd7_pets_owners',
      'relationship field' => 'pet_type',
    ],
  ];

  $data['d7_pets_owners']['email']=[
    'title' => t('Email'),
    'help' => t('Email of pets owner.'),
    'field' => [
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ],
    'sort' => [
      'handler' => 'views_handler_sort',
    ],
    'filter' => [
      'handler' => 'views_handler_filter_string',
    ],
    'argument' => [
      'handler' => 'views_handler_argument_string',
    ],
  ];
return $data;
}
