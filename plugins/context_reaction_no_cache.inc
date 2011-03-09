<?php
/**
 * Extend the context reaction engine to have a reaction for per-page cache inclusion or exclusion.
 * @version 6.x-1.1
 */
class context_reaction_no_cache extends context_reaction {

  /**
   * Implementation of options_form().
   * @param object $context
   * @return array $form
   */
  function options_form($context) {
    //Saved values.
    $values = $this->fetch_from_context($context);
    //Radio Options.
    $options = array(t('Cache'), t('Do Not Cache'));
    //Form.
    $form = array(
      '#tree'    => TRUE,
      '#title'   => t('Caching: Core'),
      'no_cache' => array(
        '#title'         => t('Caching Option'),
        '#description'   => t('Choose to disable Drupal\'s core cache when this context is active.'),
        '#type'          => 'radios',
        '#options'       => $options,
        '#default_value' => isset($values['no_cache']) ? $values['no_cache'] : 1,
      ),
    );
    return $form;
  }

  /**
   * Implementation of options_form_submit().
   * Override the form submit.
   * Clear the cache, just like the cache exclude module.
   * @param array $values - the values passed through the form.
   * @return array $values - the values passed through the form.
   */
  function options_form_submit($values) {
    //Set a friendly message, saying the cache has been cleared.
    drupal_set_message('Caches Cleared.');
    //Clear the page cache when new settings are added.
    cache_clear_all(NULL, 'cache_page', '*');
    //Return Form values.
    return $values;
  }

  /**
   * Implementation of execute().
   * @param global $conf - the current configuration for Drupal. This variable always passes through this function
   *  and will only invoke if the context condition is met.
   * @return global $conf
   */
  function execute($conf = NULL) {
    //Set our variables, to check later if we need to actually do anything.
    $old_setting = $new_setting = $conf['cache'];
    //Loop through active contexts.
    foreach (context_active_contexts() as $context) {
      if ($context->reactions[$this->plugin]['no_cache'] == 1) {
        //No Caching off this page. Flush the damn thing too.
        $new_setting = CACHE_DISABLED;
      } else if ($context->reactions[$this->plugin]['no_cache'] == 0) {
        //Cache this page.
        $new_setting = CACHE_NORMAL;
      }
    }
    //Return $conf if we have altered the cache criteria from the original. There is no reason to change something that is the same.
    if ($old_setting != $new_setting) {
      $conf['cache'] = $new_setting;
    }
    //Always return $conf.
    return $conf;
  }
}