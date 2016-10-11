<?php

/**
 * Implements hook_views_data().
 */
function d7_youtube_views_data() {
  $data['custom']['table']['group'] = t('Youtube video');
  $data['custom']['table']['join'] = [
    '#global' => [],
  ];

  $data['custom']['custom_handler'] = [
    'title' => t('Youtube video'),
    'help' => t('Youtube video field add.'),
    'field' => [
      'handler' => 'd7_youtube_handler',
    ],
  ];

  return $data;
}
