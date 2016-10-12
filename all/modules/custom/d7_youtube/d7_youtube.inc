<?php

function glue_url($parsed) {
  if (!is_array($parsed)) {
    return FALSE;
  }

  $uri = isset($parsed['scheme']) ? $parsed['scheme'] . ':' . ((strtolower($parsed['scheme']) == 'mailto') ? '' : '//') : 'https://';
  $uri .= isset($parsed['user']) ? $parsed['user'] . (isset($parsed['pass']) ? ':' . $parsed['pass'] : '') . '@' : '';
  $uri .= isset($parsed['host']) ? (($parsed['host']) == 'youtu.be' ? 'www.youtube.com/embed' : $parsed['host']) : '';
  $uri .= isset($parsed['port']) ? ':' . $parsed['port'] : '';

  if (isset($parsed['path'])) {
    $uri .= (substr($parsed['path'], 0, 1) == '/') ?
      $parsed['path'] : ((!empty($uri) ? '/' : '') . $parsed['path']);
  }

  $uri .= isset($parsed['query']) ? (($parsed['path'] == '/watch') ? '?' . $parsed['query'] : '') : '';
  $uri .= isset($parsed['fragment']) ? '#' . $parsed['fragment'] : '';
  if ($parsed['path'] == '/watch') {
    $uri = str_replace('watch?v=', 'embed/', $uri);
  }

  return $uri;
}