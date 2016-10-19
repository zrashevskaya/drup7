<?php

/**
 * Extending the EntityAPIController for the Project entity.
 */
class d7CustomEntityController extends EntityAPIController {

  /**
   * Builds a structured array representing the entity's content.
   *
   * The content built for the entity will vary depending on the $view_mode
   * parameter.
   *
   * @param $entity
   *   An entity object.
   * @param $view_mode
   *   View mode, e.g. 'full', 'teaser'...
   * @param $langcode
   *   (optional) A language code to use for rendering. Defaults to the global
   *   content language of the current request.
   * @param $content
   * Optionally.
   * @return array The renderable array.
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = []) {

    $build = parent::buildContent($entity, $view_mode, $langcode, $content);

    $build['description'] = [
      '#type' => 'markup',
      '#markup' => check_plain($entity->description),
      '#prefix' => '<div class="project-description">',
      '#suffix' => '</div>',
    ];
    $build['created'] = [
      '#type' => 'markup',
      '#markup' => date('d F, Y', $entity->created),
      '#prefix' => '<p>Created: ',
      '#suffix' => '</p>',
    ];

    return $build;

  }
}
