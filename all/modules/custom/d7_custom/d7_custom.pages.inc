<?php

/**
 * Callback function for displaying the custom entity items
 */
function d7_custom_callback() {
  $projects = entity_load('d7_custom');
  $list = entity_view('d7_custom', $projects);

  $output = [];

  foreach ($list['d7_custom'] as $project) {
    $output[] = drupal_render($project);
  }

  return implode($output);
}

/**
 * Callback function for displaying the individual custom entity page
 */
function d7_custom_demo_view($id) {

  $projects = entity_load('d7_custom', [$id]);
  $project = $projects[$id];

  drupal_set_title($project->name);
  $output = entity_view('d7_custom', [$project]);

  return $output;

}
