<?php

/**
 * D7 Custom entity class extending the Entity class
 */
class d7CustomEntity extends Entity {

  /**
   * Change the default URI from default/id to d7_custom/id
   */
  protected function defaultUri() {
    return array('path' => 'd7_custom/' . $this->identifier());
  }

}
