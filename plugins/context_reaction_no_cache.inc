<?php
/**
 * Expose themes as context reactions.
 */
class context_reaction_no_cache extends context_reaction {

  /**
   * Allow admins to choose the theme to be set.
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
   * Set the active theme.
   */
  function execute() {
    foreach (context_active_contexts() as $context) {
      if ($context->reactions[$this->plugin]['no_cache'] == 1) {
        //Turn Cache on or off in our context.
        global $conf;
        $conf['cache'] = 0;
      }
    }
  }
}