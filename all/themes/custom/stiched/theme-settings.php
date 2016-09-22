<?php
/**
 * Created by PhpStorm.
 * User: root
 * Date: 22.09.16
 * Time: 13:46
 */

function stiched_form_system_theme_settings_alter(&$form, $form_state){
  $form['theme_settings']['secret_text'] = array(
    '#type' => 'checkbox',
    '#title' => t('Secret field'),
    '#default_value' => theme_get_setting('secret_text'),
    '#description' => t('Show secret text in the footer'),
  );
}
