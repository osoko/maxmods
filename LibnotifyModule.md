# Introduction #

[Libnotify](http://library.gnome.org/devel/libnotify/) is a system for posting notifications to users on Linux.

## Example ##

This small example creates a "Hello World" notification.
```
SuperStrict

Framework BaH.libnotify

If TNotify.Initialize("Hello World App") Then

	Local notification:TNotification = New TNotification.Create("Hello World!!")

	notification.Show()

End If

```


# Building #

See HowToInstallModules to help you get started.