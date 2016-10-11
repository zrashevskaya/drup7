<?php

function d7_youtube_form_alter(&$form, &$form_state, $form_id) {

  if($form_id=="field_ui_field_edit_form"){
    $form['field']['cardinality']['#options'] = [FIELD_CARDINALITY_UNLIMITED => t('Unlimited')] + drupal_map_assoc(range(1, 30));
  }
}

function d7_youtube_videos_list() {
  $header = [
    t('Content Title'),
    t('Content Type'),
    t('Video Title'),
  ];
  $rows = [];
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'page')
        ->propertyCondition('status', NODE_PUBLISHED)
        ->fieldCondition('field_video', 'youtube_control', 1);

  $result = $query->execute();
  if (isset($result['node'])) {
    $news_items_nids = array_keys($result['node']);
    foreach($news_items_nids as $value) {
      $node_items = node_load($value);
      $field_items = field_get_items('node', $node_items, 'field_video');
      $rows[] = [
        $node_items->title,
        $node_items->type,
        l($field_items[0]['youtube_title'], $field_items[0]['youtube_url'], ['attributes'=>['target' => 'blanc']]),
      ];
    }
  }
  $array = theme('table', ['header' => $header, 'rows' => $rows]);
  return $array;
}
