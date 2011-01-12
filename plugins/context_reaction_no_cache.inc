<?php
// $Id: context_reaction_no_cache.inc,v 1.1.2.2 2010/10/25 18:47:40 brynbellomy Exp $

/**
 * Expose themes as context reactions.
 */
class context_reaction_no_cache extends context_reaction {

  /**
   * Allow admins to choose the theme to be set.
   */
  function options_form($context) {
    //Radio Options.
    $options = array(t('Cache'), t('Do Not Cache'));
    //Form.
    $form = array(
      '#tree'    => TRUE,
      '#title'   => t('Caching: Core'),
      'no_cache' => array(
        '#title'         => t('No Cache'),
        '#description'   => t('Choose to disable Drupal\'s core cache when this context is active.'),
        '#type'          => 'radio',
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
      if (!empty($context->reactions[$this->plugin]['no_cache'])) {
        //Turn Cache on or off in our context.
        $GLOBALS['conf']['cache'] = FALSE;
      }
    }
  }
}