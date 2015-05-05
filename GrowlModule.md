# Introduction #

[Growl](http://growl.info) is a system for posting notifications to users on Mac OS X.

This module adds BlitzMax support for Growl.

See the included documentation for details on usage and packaging of the Growl Framework with your applications.

## Example ##

This small example creates a "Hello World" notification.
```
SuperStrict

Framework BaH.Growl

Local delegate:TGrowlDelegate = New TGrowlDelegate.Create()

delegate.SetApplicationName("HelloWorld")

delegate.SetAllNotifications(["Hello World"]) ' Supported notifications list '

If delegate.Install() Then ' install the delegate, so that we can send notifications '

	Local notification:TGrowlNotification = New TGrowlNotification.Create("Hello World", ..
		"Hello World!", "A small Hello World example from BlitzMax!")
		
	notification.Post() ' post the notification '

End If
```


# Building #

See HowToInstallModules to help you get started.