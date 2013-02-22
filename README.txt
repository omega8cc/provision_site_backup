Hosting site Backup Manager
===========================

This module adds a more backup options to Aegir.

- "Backups" tab to the "site" nodes in the Hostmaster environment.
  The tab shows the backups and enables per backup actions (Restore, Delete and Get).

- Specify how long Aegir should retain backups for.

Installation
------------

1. Install as any other Drupal module into your hostmaster site.
2. Enable the feature in the 'experimental' section of 'admin/hosting' page.
3. The file hosting_site_backup_manager.drush.inc should be copied/linked to the drush installation.
An easy way is to create a symlink in ~/.drush/ to e.g. /var/aegir/clients/admin/hostmaster.example.com/modules/hosting_site_backup_manager/.

Configuration
-------------

1. Settings are available at 'admin/hosting/backup_manager' and allow you to e.g. choose
the numbers of backups to keep after specified periods of time.


TODO
----
- Check if there are tasks working with the backups to prevent "collisions"
