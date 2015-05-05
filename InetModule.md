# Introduction #

If you need information about network interfaces (eg. ethernet, wifi) attached to your computer, this module can provide it for you via a very simple API.

It retrieves details such as IP Address, Netmask and the hardware MAC Address.

## Example ##

Listing all Interfaces :
```
SuperStrict

Framework BaH.INet
Import BRL.Socket ' for DottedIP() '
Import BRL.StandardIO ' for Print '

Local interfaces:TInet[] = GetInetInterfaces()

For Local inet:TInet = EachIn interfaces
	Print ""
	Print "Interface   : " + inet.name
	Print "IP Address  : " + DottedIP(inet.address)
Next
```


# Building #

See HowToInstallModules to help you get started.