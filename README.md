drush-uroll
===========

###Update Rollback

When you are writting complicated drupal module update functions it's often necessary to run the update function over and over.

But when you run "drush updb" after the required update function has already been run, your drush updb will simply say there is 
nothing to update.  But, but, I want to run the update again you say!
And since your a well accomplished drupal developer you could go into the mysql system table and modify the version of the 
module manually and then you'll be running your test update function again just fine. 

BUT why do that when a simple drush module can do it for you.

## Example:
Rollback the system table so that drupal think it has not run the update for becker_general version 12 

```
 drush uroll --module=becker_general --version=12       
```
## Options:
 --module                                  module to change the update function version on 

 --version                                 Version to set to roll back to


##Output:

I'm leaving the debugging output in there for now.  It just prints the data structure of the version that the update function is currently at, and then the data structure of the 
system table element after the uroll has run.  This just gives you a warm fuzzy feeling that it actually did something.

The output should look something like this:

```
drush uroll --module=vcd_admin --version=2  
Array   (    [name] => vcd_admin   [schema_version] => 3   )    
Array    (
    [name] => vcd_admin
    [schema_version] => 2
)
```

##Installation:

Just put the uroll.drush.inc file in your ~/.drush directory.


##Benefits:

By writing more and more update functions you'll learn the guts of drupal quickly and eventually not have to repeat a bunch of error pron mouse clicks on a production server. 
