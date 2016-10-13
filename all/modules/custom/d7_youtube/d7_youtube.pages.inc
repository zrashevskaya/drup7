<?php

/**
 * Display the result of entity query, which shows nodes with youtube video
 * according to conditions.
 *
 * @return bool|array An array representing the list of nodes with links to
 * youtube videos in the table view.
 */
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
        l($field_items[0]['youtube_title'], $field_items[0]['youtube_url'], ['attributes'=>['target' => '_blank']]),
      ];
    }
  }
  $array = theme('table', ['header' => $header, 'rows' => $rows]);

  return $array;
}
