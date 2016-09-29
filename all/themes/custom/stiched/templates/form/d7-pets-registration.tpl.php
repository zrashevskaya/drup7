<div class="section back">
  <div class="subscribe_title"><h1 id="page-title">Pet's owners registry</h1></div>
  <div id ="first" class="short input_field"><?php print render($form['userName']); ?></div>
  <div class="short input_field"><?php print render($form['lastName']); ?></div>
  <div class="long input_field"><?php print render($form['email']); ?></div>
  <div
    class="long input_field"><?php print render($form['confirm_email']); ?></div>
  <div
    class="long subscribe_button"><?php print render($form['submitButton']); ?></div>
  <?php print drupal_render_children($form); ?>
</div>
