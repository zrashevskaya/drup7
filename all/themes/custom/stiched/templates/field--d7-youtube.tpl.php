<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$label_hidden): ?>
    <div
      class="field-label"<?php print $title_attributes; ?>><?php print $label ?>
      :&nbsp;</div>
  <?php endif; ?>
  <div class="field-items"<?php print $content_attributes; ?>>
    <?php foreach ($items as $delta => $item): ?>
    <div
      class="field-item <?php print $delta % 2 ? 'odd' : 'even'; ?>"<?php print $item_attributes[$delta]; ?>>
      <?php if (!$item['frame']): ?>
         <a
          href="<?php print render($item['url']); ?>"
          target="<?php print render($item['attributes']['target']); ?>"><?php print render($item['value']); ?></a>
      <?php else: ?>
        <div>
          <iframe
            width="<?php print render($item['attributes']['width']); ?>"
            height="<?php print render($item['attributes']['height']); ?>"
            src="<?php print render($item['iframe_url']); ?>"
            frameborder="0" allowfullscreen></iframe>
        </div>
        </div>
      <?php endif; endforeach; ?>
  </div>
</div>

