<?php 

/**
 * @file
 * Provision/Drush hooks for the provision-export_backup command.
 *
 * These are the hooks that will be executed by the drush_invoke function
 * when asking for an export backup command
 */

/**
 * Implementation of hook_drush_command().
 */
function hosting_site_backup_manager_drush_command() {
  $items['provision-export_backup'] = array(
    'description' => 'Make a site backup available for download.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'backup' => dt('The complete filepath of the backup to export.'),
    ),
  );
  
  return $items;
}

/**
* Map values of site node into command line arguments
*/
function drush_hosting_site_backup_manager_pre_hosting_task($task) {
  $task =& drush_get_context('HOSTING_TASK');

  // Pass the dialog entries to the drush provision script
  if ($task->task_type == 'export_backup') {
    $task->args[1] = $task->task_args['backup'];
  }
}

/**
* Implements the provision-export_backup command
*/
function drush_hosting_site_backup_manager_provision_export_backup($backup) {
  drush_log(dt('Start export backup command'), 'ok');
  
  // Path for exported backups
  $backupdir = d()->platform->server->aegir_root . '/backup-exports';
  if(!is_dir($backupdir)) {
    provision_file()->create_dir($backupdir, dt('General backup export directory'), 0751);    
  }

  // Path for client exported backups
  $clientbackupdir = $backupdir . '/' . d()->client_name;
  if(!is_dir($clientbackupdir)) {
    provision_file()->create_dir($clientbackupdir, dt('Client backup export directory '), 0751);
  }
  
  if (drush_shell_cd_and_exec($clientbackupdir, 'ln %s .', $backup)) {
    drush_log(dt('Backup exported', array()), 'ok');
  }
  else {
    // The command failed
    return drush_set_error('DRUSH_PROVISION_EXPORT_BACKUP_FAILED', dt("Drush was unable to export the backup.\nThe specific errors are below:\n!errors", array('!path' => $clientbackupdir, '!errors' => implode("\n", drush_shell_exec_output())))); 
  }
  
}

