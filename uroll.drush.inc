<?php 
/**
 * @file
 *   Update Rollback Drush Drupal Testing
 *   Author: Dan Shumaker
 *   Date: 9/17/2013
 *
 * Installation: Put this file in your ~/.drush   directory
 *
 * Tested in drush 5 and 6.
 */

/*
 * Implementation of hook_drush_command()
 */
function uroll_drush_command()  {
  $items = array();

  $items['uroll'] = array(
    'description' => "Rollback update function version recorded by drupal system.  ",
    'options' => array(
      'module' => 'module to change the version on',
      'version' => 'Version to set to roll back to',
    ),
    'examples' => array(
      'drush uroll --module=becker_general --version=12' => 'Rollback the system table so that drupal think it has not run the update for becker_general version 12',
    ),
  'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL, // No bootstrap at all.
  );

  return $items;
 
} 

/*
 * Implementation of hook_drush_help()
 *
 */
function uroll_drush_help($section) {
  switch ($section) {
    case 'drush:uroll':
      return dt("Update Rollback");
    // The 'title' meta item is used to name a group of
    // commands in `drush help`.  If a title is not defined,
    // the default is "All commands in ___", with the
    // specific name of the commandfile (e.g. sandwich).
    // Command files with less than four commands will 
    // be placed in the "Other commands" section, _unless_
    // they define a title.  It is therefore preferable
    // to not define a title unless the file defines a lot
    // of commands.
    case 'meta:uroll:title':
      return dt("Update Rollback");
    // The 'summary' meta item is displayed in `drush help --filter`,
    // and is used to give a general idea what the commands in this
    // command file do, and what they have in common.
    case 'meta:uroll:summary':
      return dt("Rolls back the version of update script that has been run.");
  }

}
/**
 * Implementation of drush_hook_COMMAND_validate().
 *
 */
function drush_uroll_validate() {
/*
  $name = posix_getpwuid(posix_geteuid());
  if ($name['name'] !== 'root') {
    return drush_set_error('MAKE_IT_YOUSELF', dt('What? Make your own sandwich.'));
  }
 */
}

/**
 * Implementation of drush_hook()
 */
function drush_uroll() {
    $module = drush_get_option('module', 1);
    $version = drush_get_option('version', 1);
    $context = drush_get_context();
    //dlm($context);
    //$url = $context['site-aliases']['@self']['uri'];
    if ( !strstr($context['DRUSH_URI'], 'http') ) {
      $url  = $protocol . "://" . $context['DRUSH_URI'] . '/';
    } else {
      $url = $context['DRUSH_URI'];
    }
    $before = db_select('system', 'sys')
      ->condition('name', trim($module))
      ->fields('sys',array('name', 'schema_version'))
      ->execute()
      ->fetchAssoc();
     print_r($before);
    $res = db_update('system')
      ->fields(array('schema_version' => $version))
      ->condition('name', $module)
      ->execute();
    $after = db_select('system', 'sys')
      ->condition('name', $module)
      ->fields('sys',array('name', 'schema_version'))
      ->execute()
      ->fetchAssoc();
     print_r($after);
}

