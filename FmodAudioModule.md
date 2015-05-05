# Introduction #

Allows you to use the FmodModule as a BlitzMax Audio driver.

By importing BaH.FMODAudio, you can specify `FMOD` as an audio driver, and use the standard audio commands to play sounds.


## Example ##

```
Import BaH.FMODAudio

SetAudioDriver("FMOD")

Local sound:TSound = LoadSound("track01.ogg", SOUND_LOOP)

PlaySound(sound)

```

# Requirements #

  * The FmodModule
  * **Note** : Also requires the latest BRL.Audio module, available via SVN from blitzmax.com.


# Building #

See HowToInstallModules to help you get started.